//
// Created by mbyrn on 22/05/2023.

#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include <cmath>
#include "Globals.cpp"
#include <random>

class Submarine_UK_Vanguard_Class {
public:

    Submarine_UK_Vanguard_Class() {
        Current_Depth = 0;
        SubType = SUB_TYPE_UK_VANGUARD;
        Nationality_Code = 0;
        Position.x = 1.0f;
        Position.y = 1.0f;
    };

    Submarine_UK_Vanguard_Class(float p_x, float p_y, float p_depth) : Current_Depth(p_depth) {
        SubType = SUB_TYPE_UK_VANGUARD;
        Position.x = p_x;
        Position.y = p_y;
    };


    const sf::Vector2f &getPosition() const {
        return Position;
    }

    void Advance_Position(float p_x, float p_y) {
        Position.x += p_x;
        Position.y += p_y;

    }

    void Advance_to_Destination() {
        int deltaY = Destination.y - Position.y;
        int deltaX = Destination.x - Position.x;

        if (Destination.x != 0 && Destination.y != 0)  // using the home corner as no destination set
        {
            if (deltaX != 0 || deltaY != 0) {
                float angleInRadians = atan2(deltaY, deltaX);
                Position.x = Position.x + cos(angleInRadians) * Current_Speed_Knots;
                Position.y = Position.y + sin(angleInRadians) * Current_Speed_Knots;
                float angleInDegrees = angleInRadians * 180 / 3.1415 * -1;

                // if we're at the edge of the screen (for any reason) then turn around
                if ((Position.x < 0 || Position.x > 1980 - 100) || (Position.y < 0 || Position.y > 1080 - 100)) {
                    Destination.x = 0;
                    Destination.y = 0;
                }
                setCurrentDirection(angleInDegrees * -1);
            }
        }
    };


private:
    int generateRandomNumber(int min, int max) {
        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 eng(rd()); // Seed the generator
        std::uniform_int_distribution<int> distr(min, max); // Define the range

        return distr(eng);  // Generate and return a random number
    }

public:

    void setPosition(const sf::Vector2f &position) {
        Position = position;
    }

    const sf::Vector2f &getDestination() const {
        return Destination;
    }

    void setDestination(const sf::Vector2f &destination) {
        Destination = destination;
    }

    void setRandomDestination() {
        Destination.x = generateRandomNumber(1, 1920);           // avoid the home corner and within the screen width
        Destination.y = generateRandomNumber(1, 1080);           // avoide the home corner and withing the screen height
    }

    float getCurrentDirection() const {
        return Current_Direction;
    }

    void setCurrentDirection(float currentDirection) {
        Current_Direction = currentDirection;
    }

    float getCurrentDepth() const {
        return Current_Depth;
    }

    void setCurrentDepth(float currentDepth) {
        Current_Depth = currentDepth;
    }

    float getCurrentSpeedKnots() const {
        return Current_Speed_Knots;
    }

    void increaseSpeedKnots(float p_increaseKnots) {
        setCurrentSpeedKnots(getCurrentSpeedKnots() + p_increaseKnots);
    }

    void setCurrentSpeedKnots(float p_currentSpeedKnots) {
        if (p_currentSpeedKnots < Max_Speed_Knots)
            Current_Speed_Knots = p_currentSpeedKnots;

        Current_Noise_Decibels = Max_Noise_Decibels * (pow(Current_Speed_Knots, 2) / pow(Max_Speed_Knots, 2));

        if (Active_Sonar)
            Current_Sonar_Range_Kms = Max_Active_Sonar_Range_Kms;
        else
            Current_Sonar_Range_Kms = Max_Passive_Sonar_Range_Kms * ((Max_Speed_Knots - Current_Speed_Knots) / Max_Speed_Knots);
    }

    float getCurrentNoiseDecibels() const {
        return Current_Noise_Decibels;
    }

    bool isActiveSonar() const {
        return Active_Sonar;
    }

    void setActiveSonar(bool activeSonar) {
        Active_Sonar = activeSonar;
    }

    float getCurrentSonarRangeKms() {
        if (isActiveSonar()) { Current_Sonar_Range_Kms = Max_Active_Sonar_Range_Kms; }
        else { Current_Sonar_Range_Kms = Max_Passive_Sonar_Range_Kms; }

        return Current_Sonar_Range_Kms;
    }

    float getDiveAngle() const {
        return Dive_Angle;
    }

    void setDiveAngle(float p_diveAngle) {
        if (p_diveAngle > Max_Dive_Angle) {
            p_diveAngle = Max_Dive_Angle;
        };
        if (p_diveAngle < Max_Dive_Angle * -1.0f) {
            p_diveAngle = Max_Dive_Angle * -1.0f;
        };
        Dive_Angle = p_diveAngle;
    };


private:
    float Current_Direction;
    float Current_Depth;
    float Current_Speed_Knots;
    float Current_Noise_Decibels;
    bool Active_Sonar = false;
    float Current_Sonar_Range_Kms;
    float Dive_Angle;
    int SubType;
    int Nationality_Code = COUNTRY_UK;
    bool Friend = true;
    int Max_Number = 4;
    int Displacement_Tonnes = 15900;
    float Length_Meters = 149.9f;
    float Beam_Meters = 12.8f;
    float Draught_Meters = 12.0f;
    bool Nuclear_Armed = true;
    bool Nuclear_Fuelled = true;
    float Max_Depth_Meters = 100.0f;
    float Max_Speed_Knots = 25.0f;
    float Max_Noise_Decibels = 80.0f;
    float Max_Passive_Sonar_Range_Kms = 100.0f;
    float Max_Active_Sonar_Range_Kms = 600.0f;
    int Complement_Staff = 135;
    int Age_Years = 24;
    float Max_Dive_Angle = 45.0f;
    sf::Vector2f Position;
    sf::Vector2f Destination = {100.0f, 100.0f};
};

class Submarine_China_091 : public Submarine_UK_Vanguard_Class {
    int Nationality_Code = COUNTRY_CHINA;
    bool Friend = false;
    int Max_Number = 3;
    int Displacement_Tonnes = 5500;
    float Length_Meters = 98.0f;
    float Beam_Meters = 10.0f;
    float Draught_Meters = 7.4f;
    bool Nuclear_Armed = false;
    bool Nuclear_Fuelled = true;
    float Max_Depth_Meters = 300.0f;
    float Max_Speed_Knots = 22.0f;
    float Max_Noise_Decibels = 120.0f;
    int Complement_Staff = 75;
    int Age_Years = 33;
};