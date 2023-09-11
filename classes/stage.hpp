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
    float shrinkRate; // amount the play area shrinks by
    float initialShrinkRate; // the shrinkRate on stage construction
    
public:
    // constructors
    Stage(); // Default constructor
    Stage(float, float, Player*); // Constructor with parameters
    Stage(float, float, int, int, int, Player*);
    Stage(Player*);

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
    float getShrinkRate();
    float getInitialShrinkRate();

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
    void setShrinkRate(float);

    // other
    void stageManager(); // master controller, called once per frame, processes entire stage (& respawns)
    Enemy* createEnemyArray(); // allocates memory for enemy array to keep track of all enemy objects
    Projectile* createProjectileArray(); // allocates memory for proj. array to track all projectiles
    void populateEnemies(); // fills enemy array with enemy objects
    void populateProjectiles(); // fills projectile array with projectile objects
    void initialPopulation(); // sets initial enemies active based on initialEnemies
    void respawnEnemy(Enemy*); // sets an enemy as active
    void respawnProjectile(Projectile*); // sets a projectile as active
    void drawStage(); // draws walls and background
    Vector2 generateExitPosition(); // generates the position of the exit
    Texture2D loadSprite();
    Vector2 generateRandomPoint(); // returns a vector2 in the play area
    Vector2 generateRandomOnEdge();
    Enemy* isSpaceEnemy(); // returns enemy if there is space (isActive == false) in a given array, else NULL
    Projectile* isSpaceProjectile(); // returns projectile if there is space (isActive == false) in a given array, else NULL
    Vector2 generateRandomForProjectile(int);

    // Destructor
    ~Stage();

};

#endif // stage_hpp