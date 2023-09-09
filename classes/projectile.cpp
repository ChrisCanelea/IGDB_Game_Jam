// Class implementation for projectiles

#include "projectile.hpp"

//constructors
Projectile::Projectile() // Default constructor
{
    this->sprite = LoadTexture("");
    this->hitbox = Rectangle {0, 0, 60, 20};
    this->isVertical = false;
    this->velocity = 0;
    this->isActive = false;
    this->theVoid = {0,0};
}

Projectile::Projectile(Rectangle hitbox_, bool isVertical_, Vector2 theVoid_) // Constructor with params 
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_;
    this->isVertical = isVertical_;
    this->velocity = 3.0f;
    this->isActive = false;
    this->theVoid = theVoid_;
}

// getters
Texture2D Projectile::getSprite() // returns sprite
{
    return this->sprite;
}

Rectangle Projectile::getHitbox() // returns hitbox
{
    return this->hitbox;
}

bool Projectile::getIsVertical() // returns rotation 
{
    return this->isVertical;
}

float Projectile::getVelocity() //returns velocity 
{
    return this->velocity;
}

bool Projectile::getIsActive() 
{
    return this->isActive;
}

Vector2 Projectile::getTheVoid() 
{
    return this->theVoid;
}

Vector2 Projectile::getPos() // returns the projectile's position 
{
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Projectile::getCenter() 
{
    return {this->getHitbox().x + (this->getHitbox().width/2), this->getHitbox().y + (this->getHitbox().height/2)};
}

float Projectile::getWidth() // returns width of hitbox 
{
    return this->hitbox.width;
}

float Projectile::getHeight() // returns height of hitbox 
{
    return this->hitbox.height;
}

//setters
void Projectile::setSprite(Texture2D sprite_)
{
    this->sprite = sprite_;
}

void Projectile::setHitbox(Rectangle hitbox_) // sets hitbox
{
    this->hitbox = hitbox_;
}

void Projectile::setIsVertical(bool isVertical_) // sets rotation
{
    this->isVertical = isVertical_;
}

void Projectile::setVelocity(float velocity_) // sets velocity 
{
    this->velocity = velocity_;
}

void Projectile::setIsActive(bool isActive_) 
{
    this->isActive = isActive_;
}

void Projectile::setPos(Vector2 pos_) // sets projectile position
{
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Projectile::setX(float x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void Projectile::setY(float y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void Projectile::setWidth(float width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void Projectile::setHeight(float height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

// other
void Projectile::moveProjectile() // calculate and apply the motion of the projectile 
{
    if (this->getIsActive()) 
    {
        //move
    }
}

void Projectile::drawProjectile() // draws projectile 
{
    if (this->getIsActive()) DrawRectanglePro(this->getHitbox(), {0,0}, 0, ORANGE);
    else DrawRectanglePro(this->getHitbox(), {0,0}, 0, RED);
}

Texture2D Projectile::loadSprite() 
{
    return LoadTexture("assets/arrow.png");
}

void Projectile::killProjectile() 
{
    this->setPos(this->getTheVoid());
    this->setIsActive(false);
}