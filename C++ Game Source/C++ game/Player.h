#pragma once
#include <GL\glut.h>
#include <SOIL.h>
#include "Enums.h"
#include <iostream>
#include "GameObject.h"
#include "Structs.h"
#include "Enemy.h"
#include <vector>
#include <math.h>
#include <fstream>

class Player : public GameObject {
// Variables
public:

private:
	float x, y; // Stores X and Y position.
	float survivedInSeconds; // Stores the time the player is living in seconds.
	int survivedInMinutes; // Stores the time the player is living in minutes.
	PlayerDirection direction; // Stores the possible directions the player can move.
	std::vector<Enemy*> *enemies;// A pointer vector of pointers, pointing to the pointer vector in GameWorld.
	GLuint texture; // Stores the player texture.	
	std::ofstream writeTimeToFile; // Stores the time the player lived in seconds and minutes.

// Functions
public:
	Player(float x, float y, std::vector<Enemy*> *enemies);
	void InitializeRectangle() override; // Stores the values of the enemy rectangle.
	void KeyboardInput(unsigned char key); // Sets the direction enum according to valid key presses.
	void Move(float gameTime) override; // Moves the player object according to the enum state.
	void Render() override; // Renders the texture and rectangle of the enemy.
	void Update(float gameTime) override; // Updates neccesarry logic.

	~Player();

private:
	void DrawRectangle(Rect rect); // Sets the coordinates for the vertexes of the rectangle.
	void DisplayTimeToConsole(float gameTime); // Displays the time the player have been alive to the console. NOTE:: DO NOT COMMENT THIS FUNCTION OUT ::NOTE
	void OnCollision(); // Stores logic of what happens if the player intersects with an enemy.
	void SaveLatestRoundTimeToFile(); // Function that saves the time the player lived to a document.
};