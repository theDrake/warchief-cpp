/******************************************************************************
   Filename: main.h

     Author: David C. Drake (http://davidcdrake.com), with initial assistance
             from Dr. Barton Stander (http://cit.dixie.edu/faculty/stander.php)

Description: Main header file for "Warchief," a strategy-RPG based on the
             tabletop wargame "Fantasy Warriors" by Nick Lund of Grenadier
             Models.
******************************************************************************/

#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <cmath>
#include <cstring>
#include "glut.h"
#include "keys.h"
#include "Battlefield.h"
#include "Character.h"

using namespace std;

const double PI = 4.0 * atan(1.0);

const enum Perspective
{
  FIRST_PERSON, DIRECTLY_OVERHEAD, PERCH
};

void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void reshape(int w, int h);
double getFramesPerSecond();
int diceRoll(int nDice);

#endif
