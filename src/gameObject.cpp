// Class implementation for gameObject

#include "gameObject.hpp"


// constructors
gameObject::gameObject() // Default constructor
{
    this->hitbox = Rectangle {0, 0, 50, 50}; // Default hitbox is a 50x50 square at (0, 0)
    this->dx = 0;
    this->dy = 0;
    this->state = STILL;
}

gameObject::gameObject(Rectangle hitbox_, int dx_, int dy_) // Constructor with parameters
{
    this->hitbox = hitbox_;
    this->dx = dx_;
    this->dy = dy_;
    this->state = STILL;
}

// getters
int gameObject::getDx() // returns x speed
{
    return this->dx;
}

int gameObject::getDy() // returns y speed
{
    return this->dy;
}

int gameObject::getLeft() // returns x position of left of hitbox
{
    return this->hitbox.x;
}

int gameObject::getRight() // returns x position of right of hitbox
{
    return this->hitbox.x + this->hitbox.width;
}

int gameObject::getTop() // returns y position of top of hitbox
{
    return this->hitbox.y;
}

int gameObject::getBottom() // returns y position of bottom of hitbox
{
    return this->hitbox.y + this->hitbox.height;
}

int gameObject::getWidth() // returns width of hitbox
{
    return this->hitbox.width;
}

int gameObject::getHeight() // returns height of hitbox
{
    return this->hitbox.height;
}

Rectangle gameObject::getHitbox() // returns hitbox
{
    return this->hitbox;
}

gameObjectState gameObject::getState() // returns state of gameObject
{
    return this->state;
}

// setters
void gameObject::setDx(int dx_) // sets x speed
{
    this->dx = dx_;
}

void gameObject::setDy(int dy_) // sets y speed
{
    this->dy = dy_;
}

void gameObject::setX(int x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void gameObject::setY(int y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void gameObject::setWidth(int width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void gameObject::setHeight(int height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

void gameObject::setHitbox(Rectangle hitbox_) // sets hitbox
{
    this->hitbox = hitbox_;
}

void gameObject::setState(gameObjectState state_) // sets the state of the gameObject
{
    this->state = state_;
}