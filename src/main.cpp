#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>




int main()
{

    float x_position , y_position;

    std::ofstream logfile;
    logfile.open("Submarine_Game.log");
    logfile << "Started Game\n";


    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    sf::Texture submarine_image;
    bool file_loaded = submarine_image.loadFromFile("../images/Submarine.jpg");
    if (!file_loaded) {
        logfile << "Failed to find Submarine.jpg file \n";
    }

  sf::Sprite Sub_Sprite(submarine_image);
    Sub_Sprite.setPosition( 20.0, 20.0);
    Sub_Sprite.scale(0.5, 0.5);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
            switch (event.type) {
            case sf::Event::Closed :
            {
                logfile << "Ended Game\n";
                logfile.close();
                window.close();
            }
            case sf::Event::MouseMoved:
            {
                x_position  = event.mouseMove.x;
                y_position = event.mouseMove.y;
                window.clear();
                Sub_Sprite.setPosition( x_position, y_position);
                window.draw(Sub_Sprite);
                window.display();
                break;
            }
            case sf::Event::MouseWheelScrolled :{
                x_position = x_position + event.mouseWheelScroll.delta;
                y_position = y_position + event.mouseWheelScroll.delta;

                window.clear();
                Sub_Sprite.setPosition( x_position, y_position);
                window.draw(Sub_Sprite);
                window.display();
                break;
            }

        }

    }
}