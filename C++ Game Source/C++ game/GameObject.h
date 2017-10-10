#pragma once
#include <GL\glut.h>
#include <Windows.h>
#include "Structs.h"
#include <SOIL.h>

class GameObject {
// Variables
public:
	Rect rect; // Instantiation of the Rect struct for the player and enemies to use.

private:

// Functions
public:
	GameObject();	

	~GameObject();

protected:
	void virtual InitializeRectangle(); // Used by it's children to store the values for the rectangle.
	void virtual Move(float gameTime); // Used by it's children to move the object.
	void virtual Render(); // Used by it's children to handle rendering.
	void virtual Update(float gameTime); // Used by it's children to update neccesarry logic.

private:
};