#include "flowNetwork.hpp"

Node::Node() {
	value = -1;
	toShow = 0;
}

Node::Node(char value, float radius, sf::Color color, sf::Vector2f position, sf::Font& font) {
	this->value = value;
	this->position = position;
	toShow = 1;

	shape.setRadius(radius);
	shape.setFillColor(color);
	shape.setPosition(position);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPointCount(5000);

	sf::Vector2f center = shape.getPosition() + sf::Vector2f(shape.getRadius() / 1.5f, shape.getRadius() / 2.5f);

	text.setFont(font);
	std::string val; val.push_back(value);
	text.setString(val);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setPosition(center);
}

void Node::setColor(sf::Color color) {
	shape.setFillColor(color);
}

void Node::setRadius(float radius) {
	shape.setRadius(radius);
}

sf::Vector2f Node::getPosition() {
	return position;
}

float Node::getRadius() {
	return shape.getRadius();
}

void Node::drawTo(sf::RenderWindow& window) {
	if (toShow) {
		window.draw(shape);
		window.draw(text);
	}
}

bool Node::isPres(sf::Vector2f pos) {
	return shape.getGlobalBounds().contains(pos);
}

void Node::updatePosition(sf::Vector2f pos, char value) {
	position = pos;
	shape.setPosition(pos);
	std::string val; val.push_back(value);
	text.setString(val);
	//shape.setFillColor(sf::Color::Yellow);
	//shape.setOutlineThickness(1);
	sf::Vector2f center = shape.getPosition() + sf::Vector2f(shape.getRadius() / 1.5f, shape.getRadius() / 2.5f);
	text.setPosition(center);
}

void Node::hideNode() {
	toShow = 0;
}