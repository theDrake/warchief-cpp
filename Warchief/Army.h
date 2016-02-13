/******************************************************************************
   Filename: Army.h

     Author: David C. Drake (http://davidcdrake.com)

Description: Declaration of an 'Army' class.
******************************************************************************/

#ifndef ARMY_H_
#define ARMY_H_

#include <vector>
#include "Command.h"
#include "Character.h"

using namespace std;

class Army {
 public:
  Army();
  ~Army();
 private:
  int maxPoints_;
  vector<Command *> commands_;
  vector<Character *> individuals_;
};

#endif  // ARMY_H_
