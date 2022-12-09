/*******************************************************************************
   Filename: main.h

     Author: David C. Drake (https://davidcdrake.com)

Description: Main header file for "Warchief," a strategy-RPG based on the
             tabletop wargame "Fantasy Warriors" by Nick Lund of Grenadier
             Models.
*******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <GL/glut.h>
#include "keys.h"
#include "battlefield.h"
#include "character.h"

using namespace std;

const double PI = 4.0 * atan(1.0);

enum Perspective {
  FIRST_PERSON,
  DIRECTLY_OVERHEAD,
  PERCH,
  NUM_PERSPECTIVES
};

void drawTriangle(double x1, double y1,
                  double x2, double y2,
                  double x3, double y3);
void reshape(int w, int h);
double GetFramesPerSecond();
int diceRoll(int nDice);

#endif  // MAIN_H_
