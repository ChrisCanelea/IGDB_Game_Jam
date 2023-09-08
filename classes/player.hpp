#ifndef player_hpp
#define player_hpp

#include "enemy.hpp"
#include "globals.hpp"

class Player
{
private:
    Texture2D sprite; // sprite
    Rectangle hitbox; // hitbox
    float speed; // speed
    Direction direction; // direction
    float invulnTime;
    
public:
    // constructors
    Player(); // Default constructor
    Player(Texture2D, Rectangle, float, Direction, float); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    float getSpeed(); // returns speed
    Direction getDirection(); // returns direction
    float getInvulnTime(); // returns the number of invulnerability frames

    Vector2 getPos(); // returns the player position
    Vector2 getCenter(); // returns the player's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(float); // sets speed
    void setDirection(Direction); // sets direction
    void setInvulnTime(float); // sets the number of invulnerability frames

    void setPos(Vector2); // sets player position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    //other
    void processCooldowns(); // processes cooldowns (called once per frame, not currently used)
    void movePlayer(); // moves the player based on input
    void enemyKnockback(Enemy); // knocks the player away from an enemy (called when collision with an enemy is detected)
    void drawPlayer(); // draws the player sprite
};

#endif // player_hpp