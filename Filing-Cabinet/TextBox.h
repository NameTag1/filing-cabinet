#pragma once

#include "GUI_Object.h"
#include "ResourceHolder.h"
#include <SFML/Graphics/Text.hpp>
#include <string>

class TextBox : public GUI_Object
{
public:
	// fonts: pointer to project's FontHolder (TextBox will attempt to use key "Main")
	// rect: RelativeRect describing TextBox relative to its parent
	// charSize: initial character size
	TextBox(FontHolder* fonts, RelativeRect rect, unsigned int charSize = 14u);

	// Read-only content
	void setString(const std::string& str);
	const std::string& getString() const;

	// Appearance
	void setCharacterSize(unsigned int size);
	void setFillColor(const sf::Color& color);
	void setFont(sf::Font* font); // caller may override default font

	// GUI_Object overrides
	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// word-wrap algorithm that preserves whole words; a word that doesn't fit on the current line
	// is pushed to the next line (no hyphenation / no splitting).
	void wrapText();

	std::string mRawString;
	sf::Text mText;

	// Prevent excessive re-wrapping when window size changes:
	// only re-wrap when width meaningfully changes or when content/font/size changes.
	float mLastWrapWidth;
	bool mNeedsWrap;
};

