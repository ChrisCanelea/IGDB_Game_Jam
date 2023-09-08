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
    Stage(Texture2D, Rectangle, Player*); // Constructor with parameters

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
    void initialPopulation(); // creates enemies and puts them in array based on initialEnemies
    Enemy spawnEnemy(); // creates an enemy and puts it in the array (check for space done in manager)
    Projectile spawnProjectile(); // creates a proj. and puts in array (check for space done in manager)
    void drawStage(); // draws walls and background
    Vector2 generateExitPosition(); // generates the position of the exit

    // Destructor
    ~Stage();

};

#endif // stage_hpp