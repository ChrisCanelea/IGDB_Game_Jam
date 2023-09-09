#ifndef projectile_hpp
#define projectile_hpp

#include "globals.hpp"

class Projectile 
{
private:
    Texture2D sprite;
    Rectangle hitbox;
    float rotation;
    Vector2 destination;
    float velocity;
    Vector2 direction;

public:
    // constructors
    Projectile(); // Default constructor
    Projectile(Rectangle, Vector2); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    float getRotation(); // returns rotation
    Vector2 getDestination(); // returns destination
    float getVelocity(); //returns velocity
    Vector2 getDirection(); // returns direction vector

    Vector2 getPos(); // returns the projectile's position
    float getWidth(); // returns width of hitbox
    float getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setRotation(float); // sets rotation
    void setDestination(Vector2); // sets destination
    void setVelocity(float); //returns velocity
    void setDirection(Vector2); // returns direction vector
    
    void setPos(Vector2); // sets player position
    void setX(float); // sets x position (top left corner of hitbox)
    void setY(float); // sets y position (top left corner of hitbox)
    void setWidth(float); // sets width of hitbox
    void setHeight(float); // sets height of hitbox

    // other
    Vector2 calculateDirection();
    float calculateRotation();
    void moveProjectile(); // moves the player based on input
    void drawProjectile(); // draws the player sprite
    Texture2D loadSprite();
};

#endif // projectile_hpp