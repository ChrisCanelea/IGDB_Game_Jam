#ifndef gameObject_hpp
#define gameObject_hpp

#include <raylib.h>

// define states for the gameObject
enum gameObjectState {STILL = 0, WALKING = 1, JUMPING = 2, FALLING = 3};

class gameObject 
{
private:
    Rectangle hitbox; // hitbox
    int dx; // x speed
    int dy; // y speed
    gameObjectState state;
    
public:
    // constructors
    gameObject(); // Default constructor
    gameObject(Rectangle, int, int); // Constructor with parameters

    // getters
    int getDx(); // returns x speed
    int getDy(); // returns y speed
    int getLeft(); // returns x position of left of hitbox
    int getRight(); // returns x position of right of hitbox
    int getTop(); // returns y position of top of hitbox
    int getBottom(); // returns y position of bottom of hitbox
    int getWidth(); // returns width of hitbox
    int getHeight(); // returns height of hitbox
    Rectangle getHitbox(); // returns hitbox
    gameObjectState getState(); // returns state of gameObject

    // setters
    void setDx(int); // sets x speed
    void setDy(int); // sets y speed
    void setX(int); // sets x position (top left corner of hitbox)
    void setY(int); // sets y position (top left corner of hitbox)
    void setWidth(int); // sets width of hitbox
    void setHeight(int); // sets height of hitbox
    void setHitbox(Rectangle); // sets hitbox
    void setState(gameObjectState); // sets the state of the gameObject
};

#endif // gameObject_hpp