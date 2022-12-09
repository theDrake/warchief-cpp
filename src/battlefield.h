/*******************************************************************************
   Filename: battlefield.h

     Author: David C. Drake (https://davidcdrake.com)

Description: Declaration of a 'Battlefield' class.
*******************************************************************************/

#ifndef BATTLEFIELD_H_
#define BATTLEFIELD_H_

#include <ctime>
#include <iostream>
#include "main.h"

using namespace std;

enum Lighting {
  kDay,
  kNight,
  kNumLightingTypes
};

enum TerrainType {
  kDefaultTerrain,
  kLargeHill,
  kSmallHill,
  kLargeWood,
  kSmallWood,
  kBrokenGround,
  kSwamp,
  kMarsh,
  kNumTerrainTypes
};

class Battlefield {
 public:
  Battlefield();
  Battlefield(double resolution, double water_height, int perspective);
  void Initialize(double resolution, double water_height, int perspective);
  ~Battlefield();
  int SetPerspective(int p);
  void Draw();
  bool IsLegalPosition(double x, double y, double z);
  double GetResolution() { return resolution_; }
  double GetWaterHeight() { return water_height_; }
  double SetWaterHeight(double h) { return water_height_ = h; }
  int GetPerspective() { return perspective_; }
  double GetZ(double i, double j);
 private:
  double resolution_,
         water_height_;
  int time_,
      perspective_;
};

#endif  // BATTLEFIELD_H_
