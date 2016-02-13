/******************************************************************************
   Filename: Unit.h

     Author: David C. Drake (http://davidcdrake.com)

Description: Declaration of a 'Unit' class.
******************************************************************************/

#ifndef UNIT_H_
#define UNIT_H_

#include <vector>
#include "Character.h"

using namespace std;

const enum Morale {
  OK,
  BLOODLUST,
  SHAKEN,
  ROUT,
  NUM_MORALE_TYPES
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
