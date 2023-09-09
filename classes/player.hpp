#ifndef player_hpp
#define player_hpp

#include "enemy.hpp"
#include "circle.hpp"
#include "globals.hpp"

class Player
{
private:
    Texture2D sprite; // sprite
    Rectangle hitbox; // hitbox
    float speed; // speed
    Vector2 direction; // direction
    Circle attackHitbox; // attackHitbox
    float attackCooldown;
    float invulnTime;
    Enemy* enemyReference; // reference to the enemy the player is interacting with
    
public:
    // constructors
    Player(); // Default constructor
    Player(Rectangle); // Constructor with hitbox parameter

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    float getSpeed(); // returns speed
    Vector2 getDirection(); // returns direction unit vector
    Circle getAttackHitbox(); // returns attackHitbox
    float getAttackCooldown(); // returs the number of attack cooldown frames
    float getInvulnTime(); // returns the number of invulnerability frames
    Enemy* getEnemyReference(); // returns the address of the enemy the player is interacting with

    Vector2 getPos(); // returns the player position
    Vector2 getCenter(); // returns the player's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(float); // sets speed
    void setDirection(Vector2); // sets direction
    void setAttackHitbox(Circle); // sets attackHitbox
    void setAttackCooldown(float); // sets the number of attack cooldown frames
    void setInvulnTime(float); // sets the number of invulnerability frames
    void setEnemyReference(Enemy*); // sets the address of the enemy the player is interacting with

    void setPos(Vector2); // sets player position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    //other
    void movePlayer(); // moves the player based on input
    void enemyKnockback(); // knocks the player away from an enemy (called when collision with an enemy is detected)
    void drawPlayer(); // draws the player sprite
    Texture2D loadSprite();
};

#endif // player_hpp