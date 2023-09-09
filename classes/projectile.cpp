// Class implementation for projectiles

#include "projectile.hpp"

//constructors
Projectile::Projectile() // Default constructor
{
    this->sprite = LoadTexture("");
    this->hitbox = Rectangle {0, 0, 30, 10};
    this->rotation = 0; // supposedly aligned with x axis
    this->destination = {0,0};
    this->velocity = 0;
    this->direction = {0,0};
    this->isActive = false;
    this->theVoid = {0,0};
}

Projectile::Projectile(Rectangle hitbox_, Vector2 destination_, Vector2 theVoid_) // Constructor with params 
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_;
    this->destination = destination_;
    this->velocity = 3.0f;
    this->direction = calculateDirection();
    this->rotation = calculateRotation();
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

float Projectile::getRotation() // returns rotation 
{
    return this->rotation;
}

Vector2 Projectile::getDestination() // returns destination 
{
    return this->destination;
}

float Projectile::getVelocity() //returns velocity 
{
    return this->velocity;
}

Vector2 Projectile::getDirection() // returns direction vector 
{
    return this->direction;
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

void Projectile::setRotation(float rotation_) // sets rotation
{
    this->rotation = rotation_;
}

void Projectile::setDestination(Vector2 destination_) // sets direction
{
    this->destination = destination_;
}

void Projectile::setIsActive(bool isActive_) 
{
    this->isActive = isActive_;
}

void Projectile::setVelocity(float velocity_) // sets velocity 
{
    this->velocity = velocity_;
}

void Projectile::setDirection(Vector2 direction_) // sets direction vector 
{
    this->direction = direction_;
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
Vector2 Projectile::calculateDirection() 
{
    return Vector2Normalize(Vector2Rotate(Vector2Subtract(this->getDestination(), this->getPos()), GetRandomValue(-8, 8)));
}

float Projectile::calculateRotation()
{   
    return RAD2DEG * Vector2Angle({1,0}, this->getDirection());
}

void Projectile::moveProjectile() // calculate and apply the motion of the projectile 
{
    if (this->getIsActive()) 
    {
        this->setPos(Vector2Add(this->getPos(), Vector2Scale(this->getDirection(), this->getVelocity())));
    }
}

void Projectile::drawProjectile() // draws projectile 
{
    if (this->getIsActive()) DrawRectanglePro(this->getHitbox(), {0,0}, this->getRotation(), ORANGE);
    else DrawRectanglePro(this->getHitbox(), {0,0}, this->getRotation(), RED);
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