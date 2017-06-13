#include "Enemy.h"



/*
* DEFAULT CONSTRUCTOR - since this is just a parent-class
*/
Enemy::Enemy()
{
}



/*
* DESTRUCTOR - in here we would clean up after our enemy-object has died
*/
Enemy::~Enemy()
{
}



/*
* GET POSITION - return the position of our NPC
*/
sf::Vector2f Enemy::getPosition()
{
	return sprite.getPosition();
}



/*
* GET BOUNDING BOX - return the bounding box of this enemy
*/
sf::FloatRect Enemy::getBoundingBox()
{
	return sprite.getGlobalBounds();
}



/*
* NEXT WAYPOINT - return the current waypoint and count to the next one
*/
sf::Vector2f Enemy::nextWaypoint()
{
	sf::Vector2f waypoint;

	// if the enemy-object has waypoints, get the next one and count up the counter
	if (waypoints.size() > 0) {

		waypoint = waypoints[currentWaypointNumber];

		if (currentWaypointNumber >= waypoints.size() - 1)
			currentWaypointNumber = 0;
		else
			currentWaypointNumber++;
	}
	else {	// if not just use the enemies position - this means he will not move
		waypoint = getPosition();
	}

	return waypoint;
}



/*
* IS DEAD - returns if our hero has died
*/
bool Enemy::isDead()
{
	return dead;
}



/*
* SET POSITION - set a new postion for the enemy
*/
void Enemy::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}



/*
* SET POSITION - set a new postion for the enemy
*/
void Enemy::addWaypoint(sf::Vector2f position)
{
	waypoints.push_back(position);
}



/*
* SET DEATH ANIMATION - set the death animation for the enemy
*/
void Enemy::setDeathAnimation(sf::Texture & texture)
{
	// set texture and animation
	poof.setTexture(texture);
	poofAnimation.setTexture(texture, sf::Vector2u(5, 1), 0.05f, true);
}



/*
* SET HIT SOUND - set the hit sound for the enemy
*/
void Enemy::setHitSound(sf::SoundBuffer & soundBuffer)
{
	sound_getHit.setBuffer(soundBuffer);
}



/*
* UPDATE - update our enemy-object (called every cycle)
*/
void Enemy::update(float elapsedTime, sf::FloatRect heroBoundingBox)
{
	sf::Vector2f movement(0.0f, 0.0f);


	// check for death
	if (hp <= 0) {

		// play death animation and if its done set the enemy to "dead"
		if (poof.getGlobalBounds().width != 0 && !poofAnimation.animationDone()) {
			dying = true;

			// animate the death
			poofAnimation.update(0, elapsedTime);
			poof.setTextureRect(poofAnimation.uvRect);

			poof.setPosition(getPosition());

		}
		else {
			dead = true;
		}

	}
	else {
		// if not dead do everything else

		// Move
		if (moving) {
			// get the angle between two points
			float angle = atan2(currentWaypoint.y - getPosition().y, currentWaypoint.x - getPosition().x);

			// set the waypoint
			sf::Vector2f direction(std::cos(angle), std::sin(angle));

			// move towards the waypoint
			movement.x = direction.x * speed * elapsedTime;
			movement.y = direction.y * speed * elapsedTime;

			// if the waypoint (taget area to make it more fluid) is reached get back to waiting
			sf::FloatRect targetArea(currentWaypoint.x - 1, currentWaypoint.y - 1, 2, 2);

			if (targetArea.contains(getPosition()))
				moving = false;

		}
		else {
			waitTime += elapsedTime;

			// wait for a time before moving to the next waypoint
			if (waitTime > 1.5f) {
				// this is our version of enemy AI
				sf::FloatRect aggroRectangle(getBoundingBox().left - aggroRange, getBoundingBox().top - aggroRange, (aggroRange * 2) - getBoundingBox().width, (aggroRange * 2) - getBoundingBox().width);
				sf::Vector2f heroPosition(heroBoundingBox.left, heroBoundingBox.top);

				if (aggroRectangle.intersects(heroBoundingBox))		// if the hero is within aggro-range move towards the hero
					currentWaypoint = heroPosition;
				else												// if not just take the next waypoint
					currentWaypoint = nextWaypoint();

				moving = true;
				waitTime = 0.0f;
			}
		}


		// Taking Damage
		if (flinching) {
			iFrames += elapsedTime;

			// Hit color
			sprite.setColor(sf::Color(255, 70, 70, 255));

			if (iFrames > 0.3f) {		// flinching state lasts this long
				flinching = false;
				sprite.setColor(sf::Color::White);
				iFrames = 0.0f;
			}
		}


		// Animate and Move
		animation.update(0, elapsedTime);

		if (moving && animation.hasSpecialAnimation())
			// set movement animation if there is one
			sprite.setTextureRect(sf::IntRect(50, animation.uvRect.height * 0, animation.uvRect.width, animation.uvRect.height));
		else
			sprite.setTextureRect(animation.uvRect);

		sprite.move(movement);
	}
}




/*
* DRAW - pass our enemy-object on to the window so it can be drawn
*/
void Enemy::draw(sf::RenderWindow & window)
{
	if (dying)
		window.draw(poof);
	else
		window.draw(sprite);
}



/*
* TAKE DAMAGE - this is called when the enemy is struck with a sword-object and reduces the hp
*/
void Enemy::takeDamage(int damage)
{
	// Reduce Hp
	if (!flinching) {
		hp -= damage;
		sound_getHit.play();
		flinching = true;
	}
}



/*
* GET DAMAGE - get the damage value for this enemy
*/
int Enemy::getDamage()
{
	return damage;
}
