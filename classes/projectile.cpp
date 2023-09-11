// Class implementation for projectiles

#include "projectile.hpp"

//constructors
Projectile::Projectile() // Default constructor
{
    this->sprite = LoadTexture("");
    this->hitbox = Rectangle {0, 0, 60, 20};
    this->orientation = 1;
    this->velocity = 0;
    this->isActive = false;
    this->theVoid = {0,0};
    this->sourceRec = {0,0,60,20};
    this->adjustProjectile();
}

Projectile::Projectile(Rectangle hitbox_, int orientation_, Vector2 theVoid_) // Constructor with params 
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_; //default hitbox
    this->orientation = orientation_;
    this->velocity = 3.0f;
    this->isActive = false;
    this->theVoid = theVoid_;
    this->sourceRec = {0,0,60,20};
    this->adjustProjectile();
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

int Projectile::getOrientation() // returns rotation 
{
    return this->orientation;
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

Rectangle Projectile::getSourceRec() 
{
    return this->sourceRec;
}

Vector2 Projectile::getPos() // returns the projectile's position 
{
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Projectile::getCenter() 
{
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Projectile::getX() 
{
    return this->getPos().x;
}

float Projectile::getY() 
{
    return this->getPos().y;
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

void Projectile::setOrientation(int orientation_) // sets rotation
{
    this->orientation = orientation_;
}

void Projectile::setVelocity(float velocity_) // sets velocity 
{
    this->velocity = velocity_;
}

void Projectile::setIsActive(bool isActive_) 
{
    this->isActive = isActive_;
}

void Projectile::setSourceRec(Rectangle sourceRec_) 
{
    this->sourceRec = sourceRec_;
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
        if (this->getOrientation()%2 == 0) // vertical 
        {
            this->setY(this->getY() + this->getVelocity());
        } else // horizontal
        {
            this->setX(this->getX() + this->getVelocity());
        }
    }
}

void Projectile::drawProjectile(Rectangle playArea) // draws projectile 
{
    Rectangle tempSource = GetCollisionRec(this->getHitbox(), playArea);

    if (this->getOrientation() == 0) // NORTH
    {
        this->setSourceRec({60, 60 - tempSource.height, tempSource.width, tempSource.height});
    } else if (this->getOrientation() == 1) // EAST
    {
        this->setSourceRec({0, 0, tempSource.width, tempSource.height});
    } else if (this->getOrientation() == 2) // SOUTH
    {
        this->setSourceRec({80, 0, tempSource.width, tempSource.height});
    } else // WEST
    {
        this->setSourceRec({60 - tempSource.width, 20, tempSource.width, tempSource.height});
    }

    DrawTexturePro(this->getSprite(), this->getSourceRec(), GetCollisionRec(this->getHitbox(), playArea), {0,0}, 0, WHITE);
}

Texture2D Projectile::loadSprite() 
{
    return LoadTexture("assets/arrowSprites.png");
}

void Projectile::killProjectile() 
{
    this->setPos(this->getTheVoid());
    this->setIsActive(false);
}

void Projectile::adjustProjectile() 
{
    if (this->getOrientation() == 0) // NORTH
    {
        this->setSourceRec({60,0,20,60});
        this->setHitbox({this->getPos().x, this->getPos().y, 20, 60});
        this->setVelocity(-3.0f);
    } else if (this->getOrientation() == 1) // EAST
    {
        this->setSourceRec({0,0,60,20});
        this->setHitbox({this->getPos().x, this->getPos().y, 60, 20});
        this->setVelocity(3.0f);
    } else if (this->getOrientation() == 2) // SOUTH
    {
        this->setSourceRec({80,0,20,60});
        this->setHitbox({this->getPos().x, this->getPos().y, 20, 60});
        this->setVelocity(3.0f);
    } else // WEST
    {
        this->setSourceRec({0,20,60,20});
        this->setHitbox({this->getPos().x, this->getPos().y, 60, 20});
        this->setVelocity(-3.0f);
    }
}