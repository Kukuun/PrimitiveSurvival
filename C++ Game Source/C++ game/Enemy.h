#pragma once
#include <GL\glut.h>
#include <iostream>
#include <SOIL.h>
#include <ctime>
#include "Enums.h"
#include "GameObject.h"
#include "Structs.h"


class Enemy : public GameObject {
// Variables
public:
	float x, y; // Stores X and Y position.

private:
	float patternTimer; // Used when switching direction/speed for the EdgyWave/Speed movementpattern.
	int rndMovementPattern; // Used to determine a random pattern to use.
	GLuint texture; // Stores the enemy texture.
	int regularSpeed; // Regular speed for enemies.
	int fastSpeed; // Speed used by enemies with the speed pattern.
	int slowSpeed; // Speed used by enemies with the speed pattern.
	int edgeCurveValue; // How far enemies with the edge pattern should travel when doing sideways movement. 
	int sineCurveValue; // How big a curve the enemies with the sine pattern should make.
	float switchValue; // Determines how long an enemy with the edge/speed pattern should stay in a phase.
	int thresholdValue; // Determines the threshold that the edge/speed pattern should reset.

	// Stores a reference to the spawnPosition variable from GameWorld.
	// Used to determine what side of the screen that the enemy is gonna spawn.
	SpawnPosition spawnPosition;

// Functions
public:
	Enemy(float x, float y, SpawnPosition &spawnPosition);

	void InitializeRectangle() override; // Stores the values of the enemy rectangle.
	void Move(float gameTime) override; // Executes movement.
	void Render() override; // Renders the texture and rectangle of the enemy.
	void Update(float gameTime) override; // Updates neccesarry logic.
	
	~Enemy();

private:
	void DrawRectangle(Rect rect); // Sets the coordinates for the vertexes of the rectangle.

#pragma region MovementPatternMethods
	// Methods containing the different movement patterns.
	void LeftRegularPattern(float gameTime);
	void RightRegularPattern(float gameTime);
	void TopRegularPattern(float gameTime);
	void BottomRegularPattern(float gameTime);
	void LeftEdgytWavePattern(float gameTime);
	void RightEdgytWavePattern(float gameTime);
	void TopEdgyWaveVerticalPattern(float gameTime);
	void BottomEdgyWaveVerticalPattern(float gameTime);
	void LeftSpeedPattern(float gameTime);
	void RightSpeedPattern(float gameTime);
	void TopSpeedPattern(float gameTime);
	void BottomSpeedPattern(float gameTime);
	void LeftSineWavePattern(float gameTime);
	void RightSineWavePattern(float gameTime);
	void TopSineWavePattern(float gameTime);
	void BottomSineWavePattern(float gameTime);
#pragma endregion
};
