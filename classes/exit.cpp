// Class implementation for Player

#include "exit.hpp"
#include "globals.hpp"


// constructors
Exit::Exit() // Default constructor
{
    this->sprite = LoadTexture("assets/squareNinja.png");
    this->hitbox = Rectangle {200, 200, 50, 50}; // Default hitbox is a 50x50 square at (200, 200)
}

// getters
Texture2D Exit::getSprite() // returns sprite
{
    return this->sprite;
}

Rectangle Exit::getHitbox() // returns hitbox
{
    return this->hitbox;
}

Vector2 Exit::getPos() // returns the exit position
{
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Exit::getCenter() // returns the exit's center position
{
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Exit::getWidth() // returns width of hitbox
{
    return this->hitbox.width;
}

float Exit::getHeight() // returns height of hitbox
{
    return this->hitbox.height;
}

// setters
void Exit::setSprite(Texture2D sprite_) // sets sprite
{
    this->sprite = sprite_;
}

void Exit::setHitbox(Rectangle hitbox_) // sets hitbox
{
    this->hitbox = hitbox_;
}


void Exit::setPos(Vector2 pos_) // sets exit position
{
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Exit::setX(float x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void Exit::setY(float y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void Exit::setWidth(float width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void Exit::setHeight(float height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

//other
void Exit::drawExit() // draws the player sprite
{    
    DrawRectangle(this->getPos().x, this->getPos().y, this->getWidth(), this->getHeight(), YELLOW);
}

Texture2D Exit::loadSprite() 
{
    return LoadTexture("assets/squareNinja.png");
}