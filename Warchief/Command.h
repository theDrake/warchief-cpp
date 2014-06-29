#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include "Unit.h"
#include "Character.h"

using namespace std;

const enum Order
{
  ATTACK,
  HOLD,
  OPPOSE,

  NUM_ORDERS
};

class Command
{
public:
  Command();
  ~Command();
private:
  Character* leader_;  // The warchief or a battle leader.
  vector<Unit*> units_;
};

#endif
