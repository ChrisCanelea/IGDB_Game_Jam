#ifndef stage_hpp
#define stage_hpp

#include "globals.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "player.hpp"

class Stage
{
private:
    Texture2D sprite; // sprite
    Rectangle playArea; // playArea
    Rectangle northWall; // northWall
    Rectangle eastWall; // eastWall
    Rectangle southWall; // southWall
    Rectangle westWall; // westWall
    int maxEnemies;
    int maxProjectiles;
    int initialEnemies;
    float enemyRespawnTime; // in frames
    float projectileRespawnTime; // in frames
    Vector2 exitLocation;
    Enemy* enemiesArray; // dynamic array of enemies based on maxEnemies
    Projectile* projectilesArray; // dynamic array of projectiles based on maxProjectiles
    Player* playerReference; // reference to player object in order to get its position for spawning purposes
    
public:
    // constructors
    Stage(); // Default constructor
    Stage(Rectangle, Player*); // Constructor with parameters

    // getters
    Texture2D getSprite();
    Rectangle getPlayArea();
    Rectangle getNorthWall();
    Rectangle getEastWall();
    Rectangle getSouthWall();
    Rectangle getWestWall();
    int getMaxEnemies();
    int getMaxProjectiles();
    int getInitialEnemies();
    float getEnemyRespawnTime();
    float getProjectileRespawnTime();
    Vector2 getExitLocation();
    Enemy* getEnemiesArray();
    Projectile* getProjectileArray();
    Player* getPlayerReference();

    // setters
    void setSprite(Texture2D);
    void setPlayArea(Rectangle);
    void setNorthWall(Rectangle);
    void setEastWall(Rectangle);
    void setSouthWall(Rectangle);
    void setWestWall(Rectangle);
    void setMaxEnemies(int);
    void setMaxProjectiles(int);
    void setInitialEnemies(int);
    void setEnemyRespawnTime(float);
    void setProjectileRespawnTime(float);
    void setExitLocation(Vector2);
    void setPlayerReference(Player*);

    // other
    void stageManager(); // master controller, called once per frame, processes entire stage (& respawns)
    Enemy* createEnemyArray(); // allocates memory for enemy array to keep track of all enemy objects
    Projectile* createProjectileArray(); // allocates memory for proj. array to track all projectiles
    void populateEnemies(); // fills enemy array with enemy objects
    void populateProjectiles(); // fills projectile array with projectile objects
    void initialPopulation(); // sets initial enemies active based on initialEnemies
    void spawnEnemy(); // sets an enemy as active
    void spawnProjectile(); // sets a projectile as active
    void drawStage(); // draws walls and background
    Vector2 generateExitPosition(); // generates the position of the exit
    Texture2D loadSprite();
    Vector2 generateRandomPoint(); // returns a vector2 in the play area
    Vector2 generateRandomOnEdge();
    bool isSpaceEnemy(); // returns true if there is space (isActive == false) in a given array
    bool isSpaceProjectile(); // returns true if there is space (isActive == false) in a given array

    // Destructor
    ~Stage();

};

#endif // stage_hpp