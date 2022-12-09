/*******************************************************************************
   Filename: army.h

     Author: David C. Drake (https://davidcdrake.com)

Description: Declaration of an 'Army' class.
*******************************************************************************/

#ifndef ARMY_H_
#define ARMY_H_

#include <vector>
#include "command.h"
#include "character.h"

using namespace std;

class Army {
 public:
  Army();
  ~Army();
 private:
  int max_points_;
  vector<Command *> commands_;
  vector<Character *> individuals_;
};

#endif  // ARMY_H_
