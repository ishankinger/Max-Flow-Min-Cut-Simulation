#include "flowNetwork.hpp"

TextBox::TextBox() {
	isCentre = true;
}

TextBox::TextBox(std::string textVal, unsigned charSize, float outline_thickness, sf::Vector2f boxSize, sf::Vector2f boxPos, sf::Color textColor, sf::Color bgColor, sf::Color outlineColor, sf::Font &font, bool centre, bool textBold) {
	box.setSize(boxSize);
	box.setFillColor(bgColor);
	box.setOutlineThickness(outline_thickness);
	box.setOutlineColor(outlineColor);
	box.setPosition(boxPos);
	bounding_box_size = boxSize;
	bounding_box_pos = boxPos;
	isCentre = centre;

	text.setFont(font);
	text.setString(textVal);
	text.setFillColor(textColor);
	text.setCharacterSize(charSize);
	if (textBold) text.setStyle(sf::Text::Bold);
	setTextPosition(sf::Vector2f(0.0f, 0.0f));
}

TextBox::TextBox(std::string textVal, unsigned charSize, float outline_thickness, sf::Vector2f boxSize, sf::Vector2f boxPos, sf::Vector2f boundSize, sf::Vector2f boundPos, sf::Color textColor, sf::Color bgColor, sf::Color outlineColor, sf::Font& font, bool centre, bool textBold) {
	box.setSize(boxSize);
	box.setFillColor(bgColor);
	box.setOutlineThickness(outline_thickness);
	box.setOutlineColor(outlineColor);
	box.setPosition(boxPos);
	bounding_box_size = boundSize;
	bounding_box_pos = boundPos;
	isCentre = centre;

	text.setFont(font);
	text.setString(textVal);
	text.setFillColor(textColor);
	text.setCharacterSize(charSize);
	if (textBold) text.setStyle(sf::Text::Bold);
	setTextPosition(sf::Vector2f(0.0f, 0.0f));
}

void TextBox::setText(std::string textVal) {
	text.setString(textVal);
	setTextPosition(sf::Vector2f(0.0f, 0.0f));
}

void TextBox::setTextColor(sf::Color textColor) {
	text.setFillColor(textColor);
}

void TextBox::setTextSize(int charSize) {
	text.setCharacterSize(charSize);
}

void TextBox::setBoxSize(sf::Vector2f size) {
	box.setSize(size);
}

void TextBox::setBackgroundColor(sf::Color bgColor) {
	box.setFillColor(bgColor);
}

void TextBox::setOutlineColor(sf::Color color) {
	box.setOutlineColor(color);
}

void TextBox::setPosition(sf::Vector2f pos) {
	box.setPosition(pos);
	setTextPosition(sf::Vector2f(0.0f, 0.0f));
}

float TextBox::get_center_coord(float div_x, float div_size, float box_size) {
	float box_x = (div_x + (div_size / 2.0f)) - (box_size / 2.0f);
	return box_x;
}

void TextBox::setTextPosition(sf::Vector2f pos) {
	float xPos = isCentre ? (get_center_coord(box.getPosition().x, box.getLocalBounds().width - 2 * box.getOutlineThickness(), text.getLocalBounds().width + 2 * text.getLocalBounds().left)) : (box.getPosition().x + 10.0f);
	float yPos = get_center_coord(pos.y + box.getPosition().y, box.getLocalBounds().height - 2 * box.getOutlineThickness(), text.getLocalBounds().height + 2 * text.getLocalBounds().top);

	text.setPosition(xPos, yPos);
}

void TextBox::drawTo(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
}

std::string TextBox::getText() {
	return text.getString();
}