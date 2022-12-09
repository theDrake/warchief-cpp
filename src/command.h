/*******************************************************************************
   Filename: command.h

     Author: David C. Drake (https://davidcdrake.com)

Description: Declaration of a 'Command' class.
*******************************************************************************/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include "unit.h"
#include "character.h"

using namespace std;

const enum Order {
  kAttack,
  kHold,
  kOppose,
  kNumOrderTypes
};

class Command {
 public:
  Command();
  ~Command();
 private:
  Character *leader_;  // The warchief or a battle leader.
  vector<Unit *> units_;
};

#endif  // COMMAND_H_
