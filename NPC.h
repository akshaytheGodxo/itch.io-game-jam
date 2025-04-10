#pragma once
#include <SFML/Graphics.hpp>
#include "Quest.h"
#include "Dialogue.h"

class NPC {
public:
    NPC();

    void update();
    void draw(sf::RenderWindow& window);

    void interact();  // called when player is near & presses interact key
    sf::FloatRect getBounds() const;

    void handleIdle();

    Quest quest;
    Dialogue dialogue;
    bool dialogueActive = false;

private:
    sf::Clock clock;
    sf::Sprite sprite;
    sf::Texture idleTexture;
    sf::Font font;
    sf::Text dialogueText;
    sf::Texture dialogueBoxTexture;
    sf::Sprite dialogueBoxSprite;

    int numIdleFrames = 5;
	int frameDuration = 1.0f; 
    int frameWidth = 128;
    int frameHeight = 128;
	int currentFrame = 0;
	int npc_position_x = 1000;
    int npc_position_y = 500;



};
