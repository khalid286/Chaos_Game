//Michael Sundukos & Mohammad Khalid Daneshwar
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

// Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    // Load font once before the game loop
    sf::Font font;
    if (!font.loadFromFile("Font.ttf"))
    {
        cout << "Unable to open file" << endl;
    }

    // Create the text object once
    sf::Text text;
    text.setFont(font);
    text.setString("Please click on any three points on the screen!\nAfter three click, click on a fourth point to start!");
    text.setCharacterSize(30);
    text.setFillColor(Color::White);
    text.setPosition(50, 50); // Adjust position as needed

    // Variables
    vector<Vector2f> vertices;
    vector<Vector2f> points;
    vector<Vector2f> mirroredVertices;
    vector<Vector2f> mirroredPoints;

    int x_axis = vm.width / 2;
    int distance = 0;

    // Game loop
    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (vertices.size() < 3)
                    {
                        Vector2f clicked(event.mouseButton.x, event.mouseButton.y);
                        vertices.push_back(clicked);

                        // Mirror logic
                        if (clicked.x > x_axis)
                            distance = clicked.x - x_axis;
                        else
                            distance = x_axis - clicked.x;

                        float mirroredX = clicked.x > x_axis ? x_axis - distance : x_axis + distance;
                        mirroredVertices.push_back(Vector2f(mirroredX, clicked.y));
                    }
                    else if (points.empty())
                    {
                        Vector2f clicked(event.mouseButton.x, event.mouseButton.y);
                        points.push_back(clicked);

                        // Mirror logic
                        if (clicked.x > x_axis)
                            distance = clicked.x - x_axis;
                        else
                            distance = x_axis - clicked.x;

                        float mirroredX = clicked.x > x_axis ? x_axis - distance : x_axis + distance;
                        mirroredPoints.push_back(Vector2f(mirroredX, clicked.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Update Points - Original
        if (!points.empty())
        {
            for (int i = 0; i < 100; i++)
            {
                int randIndex = rand() % vertices.size();
                Vector2f randVertex = vertices[randIndex];
                Vector2f lastPoint = points.back();

                Vector2f midpoint((randVertex.x + lastPoint.x) / 2, (randVertex.y + lastPoint.y) / 2);
                points.push_back(midpoint);
            }
        }

        // Update Points - Mirrored
        if (!mirroredPoints.empty())
        {
            for (int i = 0; i < 100; i++)
            {
                int randIndex = rand() % mirroredVertices.size();
                Vector2f randVertex = mirroredVertices[randIndex];
                Vector2f lastPoint = mirroredPoints.back();

                Vector2f midpoint((randVertex.x + lastPoint.x) / 2, (randVertex.y + lastPoint.y) / 2);
                mirroredPoints.push_back(midpoint);
            }
        }

        // Draw
        window.clear();

        // Always show prompt at top
        window.draw(text);

        // Draw Vertices
        for (const auto& vertex : vertices)
        {
            CircleShape circ(5, 30);
            circ.setPosition(vertex);
            circ.setFillColor(Color::White);
            window.draw(circ);
        }

        // Draw Mirrored Vertices
        for (const auto& vertex : mirroredVertices)
        {
            CircleShape circ(5, 30);
            circ.setPosition(vertex);
            circ.setFillColor(Color::Red);
            window.draw(circ);
        }

        // Draw Points
        for (const auto& point : points)
        {
            CircleShape circ(5, 30);
            circ.setPosition(point);
            circ.setFillColor(Color::White);
            window.draw(circ);
        }

        // Draw Mirrored Points
        for (const auto& point : mirroredPoints)
        {
            CircleShape circ(5, 30);
            circ.setPosition(point);
            circ.setFillColor(Color::Red);
            window.draw(circ);
        }

        window.display();
    }

    return 0;
}
