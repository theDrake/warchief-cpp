//*****************************************************************************
//	  Filename: Character.h
//
//	    Author: David C. Drake (www.davidcdrake.com)
//
// Description: Declaration of a 'Character' class responsible for representing
//				      both player and non-player characters.
//*****************************************************************************

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "main.h"
#include "Battlefield.h"

using namespace std;

const double DEFAULT_Z_OFFSET = 0.1;
const double GRAVITY		      = 0.004;

class Battlefield;

const enum Race
{
  MAN,
  BARBARIAN,
  AMAZON,
  HORSE_RAIDER,
  DWARF,
  WOOD_ELF,
  HIGH_ELF,
  ORC,
  HALF_ORC,
  GOBLIN,
  TROLL,
  OGRE,
  DRAGON,
  GIANT,
  UNDEAD,
  SUMMONED,

  NUM_RACES
};

const enum Quality
{
  ELITE,
  VETERAN,
  AVERAGE,
  POOR,
  UNPREDICTABLE,

  NUM_QUALITIES
};

const enum Type
{
	DISCIPLINED,
	TRIBAL,
	FANATIC,
	STUPID,

	NUM_TYPES
};

const enum Armor
{
  NO_ARMOR,
  LIGHT,
  MEDIUM,
  HEAVY,
  EXTRA_HEAVY,

  NUM_ARMORS
};

const enum Weapon
{
  ONE_HANDED,
  TWO_HANDED,       // May not carry a shield.
  SPEAR,            // May fight in two ranks.
  LANCE,            // May fight in two ranks.
  PIKE,             // May fight in three ranks.
  POLEARM,          // May use as TWO_HANDED or SPEAR. May not carry a shield.
  TOOTH_AND_CLAW,
  HORN_AND_HOOF,

  NUM_WEAPONS
};

class Character
{
public:
	Character(int race, int type, Battlefield* battlefield);
	~Character();
	void initialize(int race, int type, Battlefield* battlefield);
	int getType() const;
	double getX() const;
	double getY() const;
	double getZ() const;
	double getZOffset() const;
	double getHeight() const;
	double getRotation() const;
	double getRotationRate() const;
	double getMovementRate() const;
	double getRed() const;
	double getGreen() const;
	double getBlue() const;
	double getNextX() const;
	double getNextY() const;
	double getNextZ() const;
	void act();
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void rotateLeft();
	void rotateRight();
	bool isPlayer() const;
	bool isOnGround();
	void draw();
protected:
	string name_;
	int race_,
		  quality_,
      type_,
      strength_,
      resilience_,
      worth_,
      armor_,
      handWeapon_,
      rangedWeapon_,
      savingThrow_,
      volleys_,
      magicPoints_,
      leadership_,
      points_;
  bool shield_,
       terrible_,
       hatesDay_,
       hatesNight_;
	double red_,
		     green_,
		     blue_,
		     x_,
		     y_,
		     z_,
         zOffset_,
		     height_,
		     rotation_,
		     rotationRate_,
		     movementRate_,
		     collisionRadius_;
	Battlefield* battlefield_;
};

#endif
