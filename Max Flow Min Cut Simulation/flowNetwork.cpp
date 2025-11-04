#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

#define nodeColor sf::Color(255, 204, 0)

class Node {

private:
	char value;
	sf::Vector2f position;
	sf::CircleShape shape;
	sf::Text text;

public:

	Node(){
		value = -1;
	}

	Node(char value, float radius, sf::Color color, sf::Vector2f position, sf::Font &font) {
		this->value = value;
		this->position = position;

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
	float length;
	float triLength;
	float triWidth;
	Node* startNode;
	Node* endNode;
	sf::RectangleShape shape;
	sf::ConvexShape direct;

public:

	Edge(){
		length = 0;
		triLength = 0;
		triWidth = 0;
		startNode = nullptr;
		endNode = nullptr;
	}

	Edge(Node &u, Node &v, float tl = 20.f, float tw = 15.f) {
		startNode = &u;
		endNode = &v;
		triLength = tl;
		triWidth = tw;

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

	void setColor(sf::Color color) {
		shape.setFillColor(color);
		direct.setFillColor(color);
	}

	void setThickness(int thick) {
		shape.setSize(sf::Vector2f(length, (float)thick));
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(direct);
		window.draw(shape);
	}
};

class ResidualEdge {

private:
	float length1;
	float length2;
	float triLength;
	float triWidth;
	Node *startNode;
	Node *endNode;
	sf::RectangleShape shape1;
	sf::RectangleShape shape2;
	sf::ConvexShape direct1;
	sf::ConvexShape direct2;

public:

	ResidualEdge() {
		length1 = 0;
		length2 = 0;
		triLength = 0;
		triWidth = 0;
		startNode = nullptr;
		endNode = nullptr;
	}

	void addEdge(int up) {

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

	ResidualEdge(Node &u, Node &v, float tl = 20.f, float tw = 15.f) {
		startNode = &u;
		endNode = &v;
		triLength = tl;
		triWidth = tw;

		addEdge(1);
		addEdge(0);
	}

	void setColor(sf::Color color) {
		shape1.setFillColor(color);
		direct1.setFillColor(color);
		shape2.setFillColor(color);
		direct2.setFillColor(color);
	}

	void setThickness(int thick) {
		shape1.setSize(sf::Vector2f(length1, (float)thick));
		shape2.setSize(sf::Vector2f(length2, (float)thick));
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(direct1);
		window.draw(direct2);
		window.draw(shape1);
		window.draw(shape2);
	}
};

class Graph {

private:
	int isResidual;
	std::vector<Node> nodeList;
	std::vector<Edge> edgeList;
	std::vector<ResidualEdge> resEdgeList;
	sf::Font& font;

public:
	Graph(int n, std::vector<std::vector<int>> edges, int type, sf::Font &f) : font(f) {
		int m = (int)edges.size();
		isResidual = type;

		nodeList.push_back(Node('s', 30.0f, nodeColor, { 50, 375 }, font));

		int left = n - 2;

		switch (left) {
		case 1:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 525, 50 }, font));
			break;
		case 2:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 700 }, font));
			break;
		case 3:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 366, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 682, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 475, 700 }, font));
			break;
		case 4:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 366, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 682, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 366, 700 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 682, 700 }, font));
			break;
		case 5:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 366, 700 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 682, 700 }, font));
			break;
		case 6:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		case 7:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 525, 266 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('g', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		case 8:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 525, 266 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 525, 482 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('g', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('h', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		case 9:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 525, 266 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 525, 482 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 287, 266 }, font));
			nodeList.push_back(Node('g', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('h', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('i', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		case 10:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 525, 266 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 525, 482 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 287, 266 }, font));
			nodeList.push_back(Node('g', 30.0f, nodeColor, { 287, 482 }, font));
			nodeList.push_back(Node('h', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('i', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('j', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		case 11:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 525, 266 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 525, 482 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 287, 266 }, font));
			nodeList.push_back(Node('g', 30.0f, nodeColor, { 287, 482 }, font));
			nodeList.push_back(Node('h', 30.0f, nodeColor, { 762, 266 }, font));
			nodeList.push_back(Node('i', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('j', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('k', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		case 12:
			nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
			nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
			nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
			nodeList.push_back(Node('d', 30.0f, nodeColor, { 525, 266 }, font));
			nodeList.push_back(Node('e', 30.0f, nodeColor, { 525, 482 }, font));
			nodeList.push_back(Node('f', 30.0f, nodeColor, { 287, 266 }, font));
			nodeList.push_back(Node('g', 30.0f, nodeColor, { 287, 482 }, font));
			nodeList.push_back(Node('h', 30.0f, nodeColor, { 762, 266 }, font));
			nodeList.push_back(Node('i', 30.0f, nodeColor, { 762, 482 }, font));
			nodeList.push_back(Node('j', 30.0f, nodeColor, { 287, 700 }, font));
			nodeList.push_back(Node('k', 30.0f, nodeColor, { 525, 700 }, font));
			nodeList.push_back(Node('l', 30.0f, nodeColor, { 762, 700 }, font));
			break;
		default:
			break;
		}

		nodeList.push_back(Node('t', 30.0f, nodeColor, { 1000, 375 }, font));

		if (isResidual) {
			for (int i = 0; i < m; i++) {
				int u = edges[i][0];
				int v = edges[i][1];
				resEdgeList.push_back(ResidualEdge(nodeList[u - 1], nodeList[v - 1]));
			}
		}
		else {
			for (int i = 0; i < m; i++) {
				int u = edges[i][0];
				int v = edges[i][1];
				edgeList.push_back(Edge(nodeList[u - 1], nodeList[v - 1]));
			}
		}
	}

	void drawTo(sf::RenderWindow& window) {
		for (auto& e : edgeList)
			e.drawTo(window);
		for (auto& e : resEdgeList)
			e.drawTo(window);
		for (auto& n : nodeList)
			n.drawTo(window);
	}
};

static void testFunc() {

	sf::Font font;
	if (!font.loadFromFile("./Quaaykop-DYE1R.ttf")) {
		std::cout << "Error loading the font file\n";
		return;
	}

	//Graph g(6, { {1, 2}, {1, 3}, {2, 5}, {5, 2}, {3, 6}, {5, 6}, {2, 3} , {1, 4}, {4, 5} }, 0);
	//Graph g(2, { {1, 2} }, 0);
	std::vector<Graph> listOfGraphs;

	// --- Load the font ONCE at the beginning ---
	sf::Font mainFont;
	if (!mainFont.loadFromFile("./Quaaykop-DYE1R.ttf")) {
		std::cout << "Error loading the font file\n";
		return; // Exit if font fails to load
	}

	// --- Graph with n=2 ---
	std::vector<std::vector<int>> edges_n2 = { {1, 2} };
	listOfGraphs.emplace_back(2, edges_n2, 0, mainFont); // <-- Pass font

	// --- Graph with n=3 ---
	std::vector<std::vector<int>> edges_n3 = { {1, 2}, {2, 3}, {1, 3} };
	listOfGraphs.emplace_back(3, edges_n3, 0, mainFont); // <-- Pass font

	// --- Graph with n=4 ---
	std::vector<std::vector<int>> edges_n4 = { {1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3} };
	listOfGraphs.emplace_back(4, edges_n4, 0, mainFont); // <-- Pass font

	// --- Graph with n=5 ---
	std::vector<std::vector<int>> edges_n5 = { {1, 2}, {1, 3}, {2, 5}, {3, 4}, {4, 5}, {2, 4} };
	listOfGraphs.emplace_back(5, edges_n5, 0, mainFont); // <-- Pass font

	// --- Graph with n=6 ---
	std::vector<std::vector<int>> edges_n6 = { {1, 2}, {1, 3}, {2, 5}, {5, 2}, {3, 6}, {5, 6}, {2, 3}, {1, 4}, {4, 5} };
	listOfGraphs.emplace_back(6, edges_n6, 0, mainFont); // <-- Pass font

	// --- Graph with n=7 ---
	std::vector<std::vector<int>> edges_n7 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {1, 4}, {2, 6}, {3, 7} };
	listOfGraphs.emplace_back(7, edges_n7, 0, mainFont); // <-- Pass font

	// --- Graph with n=8 ---
	std::vector<std::vector<int>> edges_n8 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {1, 5}, {2, 6}, {3, 7}, {4, 8} };
	listOfGraphs.emplace_back(8, edges_n8, 0, mainFont); // <-- Pass font

	// --- Graph with n=9 ---
	std::vector<std::vector<int>> edges_n9 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {1, 5}, {2, 6}, {3, 7}, {4, 8}, {5, 9} };
	listOfGraphs.emplace_back(9, edges_n9, 0, mainFont); // <-- Pass font

	// --- Graph with n=10 ---
	std::vector<std::vector<int>> edges_n10 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
	listOfGraphs.emplace_back(10, edges_n10, 0, mainFont); // <-- Pass font

	// --- Graph with n=11 ---
	std::vector<std::vector<int>> edges_n11 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {1, 7}, {2, 8}, {3, 9}, {4, 10}, {5, 11} };
	listOfGraphs.emplace_back(11, edges_n11, 0, mainFont); // <-- Pass font

	// --- Graph with n=12 ---
	std::vector<std::vector<int>> edges_n12 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {1, 8}, {2, 9}, {3, 10}, {4, 11}, {5, 12} };
	listOfGraphs.emplace_back(12, edges_n12, 0, mainFont); // <-- Pass font

	// --- Graph with n=13 ---
	std::vector<std::vector<int>> edges_n13 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {1, 9}, {2, 10}, {3, 11}, {4, 12}, {5, 13} };
	listOfGraphs.emplace_back(13, edges_n13, 0, mainFont); // <-- Pass font

	// --- Graph with n=14 ---
	std::vector<std::vector<int>> edges_n14 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {1, 10}, {2, 11}, {3, 12}, {4, 13}, {5, 14} };
	listOfGraphs.emplace_back(14, edges_n14, 0, mainFont); // <-- Pass font

	sf::RenderWindow window(sf::VideoMode(1600, 800), "Network Flow Graph");
	int currGraph = 0;

	while (window.isOpen()) {
		
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					if (currGraph > 0)
						currGraph--;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					if (currGraph < ((int)listOfGraphs.size()) - 1)
						currGraph++;
				}
			}
		}

		window.clear(sf::Color::White);

		listOfGraphs[currGraph].drawTo(window);
		//g.drawTo(window);

		window.display();
	}
}
