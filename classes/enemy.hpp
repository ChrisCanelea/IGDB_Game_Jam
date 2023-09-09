#ifndef enemy_hpp
#define enemy_hpp

#include "globals.hpp"

class Enemy
{
private:
    Texture2D sprite; // sprite
    Rectangle hitbox; // hitbox
    float speed; // speed
    Vector2 direction; // direction
    bool isActive;
    Vector2 theVoid;
    
public:
    // constructors
    Enemy(); // Default constructor
    Enemy(Rectangle, Vector2); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    int getSpeed(); // returns speed
    Vector2 getDirection(); // returns direction
    bool getIsActive();
    Vector2 getTheVoid();

    Vector2 getPos(); // returns the Enemy position
    Vector2 getCenter(); // returns the Enemy's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox
    
    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(float); // sets speed
    void setDirection(Vector2); // sets direction
    void setIsActive(bool);

    void setPos(Vector2); // sets Enemy position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    //other
    void moveEnemy(); // moves the Enemy based on input
    void drawEnemy(); // draws the Enemy sprite
    Texture2D loadSprite();
    void killEnemy(); // moves enemy outside the play area and makes it inactive
};

#endif // Enemy_hpp