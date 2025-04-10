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

	if (!font.loadFromFile(DISPLAY_FONT)) {
		throw std::runtime_error("Failed to load font");
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



void Player::drawHealthBar(sf::RenderWindow& window) {
	float barWidth = 100.0f;
	float barHeight = 10.0f;
	float healthPercentage = static_cast<float>(currentHealth) / maxHealth;

	sf::RectangleShape backgroundBar(sf::Vector2f(barWidth, barHeight));
	backgroundBar.setFillColor(sf::Color::Red); // Red background
	backgroundBar.setPosition(20, 20);

	sf::RectangleShape healthBar(sf::Vector2f(barWidth * healthPercentage, barHeight));
	healthBar.setFillColor(sf::Color::Green); // Green health
	healthBar.setPosition(20, 20);

	window.draw(backgroundBar);
	window.draw(healthBar);
}


void Player::addItem(const Item& item) {
	for (auto& i : inventory) {
		if (i.name == item.name) {
			i.quantity++;
			return;
		}
	}
	inventory.push_back(item);
}

void Player::removeItem(const std::string& itemName) {
	for (auto it = inventory.begin(); it != inventory.end(); ++it) {
		if (it->name == itemName) {
			if (--(it->quantity) <= 0) {
				inventory.erase(it);
			}
			return;
		}
	}
}

void Player::toggleInventory() {
	showInventory = !showInventory;
}

const std::vector<Item>& Player::getInventory() const {
	return inventory;
}


sf::Sprite& Player::getSprite() {
	return sprite;
}


void Player::draw(sf::RenderWindow& window) {
	window.draw(sprite);

	drawHealthBar(window);


	// inventory toggle
	if (showInventory) {
		sf::RectangleShape invBox;
		invBox.setSize(sf::Vector2f(400, 300));
		invBox.setFillColor(sf::Color(50, 50, 50, 200));
		invBox.setPosition(50, 50);
		window.draw(invBox);

		sf::Text itemText;
		itemText.setFont(font); // already loaded
		itemText.setCharacterSize(18);
		itemText.setFillColor(sf::Color::White);

		int offset = 0;
		for (const auto& item : inventory) {
			itemText.setString(item.name + " x" + std::to_string(item.quantity));
			itemText.setPosition(60, 60 + offset);
			window.draw(itemText);
			offset += 30;
		}
	}

}