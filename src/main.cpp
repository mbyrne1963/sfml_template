#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

auto g_window_background = sf::Color::White ;
float g_move_increment = 10.0f ;

auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };

void reset_rectangle_origin(sf::RectangleShape *pShape);

void Move_Sub(float move_x, float move_y);


int main()
{
    sf::Vector2f Sub_Position;
    float mouse_x_position, mouse_y_position ;

    std::ofstream logfile;
    logfile.open("Submarine_Game.log");
    logfile << "Started Game\n";


    window.setFramerateLimit(144);
    window.clear(g_window_background);


    // launch the rendering thread

    sf::Texture submarine_imageR;
    bool file_loaded = submarine_imageR.loadFromFile("../images/SubmarineR.jpg");
    if (!file_loaded) {
        logfile << "Failed to find SubmarineR.jpg file \n";
    }

   sf::Sprite Sub_Sprite(submarine_imageR);
   Sub_Sprite.setPosition( 20.0, 20.0);
   //Sub_Sprite.scale(0.07, 0.07);

   // get details of the rectangle that contains the sprite and then move the origin to the middle of the sprite
    sf::FloatRect Sprite_Size;
    Sprite_Size = Sub_Sprite.getLocalBounds();
    Sub_Sprite.setOrigin( Sprite_Size.width / 2 , Sprite_Size.height / 2);

    window.draw(Sub_Sprite);
    window.display();

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

            }
            case sf::Event::MouseButtonPressed:         // move the sub to the mouse position
            {

            }

            // use the scroll wheel to move the sub up and down.
            case sf::Event::MouseWheelScrolled :{
                Sub_Position = Sub_Sprite.getPosition();
                Sub_Sprite.setPosition( Sub_Position.x  , Sub_Position.y + event.mouseWheelScroll.delta);
                window.clear(g_window_background);
                window.draw(Sub_Sprite);
                window.display();
                break;
            }
            case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        Sub_Position= Sub_Sprite.getPosition();
                        Sub_Sprite.setPosition( Sub_Position.x - g_move_increment, Sub_Position.y );
                        window.clear(g_window_background);
                        window.draw(Sub_Sprite);
                        window.display();
                        break;  // move left...
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        Sub_Position= Sub_Sprite.getPosition();
                        Sub_Sprite.setPosition( Sub_Position.x + g_move_increment, Sub_Position.y  );
                        window.clear(g_window_background);
                        window.draw(Sub_Sprite);
                        window.display();
                        // move right...
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        Sub_Position = Sub_Sprite.getPosition();
                        Sub_Sprite.setPosition(Sub_Position.x, Sub_Position.y - g_move_increment);
                        window.clear(g_window_background);
                        window.draw(Sub_Sprite);
                        window.display();
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        {
                            Sub_Position= Sub_Sprite.getPosition();
                            Sub_Sprite.setPosition( Sub_Position.x, Sub_Position.y +g_move_increment  );
                            window.clear(g_window_background);
                            window.draw(Sub_Sprite);
                            window.display();
                        }


        }

    }
}
