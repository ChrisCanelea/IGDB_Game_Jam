#ifndef player_hpp
#define player_hpp

#include "globals.hpp"
#include <raylib.h>

class Player
{
private:
    Texture2D sprite; // sprite
    Rectangle hitbox; // hitbox
    int speed; // speed
    Direction direction; // direction
    
public:
    // constructors
    Player(); // Default constructor
    Player(Texture2D, Rectangle, int, Direction); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    int getSpeed(); // returns speed
    Direction getDirection(); // returns direction

    Vector2 getPos(); // returns the player position
    Vector2 getCenter(); // returns the player's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(int); // sets speed
    void setDirection(Direction); // sets direction

    void setPos(Vector2); // sets player position
    void setX(int); // sets x position (top left corner of hitbox)
    void setY(int); // sets y position (top left corner of hitbox)
    void setWidth(int); // sets width of hitbox
    void setHeight(int); // sets height of hitbox

    //other
    void movePlayer(); // moves the player based on input
    void drawPlayer(); // draws the player sprite
};

#endif // player_hpp