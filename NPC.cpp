#include "NPC.h"
#include "DEFINITIONS.h"

NPC::NPC() {
    idleTexture.loadFromFile(NPC_1_IDLE);
    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(frameWidth / 2, frameHeight / 2);
    sprite.setPosition(npc_position_x, npc_position_y);
    sprite.setScale(-1, 1);
    quest = { "Find the Sword", "Retrieve the lost sword from the cave." };
    dialogue.lines = {
        "Hello, brave warrior!",
        "Can you kill him",
        "I will give u 100 gold coins"
    };
    dialogueBoxTexture.loadFromFile("assets/message_boxes.png");
    
    dialogueBoxSprite.setTexture(dialogueBoxTexture);
    dialogueBoxSprite.setPosition(100 , 600);  // adjust to your layout
        // scale if needed
    dialogueBoxSprite.setScale(3, 1);
    font.loadFromFile(DISPLAY_FONT);
    dialogueText.setFont(font);
    dialogueText.setCharacterSize(20);
    dialogueText.setFillColor(sf::Color::White);
    dialogueText.setPosition(120, 620);
}
void NPC::handleIdle() {
	int row = 0;
	if (clock.getElapsedTime().asSeconds() > frameDuration) {
		currentFrame = (currentFrame + 1) % numIdleFrames;
		sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
		clock.restart();
	}
}
void NPC::update() {
    if (dialogueActive) {
        dialogueText.setString(dialogue.getCurrentLine());
    }
    handleIdle();
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if (dialogueActive) {
        window.draw(dialogueBoxSprite);
        window.draw(dialogueText);
    }
}

void NPC::interact() {
    if (!dialogueActive) {
        dialogueActive = true;
        dialogue.reset();
    }
    else if (!dialogue.isFinished()) {
        dialogue.nextLine();
    }
    else {
        dialogueActive = false;
        dialogue.reset();
        quest.isAccepted = true;  // player accepts quest after dialogue
    }
}

sf::FloatRect NPC::getBounds() const {
    return sprite.getGlobalBounds();
}
