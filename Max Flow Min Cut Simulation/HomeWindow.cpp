#include "HomeWindow.hpp"

void runSimuation() {

	sf::Font font;
	if (!font.loadFromFile("./Quaaykop-DYE1R.ttf")) {
		std::cout << "Error loading the font file\n";
		return;
	}
	std::vector<Graph> listOfGraphs;

	sf::Font mainFont;
	if (!mainFont.loadFromFile("./Quaaykop-DYE1R.ttf")) {
		std::cout << "Error loading the font file\n";
		return;
	}

	//std::vector<std::vector<int>> edges_n2 = { {1, 2} };
	//listOfGraphs.emplace_back(2, edges_n2, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n3 = { {1, 2}, {2, 3}, {1, 3} };
	//listOfGraphs.emplace_back(3, edges_n3, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n4 = { {1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3} };
	//listOfGraphs.emplace_back(4, edges_n4, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n5 = { {1, 2}, {1, 3}, {2, 5}, {3, 4}, {4, 5}, {2, 4} };
	//listOfGraphs.emplace_back(5, edges_n5, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n6 = { {1, 2}, {1, 3}, {2, 5}, {5, 2}, {3, 6}, {5, 6}, {2, 3}, {1, 4}, {4, 5} };
	//listOfGraphs.emplace_back(6, edges_n6, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n7 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {1, 4}, {2, 6}, {3, 7} };
	//listOfGraphs.emplace_back(7, edges_n7, 0, mainFont); 

	std::vector<std::vector<int>> edges_n8 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {1, 5}, {2, 6}, {3, 7}, {4, 8} };
	listOfGraphs.emplace_back(8, edges_n8, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n9 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {1, 5}, {2, 6}, {3, 7}, {4, 8}, {5, 9} };
	//listOfGraphs.emplace_back(9, edges_n9, 0, mainFont); 

	//std::vector<std::vector<int>> edges_n10 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
	//listOfGraphs.emplace_back(10, edges_n10, 1, mainFont); 

	std::vector<std::vector<int>> edges_n11 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {1, 7}, {2, 8}, {3, 9}, {4, 10}, {5, 11} };
	listOfGraphs.emplace_back(11, edges_n11, 1, mainFont);

	std::vector<std::vector<int>> edges_n12 = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {1, 8}, {2, 9}, {3, 10}, {4, 11}, {5, 12} };
	listOfGraphs.emplace_back(12, edges_n12, 0, mainFont); 

	sf::RenderWindow window(sf::VideoMode(1600, 800), "Network Flow Graph");
	int currGraph = 0;

	int state = 0;
	sf::Vector2f start = sf::Vector2f(0, 0), end = sf::Vector2f(0, 0);

	Node fadeNode(' ', 30.0f, nodeColor3, { 45, 45 }, font);
	sf::Vector2f currCursor;
	char nodeVal = ' ';

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					if (currGraph > 0)
						currGraph--;
					state = 0;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					if (currGraph < ((int)listOfGraphs.size()) - 1)
						currGraph++;
					state = 0;
				}
				else if (event.key.code == sf::Keyboard::E) {
					window.close();
					state = 0;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left){
					start = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					if (listOfGraphs[currGraph].isPres(start, nodeVal)) {
						state = 1;
						listOfGraphs[currGraph].hideEdges(start);
					}
					else {
						state = 0;
					}
				}
			}

			if (event.type == sf::Event::MouseMoved) {
				currCursor = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					end = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					if (state == 1) {
						listOfGraphs[currGraph].updateGraph(start, end);
						state = 0;
					}
				}
			}
		}

		window.clear(sf::Color::White);
		 
		if (state == 1) {
			fadeNode.updatePosition(currCursor, nodeVal);
			listOfGraphs[currGraph].showEdges(start, fadeNode, window);
			fadeNode.drawTo(window);
		}

		listOfGraphs[currGraph].drawTo(window);

		window.display();
	}
}
