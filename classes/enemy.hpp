#ifndef enemy_hpp
#define enemy_hpp

#include "globals.hpp"

class Enemy
{
private:
    Texture2D sprite[2]; // sprite
    Rectangle hitbox; // hitbox
    float speed; // speed
    Vector2 directionFacing; // direction
    bool isActive;
    Vector2 theVoid;
    Vector2 playerLocation;
    Vector2 directionBlocking;
    float attackAngle;
    
public:
    // constructors
    Enemy(); // Default constructor
    Enemy(Rectangle, Vector2); // Constructor with parameters

    // getters
    Texture2D getSprite(int); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    int getSpeed(); // returns speed
    Vector2 getDirectionFacing(); // returns direction
    bool getIsActive();
    Vector2 getTheVoid();
    Vector2 getPlayerLocation();
    Vector2 getDirectionBlocking();
    float getAttackAngle();

    Vector2 getPos(); // returns the Enemy position
    Vector2 getCenter(); // returns the Enemy's center position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox
    
    // setters
    void setSprite(Texture2D, int); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(float); // sets speed
    void setDirectionFacing(Vector2); // sets direction
    void setIsActive(bool);
    void setPlayerLocation(Vector2);
    void setDirectionBlocking(Vector2);
    void setAttackAngle(float);

    void setPos(Vector2); // sets Enemy position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    //other
    void moveEnemy(); // moves the Enemy based on input
    void drawEnemy(Rectangle); // draws the Enemy (only the parts that are on top of playArea rectangle)
    void loadSprite();
    void killEnemy(); // moves enemy outside the play area and makes it inactive
    void generateDirectionBlocking(); // generates a normalized vector in direction of block
    void generateDirectionFacing(); // generates a normalized directionFacing vector
    void drawBlockIndicator(); // draws indicator for which direction enemy is blocking
};

#endif // Enemy_hpp