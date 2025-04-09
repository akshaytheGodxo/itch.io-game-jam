#include "Enemy.h"
#include <stdexcept>
#include "DEFINITIONS.h"
#include <iostream>

Enemy::Enemy(char currentState) {
    if (!enemyTexture[0].loadFromFile(ENEMY_IDLE_1) || !enemyTexture[1].loadFromFile(ENEMY_IDLE_2)) {
        throw std::runtime_error("Failed to load sprite sheets");
    }

	if (!font.loadFromFile(DISPLAY_FONT)) {
		throw std::runtime_error("Failed to load font");
	}

    if (!enemyDeadTexture.loadFromFile(ENEMY_DEADTH)) {
        throw std::runtime_error("Failed to load sprite sheets");
    }

    enemySprite.setTexture(enemyTexture[idleStage]);
    enemySprite.setPosition(enemy_position_x, enemy_position_y);
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    enemySprite.setOrigin(frameWidth / 2, frameHeight / 2);
    enemySprite.setScale(1, 1);
}

void Enemy::handleIdle() {
    int row = 0;
    if (clock.getElapsedTime().asSeconds() > frameDuration) {
        idleStage = 1 - idleStage; // Toggle between 0 and 1
        enemySprite.setTexture(enemyTexture[idleStage]);

        currentFrame = (currentFrame + 1) % numIdle1Frames;
        enemySprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
        enemySprite.setPosition(enemy_position_x, enemy_position_y);

        clock.restart();
    }
}


void Enemy::handleDead() {
    int row = 0;
    if (clock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % numDeathFrames;
        enemySprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
        enemySprite.setPosition(enemy_position_x, enemy_position_y);
        clock.restart();
    }
}

void Enemy::displayMessage() {
    if (setMessage) {
		message.setFont(font);
		message.setString("Enemy defeated!");
		message.setCharacterSize(24);
		message.setFillColor(sf::Color::Red);
		message.setPosition(enemy_position_x - 50, enemy_position_y - 50); // Adjust position as needed		
    }
}
void Enemy::takeDamage(int amount) {
	enemyHealth -= amount;
    std::cout << enemyHealth << std::endl;
	if (enemyHealth <= 0) {
        enemyHealth = 0;
        setMessage = true;
	}
}

int Enemy::getHealth() const {
	return enemyHealth;
}

void Enemy::update(char currentState) {
    
    if (isAlive) {
        handleIdle();
    } 

    else if (!isAlive && currentState == static_cast<char>('k')){
		enemySprite.setTexture(enemyDeadTexture);
        handleDead();
    }
}

sf::FloatRect Enemy::getBounds() const {
    return enemySprite.getGlobalBounds();
}

sf::Sprite& Enemy::getSprite() {
    return enemySprite;
}

void Enemy::draw(sf::RenderWindow& window) {
    
    window.draw(enemySprite);

    if (setMessage) {
        window.draw(message);
    }
}
