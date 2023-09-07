#ifndef enemy_hpp
#define enemy_hpp

#include <raylib.h>

enum Direction {NORTH = 0, NORTHEAST = 1, EAST = 2, SOUTHEAST = 3, SOUTH = 4, SOUTHWEST = 5, WEST = 6, NORTHWEST = 7};

class Enemy
{
private:
    Texture2D sprite; // sprite
    Rectangle hitbox; // hitbox
    int speed; // speed
    Direction direction; // direction
    
public:
    // constructors
    Enemy(); // Default constructor
    Enemy(Texture2D, Rectangle, int, Direction); // Constructor with parameters

    // getters
    Texture2D getSprite(); // returns sprite
    Rectangle getHitbox(); // returns hitbox
    int getSpeed(); // returns speed
    Direction getDirection(); // returns direction

    Vector2 getPos(); // returns the Enemy position
    int getLeft(); // returns x position of left of hitbox
    int getRight(); // returns x position of right of hitbox
    int getTop(); // returns y position of top of hitbox
    int getBottom(); // returns y position of bottom of hitbox
    int getWidth(); // returns width of hitbox
    int getHeight(); // returns height of hitbox

    // setters
    void setSprite(Texture2D); // sets sprite
    void setHitbox(Rectangle); // sets hitbox
    void setSpeed(int); // sets speed
    void setDirection(Direction); // sets direction

    void setPos(Vector2); // sets Enemy position
    void setX(int); // sets x position (top left corner of hitbox)
    void setY(int); // sets y position (top left corner of hitbox)
    void setWidth(int); // sets width of hitbox
    void setHeight(int); // sets height of hitbox

    //other
    void moveEnemy(); // moves the Enemy based on input
    void drawEnemy(); // draws the Enemy sprite
};

#endif // Enemy_hpp