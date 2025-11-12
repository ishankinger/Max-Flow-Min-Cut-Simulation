#include "HomeWindow.hpp"

void runSimuation(std::vector<Graph> &listOfGraphs, sf::Font &mainFont) {

	sf::RenderWindow window(sf::VideoMode(1600, 800), "Network Flow Graph");
	int currGraph = 0;

	int state = 0;
	sf::Vector2f start = sf::Vector2f(0, 0), end = sf::Vector2f(0, 0);

	Node fadeNode(' ', 30.0f, nodeColor3, { 45, 45 }, mainFont);
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