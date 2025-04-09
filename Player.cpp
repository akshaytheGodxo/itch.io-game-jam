#include "Player.h"
#include <iostream>
#include "DEFINITIONS.h"
#include <cmath>
Player::Player(char currentState) : frameHeight(128), frameWidth(128), character_position_x(220), character_position_y(500) { 
	if (!idleTexture.loadFromFile(FIGHTER_IDLE)) {
		throw std::runtime_error("Failed to load sprite sheet");
	}

	if (!walkTexture.loadFromFile(FIGHTER_WALK)) {
		throw std::runtime_error("Failed to load sprite sheet");
	}

	if (!jumpTexture.loadFromFile(FIGHTER_JUMP)) {
		throw std::runtime_error("Failed to load sprite sheet");
	}

	if (!fightTexture[0].loadFromFile(FIGHTER_ATTACK_1) || !fightTexture[1].loadFromFile(FIGHTER_ATTACK_2) || !fightTexture[2].loadFromFile(FIGHTER_ATTACK_3)) {
		throw std::runtime_error("Failed to load sprite sheet");
	}

	if (!blockTexture.loadFromFile(FIGHTER_SHIELD)) {
		throw std::runtime_error("Failed to load sprite sheet");
	}

	sprite.setTexture(idleTexture);
	sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	sprite.setOrigin(frameWidth / 2, frameHeight / 2);
	sprite.setPosition(character_position_x, character_position_y);

	border.setSize(sf::Vector2f(frameWidth, frameHeight)); 
	border.setFillColor(sf::Color::Transparent); 
	border.setOutlineColor(sf::Color::Red);      
	border.setOutlineThickness(2.0f);            
}

void Player::handleWalk(char characterState) {
	int row = 0; 
	if (clock.getElapsedTime().asSeconds() > frameDuration) {
		if (characterState == static_cast<char>('d')) {
			character_position_x += 20;
			sprite.setScale(1, 1);
		}
		if (characterState == static_cast<char>('a')) {
			character_position_x -= 20;
			sprite.setScale(-1, 1);
		}


		currentFrame = (currentFrame + 1) % numRunFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
		sprite.setPosition(character_position_x, character_position_y);
		clock.restart();
	}
}



void Player::handleIdle() {
	int row = 0;
	if (clock.getElapsedTime().asSeconds() > frameDuration) {
		currentFrame = (currentFrame + 1) % numIdleFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
		clock.restart();
	}
}


void Player::handleAttack() {
	int row = 0;
	if (clock.getElapsedTime().asSeconds() > attackFrameDuration) {
		currentFrame = (currentFrame + 1) % numAttackFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
		clock.restart();
	}
}

void Player::handleComboAttack() {
	if (attackClock.getElapsedTime().asSeconds() > attackStageDuration) {
		attackStage = (attackStage + 1) % 3; 
		sprite.setTexture(fightTexture[attackStage]);
		currentFrame = 0;
		sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
		attackClock.restart();
	}

	if (clock.getElapsedTime().asSeconds() > frameDuration) {
		currentFrame = (currentFrame + 1) % numAttackFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
		clock.restart();
	}
}


void Player::handleBlock() {
	int row = 0;
	if (clock.getElapsedTime().asSeconds() > frameDuration) {
		currentFrame = (currentFrame + 1) % numBlockFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
		clock.restart();

	}
}

void Player::updateJump() {
	if (isJumping) {
		float gravity = 300.0f; 
		character_position_y += velocityY * deltaTime;
		velocityY += gravity * deltaTime; 

		sprite.setPosition(character_position_x, character_position_y);

		if (character_position_y >= 500) {
			isJumping = false;
			isGrounded = true;
			velocityY = 0; 
			character_position_y = 500;
			sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
		}
	}
}



void Player::handleJump() {
	if (isGrounded) {
		isJumping = true;
		isGrounded = false;
		velocityY = -220.0f; 
		clock.restart();

	}
	else {
		updateJump();
	}

}


void Player::update(char currentState) {
	if ((currentState == 'd' || currentState == 'a') && !isJumping) {
		sprite.setTexture(walkTexture);
		handleWalk(currentState);
	}

	else if (currentState == 'f') {
		isAttacking = true;
		handleComboAttack();
	}


	else if (currentState == 'b') {
		sprite.setTexture(blockTexture);
		handleBlock();
	}

	else if (currentState == 'w' && !jumpInitiated && isGrounded) {
		jumpInitiated = true;
		sprite.setTexture(jumpTexture);
		handleJump(); 
	}
	else if (isJumping) {
		sprite.setTexture(jumpTexture);
		updateJump(); 
	}
	else {
		sprite.setTexture(idleTexture);
		handleIdle();
	}

	if (currentState != 'w') {
		jumpInitiated = false;
	}

	

}


sf::Sprite& Player::getSprite() {
	return sprite;
}


void Player::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}