// Class implementation for Stage

#include "stage.hpp"
#include "globals.hpp"


// constructors
Stage::Stage() // Default constructor
{
    this->sprite = LoadTexture("assets/background.png");
    this->playArea = Rectangle {-250, -250, 500, 500};
    this->playerReference = NULL;
    this->northWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->westWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->maxEnemies = 10;
    this->maxProjectiles = 10;
    this->initialEnemies = 3;
    this->enemyRespawnTime = ENEMY_RESPAWN_TIME;
    this->projectileRespawnTime = PROJECTILE_RESPAWN_TIME;
    this->exitLocation = generateExitPosition();
    this->enemiesArray = createEnemyArray();
    this->populateEnemies();
    this->projectilesArray = createProjectileArray();
    this->populateProjectiles();
    this->initialPopulation();
    this->shrinkRate = 0.0f;
    this->initialShrinkRate = 0.0f;
}

Stage::Stage(float width_, float height_, Player* playerReference_) 
{
    this->sprite = loadSprite();
    this->playArea = Rectangle {-1 * (width_/2), -1 * (height_/2), width_, height_};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->westWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->maxEnemies = 10;
    this->maxProjectiles = 10;
    this->initialEnemies = 3;
    this->enemyRespawnTime = ENEMY_RESPAWN_TIME;
    this->projectileRespawnTime = PROJECTILE_RESPAWN_TIME;
    this->exitLocation = generateExitPosition();
    this->enemiesArray = createEnemyArray();
    this->populateEnemies();
    this->projectilesArray = createProjectileArray();
    this->populateProjectiles();
    this->initialPopulation();
    this->shrinkRate = 0.5f;
    this->initialShrinkRate = this->getShrinkRate();
}

Stage::Stage(float width_, float height_, int maxEnemies_, int maxProjectiles_, int initialEnemies_, Player* playerReference_) 
{
    this->sprite = loadSprite();
    this->playArea = Rectangle {-1 * (width_/2), -1 * (height_/2), width_, height_};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->westWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->maxEnemies = maxEnemies_;
    this->maxProjectiles = maxProjectiles_;
    this->initialEnemies = initialEnemies_;
    this->enemyRespawnTime = ENEMY_RESPAWN_TIME;
    this->projectileRespawnTime = PROJECTILE_RESPAWN_TIME;
    this->exitLocation = generateExitPosition();
    this->enemiesArray = createEnemyArray();
    this->populateEnemies();
    this->projectilesArray = createProjectileArray();
    this->populateProjectiles();
    this->initialPopulation();
    this->shrinkRate = 0.5f;
    this->initialShrinkRate = this->getShrinkRate();
}

Stage::Stage(Player* playerReference_) // Default constructor
{
    this->sprite = loadSprite();
    this->playArea = Rectangle {-250, -250, 500, 500};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    this->westWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    this->maxEnemies = 10;
    this->maxProjectiles = 10;
    this->initialEnemies = 3;
    this->enemyRespawnTime = ENEMY_RESPAWN_TIME;
    this->projectileRespawnTime = PROJECTILE_RESPAWN_TIME;
    this->exitLocation = generateExitPosition();
    this->enemiesArray = createEnemyArray();
    this->populateEnemies();
    this->projectilesArray = createProjectileArray();
    this->populateProjectiles();
    this->initialPopulation();
    this->shrinkRate = 0.5f;
    this->initialShrinkRate = this->getShrinkRate();
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
float Stage::getShrinkRate()
{
    return this->shrinkRate;
}

float Stage::getInitialShrinkRate()
{
    return this->initialShrinkRate;
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
void Stage::setShrinkRate(float shrinkRate_)
{
    this->shrinkRate = shrinkRate_;
}

// other
void Stage::stageManager() 
{
    // RESPAWNING
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
        } else 
        {
            // decrement
            this->setEnemyRespawnTime(this->getEnemyRespawnTime() - 1);
        }
    }

    Projectile* queuedProjectile = this->isSpaceProjectile();
    if (queuedProjectile != NULL) 
    {
        if (this->getProjectileRespawnTime() == 0) 
        {
            this->respawnProjectile(queuedProjectile);

            this->setProjectileRespawnTime(PROJECTILE_RESPAWN_TIME);
        } else 
        {
            this->setProjectileRespawnTime(this->getProjectileRespawnTime() - 1);
        }
    }

    // ENEMY MOVEMENT
    for (int i = 0; i < this->getMaxEnemies(); ++i) 
    {
        this->getEnemiesArray()[i].setPlayerLocation(this->getPlayerReference()->getCenter());
        this->getEnemiesArray()[i].generateDirectionFacing();
        this->getEnemiesArray()[i].moveEnemy();
    }

    // PROJETILE MOVEMENT AND DESPAWNING
    for (int j = 0; j < this->getMaxProjectiles(); ++j) 
    {
        // DESPAWNING
        int tempOrientation = this->getProjectileArray()[j].getOrientation();

        if (tempOrientation == 0) // NORTH
        {
            if (this->getProjectileArray()[j].getPos().y < (this->getPlayArea().y - 60)) 
            {
                this->getProjectileArray()[j].killProjectile();
            }
        } else if (tempOrientation == 1) // EAST
        {
            if (this->getProjectileArray()[j].getPos().x > (this->getPlayArea().x + this->getPlayArea().width)) 
            {
                this->getProjectileArray()[j].killProjectile();
            }
        } else if (tempOrientation == 2) // SOUTH
        {
            if (this->getProjectileArray()[j].getPos().y > (this->getPlayArea().y + this->getPlayArea().height)) 
            {
                this->getProjectileArray()[j].killProjectile();
            }
        } else // WEST
        {
            if (this->getProjectileArray()[j].getPos().x < (this->getPlayArea().x - 60)) 
            {
                this->getProjectileArray()[j].killProjectile();
            }
        }
        
        // MOVING
        if (this->getProjectileArray()[j].getIsActive()) // only move if active
        {
            this->getProjectileArray()[j].moveProjectile();
        }
    }

    // STAGE SHRINKING
    // can set the shrinkRate elsewhere and this will update it for that frame and revert to original
    // negative shrink rate grows the playArea

    // LERP BORDER GROWING

    Rectangle oldPlayArea = this->getPlayArea();
    float newWidth = oldPlayArea.width - this->getShrinkRate();
    float newHeight = oldPlayArea.height - this->getShrinkRate();
    float newY = oldPlayArea.y + (this->getShrinkRate()/2);
    float newX = oldPlayArea.x + (this->getShrinkRate()/2);
    Rectangle newPlayArea = {newX, newY, newWidth, newHeight};
    this->setPlayArea(newPlayArea);
    this->setShrinkRate(this->getInitialShrinkRate()); // reset shrinkRate
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
        enemiesArray[i] = Enemy({temp.x, temp.y, 80, 124}, THE_VOID);
    }
}

void Stage::populateProjectiles() 
{
    for (int i = 0; i < maxProjectiles; ++i) 
    {
        Vector2 temp = this->generateRandomOnEdge();
        projectilesArray[i] = Projectile({temp.x, temp.y, 60, 20}, GetRandomValue(0,1), THE_VOID);
    }
}

void Stage::initialPopulation() 
{
    Vector2 initialPosition;
    for (int i = 0; i < this->getInitialEnemies(); ++i) 
    {
        this->getEnemiesArray()[i].setIsActive(true);
        initialPosition = this->generateRandomPoint();
        while (Vector2Distance({0,0}, initialPosition) < 600)
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
    enemy->setPos(this->generateRandomOnEdge());
    enemy->setIsActive(true);
}

void Stage::respawnProjectile(Projectile* projectile) 
{
    int orientation = GetRandomValue(0, 3);
    projectile->setPos(this->generateRandomForProjectile(orientation));
    projectile->setOrientation(orientation);
    projectile->adjustProjectile();
    projectile->setIsActive(true);
}

void Stage::drawStage() 
{
    // DrawTexturePro(this->getSprite(),{0,0,500,500},this->getPlayArea(),{0,0},0,WHITE);
    DrawTextureRec(this->getSprite(), {this->getPlayArea().x - this->getShrinkRate(), this->getPlayArea().y - this->getShrinkRate(), this->getPlayArea().width, this->getPlayArea().height}, {this->getPlayArea().x, this->getPlayArea().y}, WHITE);

    // THESE ARE TO BE REPURPOSED FOR BORDER TEXTURE IGNORE THEM FOR NOW
    // DrawRectangleRec(this->getNorthWall(), BLACK);
    // DrawRectangleRec(this->getEastWall(), BLACK);
    // DrawRectangleRec(this->getSouthWall(), BLACK);
    // DrawRectangleRec(this->getWestWall(), BLACK);

    for (int i = 0; i < maxEnemies; ++i) 
    {
        this->getEnemiesArray()[i].drawEnemy(this->getPlayArea());
    }
    for (int j = 0; j < maxProjectiles; ++j) 
    {
        this->getProjectileArray()[j].drawProjectile(this->getPlayArea());
    }
}

Vector2 Stage::generateExitPosition() 
{
    switch(GetRandomValue(0,3)) 
    {
        case 0: // NORTH
            return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width) - 32, this->getPlayArea().y - 32};
            break;

        case 1: // EAST
            return {this->getPlayArea().x + this->getPlayArea().width - 32, (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height) + 32};
            break;
        
        case 2: // SOUTH
            return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width) - 32, this->getPlayArea().y + this->getPlayArea().height - 32};
            break;
        
        case 3:
            return {this->getPlayArea().x - 32, (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height) + 32};
            break;
    }

    return {0, -200};
}

Texture2D Stage::loadSprite() 
{
    return LoadTexture("assets/tileBackground.png");
}

Vector2 Stage::generateRandomPoint() 
{
    return {(float)GetRandomValue(-1 * getPlayArea().width/2, (getPlayArea().width/2) - 50), (float)GetRandomValue(-1 * getPlayArea().height/2, (getPlayArea().height/2) - 100)};
}

Vector2 Stage::generateRandomOnEdge() 
{
    switch(GetRandomValue(0, 3)) 
    {
        case 0: // NORTH WALL
            return {(float)GetRandomValue(this->getPlayArea().x - 110, this->getPlayArea().width + this->getPlayArea().x + 60), (float)(this->getPlayArea().y - 150)};
            break;
            
        case 1: // EAST WALL
            return {(float)(this->getPlayArea().x + this->getPlayArea().width + 60), (float)GetRandomValue(this->getPlayArea().y - 150, this->getPlayArea().height + this->getPlayArea().y)};
            break;
            
        case 2: // SOUTH WALL
            return {(float)GetRandomValue(this->getPlayArea().x - 110, this->getPlayArea().width + this->getPlayArea().x + 60), (float)(this->getPlayArea().y + this->getPlayArea().height + 50)};
            break;
            
        case 3: // WEST WALL
            return {(float)(this->getPlayArea().x - 110), (float)GetRandomValue(this->getPlayArea().y - 150, this->getPlayArea().height + this->getPlayArea().y)};
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
            return &(this->getEnemiesArray()[i]);
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
            return &(this->getProjectileArray()[i]);
        }
    }

    return NULL;
}

Vector2 Stage::generateRandomForProjectile(int orientation) 
{
    if (orientation == 0) // NORTH (spawn on south wall)
    {
        return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width - 20), this->getPlayArea().y + this->getPlayArea().height + 50};
    } else if (orientation == 1) // EAST (spawn on west wall)
    {
        return {this->getPlayArea().x - 110, (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height - 20)};
    } else if (orientation == 2) // SOUTH (spawn on north wall)
    {
        return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width - 20), this->getPlayArea().y - 110};
    } else // WEST (spawn on east wall)
    {
        return {this->getPlayArea().x + this->getPlayArea().width + 50, (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height - 20)};
    }
}

Stage::~Stage() 
{
    delete[] this->getEnemiesArray();
    delete[] this->getProjectileArray();
}