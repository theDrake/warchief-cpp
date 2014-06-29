//*****************************************************************************
//	  Filename: main.cpp
//
//	    Author: David C. Drake (www.davidcdrake.com)
//
// Description: Main file for "Warchief": a strategy-RPG based on the tabletop
//              battle game "Fantasy Warriors" by Nick Lund of Grenadier
//              Models.
//*****************************************************************************

#include "main.h"

double screenX = 1200;
double screenY = 600;

double resolution       = 100.0;
double waterHeight      = 0.5;
Perspective perspective = FIRST_PERSON;

const double MARGIN = 0.5; // Half the size of a cell.

double WL = -MARGIN;
double WR = resolution + MARGIN;
double WB = -MARGIN;
double WT = resolution + MARGIN;

double VL = 0;
double VR = screenX;
double VB = 0;
double VT = screenY;

const int CLOCKS_PER_SECOND = 1000;

bool gLeftButtonDown     = false;
bool gMiddleButtonDown   = false;
bool gRightButtonDown    = false;
bool gPerspectiveKeyDown = false;

Battlefield* gBattlefield = NULL;
Character* gPlayer        = NULL;

//--------------------------------------------------------------------------------------------------
// Functions that draw basic primitives.
//--------------------------------------------------------------------------------------------------

void drawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double) i / 32.0 * 2.0 * PI;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void drawRectangle(double x1, double y1,
                   double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

void drawRectangle3D(double x1, double y1, double z1,
                     double x2, double y2, double z2,
                     double x3, double y3, double z3,
                     double x4, double y4, double z4)
{
	glBegin(GL_QUADS);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glVertex3d(x3, y3, z3);
	glVertex3d(x4, y4, z4);
	glEnd();
}

void drawTriangle(double x1, double y1,
                  double x2, double y2,
                  double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

void drawLine(double x1, double y1,
              double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glEnd();
}

void drawLine3D(double x1, double y1, double z1,
                double x2, double y2, double z2)
{
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}

// To output a string of text at a specified location:
void drawText(double x, double y, char* string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

  glDisable(GL_BLEND);
}

//--------------------------------------------------------------------------------------------------
// GLUT callback functions.
//--------------------------------------------------------------------------------------------------

void display(void)
{
	double fps = getFramesPerSecond();
	double spf = 1.0 / fps;

  if (isKeyPressed(KEY_ESCAPE))
	{
		if (gBattlefield)
			delete gBattlefield;
		if (gPlayer)
			delete gPlayer;
		exit(0);
	}
	if (isKeyPressed('p') || isKeyPressed('r'))
	{
		gPerspectiveKeyDown = true;
	}
	else if (gPerspectiveKeyDown)
	{
		gPerspectiveKeyDown = false;
		if (gBattlefield->getPerspective() == FIRST_PERSON)
		{
			gBattlefield->setPerspective(PERCH);
		}
		else
		{
			gBattlefield->setPerspective(FIRST_PERSON);
		}
		reshape(screenX, screenY);
	}
	/*if (isKeyPressed(KEY_SPACE) && gPlayer->isOnGround())
	{
		gPlayer->jump();
	}*/
	if (isKeyPressed(KEY_UP) || isKeyPressed('w'))
	{
		gPlayer->moveForward();
	}
	if (isKeyPressed(KEY_DOWN) || isKeyPressed('s'))
	{
		gPlayer->moveBackward();
	}
	if (isKeyPressed('z'))
	{
		gPlayer->strafeLeft();
	}
	if (isKeyPressed('c'))
	{
		gPlayer->strafeRight();
	}
	if (isKeyPressed(KEY_LEFT) || isKeyPressed('a'))
	{
		gPlayer->rotateLeft();
	}
	if (isKeyPressed(KEY_RIGHT) || isKeyPressed('d'))
	{
		gPlayer->rotateRight();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	if (gBattlefield->getPerspective() == FIRST_PERSON)
	{
		double tempX = gPlayer->getX() + cos(gPlayer->getRotation() * PI / 180);
		double tempY = gPlayer->getY() + sin(gPlayer->getRotation() * PI / 180);
		double tempZ = gBattlefield->getZ(tempX, tempY);
		if (tempZ < gBattlefield->getWaterHeight())
    {
			tempZ = gBattlefield->getWaterHeight();
    }
		tempZ += gPlayer->getZOffset();

		gluLookAt(gPlayer->getX(), gPlayer->getY(), gPlayer->getZ(),
              tempX, tempY, tempZ,
              0, 0, 1);
	}
	else if (gBattlefield->getPerspective() == DIRECTLY_OVERHEAD)
	{
		glDisable(GL_DEPTH_TEST);
	}
	else if (gBattlefield->getPerspective() == PERCH)
	{
		gluLookAt(resolution / 2.0, -resolution / 2.0, resolution * 2 / 5,
              gPlayer->getX(), gPlayer->getY(), gPlayer->getZ(),
              0, 0, 1);
	}

	gBattlefield->draw();

	if (gLeftButtonDown)
	{
		gPlayer->rotateLeft();
	}
	if (gMiddleButtonDown)
	{
		gPlayer->moveForward();
	}
	if (gRightButtonDown)
	{
		gPlayer->rotateRight();
	}

	if (gBattlefield->getPerspective() != FIRST_PERSON)
		gPlayer->draw();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	// Reset global variables to the new width and height:
	screenX = w;
	screenY = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (gBattlefield->getPerspective() == FIRST_PERSON)
	{
		gluPerspective(35, (double) w/h, 0.1, resolution * 3);
	}
	else if (gBattlefield->getPerspective() == DIRECTLY_OVERHEAD)
	{
		gluOrtho2D(-0.5, resolution + 0.5, -0.5, resolution + 0.5);
	}
	else if (gBattlefield->getPerspective() == PERCH)
	{
		gluPerspective(35, (double) w/h, 1, resolution * 3);
	}
	glMatrixMode(GL_MODELVIEW);
}

void SolveRatio(double aLow, double aValue, double aHigh,
                double bLow, double &bValue, double bHigh)
{
	double ratio = (aValue - aLow) / (aHigh - aLow);
	bValue = bLow + ratio * (bHigh - bLow);
}

void mouse(int mouse_button, int state, int px, int py)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gLeftButtonDown = true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		gLeftButtonDown = false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
		gMiddleButtonDown = true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
		gMiddleButtonDown = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gRightButtonDown = true;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
	{
		gRightButtonDown = false;
	}

	glutPostRedisplay();
}

double getFramesPerSecond()
{
	static int frames = 0;
	static clock_t start_time = clock();

	++frames;
	clock_t current = clock() + 0.0001;

	double elapsed_time = (double) (current - start_time) / (double) CLOCKS_PER_SECOND;
	
	return (double) frames / elapsed_time;
}

int diceRoll(int nDice)
{
  int total = 0;

  for (int i = 0; i < nDice; ++i)
  {
    total += (rand() % 6) + 1;
  }

  return total;
}

//--------------------------------------------------------------------------------------------------
// Initialization function.
//--------------------------------------------------------------------------------------------------

void initializeMyStuff()
{
  gBattlefield = new Battlefield();
  gPlayer = new Character(MAN, 0, gBattlefield);
}

//--------------------------------------------------------------------------------------------------
// Main function.
//--------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	srand(time(0));
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenX, screenY);
	glutInitWindowPosition(50, 50);

	bool fullscreen = false;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow("Battlefield");
	}

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
  initKeyboard();

	glColor3d(0, 0, 0);             // Foreground color.
	glClearColor(0.4, 0.4, 0.9, 0);	// Background color.
	initializeMyStuff();

	glutMainLoop();

  if (gBattlefield)
  {
    delete gBattlefield;
    gBattlefield = NULL;
  }
  if (gPlayer)
  {
    delete gPlayer;
    gPlayer = NULL;
  }

	return 0;
}
