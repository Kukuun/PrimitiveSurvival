#include "GameWorld.h"
#include <GL/glut.h>
#include <SOIL.h>
#include <Windows.h>

GameWorld *world;

void InitOpenGL() {
	glShadeModel(GL_SMOOTH); // Enable smooth shading.
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); //Set clear color.
	glClearDepth(1.0f); // Set clearing depth for depth buffer.
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
	glDepthFunc(GL_LEQUAL); // Set depth buffer testing to less then or equal.

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Specifies how colors/textures are interpolized on surfaces.
}

void Reshape(int width, int height) {
	if (height == 0) { // Makes sure no divide by zero can happen .
		height = 1;
	}
	glViewport(0, 0, width, height); // Resets the current viewport.

	glMatrixMode(GL_PROJECTION); // Specifies projection matrix stack.
	glLoadIdentity(); // Resets projection matrix stack - top matrix.

	gluPerspective(45.0f, width / height, 0.0f, 100.0f); // Sets perspective to match current display size.

	glMatrixMode(GL_MODELVIEW); // Specifies model view matrix.
	glLoadIdentity(); // Resets model view matrix - top matrix.
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // Keycode for the escape button.
		exit(0);
		break;
	default:
		break;
	}

	world->Keyboard(key, x, y);
}


void GameLoop() {
	world->Update();
}

void main(int argc, char** argv) {
	irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();

	glutInit(&argc, argv);// Initializes GLUT.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH); // Initializes glut display mode with rgb and alpha colors and Depth.
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT); // Sets window size - Defined in GameWorld.
	glutInitWindowPosition(SCREENPOSITION_X, SCREENPOSITION_Y); // Sets window position - Defined in GameWorld.

	glutCreateWindow("A C++ game by Poul Munk."); // Creates GLUT OpenGL Window.

	InitOpenGL();
	glutReshapeFunc(&Reshape);
	glutDisplayFunc(&GameLoop);
	glutKeyboardFunc(&Keyboard);

	world = new GameWorld();
	engine->setSoundVolume(0.1f);
	engine->play2D("Misc/MegaMan2.mp3", true);

	glutMainLoop();
	engine->drop();
}