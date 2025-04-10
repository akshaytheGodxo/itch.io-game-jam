#include "Game.h"
#include "DEFINITIONS.h"
#include <iostream>
Game::Game() : window(sf::VideoMode(1200, 675), "Classic"), player(characterState[0]), state(characterState[0], gameState[0]), enemy(characterState[0]) {

	if (!backgroundTexture.loadFromFile(MAIN_BACKGROUND)) {
		std::cout << "Failed to load background";
	}

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
}


void Game::run() {
	while (window.isOpen()) {
		float dt = dtClock.restart().asSeconds();
		player.setDeltaTime(dt);
		processEvents();
		update();
		render();
		checkCollision();
		handlePlayerAttack();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				std::cout << "Mouse clicked at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
				characterState[1] = 'f';
				setState();
			}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				characterState[1] = 'b';
				setState();

			}
		}

		else if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				characterState[1] = 'i';
				setState();
			}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				characterState[1] = 'i';
				setState();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			characterState[1] = 'd';
			setState();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			characterState[1] = 'a';
			setState();
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.isGrounded) {
			characterState[1] = 'w';			
			setState();
		}
		
		

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A) {
				characterState[1] = 'i';  
				setState();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			state.videGameStates('1');
		}
		

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
			player.toggleInventory();
			player.addItem(Item("Sword", "A sharp blade", 10));
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
			if (player.getSprite().getGlobalBounds().intersects(npc.getBounds())) {
				npc.interact();
			}
		}

	}
}

void Game::setState() {
	state.handleStates(characterState[1]);
}

void Game::checkCollision() {
	if (player.getSprite().getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())) {
		
	} 
}


void Game::handlePlayerAttack() {
	sf::FloatRect playerAttackBox = player.getSprite().getGlobalBounds();
	sf::FloatRect enemyBox = enemy.getSprite().getGlobalBounds();
	enemyBox.left += 20;
	enemyBox.width -= 40;
	enemyBox.top += 20;
	enemyBox.height -= 40;
	playerAttackBox.width /= 2;
	if (player.getSprite().getScale().x < 0) {
		playerAttackBox.left 
			+= playerAttackBox.width;

	}

	if (player.isAttacking && enemy.isAlive && playerAttackBox.intersects(enemyBox))
	{
		enemy.takeDamage(10); // Example damage value
		std::cout << "Player attacked enemy!" << std::endl;
	}


	if (enemy.getHealth() <= 0 && !enemyDeadTriggered) {
		enemy.isAlive = false;
		enemyDeadTriggered = true;
	}
}
void Game::update() {
	player.update(characterState[1]);
	enemy.update();
	npc.update();

	

}

void Game::renderMenu() {

}

void Game::render() {
	window.clear();
	window.draw(backgroundSprite);
	player.draw(window);
	enemy.draw(window);
	npc.draw(window);
	window.display();
}