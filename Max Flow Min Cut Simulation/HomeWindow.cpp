#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "HomeWindow.h"

void createHomeWindow() {

	std::cout << "HELLO\n";

	sf::RenderWindow window(sf::VideoMode(1320, 750), "My window");
	//sf::RenderWindow window(sf::VideoMode(200, 800), "My window", sf::Style::Fullscreen | sf::Style::Titlebar);

	sf::CircleShape shape(30.f);

	// set the shape color to green
	shape.setFillColor(sf::Color::Green);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(shape);

		window.display();
	}

}