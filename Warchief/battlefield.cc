/*******************************************************************************
   Filename: battlefield.cc

     Author: David C. Drake (https://davidcdrake.com)

Description: Definition of a 'Battlefield' class.
*******************************************************************************/

#include "battlefield.h"

const int kDefaultPerspective = FIRST_PERSON;
const double kDefaultResolution = 100.0;
const double kDefaultWaterHeight = 0.5;
const double kDefaultPlayerZOffset = 0.15;

Battlefield::Battlefield() {
  Initialize(kDefaultResolution, kDefaultWaterHeight, kDefaultPerspective);
}

Battlefield::Battlefield(double resolution, double water_height,
                         int perspective) {
  Initialize(resolution, water_height, perspective);
}

void Battlefield::Initialize(double resolution, double water_height,
                             int perspective) {
  resolution_ = resolution;
  water_height_ = water_height;
  perspective_ = perspective;
}

Battlefield::~Battlefield() {}

int Battlefield::SetPerspective(int p) {
  return perspective_ = p;
}

bool Battlefield::IsLegalPosition(double x, double y, double z) {
  if (y < 0 || y > resolution_ || x < 0 || x > resolution_) {
    return false;
  }

  return true;
}

void Battlefield::Draw() {
  for (int i = 0; i < resolution_; ++i) {
    for (int j = 0; j < resolution_; ++j) {
      /*double r = i / (double) resolution_;
      double g = j / (double) resolution_;
      double b = 0.5;*/

      /*double r = GetZ(i * 0.2345, j * 0.4635);
      double g = GetZ(i * 0.9876, j * 0.2345);
      double b = GetZ(i * 0.4635, j * 0.9876);*/

      glBegin(GL_QUADS);

      double r = 0.2 * GetZ(i, j);
      double g = 0.9 * GetZ(i, j);
      double b = b = 0.2 * GetZ(i, j);
      glColor3d(r, g, b);
      glVertex3d(i, j, GetZ(i,j));

      r = 0.2 * GetZ(i + 1, j);
      g = 0.9 * GetZ(i + 1, j);
      b = b = 0.2 * GetZ(i + 1, j);
      glColor3d(r, g, b);
      glVertex3d(i + 1, j, GetZ(i + 1, j));

      r = 0.2 * GetZ(i + 1, j + 1);
      g = 0.9 * GetZ(i + 1, j + 1);
      b = b = 0.2 * GetZ(i + 1, j + 1);
      glColor3d(r, g, b);
      glVertex3d(i + 1, j + 1, GetZ(i + 1, j + 1));

      r = 0.2 * GetZ(i, j + 1);
      g = 0.9 * GetZ(i, j + 1);
      b = b = 0.2 * GetZ(i, j + 1);
      glColor3d(r, g, b);
      glVertex3d(i, j + 1, GetZ(i, j + 1));

      glEnd();
    }
  }

  // Draw the water as one large quad at a given height:
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glColor4d(0.1, 0.2, 0.9, 0.8);
  glBegin(GL_QUADS);
  glVertex3f(0, 0, water_height_);
  glVertex3f(resolution_, 0, water_height_);
  glVertex3f(resolution_, resolution_, water_height_);
  glVertex3f(0, resolution_, water_height_);
  glEnd();
  glDisable(GL_QUADS);
}

// Generate each point's elevation according to its 'x' and 'y' coordinates:
double Battlefield::GetZ(double x, double y) {
  //return sin(x * 0.789) + cos(y * 0.8907) + 0.34143 *
  //  sin(1 + x * 0.789 + y * 0.8907);
  //return cos(x / 5) + sin(y / 10) + 0.7 * sin(y / 10 + 1 + x / 11);
  return 2 * sin (0.4 * y) + 1.5 * cos (0.3 * x) + 4 * sin (0.2 * x) *
    cos(0.3 * y) + 6 * sin(0.11 * x) * cos(0.03 * y);
}
