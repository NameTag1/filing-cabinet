#include "MenuState.h"

#include "ResourceHolder.h"
#include "Image.h"
#include "Button.h"
#include "DropDown.h"
#include "Sidebar.h"

#include "Utility.h"
#include <memory>
#include <utility>
#include "FloatBox.h"

#include "Camera_Wrapper.h"
#include "ExpandableSidebar.h"

MenuState::MenuState()
	: mContainer(RelativeRect(sf::FloatRect({ 0.f, 0.f },{ 1.f, 1.f })))
{
	context->mTextureHolder->loadResource("Resources/Button.png", "Button");
	context->mTextureHolder->loadResource("Resources/Button_Hover.png", "Button_Hover");
	context->mTextureHolder->loadResource("Resources/Upper_Bar.png", "Menu Bar");

	context->mTextureHolder->loadResource("Resources/Sidebar_Closed.bmp", "Sidebar_Closed");
	context->mTextureHolder->loadResource("Resources/Sidebar_Open.bmp", "Sidebar_Open");

	//--------------- Top Bar ---------------

	std::unique_ptr<Container> TopBar = std::make_unique<Container>(RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 50.f }), RelativeWH::StaticH, Anchor::TL));

	//Background
	TopBar->pushObject(std::make_unique<Image>(
		context->mTextureHolder->getResource("Menu Bar"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }), RelativeWH::Normal, Anchor::TL)
	));

	//File Dropdown
	std::unique_ptr<DropDown> fileTabDropDown = std::make_unique<DropDown>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({ 0.5f, 0.f }, { 0.2f, 1.f }), RelativeWH::Normal, Anchor::TL)
	);

	std::unique_ptr<Button> popButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }), RelativeWH::Normal, Anchor::TL)
	);
	popButton->SetCallback([this]() {
		this->pop();
		});

	std::unique_ptr<Button> fileButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }), RelativeWH::Normal, Anchor::TL)
	);
	fileButton->SetCallback([this]() {
		OpenFileDialog();
	});

	std::unique_ptr<Button> takePicButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }), RelativeWH::Normal, Anchor::TL)
	);
	takePicButton->SetCallback([this]() {
		Camera_Wrapper::takePicture();
		});

	std::unique_ptr<FloatBox> c = std::make_unique<FloatBox>(
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 0.05f, 1.f }), RelativeWH::Normal, Anchor::TL)
	);
	c->pushObject(std::move(popButton));
	c->pushObject(std::move(fileButton));
	c->pushObject(std::move(takePicButton));

	fileTabDropDown->setChild(std::move(c));

	TopBar->pushObject(std::move(fileTabDropDown));

	//Quit Button
	std::unique_ptr<Button> exitButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 1.f, 0.f }, { 0.2f, 1.f }), RelativeWH::Normal, Anchor::TR)
	);
	exitButton->SetCallback([this]() {
		this->clear();
	});
	TopBar->pushObject(std::move(exitButton));

	mContainer.pushObject(std::move(TopBar));

	//--------------- Top Bar End ---------------

	std::unique_ptr<Button> newContainerButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.4f }, { 0.05f, 0.2f }), RelativeWH::Normal, Anchor::TL)
	);
	newContainerButton->SetCallback([this]() {
		this->push(NewDocState);
		});

	mContainer.pushObject(std::move(newContainerButton));

	/*std::unique_ptr<ExpandableSidebar> sidebar = std::make_unique<ExpandableSidebar>(
		context->mTextureHolder->getResource("Sidebar_Closed"),
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.05f, 0.95f }), RelativeWH::Normal, Anchor::TR),
		ExpandableSidebar::Edge::Left,
		50.f
	);
	mContainer.pushObject(std::move(sidebar));*/

	//Sidebar Test
	/*std::unique_ptr<Sidebar> sidebar = std::make_unique<Sidebar>(
		context->mTextureHolder->getResource("Sidebar_Closed"),
		context->mTextureHolder->getResource("Sidebar_Open"),
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.05f, 0.95f }), RelativeWH::Normal, Anchor::TR),
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.2f, 0.95f }), RelativeWH::Normal, Anchor::TR)
	);
	sidebar->setChild(std::make_unique<Container>(
		RelativeRect(sf::FloatRect({ 1.f, 0.05f }, { 0.15f, 0.95f }), RelativeWH::Normal, Anchor::TR)
	));
	mContainer.pushObject(std::move(sidebar));*/
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
