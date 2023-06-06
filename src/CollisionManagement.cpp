//
// Created by Mick Byrne on 14/05/2023.
//

#include "CollisionManagement.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <windef.h>

using namespace std;

struct Circle {
    int x, y;
    int radius;
};

// Define a triangle struct
struct Triangle {
    int x1, y1, x2, y2, x3, y3;
};

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


// Function to check if a circle and a rectangle intersect
bool checkCollisionCircleTriangle(Circle circle, sf::Rect<float> rect) {
    // Find the closest point to the circle within the rectangle
    sf::Vector2f rectanglePos;
    rectanglePos = rect.getPosition();
   // int closestX = max(rectanglePos.x, std::min(circle.x, rectanglePos.x  + rect.width));
   // int closestY = max(rect.height, min(circle.y, rectanglePos.y + rect.height));

    // Calculate the distance between the circle's center and the closest point
    //int distanceX = circle.x - closestX;
    //int distanceY = circle.y - closestY;
    //int distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    // If the distance is less than the circle's radius squared, they intersect
    return 0;
    //distanceSquared <= (circle.radius * circle.radius);
}



// Function to calculate area of a triangle
double triangleArea(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2))/2.0);
};

// Function to check if a point is inside a triangle
bool pointInsideTriangle(int x, int y, Triangle tri) {
    double area = triangleArea(tri.x1, tri.y1, tri.x2, tri.y2, tri.x3, tri.y3);
    double area1 = triangleArea(x, y, tri.x2, tri.y2, tri.x3, tri.y3);
    double area2 = triangleArea(tri.x1, tri.y1, x, y, tri.x3, tri.y3);
    double area3 = triangleArea(tri.x1, tri.y1, tri.x2, tri.y2, x, y);
    return (area == area1 + area2 + area3);
}

// Function to check if a point is inside a circle
bool pointInsideCircle(int x, int y, Circle c) {
    int dx = x - c.x;
    int dy = y - c.y;
    int distSquared = dx * dx + dy * dy;
    return (distSquared <= c.radius * c.radius);
}

// Function to check if a circle and a triangle intersect
bool checkCircleTriangleCollision(Circle c, Triangle tri) {
    // Check if any of the vertices of triangle are inside the circle
    if (pointInsideCircle(tri.x1, tri.y1, c) ||
        pointInsideCircle(tri.x2, tri.y2, c) ||
        pointInsideCircle(tri.x3, tri.y3, c)) {
        return true;
    }

    // Check if any of the edges of triangle intersect with the circle
    if (pointInsideTriangle(c.x, c.y, tri)) {
        return true;
    }

    // Check if the center of the circle is inside the triangle
    double area = triangleArea(tri.x1, tri.y1, tri.x2, tri.y2, tri.x3, tri.y3);
    double area1 = triangleArea(c.x, c.y, tri.x2, tri.y2, tri.x3, tri.y3);
    double area2 = triangleArea(tri.x1, tri.y1, c.x, c.y, tri.x3, tri.y3);
    double area3 = triangleArea(tri.x1, tri.y1, tri.x2, tri.y2, c.x, c.y);
    return (area == area1 + area2 + area3);
}
