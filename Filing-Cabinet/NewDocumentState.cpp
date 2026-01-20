#include "NewDocumentState.h"
#include "Image.h"
#include "TextBox.h"
#include "Constants.h"
#include "Button.h"
#include "OCR_Wrapper.h"
#include "Utility.h"

NewDocumentState::NewDocumentState()
	: mContainer(RelativeRect(sf::FloatRect({ 0.5f, 0.5f }, { 0.6f, 0.9f }), Normal, Center))
{
	context->mTextureHolder->loadResource("Resources/Upper_Bar.png", "Menu Bar");

	//Background
	mContainer.pushObject(std::make_unique<Image>(
		context->mTextureHolder->getResource("Menu Bar"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }), RelativeWH::Normal, Anchor::TL)
	));

	std::unique_ptr<TextBox> title = std::make_unique<TextBox>(
		context->mFontHolder,
		RelativeRect(sf::FloatRect({ 0.05f, 0.01f }, { 0.9f, 0.98f }), RelativeWH::Normal, Anchor::TL),
		Constants::TitleSize
	);
	title->setString("New Document State");
	mContainer.pushObject(std::move(title));

	std::unique_ptr<TextBox> content = std::make_unique<TextBox>(
		context->mFontHolder,
		RelativeRect(sf::FloatRect({ 0.05f, 0.04f }, { 0.9f, 0.98f }), RelativeWH::Normal, Anchor::TL),
		Constants::NormaTextlSize
	);
	content->setString("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales sagittis magna. Sed consequat, leo eget bibendum sodales, augue velit cursus nunc, quis gravida magna mi a libero. Fusce vulputate eleifend sapien. Vestibulum purus quam, scelerisque ut, mollis sed, nonummy id, metus. Nullam accumsan lorem in dui. Cras ultricies mi eu turpis hendrerit fringilla. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; In ac dui quis mi consectetuer lacinia. Nam pretium turpis et arcu. Duis arcu tortor, suscipit eget, imperdiet nec, imperdiet iaculis, ipsum. Sed aliquam ultrices mauris. Integer ante arcu, accumsan a, consectetuer eget, posuere ut, mauris. Praesent adipiscing. Phasellus ullamcorper ipsum rutrum nunc. Nunc nonummy metus. Vestibulum volutpat pretium libero. Cras id dui. Aenean ut eros et nisl sagittis vestibulum. Nullam nulla eros, ultricies sit amet, nonummy id, imperdiet feugiat, pede. Sed lectus. Donec mollis hendrerit risus. Phasellus nec sem in justo pellentesque facilisis. Etiam imperdiet imperdiet orci. Nunc nec neque. Phasellus leo dolor, tempus non, auctor et, hendrerit quis, nisi. Curabitur ligula sapien, tincidunt non, euismod vitae, posuere imperdiet, leo. Maecenas malesuada. Praesent congue erat at massa. Sed cursus turpis vitae tortor. Donec posuere vulputate arcu. Phasellus accumsan cursus velit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed aliquam, nisi quis porttitor congue, elit erat euismod orci, ac");
	mContainer.pushObject(std::move(content));

	std::unique_ptr<Button> popButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 1.f, 0.f }, { 0.05f, 0.05f }), RelativeWH::WHBased, Anchor::TR)
	);
	popButton->SetCallback([this]() {
		this->pop();
		});
	mContainer.pushObject(std::move(popButton));

	std::unique_ptr<Button> fromExistingDocument = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.2f }, { 0.08f, 0.05f }), RelativeWH::WHBased, Anchor::TL)
	);
	fromExistingDocument->SetCallback([this]() {
		OCR_Wrapper::getInstance()->addToScanQueue(wstring_to_string(OpenFileDialog()));
		this->pop();
		});
	mContainer.pushObject(std::move(fromExistingDocument));

	std::unique_ptr<Button> fromNewDocument = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		context->mTextureHolder->getResource("Button_Hover"),
		RelativeRect(sf::FloatRect({ 0.f, 0.2f }, { 0.08f, 0.05f }), RelativeWH::WHBased, Anchor::TL)
	);
	fromNewDocument->SetCallback([this]() {
		OCR_Wrapper::getInstance()->addToScanQueue(wstring_to_string(OpenFileDialog()));
		this->pop();
		});
	mContainer.pushObject(std::move(fromNewDocument));

}

bool NewDocumentState::update() {
	sf::Vector2f viewSize = context->mWindow->getView().getSize();
	mContainer.update(sf::FloatRect({ 0.f, 0.f }, { viewSize.x, viewSize.y }));

	return true;
}

bool NewDocumentState::handleEvent(const std::optional<sf::Event> event) {
	// pass the window pointer so children can map pixel -> world coords
	mContainer.handleEvent(event, context->mWindow);
	return false;
}

bool NewDocumentState::draw() {
	context->mWindow->draw(mContainer);
	return true;
}