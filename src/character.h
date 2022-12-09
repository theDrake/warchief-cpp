/*******************************************************************************
   Filename: character.h

     Author: David C. Drake (https://davidcdrake.com)

Description: Declaration of a 'Character' class responsible for representing
             both player and non-player characters.
*******************************************************************************/

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include "main.h"
#include "battlefield.h"

using namespace std;

const double kDefaultZOffset = 0.1;
const double kGravity = 0.004;

class Battlefield;

enum Race {
  kMan,
  kBarbarian,
  kAmazon,
  kHorseRaider,
  kDwarf,
  kWoodElf,
  kHighElf,
  kOrc,
  kHalfOrc,
  kGoblin,
  kTroll,
  kOgre,
  kDragon,
  kGiant,
  kUndead,
  kSummoned,
  kNumRaces
};

enum Quality {
  kElite,
  kVeteran,
  kAverage,
  kPoor,
  kUnpredictable,
  kNumQualityTypes
};

enum Type {
  kDisciplined,
  kTribal,
  kFanatic,
  kStupid,
  kNumCharacterTypes
};

enum Armor {
  kNoArmor,
  kLightArmor,
  kMediumArmor,
  kHeavyArmor,
  kExtraHeavyArmor,
  kNumArmorTypes
};

enum Weapon {
  kOneHanded,
  kTwoHanded,  // May not carry a shield.
  kSpear,  // May fight in two ranks.
  kLance,  // May fight in two ranks.
  kPike,  // May fight in three ranks.
  kPolearm,  // May use as TWO_HANDED or SPEAR. May not carry a shield.
  kToothAndClaw,
  kHornAndHoof,
  kNumWeaponTypes
};

class Character {
 public:
  Character(int race, int type, Battlefield *battlefield);
  ~Character();
  void Initialize(int race, int type, Battlefield *battlefield);
  int GetType() const { return type_; }
  double GetX() const { return x_; }
  double GetY() const { return y_; }
  double GetZ() const { return z_; }
  double GetZOffset() const { return z_offset_; }
  double GetHeight() const { return height_; }
  double GetRotation() const { return rotation_; }
  double GetRotationRate() const { return rotation_rate_; }
  double GetMovementRate() const { return movement_rate_; }
  double GetRed() const { return red_; }
  double GetGreen() const { return green_; }
  double GetBlue() const { return blue_; }
  double GetNextX() const;
  double GetNextY() const;
  double GetNextZ() const;
  void Act();
  void MoveForward();
  void MoveBackward();
  void StrafeLeft();
  void StrafeRight();
  void RotateLeft();
  void RotateRight();
  bool IsPlayer() const;
  bool IsOnGround();
  void Draw();
 protected:
  string name_;
  int race_,
      quality_,
      type_,
      strength_,
      resilience_,
      worth_,
      armor_,
      hand_weapon_,
      ranged_weapon_,
      saving_throw_,
      volleys_,
      magic_points_,
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
         z_offset_,
         height_,
         rotation_,
         rotation_rate_,
         movement_rate_,
         collision_radius_;
  Battlefield *battlefield_;
};

#endif  // CHARACTER_H_
