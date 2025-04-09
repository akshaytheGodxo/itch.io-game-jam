#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "StateManager.h"
class Game
{
public:
	Game();
	void run();
	
	void setState();

	void checkInputs();

	void renderMenu();

	void checkCollision();

	void handlePlayerAttack();

private:
	sf::Clock dtClock;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::RenderWindow window;
	sf::RectangleShape debugBox;
	sf::RectangleShape enemyHitbox;
	Player player;
	StateManager state;
	Enemy enemy;
	char characterState[1];
	char gameState[1];
	void processEvents();
	void update();
	void render();
};

