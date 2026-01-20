#include "TextBox.h"
#include "Logger.h"
#include <sstream>
#include <vector>
#include <cmath>

TextBox::TextBox(FontHolder* fonts, RelativeRect rect, unsigned int charSize)
	: GUI_Object(rect)
	, mRawString("")
	, mText(*fonts->getResource("Main"), "", charSize)
	, mLastWrapWidth(-1.f)
	, mNeedsWrap(true)
{
	
	/*if (fonts) {
		sf::Font* f = fonts->getResource("Main");
		if (f) mText.setFont(*f);
	}*/

	mText.setFillColor(sf::Color::Black);
}

void TextBox::setString(const std::string& str)
{
	mRawString = str;
	mNeedsWrap = true;
}

const std::string& TextBox::getString() const
{
	return mRawString;
}

void TextBox::setCharacterSize(unsigned int size)
{
	mText.setCharacterSize(size);
	mNeedsWrap = true;
}

void TextBox::setFillColor(const sf::Color& color)
{
	mText.setFillColor(color);
}

void TextBox::setFont(sf::Font* font)
{
	if (font) {
		mText.setFont(*font);
		mNeedsWrap = true;
	}
}

bool TextBox::update(sf::FloatRect parrentRect)
{
	// Update relative rectangle and place this object's transform to match its computed position.
	mRect.update(parrentRect);
	setPosition(mRect.getRect().position);

	// Only re-wrap when necessary: either flagged (content/font/size changed) or width changed.
	const float currentWidth = mRect.getRect().size.x;
	const float EPS = 0.5f; // tolerance in pixels to avoid re-wrapping for tiny changes
	if (mNeedsWrap || std::fabs(currentWidth - mLastWrapWidth) > EPS) {
		wrapText();
		mLastWrapWidth = currentWidth;
		mNeedsWrap = false;
	}

	return false;
}

bool TextBox::handleEvent(const std::optional<sf::Event> /*event*/, sf::RenderWindow* /*window*/)
{
	// Read-only textbox; consumes no events.
	return false;
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mText, states);
}

void TextBox::wrapText()
{
	// Require font to measure; if no font, just set raw string and return.
	/*if (mText.getFont()) {
		mText.setString(mRawString);
		return;
	}*/

	const sf::FloatRect abs = mRect.getRect();
	const float maxWidth = abs.size.x;

	// If width is zero or negative, just set raw string and return.
	if (maxWidth <= 0.f) {
		mText.setString(mRawString);
		return;
	}

	std::vector<std::string> finalLines;
	std::istringstream paragraphs(mRawString);
	std::string paragraph;

	// Preserve explicit newlines by splitting into paragraphs.
	while (std::getline(paragraphs, paragraph, '\n')) {
		std::istringstream words(paragraph);
		std::string word;
		std::string line;

		while (words >> word) {
			std::string candidate = line.empty() ? word : (line + " " + word);

			// Measure candidate width using text local bounds
			mText.setString(candidate);
			const float candidateWidth = mText.getLocalBounds().size.x;

			if (candidateWidth <= maxWidth) {
				// fits on current line
				line = candidate;
			}
			else {
				// candidate doesn't fit on current line
				if (!line.empty()) {
					// push current line, start new line with word
					finalLines.push_back(line);
					line = word;
				}
				else {
					// current line empty, the single word itself doesn't fit in the current width.
					// Per requirement: move the word to its own line (we place it as is).
					// This will overflow horizontally if the word is wider than the box,
					// but we do not break words.
					line = word;
				}
			}
		}

		if (!line.empty()) {
			finalLines.push_back(line);
		}

		// Add an empty line to preserve the explicit newline between paragraphs (if more paragraphs follow)
		if (paragraphs.peek() != EOF) {
			finalLines.push_back(std::string());
		}
	}

	// Reconstruct final string
	std::string out;
	for (size_t i = 0; i < finalLines.size(); ++i) {
		out += finalLines[i];
		if (i + 1 < finalLines.size()) out += '\n';
	}

	mText.setString(out);

	Logger::Instance->LogData(Logger::Action, "TextBox wrapped text to fit width " + std::to_string(maxWidth));
}
