#include "game.h"
#include "cubeGame.h"


using namespace std;

/**********************************************************************/
/*                  V A R I A B L E S   G L O B A L E S               */
/**********************************************************************/
int windowWidth = 1920;
int windowHeight = 1080;
int windowPositionX = 300;
int windowPositionY = 200;
char title[] = "Engine Json";
char gameTitle[] = "SPACE PILOT";
GLclampf clearRed = 0.1;
GLclampf clearGreen = 0.1;
GLclampf clearBue = 0.1;
GLclampf clearAlpha = 1.0;
bool fullScreenMode = true;

/**********************************************************************/
//Game game;
CubeGame game;


void reshapeFunc(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, aspectRatio, 1.0f, 2000.f);
	glMatrixMode(GL_MODELVIEW);
}
void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	game.render();
	glutSwapBuffers();
}
void idleFunc() {
	game.update();
	glutPostRedisplay();
}
void specialKeyFunc(int key, int x, int y) {
	
	switch (key) {
	case GLUT_KEY_F11:
		fullScreenMode = !fullScreenMode;
		if (fullScreenMode) {
			windowPositionX = glutGet(GLUT_WINDOW_X);
			windowPositionY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		}
		else {
			glutReshapeWindow(windowWidth, windowHeight);
			glutPositionWindow(windowPositionX, windowPositionY);
		}
	}
}
void keyPressedFunc(unsigned char key, int x, int y) {
	//Con ESC salimos
	if (key == 27)
		exit(0);
	game.processKeyPressed(key, x, y);
}
void mouseMovedFunc(int x, int y) {
	game.processMouseMovement(x, y);
}
void mouseClickedFunc(int button, int state, int x, int y) {
	game.processMouseClick(button, state, x, y);
}
void initGraphics() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(clearRed, clearGreen, clearBue, clearAlpha);
	//game.init("juego.json");
	game.init();
}
int main(int argc, char** argv) try {
	std::cout << "PA engine\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPositionX, windowPositionY);
	glutCreateWindow(gameTitle);
	glutFullScreen();
	std::cout << "Registrando funciones de rellamada/eventos (callback)" << std::endl;
	glutReshapeFunc(reshapeFunc); //rellamada de redimensionado de ventana
	glutDisplayFunc(displayFunc); //rellamada de repintado de la ventana
	glutIdleFunc(idleFunc);       //rellamada de proceso oculto
	/* Interaccion */
	glutKeyboardFunc(keyPressedFunc);
	glutSpecialFunc(specialKeyFunc);
	glutMotionFunc(mouseMovedFunc);
	glutMouseFunc(mouseClickedFunc);
	initGraphics();

	glutMainLoop();
	std::cout << "Fin que no se ve" << std::endl;
}
catch (exception& e) {
	cout << "Error detectado en main(): " << e.what() << endl;
}
