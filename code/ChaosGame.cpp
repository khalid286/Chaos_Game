// Include important C++ libraries here
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
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	int x_axis = vm.width / 2;
	int distance = 0;
	vector<Vector2f> mirroredVertices;
	vector<Vector2f> mirroredPoints;
	//vector<Vector2f> inverseVertices;
	//vector<Vector2f> inversePoints;
	

	while (window.isOpen())
	{
		sf::Font font;
		if (!font.loadFromFile("Font.ttf"))
		{
			cout << "Unable to open file" << endl;
		}

		sf::Text text;
		text.setFont(font);
		text.setString("Please click on any three points on the screen!");
		text.setCharacterSize(30);
		text.setFillColor(Color::White);


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
				//std::cout << "Inverse x: " << event.mouseButton.y << std::endl;
				//std::cout << "Inverse y: " << event.mouseButton.x << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices.at(i).x > x_axis)
					{
						if (i != 2)
						{
							distance = vertices.at(i).x - x_axis;
							mirroredVertices.push_back(Vector2f(x_axis - distance, vertices.at(i).y));
						}
						else
						{
							distance = vertices.at(i).x - x_axis;
							mirroredVertices.push_back(Vector2f(x_axis - distance, vertices.at(i).y));
						}
					}
					else if (vertices.at(i).x < x_axis)
					{
						if (i != 2)
						{
							distance = x_axis - vertices.at(i).x;
							mirroredVertices.push_back(Vector2f(x_axis + distance, vertices.at(i).y));
						}
						else
						{
							distance = x_axis - vertices.at(i).x;
							mirroredVertices.push_back(Vector2f(x_axis + distance, vertices.at(i).y));
						}
					}
					
				}
				
				//inverseVertices.push_back(Vector2f(event.mouseButton.y, event.mouseButton.x));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					for (int i = 0; i < points.size(); i++)
					{
						if (points.at(i).x > x_axis)
						{
							distance = points.at(i).x - x_axis;
							mirroredPoints.push_back(Vector2f(distance, points.at(i).y));
						}
						else if (points.at(i).x < x_axis)
						{
							distance = x_axis - points.at(i).x;
							mirroredPoints.push_back(Vector2f(x_axis + distance , points.at(i).y));
						}

					}
					
					//inversePoints.push_back(Vector2f(event.mouseButton.y, event.mouseButton.x));
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
	
		if(points.size() > 0)
		{
			int framerate = 100;
			for (int i = 0; i < framerate; i++)
			{
				int temp = rand() % vertices.size();

				Vector2f randomVertex = vertices[temp];
				Vector2f lastPoint = points.back();

				Vector2f midpoint((randomVertex.x + lastPoint.x) / 2, (randomVertex.y + lastPoint.y) / 2);
				points.push_back(midpoint);
				
			
			}
			///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
		}

		if (mirroredPoints.size() > 0)
		{
			int FR = 100;
			for (int i = 0; i < FR; i++)
			{
				int t = rand() % mirroredVertices.size();

				Vector2f randVertex = mirroredVertices[t];
				Vector2f lastPoint = mirroredPoints.back();

				Vector2f MP((randVertex.x + lastPoint.x) / 2, (randVertex.y + lastPoint.y) / 2);
				mirroredPoints.push_back(MP);

			}
		}
		

	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(text);
		for(int i = 0; i < vertices.size(); i++)
		{
		    CircleShape circ(5,30);
		    circ.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    circ.setFillColor(Color::White);
		    window.draw(circ);
			
		for (int i = 0; i < mirroredVertices.size(); i++)
		{
			CircleShape circ(5, 30);
			circ.setPosition(Vector2f(mirroredVertices[i].x, mirroredVertices[i].y));
			circ.setFillColor(Color::Red);
			window.draw(circ);

		}
		

		for (int i = 0; i < points.size(); i++)
		{
			CircleShape circ(5, 30);
			circ.setPosition(Vector2f(points[i].x, points[i].y));
			circ.setFillColor(Color::White);
			window.draw(circ);

		}
		for (int i = 0; i < mirroredPoints.size(); i++)
		{
			CircleShape circ(5, 30);
			circ.setPosition(Vector2f(mirroredPoints[i].x, mirroredPoints[i].y));
			circ.setFillColor(Color::Red);
			window.draw(circ);

		}
		
		///TODO:  Draw points
		window.display();
		}
	}
}
