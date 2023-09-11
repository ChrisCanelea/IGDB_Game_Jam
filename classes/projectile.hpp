#ifndef projectile_hpp
#define projectile_hpp

#include "globals.hpp"

class Projectile 
{
private:
    Texture2D sprite;
    Rectangle hitbox;
    int orientation;
    float velocity;
    bool isActive;
    Vector2 theVoid;
    Rectangle sourceRec;

public:
    // constructors
    Projectile(); // Default constructor
    Projectile(Rectangle, int, Vector2); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    int getOrientation(); // returns rotation
    float getVelocity(); //returns velocity
    bool getIsActive();
    Vector2 getTheVoid();
    Rectangle getSourceRec();

    Vector2 getPos(); // returns the projectile's position
    Vector2 getCenter();
    float getX();
    float getY();
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setOrientation(int); // sets rotation
    void setVelocity(float); //returns velocity
    void setIsActive(bool);
    void setSourceRec(Rectangle);
    
    void setPos(Vector2); // sets player position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    // other
    void moveProjectile(); // moves the player based on input
    void drawProjectile(Rectangle); // draws the projectile (only part that is on top of playArea)
    Texture2D loadSprite(); 
    void killProjectile(); // moves projectile outside play area and makes it inactive
    void adjustProjectile();
};

#endif // projectile_hpp