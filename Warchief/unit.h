/*******************************************************************************
   Filename: unit.h

     Author: David C. Drake (https://davidcdrake.com)

Description: Declaration of a 'Unit' class.
*******************************************************************************/

#ifndef UNIT_H_
#define UNIT_H_

#include <vector>
#include "character.h"

using namespace std;

const enum Morale {
  kOK,
  kBloodlust,
  kShaken,
  kRout,
  kNumMoraleTypes
};

class Unit {
 public:
  Unit();
  ~Unit();
 private:
  vector<Character *> warriors_;
  double rotation_;
};

#endif  // UNIT_H_
