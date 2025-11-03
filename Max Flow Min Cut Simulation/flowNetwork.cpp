#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

#define nodeColor sf::Color(255, 204, 0)

class Node {

private:
	int value;
	sf::Vector2f position;
	sf::CircleShape shape;
	sf::Text text;

public:

	Node(){
		value = -1;
	}

	Node(int value, float radius, sf::Color color, sf::Vector2f position, sf::Font &font) {
		this->value = value;
		this->position = position;

		shape.setRadius(radius);
		shape.setFillColor(color);
		shape.setPosition(position);
		shape.setOutlineThickness(3);
		shape.setOutlineColor(sf::Color::Black);
		shape.setPointCount(5000);

		sf::Vector2f center = shape.getPosition() + sf::Vector2f(shape.getRadius() / 1.5, shape.getRadius() / 1.5);

		text.setFont(font);
		text.setString(std::to_string(value));
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(20);
		text.setStyle(sf::Text::Bold);
		text.setPosition(center);
	}

	void setColor(sf::Color color) {
		shape.setFillColor(color);
	}

	void setRadius(float radius) {
		shape.setRadius(radius);
	}

	sf::Vector2f getPosition() {
		return position;
	}

	float getRadius() {
		return shape.getRadius();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(shape);
		window.draw(text);
	}
};

class Edge {

private:
	Node startNode;
	Node endNode;
	sf::RectangleShape shape;
	sf::ConvexShape direct;
	float length;

public:

	Edge(){
		length = 0;
	}

	Edge(Node u, Node v) {
		startNode = u;
		endNode = v;

		sf::Vector2f start = startNode.getPosition() + sf::Vector2f(startNode.getRadius(), startNode.getRadius());
		sf::Vector2f end = endNode.getPosition() + sf::Vector2f(startNode.getRadius(), startNode.getRadius());

		sf::Vector2f dirVector = end - start;
		length = std::sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
		float angle = std::atan2(dirVector.y, dirVector.x) * 180 / 3.14159265f;

		shape.setSize(sf::Vector2f(length, 3.0f));
		shape.setFillColor(sf::Color::Black);
		shape.setOrigin(0, 3.0f / 2);
		shape.setPosition(start);
		shape.setRotation(angle);

		dirVector /= length;
		sf::Vector2f mid = end - 1.3f * (dirVector * endNode.getRadius());
		sf::Vector2f perp(-dirVector.y, dirVector.x);

		float triLength = 20.f;  
		float triWidth = 15.f;   

		sf::Vector2f tip = mid + dirVector * triLength / 2.f;
		sf::Vector2f left = mid - dirVector * triLength / 2.f + perp * (triWidth / 2.f);
		sf::Vector2f right = mid - dirVector * triLength / 2.f - perp * (triWidth / 2.f);

		direct.setPointCount(3);
		direct.setPoint(0, tip);
		direct.setPoint(1, left);
		direct.setPoint(2, right);
		direct.setFillColor(sf::Color::Black);
	}

	void setColor(sf::Color color) {
		shape.setFillColor(color);
		direct.setFillColor(color);
	}

	void setThickness(int thick) {
		shape.setSize(sf::Vector2f(length, thick));
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(direct);
		window.draw(shape);
	}
};

class Graph {

private:
	std::vector<Node> nodeList;
	std::vector<Edge> edgeList;
	sf::Font font;

public:
	Graph(){}

	Graph(int n, std::vector<std::vector<int>> edges) {
		int m = edges.size();

		if (!font.loadFromFile("./Diary_Beauty.otf")) {
			std::cout << "Error loading the font file\n";
			return;
		}

		nodeList.push_back(Node(1, 30.0f, nodeColor, { 100, 300 }, font));
		nodeList.push_back(Node(2, 30.0f, nodeColor, { 300, 100 }, font));
		nodeList.push_back(Node(3, 30.0f, nodeColor, { 700, 100 }, font));
		nodeList.push_back(Node(4, 30.0f, nodeColor, { 300, 500 }, font));
		nodeList.push_back(Node(5, 30.0f, nodeColor, { 700, 500 }, font));
		nodeList.push_back(Node(6, 30.0f, nodeColor, { 1000, 300 }, font));

		for (int i = 0; i < m; i++) {
			int u = edges[i][0];
			int v = edges[i][1];
			edgeList.push_back(Edge(nodeList[u - 1], nodeList[v - 1]));
		}

		edgeList[0].setColor(sf::Color::Blue);
		edgeList[2].setColor(sf::Color::Blue);
		edgeList[5].setColor(sf::Color::Blue);

	}

	void drawTo(sf::RenderWindow& window) {
		for (auto e : edgeList)
			e.drawTo(window);
		for (auto n : nodeList)
			n.drawTo(window);
	}
};

static void testFunc() {

	Graph g(6, { {1, 2}, {1, 3}, {2, 5}, {4, 6}, {3, 6}, {5, 6}, {2, 3} , {1, 4}, {4, 5} });

	sf::RenderWindow window(sf::VideoMode(1600, 800), "Network Flow Graph");
	int currScreen = 0;

	while (window.isOpen()) {
		
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					if (currScreen > 0)
						currScreen--;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					if (currScreen < 6)
						currScreen++;
				}
			}
		}

		window.clear(sf::Color::White);

		g.drawTo(window);

		window.display();
	}
}
