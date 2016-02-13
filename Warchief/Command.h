/******************************************************************************
   Filename: Command.h

     Author: David C. Drake (http://davidcdrake.com)

Description: Declaration of a 'Command' class.
******************************************************************************/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include "Unit.h"
#include "Character.h"

using namespace std;

const enum Order {
  ATTACK,
  HOLD,
  OPPOSE,
  NUM_ORDERS
};

class Command {
 public:
  Command();
  ~Command();
 private:
  Character* leader_;  // The warchief or a battle leader.
  vector<Unit*> units_;
};

#endif  // COMMAND_H_
