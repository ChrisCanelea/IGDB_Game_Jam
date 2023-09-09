#ifndef exit_hpp
#define exit_hpp

#include "globals.hpp"

class Exit
{
private:
    Texture2D sprite; // sprite
    Rectangle hitbox; // hitbox
    
public:
    // constructors
    Exit(); // Default constructor

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox

    Vector2 getPos(); // returns the exit position
    Vector2 getCenter(); // returns the exit's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox

    void setPos(Vector2); // sets exit position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    //other
    void drawExit(); // draws the player sprite
    Texture2D loadSprite();
};

#endif // player_hpp