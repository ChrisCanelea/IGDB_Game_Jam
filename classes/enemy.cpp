// Class implementation for player

#include "enemy.hpp"
#include "globals.hpp"


// constructors
Enemy::Enemy() // Default constructor
{
    this->sprite = LoadTexture("assets/Markus.png");
    this->hitbox = Rectangle {0, 0, 50, 50}; // Default hitbox is a 50x50 square at (0, 0)
    this->speed = 5.0f;
    this->direction = SOUTH;
    this->isActive = false;
}

Enemy::Enemy(Rectangle hitbox_) // Constructor with parameters
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_;
    this->speed = 5.0f;
    this->direction = SOUTH;
    this->isActive = false;
}

// getters
Texture2D Enemy::getSprite() // returns sprite
{
    return this->sprite;
}

Rectangle Enemy::getHitbox() // returns hitbox
{
    return this->hitbox;
}

int Enemy::getSpeed() // returns speed
{
    return this->speed;
}

Direction Enemy::getDirection() // returns direction
{
    return this->direction;
}

bool Enemy::getIsActive() 
{
    return this->isActive;
}

Vector2 Enemy::getPos() // returns the Enemy position
{
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Enemy::getCenter() // returns the player's center position
{
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Enemy::getWidth() // returns width of hitbox
{
    return this->hitbox.width;
}

float Enemy::getHeight() // returns height of hitbox
{
    return this->hitbox.height;
}

// setters
void Enemy::setSprite(Texture2D sprite_)
{
    this->sprite = sprite_;
}

void Enemy::setHitbox(Rectangle hitbox_) // sets hitbox
{
    this->hitbox = hitbox_;
}

void Enemy::setSpeed(float speed_) // sets speed
{
    this->speed = speed_;
}

void Enemy::setDirection(Direction direction_) // sets direction
{
    this->direction = direction_;
}

void Enemy::setIsActive(bool isActive_) 
{
    this->isActive = isActive_;
}

void Enemy::setPos(Vector2 pos_) // sets Enemy position
{
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Enemy::setX(float x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void Enemy::setY(float y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void Enemy::setWidth(float width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void Enemy::setHeight(float height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

//other
void Enemy::moveEnemy()
{

}

void Enemy::drawEnemy() // draws the player sprite
{
    // DrawTextureRec(this->sprite, this->hitbox, Vector2 {this->hitbox.x, this->hitbox.y}, WHITE);
    // DrawTexture(this->sprite, this->hitbox.x, this->hitbox.y, WHITE);
    if (this->getIsActive()) DrawRectangle(this->getPos().x, this->getPos().y, this->getWidth(), this->getHeight(), GREEN);
    else DrawRectangle(this->getPos().x, this->getPos().y, this->getWidth(), this->getHeight(), LIME);
}

Texture2D Enemy::loadSprite() 
{
    return LoadTexture("");
}