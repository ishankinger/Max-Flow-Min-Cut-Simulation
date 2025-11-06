#include "flowNetwork.hpp"

Graph::Graph(int n, std::vector<std::vector<int>> edges, int type, sf::Font& f) : font(f) {
	int m = (int)edges.size();
	isResidual = type;
	this->edges = edges;

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
		nodeList.push_back(Node('d', 30.0f, nodeColor, { 615, 266 }, font));
		nodeList.push_back(Node('e', 30.0f, nodeColor, { 287, 700 }, font));
		nodeList.push_back(Node('f', 30.0f, nodeColor, { 525, 700 }, font));
		nodeList.push_back(Node('g', 30.0f, nodeColor, { 762, 700 }, font));
		break;
	case 8:
		nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
		nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
		nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
		nodeList.push_back(Node('d', 30.0f, nodeColor, { 615, 266 }, font));
		nodeList.push_back(Node('e', 30.0f, nodeColor, { 615, 482 }, font));
		nodeList.push_back(Node('f', 30.0f, nodeColor, { 287, 700 }, font));
		nodeList.push_back(Node('g', 30.0f, nodeColor, { 525, 700 }, font));
		nodeList.push_back(Node('h', 30.0f, nodeColor, { 762, 700 }, font));
		break;
	case 9:
		nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
		nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
		nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
		nodeList.push_back(Node('d', 30.0f, nodeColor, { 615, 266 }, font));
		nodeList.push_back(Node('e', 30.0f, nodeColor, { 615, 482 }, font));
		nodeList.push_back(Node('f', 30.0f, nodeColor, { 377, 266 }, font));
		nodeList.push_back(Node('g', 30.0f, nodeColor, { 287, 700 }, font));
		nodeList.push_back(Node('h', 30.0f, nodeColor, { 525, 700 }, font));
		nodeList.push_back(Node('i', 30.0f, nodeColor, { 762, 700 }, font));
		break;
	case 10:
		nodeList.push_back(Node('a', 30.0f, nodeColor, { 287, 50 }, font));
		nodeList.push_back(Node('b', 30.0f, nodeColor, { 525, 50 }, font));
		nodeList.push_back(Node('c', 30.0f, nodeColor, { 762, 50 }, font));
		nodeList.push_back(Node('d', 30.0f, nodeColor, { 615, 266 }, font));
		nodeList.push_back(Node('e', 30.0f, nodeColor, { 615, 482 }, font));
		nodeList.push_back(Node('f', 30.0f, nodeColor, { 377, 266 }, font));
		nodeList.push_back(Node('g', 30.0f, nodeColor, { 377, 482 }, font));
		nodeList.push_back(Node('h', 30.0f, nodeColor, { 287, 700 }, font));
		nodeList.push_back(Node('i', 30.0f, nodeColor, { 525, 700 }, font));
		nodeList.push_back(Node('j', 30.0f, nodeColor, { 762, 700 }, font));
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

	if (isResidual) {
		tableList.push_back(TextBox("Edge",		30, 2.0f, sf::Vector2f(150, 60), sf::Vector2f(1100, 40), sf::Color::Black, nodeColor, sf::Color::Black, font));
		tableList.push_back(TextBox("Forward",  30, 2.0f, sf::Vector2f(150, 60), sf::Vector2f(1250, 40), sf::Color::Black, nodeColor, sf::Color::Black, font));
		tableList.push_back(TextBox("Backward", 30, 2.0f, sf::Vector2f(150, 60), sf::Vector2f(1400, 40), sf::Color::Black, nodeColor, sf::Color::Black, font));
		for (int i = 0; i < m; i++) {
			char u = getNode(edges[i][0]-1);
			char v = getNode(edges[i][1]-1);
			std::string str = "";
			str.push_back(u);
			str += " - ";
			str.push_back(v);
			tableList.push_back(TextBox(str, 25, 2.0f, sf::Vector2f(150, 40), sf::Vector2f(1100, 40 * (i + 1) + 50), sf::Color::Black, sf::Color(213, 255, 255), sf::Color::Black, font));
			tableList.push_back(TextBox("-", 25, 2.0f, sf::Vector2f(150, 40), sf::Vector2f(1250, 40 * (i + 1) + 50), sf::Color::Black, sf::Color(213, 255, 255), sf::Color::Black, font));
			tableList.push_back(TextBox("-", 25, 2.0f, sf::Vector2f(150, 40), sf::Vector2f(1400, 40 * (i + 1) + 50), sf::Color::Black, sf::Color(213, 255, 255), sf::Color::Black, font));
		}
	}
	else {
		tableList.push_back(TextBox("Edge",		30, 2.0f, sf::Vector2f(150, 60), sf::Vector2f(1100, 40), sf::Color::Black, nodeColor, sf::Color::Black, font));
		tableList.push_back(TextBox("Capacity", 30, 2.0f, sf::Vector2f(150, 60), sf::Vector2f(1250, 40), sf::Color::Black, nodeColor, sf::Color::Black, font));
		tableList.push_back(TextBox("Flow",		30, 2.0f, sf::Vector2f(150, 60), sf::Vector2f(1400, 40), sf::Color::Black, nodeColor, sf::Color::Black, font));
		for (int i = 0; i < m; i++) {
			char u = getNode(edges[i][0]-1);
			char v = getNode(edges[i][1]-1);
			std::string str = "";
			str.push_back(u);
			str += " -> ";
			str.push_back(v);
			tableList.push_back(TextBox(str, 25, 2.0f, sf::Vector2f(150, 40), sf::Vector2f(1100, 40 * (i + 1) + 50), sf::Color::Black, sf::Color(213, 255, 255), sf::Color::Black, font));
			tableList.push_back(TextBox("-", 25, 2.0f, sf::Vector2f(150, 40), sf::Vector2f(1250, 40 * (i + 1) + 50), sf::Color::Black, sf::Color(213, 255, 255), sf::Color::Black, font));
			tableList.push_back(TextBox("-", 25, 2.0f, sf::Vector2f(150, 40), sf::Vector2f(1400, 40 * (i + 1) + 50), sf::Color::Black, sf::Color(213, 255, 255), sf::Color::Black, font));
		}
	}
}

void Graph::drawTo(sf::RenderWindow& window) {
	for (auto& t : tableList)
		t.drawTo(window);
	for (auto& e : edgeList)
		e.drawTo(window);
	for (auto& e : resEdgeList)
		e.drawTo(window);
	for (auto& n : nodeList)
		n.drawTo(window);
}

bool Graph::isPres(sf::Vector2f pos, char& nodeVal) {
	for(int i = 0; i < (int)nodeList.size(); i++) {
		if (nodeList[i].isPres(pos)) {
			nodeVal = getNode(i);
			return true;
		}
	}
	return false;
}

char Graph::getNode(int value) {
	char val;
	if (value == 0)
		val = 's';
	else if (value == (int)nodeList.size() - 1)
		val = 't';
	else
		val = 'a' + value - 1;
	return val;
}

void Graph::updateGraph(sf::Vector2f start, sf::Vector2f end) {
	sf::Vector2f dirVector = end - start;
	if (dirVector.x == 0 && dirVector.y == 0) {
		dirVector.x = 0.000001;
		dirVector.y = 0.000001;
	}

	int nodeInd = -1;
	for (int i = 0; i < (int)nodeList.size(); i++) {
		if (nodeList[i].isPres(start)) {

			char val = getNode(i);

			float length = std::sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
			float angle = std::atan2(dirVector.y, dirVector.x) * 180 / 3.14159265f;
			sf::Vector2f unitVector = dirVector / length;

			sf::Vector2f centre = nodeList[i].getPosition() + sf::Vector2f(nodeList[i].getRadius(), nodeList[i].getRadius());
			sf::Vector2f newPos = centre + unitVector * length;

			Node newNode(val, 30.0f, nodeColor, newPos, font);
			nodeList[i] = newNode;
			nodeInd = i;
			break;
		}
	}

	int m = edges.size();

	if (isResidual) {
		resEdgeList = {};
		for (int i = 0; i < m; i++) {
			int u = edges[i][0];
			int v = edges[i][1];
			resEdgeList.push_back(ResidualEdge(nodeList[u - 1], nodeList[v - 1]));
		}
	}
	else {
		edgeList = {};
		for (int i = 0; i < m; i++) {
			int u = edges[i][0];
			int v = edges[i][1];
			edgeList.push_back(Edge(nodeList[u - 1], nodeList[v - 1]));
		}
	}

	if (isResidual) {
		for (int j = 0; j < (int)resEdgeList.size(); j++) {
			if (resEdgeList[j].getStartNode() == &nodeList[nodeInd]) {
				resEdgeList[j].getEndNode()->setColor(nodeColor);
				tableList[3 + 3 * j].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor4);
			}
			else if (resEdgeList[j].getEndNode() == &nodeList[nodeInd]) {
				resEdgeList[j].getStartNode()->setColor(nodeColor);
				tableList[3 + 3 * j].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor4);
			}
		}
	}
	else {
		for (int j = 0; j < (int)edgeList.size(); j++) {
			if (edgeList[j].getStartNode() == &nodeList[nodeInd]) {
				edgeList[j].getEndNode()->setColor(nodeColor);
				tableList[3 + 3 * j].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor4);
			}
			else if (edgeList[j].getEndNode() == &nodeList[nodeInd]) {
				edgeList[j].getStartNode()->setColor(nodeColor);
				tableList[3 + 3 * j].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor4);
				tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor4);
			}
		}
	}

}

void Graph::hideEdges(sf::Vector2f start) {
	if (isResidual) {
		for (int i = 0; i < (int)nodeList.size(); i++) {
			if (nodeList[i].isPres(start)) {
				nodeList[i].hideNode();
				for (int j = 0; j < (int)resEdgeList.size(); j++) {
					if (resEdgeList[j].getStartNode() == &nodeList[i] || resEdgeList[j].getEndNode() == &nodeList[i]) {
						resEdgeList[j].hideEdge();
					}
				}
				break;
			}
		}
	}
	else {
		for (int i = 0; i < (int)nodeList.size(); i++) {
			if (nodeList[i].isPres(start)) {
				nodeList[i].hideNode();
				for (int j = 0; j < (int)edgeList.size(); j++) {
					if (edgeList[j].getStartNode() == &nodeList[i] || edgeList[j].getEndNode() == &nodeList[i]) {
						edgeList[j].hideEdge();
					}
				}
				break;
			}
		}
	}
}

void Graph::showEdges(sf::Vector2f start, Node& fadeNode, sf::RenderWindow &window) {
	if (isResidual) {
		std::vector<ResidualEdge> newEdges;
		for (int i = 0; i < (int)nodeList.size(); i++) {
			if (nodeList[i].isPres(start)) {
				for (int j = 0; j < (int)resEdgeList.size(); j++) {
					if (resEdgeList[j].getStartNode() == &nodeList[i]) {
						newEdges.push_back(ResidualEdge(fadeNode, *resEdgeList[j].getEndNode()));
						resEdgeList[j].getEndNode()->setColor(nodeColor2);
						tableList[3 + 3 * j].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor);
					}
					else if (resEdgeList[j].getEndNode() == &nodeList[i]) {
						newEdges.push_back(ResidualEdge(fadeNode, *resEdgeList[j].getStartNode()));
						resEdgeList[j].getStartNode()->setColor(nodeColor2);
						tableList[3 + 3 * j].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor);
					}
				}
				break;
			}
		}
		for (auto& e : newEdges)
			e.drawTo(window);
	}
	else{
		std::vector<Edge> newEdges;
		for (int i = 0; i < (int)nodeList.size(); i++) {
			if (nodeList[i].isPres(start)) {
				for (int j = 0; j < (int)edgeList.size(); j++) {
					if (edgeList[j].getStartNode() == &nodeList[i]) {
						newEdges.push_back(Edge(fadeNode, *edgeList[j].getEndNode()));
						edgeList[j].getEndNode()->setColor(nodeColor2);
						tableList[3 + 3 * j].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor);
					}
					else if (edgeList[j].getEndNode() == &nodeList[i]) {
						newEdges.push_back(Edge(*edgeList[j].getStartNode(), fadeNode));
						edgeList[j].getStartNode()->setColor(nodeColor2);
						tableList[3 + 3 * j].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 1].setBackgroundColor(nodeColor);
						tableList[3 + 3 * j + 2].setBackgroundColor(nodeColor);
					}
				}
				break;
			}
		}

		for (auto& e : newEdges)
			e.drawTo(window);
	}
}