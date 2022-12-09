/*******************************************************************************
   Filename: character.cc

     Author: David C. Drake (https://davidcdrake.com)

Description: Definition of a 'Character' class responsible for representing
             player and non-player characters.
*******************************************************************************/

#include "character.h"

//------------------------------------------------------------------------------
//      Method: Character
//
// Description: Constructs a Character object (via the 'initialize' method)
//              according to a given character type. Also provides the
//              character with a given pointer to a Battlefield object.
//
//      Inputs: type        - Integer representing the creature's type.
//              battlefield - Pointer to the current Battlefield object.
//
//     Outputs: None.
//------------------------------------------------------------------------------
Character::Character(int race, int type, Battlefield *battlefield) {
  Initialize(race, type, battlefield);
}

//------------------------------------------------------------------------------
//      Method: ~Character
//
// Description: Destructor.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
Character::~Character() {}

//------------------------------------------------------------------------------
//      Method: Initialize
//
// Description: Initializes the Character object according to a given
//              character type. Also provides the character with a given
//              pointer to a Battlefield object.
//
//      Inputs: type        - Integer representing the creature's type.
//              battlefield - Pointer to the current Battlefield object.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::Initialize(int race, int type, Battlefield *battlefield) {
  race_ = race;
  type_ = type;
  battlefield_ = battlefield;
  x_ = rand() % (int) battlefield_->GetResolution();
  y_ = rand() % (int) battlefield_->GetResolution();
  z_ = battlefield_->GetZ(x_, y_);
  if (z_ < battlefield_->GetWaterHeight()) {
    z_ = battlefield_->GetWaterHeight();
  }
  z_offset_ = kDefaultZOffset;
  z_ += z_offset_;
  height_ = 0.3;
  movement_rate_ = battlefield_->GetResolution() / 8000;
  rotation_ = 90.0;
  rotation_rate_ = battlefield_->GetResolution() / 200;
  collision_radius_ = 0.25;
  red_ = 0.0;
  green_ = 0.0;
  blue_ = 0.0;
}

//------------------------------------------------------------------------------
//      Method: GetNextX
//
// Description: Returns the x-coordinate the character would have if it moved
//              forward one step.
//
//      Inputs: None.
//
//     Outputs: The character's next anticipated x-coordinate.
//------------------------------------------------------------------------------
double Character::GetNextX() const {
  return x_ + cos(rotation_ * PI / 180) * movement_rate_;
}

//------------------------------------------------------------------------------
//      Method: GetNextY
//
// Description: Returns the y-coordinate the character would have if it moved
//              forward one step.
//
//      Inputs: None.
//
//     Outputs: The character's next anticipated y-coordinate.
//------------------------------------------------------------------------------
double Character::GetNextY() const {
  return y_ + sin(rotation_ * PI / 180) * movement_rate_;
}

//------------------------------------------------------------------------------
//      Method: GetNextZ
//
// Description: Returns the z-coordinate the character would have if it moved
//              forward one step.
//
//      Inputs: None.
//
//     Outputs: The character's next anticipated z-coordinate.
//------------------------------------------------------------------------------
double Character::GetNextZ() const {
  double next_z = battlefield_->GetZ(GetNextX(), GetNextY());
  if (next_z < battlefield_->GetWaterHeight()) {
    next_z = battlefield_->GetWaterHeight();
  }
  next_z += z_offset_;

  return next_z;
}

//------------------------------------------------------------------------------
//      Method: MoveForward
//
// Description: Moves the character one step forward, if unobstructed.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::MoveForward() {
  double new_x = GetNextX();
  double new_y = GetNextY();
  double new_z = GetNextZ();

  if (battlefield_->IsLegalPosition(new_x, new_y, new_z)) {
    x_ = new_x;
    y_ = new_y;
    z_ = new_z;
  }
}

//------------------------------------------------------------------------------
//      Method: MoveBackward
//
// Description: Moves the character one step backward, if unobstructed.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::MoveBackward() {
  double new_x = x_ - cos(rotation_ * PI / 180) * movement_rate_;
  double new_y = y_ - sin(rotation_ * PI / 180) * movement_rate_;

  if (battlefield_->IsLegalPosition(new_x, y_, collision_radius_)) {
    x_ = new_x;
  }
  if (battlefield_->IsLegalPosition(x_, new_y, collision_radius_)) {
    y_ = new_y;
  }
}

//------------------------------------------------------------------------------
//      Method: StrafeLeft
//
// Description: Moves the character one step to the left, if unobstructed.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::StrafeLeft() {
  double new_x = x_ - sin(rotation_ * PI / 180) * movement_rate_;
  double new_y = y_ - cos(rotation_ * PI / 180) * movement_rate_ * -1.0;

  if (battlefield_->IsLegalPosition(new_x, y_, collision_radius_)) {
    x_ = new_x;
  }
  if (battlefield_->IsLegalPosition(x_, new_y, collision_radius_)) {
    y_ = new_y;
  }
}

//------------------------------------------------------------------------------
//      Method: StrafeRight
//
// Description: Moves the character one step to the right, if unobstructed.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::StrafeRight() {
  double new_x = x_ - sin(rotation_ * PI / 180) * movement_rate_ * -1.0;
  double new_y = y_ - cos(rotation_ * PI / 180) * movement_rate_;

  if (battlefield_->IsLegalPosition(new_x, y_, collision_radius_)) {
    x_ = new_x;
  }
  if (battlefield_->IsLegalPosition(x_, new_y, collision_radius_)) {
    y_ = new_y;
  }
}

//------------------------------------------------------------------------------
//      Method: RotateLeft
//
// Description: Rotates the character to the left.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::RotateLeft() {
  rotation_ += rotation_rate_;
}

//------------------------------------------------------------------------------
//      Method: RotateRight
//
// Description: Rotates the character to the right.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::RotateRight() {
  rotation_ -= rotation_rate_;
}

//------------------------------------------------------------------------------
//      Method: IsPlayer
//
// Description: Determines whether the character is the player character.
//
//      Inputs: None.
//
//     Outputs: Returns 'true' if the character's type corresponds to a player
//              character type, 'false' otherwise.
//------------------------------------------------------------------------------
bool Character::IsPlayer() const {
  return true;
}

//------------------------------------------------------------------------------
//      Method: IsOnGround
//
// Description: Determines whether the character is touching the ground.
//
//      Inputs: None.
//
//     Outputs: Returns 'true' if the character's feet are touching the ground,
//              'false' otherwise.
//------------------------------------------------------------------------------
bool Character::IsOnGround() {
  if (z_ <= kDefaultZOffset) {
    z_ = kDefaultZOffset;
  }

  return z_ == kDefaultZOffset;
}

//------------------------------------------------------------------------------
//      Method: Act
//
// Description: Executes AI behavior for the character. (Simplified for now.)
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::Act() {
  if (IsPlayer()) {
    return;
  } else if (rand() % 5) {
    RotateRight();
  }
  MoveForward();
}

//------------------------------------------------------------------------------
//      Method: Draw
//
// Description: Draws the character.
//
//      Inputs: None.
//
//     Outputs: None.
//------------------------------------------------------------------------------
void Character::Draw() {
  // Draw the character's body:
  glColor3d(red_, green_, blue_);
  glPushMatrix();
  glTranslated(x_, y_, z_);
  glRotated(rotation_, 0, 0, 1);
  drawTriangle(0.4, 0, -0.4, 0.2, -0.4, -0.2);
  /*glBegin(GL_QUADS);
  glVertex3d(-0.25, -0.25, -0.25);
  glVertex3d(0.25, -0.25, -0.25);
  glVertex3d(0.25, 0.25, 0.25);
  glVertex3d(-0.25, 0.25, 0.25);*/
  glEnd();

  /*// Draw the character's limbs:
  glPushMatrix();
  glTranslated(0, -0.025, 0);
  glrotated(mLegrotation_, 0, 0, 1);
  glBegin(GL_LINES);
  glVertex2d(0, 0.025);
  glVertex2d(0, 0.1);
  glEnd();
  glPopMatrix();*/

  glPopMatrix();
}
