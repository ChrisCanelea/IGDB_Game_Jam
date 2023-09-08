#ifndef stage_hpp
#define stage_hpp

#include "globals.hpp"

class Stage
{
private:
    Texture2D sprite; // sprite
    Rectangle playArea; // playArea
    Rectangle northWall; // northWall
    Rectangle eastWall; // eastWall
    Rectangle southWall; // southWall
    Rectangle westWall; // westWall
    
public:
    // constructors
    Stage(); // Default constructor
    Stage(Texture2D, Rectangle); // Constructor with parameters

    // getters

    // setters
    void setSprite(Texture2D); // sets sprite
    void setPlayArea(Rectangle); // sets playArea
};

#endif // stage_hpp