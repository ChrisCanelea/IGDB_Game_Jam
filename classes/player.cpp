// Class implementation for Player

#include "player.hpp"
#include "enemy.hpp"
#include "circle.hpp"
#include "globals.hpp"


// constructors
Player::Player() // Default constructor
{
    this->sprite = LoadTexture("assets/squareNinja.png");
    this->hitbox = Rectangle {0, 0, 50, 50}; // Default hitbox is a 50x50 square at (0, 0)
    this->speed = 10;
    this->direction = Vector2 {0, 1};
    this->attackHitbox = Circle {0, 0};
    this->attackCooldown = 0;
    this->invulnTime = 0;
    this->enemyReference = NULL;
    this->projectileReference = NULL;
}

Player::Player(Rectangle hitbox_) // Constructor with hitbox parameter
{
    this->sprite = loadSprite();
    this->hitbox = hitbox_;
    this->speed = 10;
    this->direction = {0, 1};
    this->attackHitbox = Circle{0, 0};
    this->attackCooldown = 0;
    this->invulnTime = 0;
    this->enemyReference = NULL;
    this->projectileReference = NULL;
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

Vector2 Player::getDirection() // returns direction unit vector
{
    return this->direction;
}

Circle Player::getAttackHitbox() // returns attackHitbox
{
    return this->attackHitbox;
}

float Player::getAttackCooldown() // returs the number of attack cooldown frames
{
    return this->attackCooldown;
}

float Player::getInvulnTime() // returns the number of invulnerability frames
{
    return this->invulnTime;
}

Enemy* Player::getEnemyReference() // returns the address of the enemy the player is interacting with
{
    return this->enemyReference;
}

Projectile* Player::getProjectileReference() // returns the address of the projectile the player is interacting with
{
    return this->projectileReference;
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

void Player::setDirection(Vector2 direction_) // sets direction
{
    this->direction = Vector2Normalize(direction_);
}

void Player::setAttackHitbox(Circle attackHitbox_) // sets attackHitbox
{
    this->attackHitbox = attackHitbox_;
}

void Player::setAttackCooldown(float attackCooldown_) // sets the number of attack cooldown frames
{
    this->attackCooldown = attackCooldown_;
}

void Player::setInvulnTime(float invulnTime_) // sets the number of invulnerability frames
{
    this->invulnTime = invulnTime_;
}

void Player::setEnemyReference(Enemy* enemyReference_) // sets the address of the enemy the player is interacting with
{
    this->enemyReference = enemyReference_;
}

void Player::setProjectileReference(Projectile* projectileReference_) // sets the address of the projectile the player is interacting with
{
    this->projectileReference = projectileReference_;
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

void Player::movePlayer() // moves the player based on input
{
    if (this->getAttackCooldown() > 0)
    {
        this->setAttackCooldown(this->getAttackCooldown() - 1);

    } else if (IsKeyPressed(KEY_J))
    {
        this->setAttackCooldown(ATTACK_COOLDOWN);

    }

    if (this->getInvulnTime() > 0) // invulnerable
    {
        if (this->getInvulnTime() > INVULN_FRAMES/2) // first half of invuln frames
        {
            if (this->enemyReference != NULL)
            {
                this->enemyKnockback();
            } else if (this->projectileReference != NULL)
            {
                this->projectileKnockback();
            }
        }

        this->setInvulnTime(this->getInvulnTime() - 1); // decrement invuln frames
    } else // not invulnerable
    {
        // reset references
        this->setEnemyReference(NULL);
        this->setProjectileReference(NULL);
    }

    bool shouldMove = true;
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->setDirection(Vector2 {1, -1});

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
    {
        this->setDirection(Vector2 {1, 1});

    } else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        this->setDirection(Vector2 {-1, 1});

    } else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
    {
        this->setDirection(Vector2 {-1, -1});

    } else if (IsKeyDown(KEY_W))
    {
        this->setDirection(Vector2 {0, -1});

    } else if (IsKeyDown(KEY_D))
    {
        this->setDirection(Vector2 {1, 0});

    } else if (IsKeyDown(KEY_S))
    {
        this->setDirection(Vector2 {0, 1});

    } else if (IsKeyDown(KEY_A))
    {
        this->setDirection(Vector2 {-1, 0});

    } else
    {
        shouldMove = false;
    }

    if (shouldMove) // ensures player doesn't keep moving after a button is released
    {
        this->setPos(Vector2Add(this->getPos(), Vector2Scale(this->getDirection(), speed)));
    }

    if (this->getAttackCooldown() > (ATTACK_COOLDOWN - 20))
    {
        Circle attack = {Vector2 {this->getCenter().x + (this->getDirection().x * ATTACK_OFFSET), this->getCenter().y + (this->getDirection().y * ATTACK_OFFSET)}, ATTACK_RADIUS}; // location of hitbox, radius of hitbox
        this->setAttackHitbox(attack);

    }
}

void Player::enemyKnockback() // knocks the player away from an enemy (called when collision with an enemy is detected)
{
    Vector2 dist = Vector2Subtract(this->getCenter(), (*this->getEnemyReference()).getCenter());
    Vector2 normalDist = Vector2Normalize(dist);

    this->setPos(Vector2Add(this->getPos(), Vector2Scale(normalDist, (this->getInvulnTime()*this->getInvulnTime())/35)));

}

void Player::projectileKnockback() // knocks the player away from a projectile (called when collision with a projectile is detected)
{
    Vector2 dist = Vector2Subtract(this->getCenter(), (*this->getProjectileReference()).getCenter());
    Vector2 normalDist = Vector2Normalize(dist);

    this->setPos(Vector2Add(this->getPos(), Vector2Scale(normalDist, (this->getInvulnTime()*this->getInvulnTime())/35)));
}

void Player::drawPlayer() // draws the player sprite
{
    // Rectangle spriteRect = {(float)16*(this->getDirection() + 1), 0, 16, 16};
    // Need a way to decode direction into sprite animation
    if (this->getInvulnTime() == 0)
    {
        // DrawTexturePro(this->sprite, spriteRect, this->hitbox, Vector2 {0, 0}, 0, WHITE);
        DrawRectangle(this->getPos().x, this->getPos().y, this->getWidth(), this->getHeight(), BLUE);
        if (this->getAttackCooldown() > (ATTACK_COOLDOWN - ATTACK_FRAMES))
        {
            DrawCircle(this->getAttackHitbox().center.x, this->getAttackHitbox().center.y, this->getAttackHitbox().radius, BLUE);

        }

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