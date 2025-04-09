#include "StateManager.h"

StateManager::StateManager(char& currentState, char& gameState) : characterState()  {
	characterState[0] = currentState;
	videoGameState[0] = gameState;
}

void StateManager::handleStates(char characterStates) {
	if (characterStates == 'a') {
		std::cout << "Moving left" << std::endl;
	}
	else if (characterStates == 'd') {
		std::cout << "Moving right" << std::endl;
	}
	else if (characterStates == 'w') {
		std::cout << "Moving up" << std::endl;
	}
	else if (characterStates == 's') {
		std::cout << "Moving down" << std::endl;
	}
	else if (characterStates == 'f') {
		std::cout << "Fight" << std::endl;
	}

	else if (characterStates == 'b') {
		std::cout << "Block" << std::endl;
	}
	else {
		std::cout << "Invalid input" << std::endl;
	}

}

void StateManager::videGameStates(char videoGameStates) {
	if (videoGameStates == '0') {
		std::cout << "Main Menu" << std::endl;
		videoGameState[0] = '0';
	}
	else if (videoGameStates == '1') {
		std::cout << "Game" << std::endl;
		videoGameState[0] = '1';
	}
	else if (videoGameStates == '2') {
		std::cout << "Pause" << std::endl;
		videoGameState[0] = '2';
	}
	else if (videoGameStates == '3') {
		std::cout << "Game Over" << std::endl;
		videoGameState[0] = '3';
	}
	else {
		std::cout << "Invalid input" << std::endl;
		videoGameState[0] = '0';
	}
}

char StateManager::getStates() {
	return characterState[0];
}

char StateManager::getVideoGameStates() {
	return videoGameState[0];
}