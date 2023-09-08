// Class implementation for player

#include "enemy.hpp"
#include <raylib.h>
#include <math.h>


// constructors
Enemy::Enemy() // Default constructor
{
    this->sprite = LoadTexture("assets/Markus.png");
    this->hitbox = Rectangle {0, 0, 50, 50}; // Default hitbox is a 50x50 square at (0, 0)
    this->speed = 10;
    this->direction = SOUTH;
}

Enemy::Enemy(Texture2D sprite_, Rectangle hitbox_, int speed_, Direction direction_) // Constructor with parameters
{
    this->sprite = sprite_;
    this->hitbox = hitbox_;
    this->speed = speed_;
    this->direction = direction_;
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


Vector2 Enemy::getPos() // returns the Enemy position
{
    Vector2 pos = {(float)this->getLeft(), (float)this->getTop()};
    return pos;
}

int Enemy::getLeft() // returns x position of left of hitbox
{
    return this->hitbox.x;
}

int Enemy::getRight() // returns x position of right of hitbox
{
    return this->hitbox.x + this->hitbox.width;
}

int Enemy::getTop() // returns y position of top of hitbox
{
    return this->hitbox.y;
}

int Enemy::getBottom() // returns y position of bottom of hitbox
{
    return this->hitbox.y + this->hitbox.height;
}

int Enemy::getWidth() // returns width of hitbox
{
    return this->hitbox.width;
}

int Enemy::getHeight() // returns height of hitbox
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

void Enemy::setSpeed(int speed_) // sets speed
{
    this->speed = speed_;
}

void Enemy::setDirection(Direction direction_) // sets direction
{
    this->direction = direction_;
}


void Enemy::setPos(Vector2 pos_) // sets Enemy position
{
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Enemy::setX(int x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void Enemy::setY(int y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void Enemy::setWidth(int width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void Enemy::setHeight(int height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

//other
void Enemy::moveEnemy() // moves the Enemy based on input
{
        if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->setDirection(NORTHEAST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getLeft() + x_speed);
        this->setY(this->getTop() - x_speed);

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
    {
        this->setDirection(SOUTHEAST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getLeft() + x_speed);
        this->setY(this->getTop() + x_speed);

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        this->setDirection(SOUTHWEST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getLeft() - x_speed);
        this->setY(this->getTop() + x_speed);

    } else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
    {
        this->setDirection(NORTHWEST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getLeft() - x_speed);
        this->setY(this->getTop() - x_speed);

    } else if (IsKeyDown(KEY_W))
    {
        this->setDirection(NORTH);
        this->setY(this->getTop() - this->getSpeed());

    } else if (IsKeyDown(KEY_D))
    {
        this->setDirection(EAST);
        this->setX(this->getLeft() + this->getSpeed());

    } else if (IsKeyDown(KEY_S))
    {
        this->setDirection(SOUTH);
        this->setY(this->getTop() + this->getSpeed());

    } else if (IsKeyDown(KEY_A))
    {
        this->setDirection(WEST);
        this->setX(this->getLeft() - this->getSpeed());

    }
}

void Enemy::drawEnemy() // draws the player sprite
{
    // DrawTextureRec(this->sprite, this->hitbox, Vector2 {this->hitbox.x, this->hitbox.y}, WHITE);
    // DrawTexture(this->sprite, this->hitbox.x, this->hitbox.y, WHITE);
    DrawRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), BLUE);
}