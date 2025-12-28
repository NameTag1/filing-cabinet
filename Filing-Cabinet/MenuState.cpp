#include "MenuState.h"

#include "ResourceHolder.h"
#include "Image.h"
#include "Button.h"
#include "DropDown.h"
#include "Sidebar.h"

#include "Utility.h"

MenuState::MenuState()
	: mContainer(RelativeRect(sf::FloatRect({ 0.f, 0.f },{ 1.f, 1.f })))
{
	context->mTextureHolder->loadResource("Resources/Button.png", "Button");
	context->mTextureHolder->loadResource("Resources/Button_Hover.png", "Button_Hover");
	context->mTextureHolder->loadResource("Resources/Upper_Bar.png", "Menu Bar");

	context->mTextureHolder->loadResource("Resources/Sidebar_Closed.bmp", "Sidebar_Closed");
	context->mTextureHolder->loadResource("Resources/Sidebar_Open.bmp", "Sidebar_Open");
	
	//Top Menu Bar
	mContainer.pushObject(std::make_unique<Image>(
		context->mTextureHolder->getResource("Menu Bar"),
		RelativeRect(sf::FloatRect({0.f, 0.f}, {1.f, 0.05f}), RelativeWH::Normal, Anchor::TL)
	));

	//Push State Button
	std::unique_ptr<Button> fileButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 0.2f, 0.05f }), RelativeWH::Normal, Anchor::TL)
	);
	fileButton->SetCallback([this]() {
		this->push(StateType::Menu);
		OpenFileDialog();
		});
	mContainer.pushObject(std::move(fileButton));

	//File Dropdown
	std::unique_ptr<DropDown> fileTabDropDown = std::make_unique<DropDown>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({ 0.5f, 0.025f }, { 0.2f, 0.05f }), RelativeWH::Normal, Anchor::Center)
	);
	std::unique_ptr<Button> popButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.5f, 0.075f }, { 0.2f, 0.05f }), RelativeWH::Normal, Anchor::Center)
	);
	popButton->SetCallback([this]() {
		this->pop();
		});
	std::unique_ptr<Container> c = std::make_unique<Container>(
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }), RelativeWH::Normal, Anchor::TL)
	);
	c->pushObject(std::move(popButton));
	fileTabDropDown->setChild(std::move(c));

	mContainer.pushObject(std::move(fileTabDropDown));

	//Quit Button
	std::unique_ptr<Button> exitButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 1.f, 0.0f }, { 0.2f, 0.05f }), RelativeWH::Normal, Anchor::TR)
	);
	exitButton->SetCallback([this]() {
		this->clear();
	});
	mContainer.pushObject(std::move(exitButton));

	//Sidebar Test
	std::unique_ptr<Sidebar> sidebar = std::make_unique<Sidebar>(
		context->mTextureHolder->getResource("Sidebar_Closed"),
		context->mTextureHolder->getResource("Sidebar_Open"),
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.05f, 0.95f }), RelativeWH::Normal, Anchor::TR),
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.2f, 0.95f }), RelativeWH::Normal, Anchor::TR)
	);
	sidebar->setChild(std::make_unique<Container>(
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.15f, 0.95f }), RelativeWH::Normal, Anchor::TR)
	));
	mContainer.pushObject(std::move(sidebar));
}

bool MenuState::update() {
	sf::Vector2f viewSize = context->mWindow->getView().getSize();
	mContainer.update(sf::FloatRect({ 0.f, 0.f }, { viewSize.x, viewSize.y }));

	return false;
}

bool MenuState::handleEvent(const std::optional<sf::Event> event) {
	// pass the window pointer so children can map pixel -> world coords
	mContainer.handleEvent(event, context->mWindow);
	return false;
}

bool MenuState::draw() {
	context->mWindow->draw(mContainer);
	return false;
}
