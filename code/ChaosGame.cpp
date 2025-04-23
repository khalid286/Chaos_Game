#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	// Seed the random number generator once
	srand(static_cast<unsigned>(time(0)));

	// Load font once (moved out of loop)
	sf::Font font;
	if (!font.loadFromFile("Font.ttf"))
	{
		cout << "Unable to open the font file!" << endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("Click on three different points with your mouse");
	text.setCharacterSize(55);
	text.setFillColor(sf::Color::White);

	vector<Vector2f> vertices;
	vector<Vector2f> points;
	bool gameStarted = false;
	bool showText = true; // New flag to control text visibility

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);

					if (vertices.size() < 3)
					{
						vertices.push_back(clickPos);
						showText = false; // Hide the text after the first click
					}
					else if (points.empty())
					{
						///fourth click
						points.push_back(clickPos);
						gameStarted = true;
						///push back to points vector
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update
		****************************************
		*/

		if (gameStarted && vertices.size() == 3 && !points.empty())
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.

			int pointsPerFrame = 100;
			for (int i = 0; i < pointsPerFrame; ++i)
			{
				int temp = rand() % vertices.size();
				Vector2f randomVertex = vertices[temp];
				Vector2f lastPoint = points.back();

				Vector2f midPoint(
					(randomVertex.x + lastPoint.x) / 2.0f,
					(randomVertex.y + lastPoint.y) / 2.0f
				);

				// Ensure the point is on-screen before pushing it
				if (midPoint.x >= 0 && midPoint.x <= 1920 &&
					midPoint.y >= 0 && midPoint.y <= 1080)
				{
					points.push_back(midPoint);
				}
			}
		}

		/*
		****************************************
		Draw
		****************************************
		*/

		window.clear();

		if (showText)
		{
			window.draw(text);
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			CircleShape circ(5, 30);
			circ.setOrigin(5, 5);
			circ.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			circ.setFillColor(Color::White);
			window.draw(circ);
		}

		///TODO:  Draw points
		for (int i =1; i < points.size(); i++)
		{
			CircleShape circ(2, 30);
			circ.setOrigin(2, 2);
			circ.setPosition(Vector2f(points[i].x, points[i].y));
			circ.setFillColor(Color::White);
			window.draw(circ);
		}

		window.display();
	}
}
