// Class implementation for Stage

#include "stage.hpp"
#include "globals.hpp"


// constructors
Stage::Stage() // Default constructor
{
    this->sprite = LoadTexture("assets/background.png");
    this->playArea = {-250, -250, 500, 500};
    this->playerReference = NULL;
    this->northWall = {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->eastWall = {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->southWall = {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->westWall = {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->maxEnemies = 10;
    this->maxProjectiles = 10;
    this->initialEnemies = 3;
    this->enemyRespawnTime = 600;
    this->projectileRespawnTime = 600;
    this->exitLocation = generateExitPosition();
    this->enemiesArray = createEnemyArray();
    this->projectilesArray = createProjectileArray();
}

Stage::Stage(Rectangle playArea_, Player* playerReference_) 
{
    this->sprite = loadSprite();
    this->playArea = playArea_;
    this->playerReference = playerReference_;
    this->northWall = {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->eastWall = {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->southWall = {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->westWall = {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->maxEnemies = 10;
    this->maxProjectiles = 10;
    this->initialEnemies = 3;
    this->enemyRespawnTime = 600;
    this->projectileRespawnTime = 600;
    this->exitLocation = generateExitPosition();
    this->enemiesArray = createEnemyArray();
    this->populateEnemies();
    this->projectilesArray = createProjectileArray();
    this->populateProjectiles();
    this->initialPopulation();
}

// getters
Texture2D Stage::getSprite() 
{
    return this->sprite;
}

Rectangle Stage::getPlayArea() 
{
    return this->playArea;
}

Rectangle Stage::getNorthWall() 
{
    return this->northWall;
}
Rectangle Stage::getEastWall() 
{
    return this->eastWall;
}
Rectangle Stage::getSouthWall() 
{
    return this->southWall;
}
Rectangle Stage::getWestWall() 
{
    return this->westWall;
}

int Stage::getMaxEnemies() 
{
    return this->maxEnemies;
}

int Stage::getMaxProjectiles() 
{
    return this->maxProjectiles;
}

int Stage::getInitialEnemies() 
{
    return this->initialEnemies;
}

float Stage::getEnemyRespawnTime() 
{
    return this->enemyRespawnTime;
}

float Stage::getProjectileRespawnTime() 
{
    return this->projectileRespawnTime;
}

Vector2 Stage::getExitLocation() 
{
    return this->exitLocation;
}

Enemy* Stage::getEnemiesArray() 
{
    return this->enemiesArray;
}

Projectile* Stage::getProjectileArray() 
{
    return this->projectilesArray;
}

Player* Stage::getPlayerReference() 
{
    return this->playerReference;
}

// setters
void Stage::setSprite(Texture2D sprite_) 
{
    this->sprite = sprite_;
}

void Stage::setPlayArea(Rectangle playArea_) 
{
    this->playArea = playArea_;
}

void Stage::setNorthWall(Rectangle northWall_) 
{
    this->northWall = northWall_;
}

void Stage::setEastWall(Rectangle eastWall_) 
{
    this->eastWall = eastWall_;
}

void Stage::setSouthWall(Rectangle southWall_) 
{
    this->southWall = southWall_;
}

void Stage::setWestWall(Rectangle westWall_) 
{
    this->westWall = westWall_;
}

void Stage::setMaxEnemies(int maxEnemies_) 
{
    this->maxEnemies = maxEnemies_;
}

void Stage::setMaxProjectiles(int maxProjectiles_) 
{
    this->maxProjectiles = maxProjectiles_;
}

void Stage::setInitialEnemies(int initialEnemies_) 
{
    this->initialEnemies = initialEnemies_;
}

void Stage::setEnemyRespawnTime(float enemyRespawnTime_) 
{
    this->enemyRespawnTime = enemyRespawnTime_;
}

void Stage::setProjectileRespawnTime(float projectileRespawnTime_) 
{
    this->projectileRespawnTime = projectileRespawnTime_;
}

void Stage::setExitLocation(Vector2 exitLocation_) 
{
    this->exitLocation = exitLocation_;
}

void Stage::setPlayerReference(Player* playerReference_) 
{
    this->playerReference = playerReference_;
}

// other
void Stage::stageManager() 
{
    // only count down respawn timer if there is space for an enemy (isActive false for at least 1 enemy)
    Enemy* queuedEnemy = this->isSpaceEnemy();
    if (queuedEnemy != NULL) 
    {
        if (this->getEnemyRespawnTime() == 0) 
        {
            // respawn an enemy
            this->respawnEnemy(queuedEnemy);

            // reset timer
            this->setEnemyRespawnTime(ENEMY_RESPAWN_TIME);
        }

        // decrement
        this->setEnemyRespawnTime(this->getEnemyRespawnTime() - 1);
    }
}

Enemy* Stage::createEnemyArray() 
{
    return new Enemy[maxEnemies];
}

Projectile* Stage::createProjectileArray() 
{
    return new Projectile[maxProjectiles];
}

void Stage::populateEnemies() 
{
    for (int i = 0; i < maxEnemies; ++i) 
    {
        Vector2 temp = this->generateRandomOnEdge();
        enemiesArray[i] = Enemy({temp.x, temp.y, 50, 100});
    }
}

void Stage::populateProjectiles() 
{
    for (int i = 0; i < maxProjectiles; ++i) 
    {
        Vector2 temp = this->generateRandomOnEdge();
        projectilesArray[i] = Projectile({temp.x, temp.y, 60, 20}, this->getPlayerReference()->getCenter());
    }
}

void Stage::initialPopulation() 
{
    Vector2 initialPosition;
    for (int i = 0; i < this->getInitialEnemies(); ++i) 
    {
        this->getEnemiesArray()[i].setIsActive(true);
        initialPosition = this->generateRandomPoint();
        while (Vector2Distance(this->getPlayerReference()->getCenter(), initialPosition) < 600)
        {
            // get new random starting position if within 600 of player
            initialPosition = this->generateRandomPoint();
        }
        this->getEnemiesArray()[i].setPos(initialPosition);
        this->getEnemiesArray()[i].setIsActive(true);
    }
}

void Stage::respawnEnemy(Enemy* enemy) 
{
    enemy->setPos({0,0});
    enemy->setIsActive(true);
}

void Stage::respawnProjectile(Projectile* projectile) 
{

}

void Stage::drawStage() 
{
    DrawTexturePro(this->getSprite(),{0,0,500,500},this->getPlayArea(),{0,0},0,WHITE);

    DrawRectangleRec(this->getNorthWall(), BLACK);
    DrawRectangleRec(this->getEastWall(), BLACK);
    DrawRectangleRec(this->getSouthWall(), BLACK);
    DrawRectangleRec(this->getWestWall(), BLACK);

    for (int i = 0; i < maxEnemies; ++i) 
    {
        this->getEnemiesArray()[i].drawEnemy();
    }
    for (int j = 0; j < maxProjectiles; ++j) 
    {
        this->getProjectileArray()[j].drawProjectile();
    }

    // DrawRectangleRec(this->getNorthWall(), BLACK);
    // DrawRectangleRec(this->getEastWall(), BLACK);
    // DrawRectangleRec(this->getSouthWall(), BLACK);
    // DrawRectangleRec(this->getWestWall(), BLACK);
}

Vector2 Stage::generateExitPosition() 
{
    return {this->generateRandomPoint()};
}

Texture2D Stage::loadSprite() 
{
    return LoadTexture("assets/background.png");
}

Vector2 Stage::generateRandomPoint() 
{
    return {(float)GetRandomValue(-1 * getPlayArea().width/2, getPlayArea().width/2), (float)GetRandomValue(-1 * getPlayArea().height/2, getPlayArea().height/2)};
}

Vector2 Stage::generateRandomOnEdge() 
{
    switch(GetRandomValue(0, 3)) 
    {
        case 0: // NORTH WALL
            return {(float)GetRandomValue(this->getPlayArea().x - 80, this->getPlayArea().width + this->getPlayArea().x + 80), (float)(this->getPlayArea().y - 150)};
            break;
            
        case 1: // EAST WALL
            return {(float)(this->getPlayArea().x + this->getPlayArea().width + 80), (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().height + this->getPlayArea().y)};
            break;
            
        case 2: // SOUTH WALL
            return {(float)GetRandomValue(this->getPlayArea().x - 80, this->getPlayArea().width + this->getPlayArea().x + 80), (float)(this->getPlayArea().y + this->getPlayArea().height + 100)};
            break;
            
        case 3: // WEST WALL
            return {(float)(this->getPlayArea().x - 60), (float)GetRandomValue(this->getPlayArea().y - 100, this->getPlayArea().height + this->getPlayArea().y + 100)};
            break;
    }

    return {0,0};
}

Enemy* Stage::isSpaceEnemy() 
{
    for (int i = 0; i < this->getMaxEnemies(); ++i) 
    {
        if (this->getEnemiesArray()[i].getIsActive() == false) 
        {
            return &this->getEnemiesArray()[i];
        }
    }

    return NULL;
}

Projectile* Stage::isSpaceProjectile() 
{
    for (int i = 0; i < this->getMaxProjectiles(); ++i) 
    {
        if (this->getProjectileArray()[i].getIsActive() == false) 
        {
            return &this->getProjectileArray()[i];
        }
    }

    return NULL;
}

Stage::~Stage() 
{
    delete[] this->getEnemiesArray();
    delete[] this->getProjectileArray();
}