#ifndef projectile_hpp
#define projectile_hpp

#include "globals.hpp"

class Projectile 
{
private:
    Texture2D sprite;
    Rectangle hitbox;
    bool isVertical;
    float velocity;
    bool isActive;
    Vector2 theVoid;

public:
    // constructors
    Projectile(); // Default constructor
    Projectile(Rectangle, bool, Vector2); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    bool getIsVertical(); // returns rotation
    float getVelocity(); //returns velocity
    bool getIsActive();
    Vector2 getTheVoid();

    Vector2 getPos(); // returns the projectile's position
    Vector2 getCenter();
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setIsVertical(bool); // sets rotation
    void setVelocity(float); //returns velocity
    void setIsActive(bool);
    
    void setPos(Vector2); // sets player position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    // other
    void moveProjectile(); // moves the player based on input
    void drawProjectile(); // draws the player sprite
    Texture2D loadSprite();
    void killProjectile(); // moves projectile outside play area and makes it inactive
};

#endif // projectile_hpp