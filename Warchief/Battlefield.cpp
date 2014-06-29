#include "Battlefield.h"

const int    DEFAULT_PERSPECTIVE	 = FIRST_PERSON;
const double DEFAULT_RESOLUTION		 = 100.0;
const double DEFAULT_WATER_HEIGHT	 = 0.5;
const double DEFAULT_PLAYER_Z_OFFSET = 0.15;

Battlefield::Battlefield()
{
	initialize(DEFAULT_RESOLUTION, DEFAULT_WATER_HEIGHT, DEFAULT_PERSPECTIVE);
}

Battlefield::Battlefield(double resolution, double waterHeight, int perspective)
{
	initialize(resolution, waterHeight, perspective);
}

void Battlefield::initialize(double resolution, double waterHeight, int perspective)
{
	resolution_	 = resolution;
	waterHeight_ = waterHeight;
	perspective_ = perspective;
}

Battlefield::~Battlefield()
{
	// Do nothing.
}

int Battlefield::setPerspective(int p)
{
	return perspective_ = p;
}

bool Battlefield::isLegalPosition(double x, double y, double z)
{
	if (y < 0 || y > resolution_ || x < 0 || x > resolution_)
	{
		return false;
	}

	return true;
}

void Battlefield::draw()
{
	for (int i = 0; i < resolution_; ++i)
	{
		for (int j = 0; j < resolution_; ++j)
		{
			/*double r = i / (double) resolution_;
			double g = j / (double) resolution_;
			double b = 0.5;*/

			/*double r = getZ(i * 0.2345, j * 0.4635);
			double g = getZ(i * 0.9876, j * 0.2345);
			double b = getZ(i * 0.4635, j * 0.9876);*/

			glBegin(GL_QUADS);

			double r = 0.2 * getZ(i, j);
			double g = 0.9 * getZ(i, j);
			double b = b = 0.2 * getZ(i, j);
			glColor3d(r, g, b);
			glVertex3d(i, j, getZ(i,j));

			r = 0.2 * getZ(i + 1, j);
			g = 0.9 * getZ(i + 1, j);
			b = b = 0.2 * getZ(i + 1, j);
			glColor3d(r, g, b);
			glVertex3d(i + 1, j, getZ(i + 1, j));

			r = 0.2 * getZ(i + 1, j + 1);
			g = 0.9 * getZ(i + 1, j + 1);
			b = b = 0.2 * getZ(i + 1, j + 1);
			glColor3d(r, g, b);
			glVertex3d(i + 1, j + 1, getZ(i + 1, j + 1));

			r = 0.2 * getZ(i, j + 1);
			g = 0.9 * getZ(i, j + 1);
			b = b = 0.2 * getZ(i, j + 1);
			glColor3d(r, g, b);
			glVertex3d(i, j + 1, getZ(i, j + 1));

			glEnd();
		}
	}

	// Draw the water as one large quad at a given height:
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4d(0.1, 0.2, 0.9, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, waterHeight_);
	glVertex3f(resolution_, 0, waterHeight_);
	glVertex3f(resolution_, resolution_, waterHeight_);
	glVertex3f(0, resolution_, waterHeight_);
	glEnd();
	glDisable(GL_QUADS);
}

// Generate each point's elevation according to its 'x' and 'y' coordinates:
double Battlefield::getZ(double x, double y)
{
	//return sin(x * 0.789) + cos(y * 0.8907) + 0.34143 * sin(1 + x * 0.789 + y * 0.8907);
	//return cos(x / 5) + sin(y / 10) + 0.7 * sin(y / 10 + 1 + x / 11);
	return 2 * sin (0.4 * y) + 1.5 * cos (0.3 * x) + 4 * sin (0.2 * x) * cos(0.3 * y) + 6 * sin(0.11 * x) * cos(0.03 * y);
}
