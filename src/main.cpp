#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Globals.cpp"
#include "SubmarineClass.cpp"

//
// Created by mbyrn on 03/06/2023.
//

#include <SFML/Graphics.hpp>
#include <unistd.h>


auto window = sf::RenderWindow{{1920u, 1080u}, "Submarine Game"};

sf::Color g_window_background = sf::Color::White ;

int main() {

    std::ofstream logfile;
    logfile.open("Submarine_Game.log");
    logfile << "Started Game\n";

    window.setFramerateLimit(144);
    window.clear(g_window_background);

    Submarine_UK_Vanguard_Class UKSubmarine ;
    sf::Sprite UKSubmarineSprite ;
    sf::Texture UKFlag;
    UKFlag.loadFromFile("../images/UK Flag.jpg");
    UKSubmarineSprite.setTexture(UKFlag);
    sf::FloatRect Sprite_Size;
    Sprite_Size = UKSubmarineSprite.getLocalBounds();
    UKSubmarineSprite.setOrigin(Sprite_Size.width / 2, Sprite_Size.height / 2);
    UKSubmarine.setRandomDestination();
    UKSubmarine.setCurrentSpeedKnots(1.0f);

    sf::Font StdFont;
    StdFont.loadFromFile("../fonts/arial.ttf");

    sf::Text UKSubmarineText;
    UKSubmarineText.setFont(StdFont);
    UKSubmarineText.setCharacterSize(6);
    sf::Vector2f Text_Position;
    Text_Position = UKSubmarine.getPosition();
    Text_Position.x += Sprite_Size.height / 2 + 2;
    UKSubmarineText.setPosition(UKSubmarine.getPosition());
    UKSubmarineText.setString("UK Submarine Speed");

    sf::CircleShape UKSubmarineSonar;
    UKSubmarineSonar.setRadius( UKSubmarine.getCurrentSonarRangeKms());

    UKSubmarineSonar.setPosition(UKSubmarine.getPosition());
    UKSubmarineSonar.setOrigin(UKSubmarineSonar.getRadius(), UKSubmarineSonar.getRadius());
    UKSubmarineSonar.setOutlineThickness(3.0f);
    UKSubmarineSonar.setOutlineColor(sf::Color::Green);         // green nothing seen

    Submarine_China_091 EnemySubmarine ;
    sf::Sprite EnemySubmarineSprite ;
    sf::Texture EnemyFlag;
    sf::Vector2f Sub_Position;

    EnemyFlag.loadFromFile("../images/China Flag.jpg");
    EnemySubmarineSprite.setTexture(EnemyFlag);
    Sprite_Size = EnemySubmarineSprite.getLocalBounds();
    EnemySubmarineSprite.setOrigin(Sprite_Size.width / 2, Sprite_Size.height / 2);

    Sub_Position.x = 100.0f;
    Sub_Position.y = 500.0f;

    EnemySubmarine.setPosition( Sub_Position);
    EnemySubmarineSprite.setPosition(EnemySubmarine.getPosition());

   // window.draw(Submarine1);
    window.display();

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);)
            switch (event.type) {
                case sf::Event::Closed : {
                    logfile << "Ended Game\n";
                    logfile.close();
                    window.close();
                }
                case sf::Event::MouseMoved: {

                }
                case sf::Event::MouseButtonPressed:         // move the sub to the mouse position
                {

                }

                    // use the scroll wheel to move the sub up and down.
                case sf::Event::MouseWheelScrolled : {
                    UKSubmarine.Advance_Position(0.0f,event.mouseWheelScroll.delta );
                    break;
                }
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        UKSubmarine.increaseSpeedKnots(-1.0f);
                        break;  // move left...
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        UKSubmarine.increaseSpeedKnots(1.0f);
                        // move right...
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        UKSubmarine.setDiveAngle(-10.0f);
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        UKSubmarine.setDiveAngle(10.0f);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){
                        UKSubmarine.setRandomDestination();
                    }

                case sf::Event::Resized:
                    break;
                case sf::Event::LostFocus:
                    break;
                case sf::Event::GainedFocus:
                    break;
                case sf::Event::TextEntered:
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseWheelMoved:
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseEntered:
                    break;
                case sf::Event::MouseLeft:

                    break;
                case sf::Event::JoystickButtonPressed:
                    break;
                case sf::Event::JoystickButtonReleased:
                    break;
                case sf::Event::JoystickMoved:
                    break;
                case sf::Event::JoystickConnected:
                    break;
                case sf::Event::JoystickDisconnected:
                    break;
                case sf::Event::TouchBegan:

                    break;

                case sf::Event::TouchMoved:
                    break;
                case sf::Event::TouchEnded:
                    break;
                case sf::Event::SensorChanged:
                    break;
                case sf::Event::Count:
                    break;
            }

        UKSubmarine.Advance_to_Destination();
        UKSubmarineSprite.setPosition( UKSubmarine.getPosition());

        //render
        window.clear(g_window_background);
        UKSubmarineSonar.setPosition(UKSubmarine.getPosition());
        UKSubmarineSonar.setRadius(UKSubmarine.getCurrentSonarRangeKms());

        window.draw(UKSubmarineSonar);
        window.draw(UKSubmarineSprite);
        window.draw(UKSubmarineText);
        window.draw(EnemySubmarineSprite);
        window.display();
        sleep(1);
    }
}




