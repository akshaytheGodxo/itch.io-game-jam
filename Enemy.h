#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(char currentState);

    void update(char currentState);
    void draw(sf::RenderWindow& window);
    void handleIdle();
    void handleDead();
    void takeDamage(int amount);
    void displayMessage();
    int getHealth() const;

    sf::FloatRect getBounds() const;
    sf::Sprite& getSprite();
    bool isAlive = true;
private:

    sf::Texture enemyDeadTexture;
    sf::Texture enemyTexture[2];
    sf::Sprite enemySprite;
	sf::Font font;
    sf::Text message;
    float frameWidth = 128.f, frameHeight = 128.f;
    float enemy_position_x = 100.f, enemy_position_y = 500.f;

    int idleStage = 0;
    int currentFrame = 0;
    int numIdle1Frames = 4;
    int numDeathFrames = 5;
    float frameDuration = 0.5f;
    int enemyHealth = 1000;
    bool setMessage = false;
    
    sf::Clock clock;
};
