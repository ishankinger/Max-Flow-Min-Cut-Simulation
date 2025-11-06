#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

#define nodeColor sf::Color(253, 204, 0)
#define nodeColor2 sf::Color(173, 216, 230)
#define nodeColor3 sf::Color(173, 216, 230)
#define nodeColor4 sf::Color(213, 255, 255)
#define fadeColor sf::Color(253, 204, 0)

class Node;
class Edge;
class ResidualEdge;
class Graph;
class TextBox;

class Node {
private:
	char value;
	sf::Vector2f position;
	sf::CircleShape shape;
	sf::Text text;
	int toShow;

public:
	Node();
	Node(char value, float radius, sf::Color color, sf::Vector2f position, sf::Font& font);
	void setColor(sf::Color color);
	void setRadius(float radius);
	sf::Vector2f getPosition();
	float getRadius();
	void drawTo(sf::RenderWindow& window);
	bool isPres(sf::Vector2f pos);
	void updatePosition(sf::Vector2f pos, char val);
	void hideNode();
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
	int toShow;

public:
	Edge();
	Edge(Node& u, Node& v, float tl = 20.f, float tw = 15.f);
	void setColor(sf::Color color);
	void setThickness(int thick);
	void drawTo(sf::RenderWindow& window);
	Node* getStartNode();
	Node* getEndNode();
	void hideEdge();
};

class ResidualEdge {
private:
	float length1;
	float length2;
	float triLength;
	float triWidth;
	Node* startNode;
	Node* endNode;
	sf::RectangleShape shape1;
	sf::RectangleShape shape2;
	sf::ConvexShape direct1;
	sf::ConvexShape direct2;
	int toShow;

public:
	ResidualEdge();
	ResidualEdge(Node& u, Node& v, float tl = 20.f, float tw = 15.f);
	void addEdge(int up);
	void setColor(sf::Color color);
	void setThickness(int thick);
	void drawTo(sf::RenderWindow& window);
	Node* getStartNode();
	Node* getEndNode();
	void hideEdge();
};

class Graph {
private:
	int isResidual;
	std::vector<Node> nodeList;
	std::vector<Edge> edgeList;
	std::vector<ResidualEdge> resEdgeList;
	sf::Font& font;
	std::vector<std::vector<int>> edges;
	std::vector<TextBox> tableList;

public:
	Graph(int n, std::vector<std::vector<int>> edges, int type, sf::Font& f);
	void drawTo(sf::RenderWindow& window);
	bool isPres(sf::Vector2f pos, char& nodeVal);
	void updateGraph(sf::Vector2f start, sf::Vector2f end);
	char getNode(int);
	void hideEdges(sf::Vector2f start);
	void showEdges(sf::Vector2f start, Node& fadeNode, sf::RenderWindow& window);
};

class TextBox {
private:
	sf::RectangleShape box;
	sf::Font font;
	sf::Text text;
	sf::Vector2f bounding_box_pos;
	sf::Vector2f bounding_box_size;
	bool isCentre;

public:
	TextBox();
	TextBox(std::string textVal, unsigned charSize, float outline_thickness, sf::Vector2f boxSize, sf::Vector2f boxPos, sf::Color textColor, sf::Color bgColor, sf::Color outlineColor, sf::Font &font, bool centre = true, bool textBold = true);
	TextBox(std::string textVal, unsigned charSize, float outline_thickness, sf::Vector2f boxSize, sf::Vector2f boxPos, sf::Vector2f boundSize, sf::Vector2f boundPos, sf::Color textColor, sf::Color bgColor, sf::Color outlineColor, sf::Font& font, bool centre = true, bool textBold = true);
	void setText(std::string textVal);
	void setTextColor(sf::Color textColor);
	void setTextSize(int charSize);
	void setBoxSize(sf::Vector2f size);
	void setBackgroundColor(sf::Color bgColor);
	void setOutlineColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	float get_center_coord(float div_x, float div_size, float box_size);
	void setTextPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	std::string getText();
};