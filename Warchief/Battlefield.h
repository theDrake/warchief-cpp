/******************************************************************************
   Filename: Battlefield.h

     Author: David C. Drake (http://davidcdrake.com)

Description: Declaration of a 'Battlefield' class.
******************************************************************************/

#ifndef BATTLEFIELD_H_
#define BATTLEFIELD_H_

#include <ctime>
#include <iostream>
#include "main.h"

using namespace std;

enum Lighting {
  DAY,
  NIGHT,
  NUM_LIGHTING_TYPES
};

enum TerrainType {
  DEFAULT_TERRAIN,
  LARGE_HILL,
  SMALL_HILL,
  LARGE_WOOD,
  SMALL_WOOD,
  BROKEN_GROUND,
  SWAMP,
  MARSH,
  NUM_TERRAIN_TYPES
};

class Battlefield {
 public:
  Battlefield();
  Battlefield(double resolution, double waterHeight, int perspective);
  void initialize(double resolution, double waterHeight, int perspective);
  ~Battlefield();
  int setPerspective(int p);
  void draw();
  bool isLegalPosition(double x, double y, double z);
  double getResolution() { return resolution_; }
  double getWaterHeight() { return waterHeight_; }
  double setWaterHeight(double h) { return waterHeight_ = h; }
  int getPerspective() { return perspective_; }
  double getZ(double i, double j);
 private:
  double resolution_,
         waterHeight_;
  int time_,
      perspective_;
};

#endif  // BATTLEFIELD_H_
