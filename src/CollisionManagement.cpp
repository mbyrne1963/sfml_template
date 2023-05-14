//
// Created by mbyrn on 14/05/2023.
//

#include "CollisionManagement.h"
#include <SFML/Graphics.hpp>


// check to see if two sprites overlap / collide - using a pointer to two sprites as parameters
bool SpritesCollide(sf::Sprite *r1, sf::Sprite *r2) {
    sf::Vector2f Sub1_Position, Sub2_Position;
    sf::Rect<float> Sub1_Size, Sub2_Size;
    Sub1_Position = r1->getPosition();
    Sub2_Position = r2->getPosition();

    Sub1_Size = r1->getGlobalBounds();
    Sub2_Size = r2->getGlobalBounds();

    if (Sub1_Position.x + Sub1_Size.width / 2 < Sub2_Position.x - Sub2_Size.width / 2) return false;
    if (Sub1_Position.x - Sub1_Size.width / 2 > Sub2_Position.x + Sub2_Size.width / 2) return false;
    if (Sub1_Position.y + Sub1_Size.height / 2 < Sub2_Position.y - Sub2_Size.height / 2) return false;
    if (Sub1_Position.y - Sub1_Size.height / 2 > Sub2_Position.y + Sub2_Size.height / 2) return false;
    return true;
};

