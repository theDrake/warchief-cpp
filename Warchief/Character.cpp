//*****************************************************************************
//	  Filename: Character.cpp
//
//	    Author: David C. Drake (www.davidcdrake.com)
//
// Description: Definition of a 'Character' class responsible for representing
//				      both player and non-player characters.
//*****************************************************************************

#include "Character.h"

//-----------------------------------------------------------------------------
//	    Method: Character
//
// Description: Constructs a Character object (via the 'initialize' method)
//				      according to a given character type. Also provides the
//				      character with a given pointer to a Battlefield object.
//
//	    Inputs: type  - Integer representing the creature's type.
//				      battlefield - Pointer to the current Battlefield object.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
Character::Character(int race, int type, Battlefield* battlefield)
{
	initialize(race, type, battlefield);
}

//-----------------------------------------------------------------------------
//	    Method: ~Character
//
// Description: Destructor.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
Character::~Character()
{}

//-----------------------------------------------------------------------------
//	    Method: initialize
//
// Description: Initializes the Character object according to a given
//				      character type. Also provides the character with a given
//				      pointer to a Battlefield object.
//
//	    Inputs: type  - Integer representing the creature's type.
//				      battlefield - Pointer to the current Battlefield object.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::initialize(int race, int type, Battlefield* battlefield)
{
	race_        = race;
  type_        = type;
	battlefield_ = battlefield;

  x_ = rand() % (int) battlefield_->getResolution();
	y_ = rand() % (int) battlefield_->getResolution();
	z_ = battlefield_->getZ(x_, y_);
	if (z_ < battlefield_->getWaterHeight())
	{
		z_ = battlefield_->getWaterHeight();
	}
	zOffset_ = DEFAULT_Z_OFFSET;
	z_ += zOffset_;
  
  height_			      = 0.3;
	movementRate_     = battlefield_->getResolution() / 8000;
	rotation_	        = 90.0;
	rotationRate_	    = battlefield_->getResolution() / 200;
	collisionRadius_  = 0.25;
	red_			        = 0.0;
	green_			      = 0.0;
	blue_			        = 0.0;
}

//-----------------------------------------------------------------------------
//	    Method: getType
//
// Description: Returns the character's type.
//
//	    Inputs: None.
//
//	   Outputs: An integer representing the character's type.
//-----------------------------------------------------------------------------
int Character::getType() const
{
	return type_;
}

//-----------------------------------------------------------------------------
//	    Method: getX
//
// Description: Returns the character's x-coordinate.
//
//	    Inputs: None.
//
//	   Outputs: The character's x-coordinate.
//-----------------------------------------------------------------------------
double Character::getX() const
{
	return x_;
}

//-----------------------------------------------------------------------------
//	    Method: getY
//
// Description: Returns the character's y-coordinate.
//
//	    Inputs: None.
//
//	   Outputs: The character's y-coordinate.
//-----------------------------------------------------------------------------
double Character::getY() const
{
	return y_;
}

//-----------------------------------------------------------------------------
//	    Method: getZ
//
// Description: Returns the character's z-coordinate.
//
//	    Inputs: None.
//
//	   Outputs: The character's z-coordinate.
//-----------------------------------------------------------------------------
double Character::getZ() const
{
	return z_;
}

//-----------------------------------------------------------------------------
//	    Method: getZOffset
//
// Description: Returns the offset for the character's z-coordinate (i.e., the
//              distance between the character's z-coordinate and the z-
//              coordinate of the ground below).
//
//	    Inputs: None.
//
//	   Outputs: The character's z-coordinate offset.
//-----------------------------------------------------------------------------
double Character::getZOffset() const
{
	return zOffset_;
}

//-----------------------------------------------------------------------------
//	    Method: getHeight
//
// Description: Returns the character's height.
//
//	    Inputs: None.
//
//	   Outputs: The character's height.
//-----------------------------------------------------------------------------
double Character::getHeight() const
{
	return height_;
}

//-----------------------------------------------------------------------------
//	    Method: getRotation
//
// Description: Returns the character's rotation.
//
//	    Inputs: None.
//
//	   Outputs: The character's rotation.
//-----------------------------------------------------------------------------
double Character::getRotation() const
{
	return rotation_;
}

//-----------------------------------------------------------------------------
//	    Method: getRotationRate
//
// Description: Returns the character's rotation rate.
//
//	    Inputs: None.
//
//	   Outputs: The character's rotation rate.
//-----------------------------------------------------------------------------
double Character::getRotationRate() const
{
	return rotationRate_;
}

//-----------------------------------------------------------------------------
//	    Method: getMovementRate
//
// Description: Returns the character's movement rate.
//
//	    Inputs: None.
//
//	   Outputs: The character's movement rate.
//-----------------------------------------------------------------------------
double Character::getMovementRate() const
{
	return movementRate_;
}

//-----------------------------------------------------------------------------
//	    Method: getRed
//
// Description: Returns the red value of the character's base color.
//
//	    Inputs: None.
//
//	   Outputs: The red value of the character's base color.
//-----------------------------------------------------------------------------
double Character::getRed() const
{
	return red_;
}

//-----------------------------------------------------------------------------
//	    Method: getGreen
//
// Description: Returns the green value of the character's base color.
//
//	    Inputs: None.
//
//	   Outputs: The green value of the character's base color.
//-----------------------------------------------------------------------------
double Character::getGreen() const
{
	return green_;
}

//-----------------------------------------------------------------------------
//	    Method: getBlue
//
// Description: Returns the blue value of the character's base color.
//
//	    Inputs: None.
//
//	   Outputs: The blue value of the character's base color.
//-----------------------------------------------------------------------------
double Character::getBlue() const
{
	return blue_;
}

//-----------------------------------------------------------------------------
//	    Method: getNextX
//
// Description: Returns the x-coordinate the character would have if it moved
//				      forward one step.
//
//	    Inputs: None.
//
//	   Outputs: The character's next anticipated x-coordinate.
//-----------------------------------------------------------------------------
double Character::getNextX() const
{
	return x_ + cos(rotation_ * PI / 180) * movementRate_;
}

//-----------------------------------------------------------------------------
//	    Method: getNextY
//
// Description: Returns the y-coordinate the character would have if it moved
//			      	forward one step.
//
//	    Inputs: None.
//
//	   Outputs: The character's next anticipated y-coordinate.
//-----------------------------------------------------------------------------
double Character::getNextY() const
{
	return y_ + sin(rotation_ * PI / 180) * movementRate_;
}

//-----------------------------------------------------------------------------
//	    Method: getNextZ
//
// Description: Returns the z-coordinate the character would have if it moved
//				      forward one step.
//
//	    Inputs: None.
//
//	   Outputs: The character's next anticipated z-coordinate.
//-----------------------------------------------------------------------------
double Character::getNextZ() const
{
	double nextZ = battlefield_->getZ(getNextX(), getNextY());
	if (nextZ < battlefield_->getWaterHeight())
	{
		nextZ = battlefield_->getWaterHeight();
	}
	nextZ += zOffset_;

	return nextZ;
}

//-----------------------------------------------------------------------------
//	    Method: moveForward
//
// Description: Moves the character one step forward, if unobstructed.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::moveForward()
{
	double newX = getNextX();
	double newY = getNextY();
	double newZ = getNextZ();

	if (battlefield_->isLegalPosition(newX, newY, newZ))
	{
		x_ = newX;
		y_ = newY;
		z_ = newZ;
	}
}

//-----------------------------------------------------------------------------
//	    Method: moveBackward
//
// Description: Moves the character one step backward, if unobstructed.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::moveBackward()
{
	double newX = x_ - cos(rotation_ * PI / 180) * movementRate_;
	double newY = y_ - sin(rotation_ * PI / 180) * movementRate_;

	if (battlefield_->isLegalPosition(newX, y_, collisionRadius_))
	{
		x_ = newX;
	}
	if (battlefield_->isLegalPosition(x_, newY, collisionRadius_))
	{
		y_ = newY;
	}
}

//-----------------------------------------------------------------------------
//	    Method: strafeLeft
//
// Description: Moves the character one step to the left, if unobstructed.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::strafeLeft()
{
	double newX = x_ - sin(rotation_ * PI / 180) * movementRate_;
	double newY = y_ - cos(rotation_ * PI / 180) * movementRate_ * -1.0;

	if (battlefield_->isLegalPosition(newX, y_, collisionRadius_))
	{
		x_ = newX;
	}
	if (battlefield_->isLegalPosition(x_, newY, collisionRadius_))
	{
		y_ = newY;
	}
}

//-----------------------------------------------------------------------------
//	    Method: strafeRight
//
// Description: Moves the character one step to the right, if unobstructed.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::strafeRight()
{
	double newX = x_ - sin(rotation_ * PI / 180) * movementRate_ * -1.0;
	double newY = y_ - cos(rotation_ * PI / 180) * movementRate_;

	if (battlefield_->isLegalPosition(newX, y_, collisionRadius_))
	{
		x_ = newX;
	}
	if (battlefield_->isLegalPosition(x_, newY, collisionRadius_))
	{
		y_ = newY;
	}
}

//-----------------------------------------------------------------------------
//	    Method: rotateLeft
//
// Description: Rotates the character to the left.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::rotateLeft()
{
	rotation_ += rotationRate_;
}

//-----------------------------------------------------------------------------
//	    Method: rotateRight
//
// Description: Rotates the character to the right.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::rotateRight()
{
	rotation_ -= rotationRate_;
}

//-----------------------------------------------------------------------------
//	    Method: isPlayer
//
// Description: Determines whether the character is the player character.
//
//	    Inputs: None.
//
//	   Outputs: Returns 'true' if the character's type corresponds to a player
//				      character type, 'false' otherwise.
//-----------------------------------------------------------------------------
bool Character::isPlayer() const
{
  return true;
	/*return (type_ == PLAYER_BARBARIAN ||
			    type_ == PLAYER_WIZARD    ||
			    type_ == PLAYER_ELF		    ||
			    type_ == PLAYER_DWARF);*/
}

//-----------------------------------------------------------------------------
//	    Method: isOnGround
//
// Description: Determines whether the character is touching the ground.
//
//	    Inputs: None.
//
//	   Outputs: Returns 'true' if the character's feet are touching the ground,
//				      'false' otherwise.
//-----------------------------------------------------------------------------
bool Character::isOnGround()
{
	if (z_ <= DEFAULT_Z_OFFSET)
		z_ = DEFAULT_Z_OFFSET;

	return z_ == DEFAULT_Z_OFFSET;
}

//-----------------------------------------------------------------------------
//	    Method: act
//
// Description: Executes AI behavior for the character. (Simplified for now.)
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::act()
{
	if (isPlayer())
	{
		return;
	}

	if (rand() % 5)
	{
		rotateRight();
	}
	moveForward();
}

//-----------------------------------------------------------------------------
//	    Method: draw
//
// Description: Draws the character.
//
//	    Inputs: None.
//
//	   Outputs: None.
//-----------------------------------------------------------------------------
void Character::draw()
{
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
