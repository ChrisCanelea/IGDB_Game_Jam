// Class implementation for Player

#include "player.hpp"
#include "enemy.hpp"
#include "globals.hpp"


// constructors
Player::Player() // Default constructor
{
    this->sprite = LoadTexture("assets/squareNinja.png");
    this->hitbox = Rectangle {0, 0, 50, 50}; // Default hitbox is a 50x50 square at (0, 0)
    this->speed = 10;
    this->direction = SOUTH;
    this->invulnTime = 0;
    this->enemyReference = NULL;
}

Player::Player(Rectangle hitbox_) // Constructor with parameters
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_;
    this->speed = 10;
    this->direction = SOUTH;
    this->invulnTime = 0;
    this->enemyReference = NULL;
}

// getters
Texture2D Player::getSprite() // returns sprite
{
    return this->sprite;
}

Rectangle Player::getHitbox() // returns hitbox
{
    return this->hitbox;
}

float Player::getSpeed() // returns speed
{
    return this->speed;
}

Direction Player::getDirection() // returns direction
{
    return this->direction;
}

float Player::getInvulnTime() // returns the number of invulnerability frames
{
    return this->invulnTime;
}

Enemy* Player::getEnemyReference() // returns the address of the enemy the player is interacting with
{
    return this->enemyReference;
}


Vector2 Player::getPos() // returns the player position
{
    Vector2 pos = {this->getHitbox().x, this->getHitbox().y};
    return pos;
}

Vector2 Player::getCenter() // returns the player's center position
{
    Vector2 pos = {this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight()/2};
    return pos;
}

float Player::getWidth() // returns width of hitbox
{
    return this->hitbox.width;
}

float Player::getHeight() // returns height of hitbox
{
    return this->hitbox.height;
}

// setters
void Player::setSprite(Texture2D sprite_)
{
    this->sprite = sprite_;
}

void Player::setHitbox(Rectangle hitbox_) // sets hitbox
{
    this->hitbox = hitbox_;
}

void Player::setSpeed(float speed_) // sets speed
{
    this->speed = speed_;
}

void Player::setDirection(Direction direction_) // sets direction
{
    this->direction = direction_;
}

void Player::setInvulnTime(float invulnTime_) // sets the number of invulnerability frames
{
    this->invulnTime = invulnTime_;
}

void Player::setEnemyReference(Enemy* enemyReference_) // sets the address of the enemy the player is interacting with
{
    this->enemyReference = enemyReference_;
}


void Player::setPos(Vector2 pos_) // sets player position
{
    this->hitbox.x = pos_.x;
    this->hitbox.y = pos_.y;
}

void Player::setX(float x_) // sets x position (top left corner of hitbox)
{
    this->hitbox.x = x_;
}

void Player::setY(float y_) // sets y position (top left corner of hitbox)
{
    this->hitbox.y = y_;
}

void Player::setWidth(float width_) // sets width of hitbox
{
    this->hitbox.width = width_;
}

void Player::setHeight(float height_) // sets height of hitbox
{
    this->hitbox.height = height_;
}

//other
void Player::processCooldowns() // processes cooldowns (called once per frame)
{
    if (this->getInvulnTime() > 0)
    {
        this->invulnTime -= 1;
    }
}

void Player::movePlayer() // moves the player based on input
{
    if (this->getInvulnTime() > 0)
    {
        if (this->getInvulnTime() > INVULN_FRAMES/2)
        {
            this->enemyKnockback();

        }

        this->setInvulnTime(this->getInvulnTime() - 1);
    }
    
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->setDirection(NORTHEAST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getPos().x + x_speed);
        this->setY(this->getPos().y - x_speed);

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
    {
        this->setDirection(SOUTHEAST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getPos().x + x_speed);
        this->setY(this->getPos().y + x_speed);

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        this->setDirection(SOUTHWEST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getPos().x - x_speed);
        this->setY(this->getPos().y + x_speed);

    } else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
    {
        this->setDirection(NORTHWEST);
        float x_speed = sqrt((speed * speed) / 2);
        this->setX(this->getPos().x - x_speed);
        this->setY(this->getPos().y - x_speed);

    } else if (IsKeyDown(KEY_W))
    {
        this->setDirection(NORTH);
        this->setY(this->getPos().y - this->getSpeed());

    } else if (IsKeyDown(KEY_D))
    {
        this->setDirection(EAST);
        this->setX(this->getPos().x + this->getSpeed());

    } else if (IsKeyDown(KEY_S))
    {
        this->setDirection(SOUTH);
        this->setY(this->getPos().y + this->getSpeed());

    } else if (IsKeyDown(KEY_A))
    {
        this->setDirection(WEST);
        this->setX(this->getPos().x - this->getSpeed());

    }
}

void Player::enemyKnockback() // knocks the player away from an enemy (called when collision with an enemy is detected)
{
    Vector2 dist = Vector2Subtract(this->getPos(), (*this->enemyReference).getPos());
    Vector2 normalDist = Vector2Normalize(dist);

    this->setX(this->getPos().x + normalDist.x * (this->getInvulnTime()*getInvulnTime()/35));
    this->setY(this->getPos().y + normalDist.y * (this->getInvulnTime()*getInvulnTime()/35));

}

void Player::drawPlayer() // draws the player sprite
{
    Rectangle spriteRect = {(float)16*(this->getDirection() + 1), 0, 16, 16};
    if (this->getInvulnTime() == 0)
    {
        DrawTexturePro(this->sprite, spriteRect, this->hitbox, Vector2 {0, 0}, 0, WHITE);

    } else
    {
        DrawRectangle(this->getPos().x, this->getPos().y, this->getWidth(), this->getHeight(), RED);
        
    }
    // DrawTextureRec(this->sprite, this->hitbox, Vector2 {this->hitbox.x, this->hitbox.y}, WHITE);
    // DrawTexture(this->sprite, this->hitbox.x, this->hitbox.y, WHITE);
}

Texture2D Player::loadSprite() 
{
    return LoadTexture("assets/squareNinja.png");
}