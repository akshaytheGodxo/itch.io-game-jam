#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
class Player {
public:
    Player(char currentState);
    void update(char currentState);
    void draw(sf::RenderWindow& window);
    void handleWalk(char characterState);
    void handleIdle();
    void handleJump();

    void updateJump();
    void setDeltaTime(float dt) { deltaTime = dt; }


    void handleAttack();
    void handleBlock();
    void handleComboAttack();
    void drawHealthBar(sf::RenderWindow& window);


    // inventory management

	void addItem(const Item& item);
	void removeItem(const std::string& itemName);
    void toggleInventory();
    const std::vector<Item>& getInventory() const;

    sf::Sprite& getSprite();
    bool isGrounded = true;

    bool isAttacking = false;

private:
    sf::Font font;
    sf::Texture walkTexture;
    sf::Texture idleTexture;
    sf::Texture jumpTexture;
    sf::Texture fightTexture[3];
	sf::Texture blockTexture;
    float character_position_x;
    float character_position_y;

    sf::Sprite sprite;
    sf::Clock clock;
    sf::Clock attackClock;

    sf::RectangleShape border;

    float attackStageDuration = 0.2f;
    int attackStage = 0;
    int frameWidth = 128;  
    int frameHeight = 128; 
    int currentFrame = 0;
    float frameDuration = 0.1f; 
    int numRunFrames = 6;  
    int numIdleFrames = 6; 
    int numJumpFrames = 10;
    int numAttackFrames = 4;
    int numBlockFrames = 2;
    float gravity = 9.8f;
    float theta = 45.0f;
    bool isJumping = false;
	float deltaTime = 0.2f;
	float velocityY = 0.0f; 
    bool jumpInitiated = false;
    int maxHealth = 100;
    int currentHealth = 80;
    int attackFrameDuration = 0.5f;


    // inventory

    std::vector<Item> inventory;
    bool showInventory = false;
};
