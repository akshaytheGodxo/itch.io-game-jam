#pragma once
#include <iostream>
#include <string>
class StateManager
{
public: 
	void handleStates(char characterStates);
	void videGameStates(char videoGameStates);
	char getStates();
	char getVideoGameStates();
	StateManager(char& currentState, char& gameState);

private:
	char characterState[1] = { 'i' };
	char videoGameState[1] = { '0' }; 
};

