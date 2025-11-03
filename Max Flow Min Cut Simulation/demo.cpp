#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

static void demo_time() {

	/* all values are equal */
	sf::Time t1 = sf::microseconds(10000);
	sf::Time t2 = sf::milliseconds(10);
	sf::Time t3 = sf::seconds(0.01f);

	/* value cna be converted to other unit also */
	sf::Time time = sf::microseconds(200340);
	sf::Int64 usec = time.asMicroseconds();
	sf::Int32 msec = time.asMilliseconds();
	float     sec = time.asSeconds();

	/* it supports the arithemetic operations */
	sf::Time t4 = -t3;
	sf::Time t5 = t4 + t2;
	bool b1 = (t1 == t2);
	bool b2 = (t3 > t4);

	/* Calcuating the elasped time */

	/* start the timer */
	sf::Clock clock;

	/* operations performed */
	int a = 0;
	while (a < 1000000) a++;

	/* get the elasped time */
	sf::Time elapsed1 = clock.getElapsedTime();
	std::cout << elapsed1.asSeconds() << std::endl;

	/* again restart the clock */
	clock.restart();

	a = 0;
	while (a < 100000000) a++;

	sf::Time elapsed2 = clock.getElapsedTime();
	std::cout << elapsed2.asSeconds() << std::endl;

	clock.restart();

	a = 0;
	while (a < 100000000) a++;

	/* clock.restart() also return the time elasped */
	sf::Time elapsed3 = clock.restart();
	std::cout << elapsed3.asSeconds() << std::endl;

	return;
}

static void demo_window()
{
	sf::Window window(sf::VideoMode(800, 600), "My window");

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
	}

	/* first declare and then create */
	sf::Window w;
	w.create(sf::VideoMode(800, 600), "Window...");

	sf::Event e;
	while (w.isOpen())
	{
		while (w.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				w.close();
			}
		}
	}

	w.create(sf::VideoMode(500, 500), "Window2...");

	// change the position of the window (relatively to the desktop)
	w.setPosition(sf::Vector2i(10, 50));

	// change the size of the window
	w.setSize(sf::Vector2u(640, 480));

	// change the title of the window
	w.setTitle("SFML window");

	// get the size of the window
	sf::Vector2u size = w.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	std::cout << width << " " << height << "\n";

	// check whether the window has the focus
	bool focus = w.hasFocus();

	std::cout << focus << "\n";

	while (w.isOpen()) {
		while (w.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				w.close();
			}
		}
	}

	return;
}

static void demo_events() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// run the program as long as the window is open
	while (window.isOpen())
	{

		sf::Event event;

		// while there are pending events...
		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{

				// window closed
			case sf::Event::Closed:
				std::cout << "Close Window\n";
				window.close();
				break;

				// window resize (using window.setsize() or user action)
			case sf::Event::Resized:
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				break;

				// lost focus when user switches
			case sf::Event::LostFocus:
				std::cout << "Game Paused\n";
				break;

				// gain focus user comes back to window
			case sf::Event::GainedFocus:
				std::cout << "Game Continued\n";
				break;

				// text entered event
			case sf::Event::TextEntered:
				if (event.text.unicode < 128)
					std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
				break;

				// key pressed
			case sf::Event::KeyPressed:
				if (event.key.scancode == sf::Keyboard::Scan::Escape)
				{
					std::cout << "the escape key was pressed" << std::endl;
					std::cout << "scancode: " << event.key.scancode << std::endl;
					std::cout << "code: " << event.key.code << std::endl;
					std::cout << "control: " << event.key.control << std::endl;
					std::cout << "alt: " << event.key.alt << std::endl;
					std::cout << "shift: " << event.key.shift << std::endl;
					std::cout << "system: " << event.key.system << std::endl;
					std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
					std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
					std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;
				}
				break;

				// track the scroll movement of the mouse
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					std::cout << "wheel type: vertical" << std::endl;
				else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
					std::cout << "wheel type: horizontal" << std::endl;
				else
					std::cout << "wheel type: unknown" << std::endl;
				std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
				std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
				std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
				break;

				// mouse button pressed
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}
				break;

				// mouse moved event
			case sf::Event::MouseMoved:
				std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
				break;

				// mouse cursor get inside the window
			case sf::Event::MouseEntered:
				std::cout << "the mouse cursor has entered the window" << std::endl;
				break;

				// mouse cursor get out of window
			case sf::Event::MouseLeft:
				std::cout << "the mouse cursor has left the window" << std::endl;
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
		window.clear(sf::Color::Black);
		window.display();
	}
}

static void demo_keyboard_mouse()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		//character.move(-1.f, 0.f);
	}

	// Key codes are defined in the sf::Keyboard::Key enum.

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
	{
		// right key is pressed: move our character
		//character.move(1.f, 0.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// left mouse button is pressed: shoot
		//gun.fire();
	}

	sf::Window window;

	// get the global mouse position (relative to the desktop)
	sf::Vector2i globalPosition = sf::Mouse::getPosition();

	// get the local mouse position (relative to a window)
	sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window

	// set the mouse position globally (relative to the desktop)
	sf::Mouse::setPosition(sf::Vector2i(10, 50));

	// set the mouse position locally (relative to a window)
	sf::Mouse::setPosition(sf::Vector2i(10, 50), window); // window is a sf::Window

	return;
}

static void demo_drawing()
{
	// create the window
	/*class : sf::RenderWindow.This class is derived from sf::Window,
	and inherits all its functions.*/
	sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

	/*clear clears the whole window with the chosen color, and
	draw draws whatever object you pass to it.*/

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

				// window closed
				case sf::Event::Closed:
					std::cout << "Close Window\n";
					window.close();
				break;

				// "close requested" event: we close the window
				case sf::Event::MouseWheelScrolled:
					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
						std::cout << "wheel type: vertical" << std::endl;
					else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
						std::cout << "wheel type: horizontal" << std::endl;
					else
						std::cout << "wheel type: unknown" << std::endl;
					std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
					std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
					std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
				break;
			}
		}

		// clear the window with black color
		/*Calling clear before drawing anything is mandatory, otherwise the contents
		from previous frames will be present behind anything you draw.*/
		window.clear(sf::Color::White);

		// draw everything here...
		// window.draw(...);

		// end the current frame
		/*Calling display is also mandatory, it takes what was drawn since the last call to display and
		displays it on the window.Indeed, things are not drawn directly to the window, but to a hidden buffer.
		This buffer is then copied to the window when you call display-- this is called double - buffering.*/
		window.display();
	}

}

static void demo_texture() {

	sf::Texture texture;
	if (!texture.loadFromFile("./image.png"))
	{
		// error...
		std::cout << "Error occured while loading file\n";
		return;
	}

	// load a 32x32 rectangle that starts at (10, 10)
	//if (!texture.loadFromFile("image.png", sf::IntRect(10, 10, 32, 32)))
	//{
	//	// error...
	//}

	// update a texture from an array of pixels
	//sf::Uint8* pixels = new sf::Uint8[width * height * 4]; // * 4 because pixels have 4 components (RGBA)
	//...
	//	texture.update(pixels);

	// update a texture from a sf::Image
	/*sf::Image image;
	...
		texture.update(image);*/

		// update the texture from the current contents of the window
		/*sf::RenderWindow window;
		...
			texture.update(window);*/

			//texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	//sprite.setTextureRect(sf::IntRect(10, 10, 32, 32));

	//sprite.setColor(sf::Color(0, 255, 0)); // green
	//sprite.setColor(sf::Color(255, 255, 255, 128)); // half transparent

	// position
	//sprite.setPosition(sf::Vector2f(10.f, 50.f)); // absolute position
	//sprite.move(sf::Vector2f(-45.f, -10.f)); // offset relative to the current position

	// rotation
	//sprite.setRotation(90.f); // absolute angle
	//sprite.rotate(15.f); // offset relative to the current angle

	// scale
	//sprite.setScale(sf::Vector2f(0.5f, 2.f)); // absolute scale factor
	//sprite.scale(sf::Vector2f(1.5f, 3.f)); // factor relative to the current scale

	//By default, the origin for these three transformations is the top - left corner
	//sprite.setOrigin(sf::Vector2f(25.f, 25.f));

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(sprite);

		window.display();
	}
}

static void demo_font() {

	sf::Font font;
	if (!font.loadFromFile("./Diary_Beauty.otf"))
	{
		// error...
		std::cout << "Error loading the font file\n";
		return;
	}

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString("Hello world");

	// set the character size
	text.setCharacterSize(36); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::Yellow);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text.setOrigin(-25, -25);

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(text);

		window.display();
	}
}

static void demo_shapes() {

	sf::CircleShape shape(50.f);

	// set the shape color to green
	shape.setFillColor(sf::Color(100, 250, 50));

	// set a 10-pixel wide orange outline
	shape.setOutlineThickness(10.f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setOrigin(-25, -25);

	// define a 120x50 rectangle
	sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));

	// change the size to 400x100
	rectangle.setSize(sf::Vector2f(400.f, 100.f));
	rectangle.setFillColor(sf::Color(10, 250, 50));
	rectangle.setOrigin(-300, -10);

	// define a triangle
	sf::CircleShape triangle(80.f, 3);
	triangle.setFillColor(sf::Color(10, 20, 50));
	triangle.setOrigin(-300, -150);

	// define a square
	sf::CircleShape square(80.f, 4);
	square.setFillColor(sf::Color(100, 20, 0));
	square.setOrigin(-300, -300);

	// define an octagon
	sf::CircleShape octagon(80.f, 8);
	octagon.setFillColor(sf::Color(100, 0, 0));
	octagon.setOrigin(-500, -300);

	// create an empty shape
	sf::ConvexShape convex;

	// resize it to 5 points
	convex.setPointCount(5);

	// define the points
	convex.setPoint(0, sf::Vector2f(0.f, 0.f));
	convex.setPoint(1, sf::Vector2f(150.f, 10.f));
	convex.setPoint(2, sf::Vector2f(120.f, 90.f));
	convex.setPoint(3, sf::Vector2f(30.f, 100.f));
	convex.setPoint(4, sf::Vector2f(0.f, 50.f));

	convex.setFillColor(sf::Color(100, 0, 0));
	convex.setOrigin(-25, -300);

	sf::RectangleShape line(sf::Vector2f(150.f, 5.f));
	line.rotate(45.f);

	//// map a 100x100 textured rectangle to the shape
	//shape.setTexture(&texture); // texture is a sf::Texture
	//shape.setTextureRect(sf::IntRect(10, 10, 100, 100));


	//sf::RenderWindow window(sf::VideoMode(800, 600), "My window",sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(400, 400), "My window");

	while (window.isOpen())
	{
		bool check = false;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				check = true;
				break;
			}
		}

		if (check) break;

		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(shape);
		window.draw(rectangle);
		window.draw(square);
		window.draw(triangle);
		window.draw(octagon);
		window.draw(convex);
		window.draw(line);

		window.display();
	}
}
