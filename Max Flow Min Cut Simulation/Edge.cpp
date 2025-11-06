#include "flowNetwork.hpp"

Edge::Edge() {
	length = 0;
	triLength = 0;
	triWidth = 0;
	startNode = nullptr;
	endNode = nullptr;
	toShow = 0;
}

Edge::Edge(Node& u, Node& v, float tl, float tw) {
	startNode = &u;
	endNode = &v;
	triLength = tl;
	triWidth = tw;
	toShow = 1;

	sf::Vector2f start = startNode->getPosition() + sf::Vector2f(startNode->getRadius(), startNode->getRadius());
	sf::Vector2f end = endNode->getPosition() + sf::Vector2f(startNode->getRadius(), startNode->getRadius());

	sf::Vector2f dirVector = end - start;
	length = std::sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	float angle = std::atan2(dirVector.y, dirVector.x) * 180 / 3.14159265f;

	shape.setSize(sf::Vector2f(length, 3.0f));
	shape.setFillColor(sf::Color::Black);
	shape.setOrigin(0, 3.0f / 2);
	shape.setPosition(start);
	shape.setRotation(angle);

	sf::Vector2f unitVector = dirVector / length;

	sf::Vector2f tip = end + sf::Vector2f(-unitVector.x, -unitVector.y) * endNode->getRadius();
	sf::Vector2f left = tip + sf::Vector2f(-unitVector.x, -unitVector.y) * triLength + sf::Vector2f(unitVector.y, -unitVector.x) * (triWidth / 2);
	sf::Vector2f right = tip + sf::Vector2f(-unitVector.x, -unitVector.y) * triLength + sf::Vector2f(-unitVector.y, unitVector.x) * (triWidth / 2);

	direct.setPointCount(3);
	direct.setPoint(0, tip);
	direct.setPoint(1, left);
	direct.setPoint(2, right);
	direct.setFillColor(sf::Color::Black);
}

void Edge::setColor(sf::Color color) {
	shape.setFillColor(color);
	direct.setFillColor(color);
}

void Edge::setThickness(int thick) {
	shape.setSize(sf::Vector2f(length, (float)thick));
}

void Edge::drawTo(sf::RenderWindow& window) {
	if (toShow) {
		window.draw(direct);
		window.draw(shape);
	}
}

Node* Edge::getStartNode() {
	return startNode;
}

Node* Edge::getEndNode() {
	return endNode;
}

void Edge::hideEdge() {
	toShow = 0;
}