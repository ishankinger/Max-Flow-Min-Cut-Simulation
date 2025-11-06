#include "flowNetwork.hpp"

ResidualEdge::ResidualEdge() {
	length1 = 0;
	length2 = 0;
	triLength = 0;
	triWidth = 0;
	startNode = nullptr;
	endNode = nullptr;
	toShow = 0;
}

ResidualEdge::ResidualEdge(Node& u, Node& v, float tl, float tw) {
	startNode = &u;
	endNode = &v;
	triLength = tl;
	triWidth = tw;
	toShow = 1;

	addEdge(1);
	addEdge(0);
}

void ResidualEdge::addEdge(int up) {

	sf::Vector2f startCentre = startNode->getPosition() + sf::Vector2f(startNode->getRadius(), startNode->getRadius());
	sf::Vector2f endCentre = endNode->getPosition() + sf::Vector2f(startNode->getRadius(), startNode->getRadius());

	sf::Vector2f dirVector = endCentre - startCentre;
	float length = std::sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
	sf::Vector2f unitVector = dirVector / length;

	sf::Vector2f start = up ? startCentre + sf::Vector2f(-unitVector.y, unitVector.x) * (startNode->getRadius() / 2) :
		startCentre - sf::Vector2f(-unitVector.y, unitVector.x) * (startNode->getRadius() / 2);

	sf::Vector2f end = up ? endCentre + sf::Vector2f(-unitVector.y, unitVector.x) * (endNode->getRadius() / 2) :
		endCentre - sf::Vector2f(-unitVector.y, unitVector.x) * (endNode->getRadius() / 2);

	float angle = std::atan2((end.y - start.y), (end.x - start.x)) * 180 / 3.14159265f;

	if (up) {
		length1 = std::sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
		shape1.setSize(sf::Vector2f(length1, 3.0f));
		shape1.setFillColor(sf::Color::Black);
		shape1.setOrigin(0, 3.0f / 2);
		shape1.setPosition(start);
		shape1.setRotation(angle);

		float fmr = (endNode->getRadius() * ((float)std::sqrt(3) / 2.0f));
		sf::Vector2f tip = end + sf::Vector2f(-unitVector.x, -unitVector.y) * fmr;
		sf::Vector2f left = tip + sf::Vector2f(-unitVector.x, -unitVector.y) * triLength + sf::Vector2f(unitVector.y, -unitVector.x) * (triWidth / 2);
		sf::Vector2f right = tip + sf::Vector2f(-unitVector.x, -unitVector.y) * triLength + sf::Vector2f(-unitVector.y, unitVector.x) * (triWidth / 2);

		direct1.setPointCount(3);
		direct1.setPoint(0, tip);
		direct1.setPoint(1, left);
		direct1.setPoint(2, right);
		direct1.setFillColor(sf::Color::Black);
	}
	else {
		length2 = std::sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
		shape2.setSize(sf::Vector2f(length2, 3.0f));
		shape2.setFillColor(sf::Color::Black);
		shape2.setOrigin(0, 3.0f / 2);
		shape2.setPosition(start);
		shape2.setRotation(angle);

		float fmr = (endNode->getRadius() * ((float)std::sqrt(3) / 2.0f));
		sf::Vector2f tip = start + sf::Vector2f(unitVector.x, unitVector.y) * fmr;
		sf::Vector2f left = tip + sf::Vector2f(unitVector.x, unitVector.y) * triLength + sf::Vector2f(unitVector.y, -unitVector.x) * (triWidth / 2);
		sf::Vector2f right = tip + sf::Vector2f(unitVector.x, unitVector.y) * triLength + sf::Vector2f(-unitVector.y, unitVector.x) * (triWidth / 2);

		direct2.setPointCount(3);
		direct2.setPoint(0, tip);
		direct2.setPoint(1, left);
		direct2.setPoint(2, right);
		direct2.setFillColor(sf::Color::Black);
	}
}

void ResidualEdge::setColor(sf::Color color) {
	shape1.setFillColor(color);
	direct1.setFillColor(color);
	shape2.setFillColor(color);
	direct2.setFillColor(color);
}

void ResidualEdge::setThickness(int thick) {
	shape1.setSize(sf::Vector2f(length1, (float)thick));
	shape2.setSize(sf::Vector2f(length2, (float)thick));
}

void ResidualEdge::drawTo(sf::RenderWindow& window) {
	if (toShow) {
		window.draw(direct1);
		window.draw(direct2);
		window.draw(shape1);
		window.draw(shape2);
	}
}

Node* ResidualEdge::getStartNode() {
	return startNode;
}

Node* ResidualEdge::getEndNode() {
	return endNode;
}

void ResidualEdge::hideEdge() {
	toShow = 0;
}