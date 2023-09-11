// Class implementation for player

#include "enemy.hpp"
#include "globals.hpp"


// constructors
Enemy::Enemy() // Default constructor
{
    this->sprite = loadSprite();
    this->hitbox = Rectangle {0, 0, 50, 50}; // Default hitbox is a 50x50 square at (0, 0)
    this->speed = 2.0f;
    this->directionFacing = Vector2 {0, 1};
    this->isActive = false;
    this->theVoid = {0,0};
    this->playerLocation = {0,0};
    this->directionBlocking = {0,-1};
    this->attackAngle = 45;
}

Enemy::Enemy(Rectangle hitbox_, Vector2 theVoid_) // Constructor with parameters
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_;
    this->speed = 2.0f;
    this->directionFacing = Vector2 {0, 1};
    this->isActive = false;
    this->theVoid = theVoid_;
    this->playerLocation = {0,0};
    this->directionBlocking = {0,-1};
    this->attackAngle = 45;
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

Vector2 Enemy::getDirectionFacing() // returns direction unit vector
{
    return this->directionFacing;
}

bool Enemy::getIsActive() 
{
    return this->isActive;
}

Vector2 Enemy::getTheVoid() 
{
    return this->theVoid;
}

Vector2 Enemy::getPlayerLocation() 
{
    return this->playerLocation;
}

Vector2 Enemy::getDirectionBlocking() 
{
    return this->directionBlocking;
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

float Enemy::getAttackAngle()
{
    return this->attackAngle;
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

void Enemy::setDirectionFacing(Vector2 directionFacing_) // sets direction
{
    this->directionFacing = Vector2Normalize(directionFacing_);
}

void Enemy::setIsActive(bool isActive_) 
{
    this->isActive = isActive_;
}

void Enemy::setPlayerLocation(Vector2 playerLocation_) 
{
    this->playerLocation = playerLocation_;
}

void Enemy::setDirectionBlocking(Vector2 directionBlocking_) 
{
    this->directionBlocking = directionBlocking_;
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

void Enemy::setAttackAngle(float attackAngle_)
{
    this->attackAngle = attackAngle_;
}

//other
void Enemy::moveEnemy()
{
    if (this->getIsActive()) // only move if active
    {
        if (Vector2Distance(this->getCenter(), this->getPlayerLocation()) > 1200)
        {

        } else if (Vector2Distance(this->getCenter(), this->getPlayerLocation()) > 300)
        {
            this->setPos(Vector2Add(this->getPos(), Vector2Scale(this->getDirectionFacing(), this->getSpeed())));
        } else
        {
            if (GetRandomValue(1, 1000) == 1)
            {
                this->setAttackAngle(GetRandomValue(30, 60));
            }
            
            if (GetRandomValue(1, 1000) == 1)
            {
                this->setAttackAngle(this->getAttackAngle() * -1);
            }
            this->setPos(Vector2Add(this->getPos(), Vector2Scale(Vector2Rotate(this->getDirectionFacing(), this->getAttackAngle()), this->getSpeed())));
            
        }
    }

    // if (this->getIsActive()) // only move if active
    // {
    //     if (Vector2Distance(this->getCenter(), this->getPlayerLocation()) > 250.0f)
    //     {
    //         this->setPos(Vector2Add(this->getPos(), Vector2Scale(this->getDirectionFacing(), this->getSpeed())));
    //     } else 
    //     {
    //         if (GetRandomValue(0, 99) > 30) // 70% chance to orbit
    //         {
    //             this->setPos(Vector2Add(this->getPos(), Vector2Scale(Vector2Rotate(this->getDirectionFacing(), DEG2RAD * -90.0f), this->getSpeed())));
    //         } else 
    //         {
    //             this->setPos(Vector2Add(this->getPos(), Vector2Scale(this->getDirectionFacing(), this->getSpeed())));
    //         }
    //     }
    // }
}

void Enemy::drawEnemy(Rectangle playArea) // draws the enemy sprite
{
    // DrawTextureRec(this->sprite, this->hitbox, Vector2 {this->hitbox.x, this->hitbox.y}, WHITE);
    // DrawTexture(this->sprite, this->hitbox.x, this->hitbox.y, WHITE);
    DrawTexturePro(this->getSprite(), Rectangle {15, 1, 40, 62}, this->getHitbox(), Vector2 {0, 0}, 0, WHITE);
    //DrawRectangleRec(GetCollisionRec(this->getHitbox(), playArea), GREEN);
}

Texture2D Enemy::loadSprite() 
{
    return LoadTexture("assets/enemySprite.png");
}

void Enemy::killEnemy() 
{
    this->setPos(this->getTheVoid());
    this->setIsActive(false);
}

void Enemy::generateDirectionBlocking() 
{
    switch (GetRandomValue(0,2)) 
    {
        case 0:
            this->setDirectionBlocking({1,0}); // block right
            break;
        case 1:
            this->setDirectionBlocking({0,-1}); // block up
            break;
        case 2:
            this->setDirectionBlocking({-1,0}); // block left
            break;
    }
}

void Enemy::generateDirectionFacing() 
{
    this->setDirectionFacing(Vector2Normalize(Vector2Subtract(this->getPlayerLocation(), this->getCenter())));
    
    // random shake variant
    // this->setDirectionFacing(Vector2Rotate(Vector2Normalize(Vector2Subtract(this->getPlayerLocation(), this->getPos())), (float)(DEG2RAD * GetRandomValue(-60, 60))));
}

void Enemy::drawBlockIndicator() 
{
    Vector2 vertex = {0, 24};
    DrawTriangle(Vector2Add(this->getCenter(), Vector2Rotate(vertex, -120)), Vector2Add(this->getCenter(), {0, 24}), Vector2Add(this->getCenter(), Vector2Rotate(vertex, 120)), RED);
}