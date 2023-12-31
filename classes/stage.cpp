// Class implementation for Stage

#include "stage.hpp"
#include "globals.hpp"


// constructors
Stage::Stage() // Default constructor
{
    this->sprite = LoadTexture("assets/background.png");
    this->wallSprite = LoadTexture("assets/fire.png");
    this->playArea = Rectangle {-250, -250, 500, 500};
    this->playerReference = NULL;
    this->northWall = Rectangle {getPlayArea().x, getPlayArea().y -100, getPlayArea().width, 100}; //x,y,w,h
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, 100, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x, getPlayArea().y + getPlayArea().height, getPlayArea().width, 100};
    this->westWall = Rectangle {getPlayArea().x - 100, getPlayArea().y, 100, getPlayArea().height};
    // this->northWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y - getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    // this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
    // this->southWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y + getPlayArea().height, getPlayArea().width * 2, getPlayArea().height};
    // this->westWall = Rectangle {getPlayArea().x - (getPlayArea().width/2), getPlayArea().y, getPlayArea().width/2, getPlayArea().height};
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
    this->shrinkTimer = 0;
    this->exitReference = NULL;
}

Stage::Stage(float width_, float height_, Player* playerReference_, Exit* exitReference_) 
{
    this->sprite = loadSprite();
    this->wallSprite = LoadTexture("assets/fire.png");
    this->playArea = Rectangle {-1 * (width_/2), -1 * (height_/2), width_, height_};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x, getPlayArea().y -100, getPlayArea().width, 100}; //x,y,w,h
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, 100, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x, getPlayArea().y + getPlayArea().height, getPlayArea().width, 100};
    this->westWall = Rectangle {getPlayArea().x - 100, getPlayArea().y, 100, getPlayArea().height};
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
    this->shrinkRate = 1.0f;
    this->initialShrinkRate = this->getShrinkRate();
    this->shrinkTimer = 0;
    this->exitReference = exitReference_;
}

Stage::Stage(float width_, float height_, int maxEnemies_, int maxProjectiles_, int initialEnemies_, Player* playerReference_, Exit* exitReference_) 
{
    this->sprite = loadSprite();
    this->wallSprite = LoadTexture("assets/fire.png");
    this->playArea = Rectangle {-1 * (width_/2), -1 * (height_/2), width_, height_};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x, getPlayArea().y -100, getPlayArea().width, 100}; //x,y,w,h
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, 100, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x, getPlayArea().y + getPlayArea().height, getPlayArea().width, 100};
    this->westWall = Rectangle {getPlayArea().x - 100, getPlayArea().y, 100, getPlayArea().height};
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
    this->shrinkRate = 1.0f;
    this->initialShrinkRate = this->getShrinkRate();
    this->shrinkTimer = 0;
    this->exitReference = exitReference_;
}

Stage::Stage(float width_, float height_, int maxEnemies_, int maxProjectiles_, int initialEnemies_, float shrinkRate_, Player* playerReference_, Exit* exitReference_) 
{
    this->sprite = loadSprite();
    this->wallSprite = LoadTexture("assets/fire.png");
    this->playArea = Rectangle {-1 * (width_/2), -1 * (height_/2), width_, height_};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x, getPlayArea().y -100, getPlayArea().width, 100}; //x,y,w,h
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, 100, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x, getPlayArea().y + getPlayArea().height, getPlayArea().width, 100};
    this->westWall = Rectangle {getPlayArea().x - 100, getPlayArea().y, 100, getPlayArea().height};
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
    this->shrinkRate = shrinkRate_;
    this->initialShrinkRate = this->getShrinkRate();
    this->shrinkTimer = 0;
    this->exitReference = exitReference_;
}

Stage::Stage(Player* playerReference_, Exit* exitReference_)
{
    this->sprite = loadSprite();
    this->wallSprite = LoadTexture("assets/fire.png");
    this->playArea = Rectangle {-250, -250, 500, 500};
    this->playerReference = playerReference_;
    this->northWall = Rectangle {getPlayArea().x, getPlayArea().y -100, getPlayArea().width, 100}; //x,y,w,h
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, 100, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x, getPlayArea().y + getPlayArea().height, getPlayArea().width, 100};
    this->westWall = Rectangle {getPlayArea().x - 100, getPlayArea().y, 100, getPlayArea().height};
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
    this->shrinkRate = 1.0f;
    this->initialShrinkRate = this->getShrinkRate();
    this->shrinkTimer = 0;
    this->exitReference = exitReference_;
}

// getters
Texture2D Stage::getSprite() 
{
    return this->sprite;
}

Texture2D Stage::getWallSprite() 
{
    return this->wallSprite;
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

float Stage::getShrinkTimer()
{
    return this->shrinkTimer;
}

Exit* Stage::getExitReference() 
{
    return this->exitReference;
}

// setters
void Stage::setSprite(Texture2D sprite_) 
{
    this->sprite = sprite_;
}

void Stage::setWallSprite(Texture2D wallSprite_) 
{
    this->wallSprite = wallSprite_;
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

void Stage::setShrinkTimer(float shrinkTimer_)
{
    this->shrinkTimer = shrinkTimer_;
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
        if (this->getProjectileRespawnTime() <= 0) 
        {
            if (this->getPlayArea().width > 500) 
            {
                this->respawnProjectile(queuedProjectile);
                if (GetRandomValue(1, 50) == 1)
                {
                    queuedProjectile->setVelocity(queuedProjectile->getVelocity()*5);
                }
                this->setProjectileRespawnTime(PROJECTILE_RESPAWN_TIME);
            }
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
        } else 
        {
            this->getProjectileArray()[j].setPos(THE_VOID);
        }
    }

    // STAGE SHRINKING
    // can set the shrinkRate elsewhere and this will update it for that frame and revert to original
    // negative shrink rate grows the playArea
    Rectangle oldPlayArea = this->getPlayArea();
    float newWidth = oldPlayArea.width - this->getShrinkRate();
    float newHeight = oldPlayArea.height - this->getShrinkRate();
    float newY = oldPlayArea.y + (this->getShrinkRate()/2);
    float newX = oldPlayArea.x + (this->getShrinkRate()/2);
    Rectangle newPlayArea = {newX, newY, newWidth, newHeight};
    this->setPlayArea(newPlayArea);
    if (this->getShrinkTimer() > 0)
    {
        this->setShrinkTimer(this->getShrinkTimer() - 1);
        if (this->getShrinkTimer() < this->getShrinkRate())
        {
            this->setShrinkRate(this->getShrinkRate() - 1);
        }
    } else
    {
        this->setShrinkRate(this->getInitialShrinkRate()); // reset shrinkRate
    }

    // MAP N/E/S/W WALLS
    //changing ths size of the surrounding walls to the shrinked play area
    this->northWall = Rectangle {getPlayArea().x, getPlayArea().y -100, getPlayArea().width, 100}; //x,y,w,h
    this->eastWall = Rectangle {getPlayArea().x + getPlayArea().width, getPlayArea().y, 100, getPlayArea().height};
    this->southWall = Rectangle {getPlayArea().x, getPlayArea().y + getPlayArea().height, getPlayArea().width, 100};
    this->westWall = Rectangle {getPlayArea().x - 100, getPlayArea().y, 100, getPlayArea().height};
    
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
        while (Vector2Distance({0,0}, initialPosition) < 100)
        {
            // get new random starting position if within 100 of player
            initialPosition = this->generateRandomPoint();
        }
        this->getEnemiesArray()[i].setPos(initialPosition);
        this->getEnemiesArray()[i].setIsActive(true);
    }
}

void Stage::respawnEnemy(Enemy* enemy) 
{
    enemy->setIsActive(true);
    enemy->setPos(this->generateRandomOnEdge());
}

void Stage::respawnProjectile(Projectile* projectile) 
{
    int orientation = GetRandomValue(0, 3);
    projectile->setIsActive(true);
    projectile->setPos(this->generateRandomForProjectile(orientation));
    projectile->setOrientation(orientation);
    projectile->adjustProjectile();
}

void Stage::drawStage() 
{
    // DrawTexturePro(this->getSprite(),{0,0,500,500},this->getPlayArea(),{0,0},0,WHITE);
    DrawTextureRec(this->getSprite(), {this->getPlayArea().x - this->getShrinkRate(), this->getPlayArea().y - this->getShrinkRate(), this->getPlayArea().width, this->getPlayArea().height}, {this->getPlayArea().x, this->getPlayArea().y}, WHITE);

    // exit
    Rectangle tempExitRec = GetCollisionRec(this->getExitReference()->getHitbox(), this->getPlayArea());
    float xOffset = 0;
    float yOffset = 0;
    if (this->getExitReference()->getPos().x <= this->getPlayArea().x) 
    {
        xOffset = this->getPlayArea().x - this->getExitReference()->getPos().x;
    }
    if (this->getExitReference()->getPos().y <= this->getPlayArea().y) 
    {
        yOffset = this->getPlayArea().y - this->getExitReference()->getPos().y;
    }
    DrawTextureRec(this->getExitReference()->getSprite(), {0 + xOffset,0 + yOffset,tempExitRec.width,tempExitRec.height}, {tempExitRec.x, tempExitRec.y}, WHITE);
    
    for (int i = 0; i < maxEnemies; ++i) 
    {
        this->getEnemiesArray()[i].drawEnemy(this->getPlayArea());
    }
    for (int j = 0; j < maxProjectiles; ++j) 
    {
        this->getProjectileArray()[j].drawProjectile(this->getPlayArea());
    }

    // THESE ARE TO BE REPURPOSED FOR BORDER TEXTURE IGNORE THEM FOR NOW
    Rectangle wallSource = {0, 0, 128, 16};
    // DrawRectangleRec(this->getNorthWall(), ORANGE);
    DrawRectangle(this->getNorthWall().x - this->getNorthWall().width, this->getNorthWall().y - 4*this->getNorthWall().height, 3*this->getNorthWall().width, 5*this->getNorthWall().height, BLACK);
    DrawTexturePro(this->getWallSprite(), wallSource, this->getNorthWall(), {0, 0}, 0, WHITE);

    Rectangle southDest = {this->getSouthWall().x + this->getSouthWall().width, this->getSouthWall().y + this->getSouthWall().height, this->getSouthWall().width, this->getSouthWall().height};
    // DrawRectangleRec(this->getSouthWall(), ORANGE);
    DrawRectangle(this->getSouthWall().x - this->getSouthWall().width, this->getSouthWall().y, 3*this->getSouthWall().width, 5*this->getSouthWall().height, BLACK);
    DrawTexturePro(this->getWallSprite(), wallSource, southDest, {0, 0}, 180, WHITE);
    
    Rectangle westDest = {this->getWestWall().x, this->getWestWall().y + this->getWestWall().height, this->getWestWall().height, this->getWestWall().width};
    // DrawRectangleRec(this->getWestWall(), ORANGE);
    DrawRectangle(this->getWestWall().x - 8*this->getWestWall().width, this->getWestWall().y - this->getWestWall().height, 9*this->getWestWall().width, 3*this->getWestWall().height, BLACK);
    DrawTexturePro(this->getWallSprite(), wallSource, westDest, {0, 0}, 270, WHITE);

    Rectangle eastDest = {this->getEastWall().x + this->getEastWall().width, this->getEastWall().y, this->getEastWall().height, this->getEastWall().width};
    // DrawRectangleRec(this->getEastWall(), ORANGE);
    DrawRectangle(this->getEastWall().x, this->getEastWall().y - this->getEastWall().height, 9*this->getEastWall().width, 3*this->getEastWall().height, BLACK);
    DrawTexturePro(this->getWallSprite(), wallSource, eastDest, {0, 0}, 90, WHITE);
}

Vector2 Stage::generateExitPosition() 
{
    switch(GetRandomValue(0,3)) 
    {
        case 0: // NORTH
            if (stageNumber <= 1)
            {
                return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width) - 32, this->getPlayArea().y - 32};
            } else 
            {
                return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width) - 32, this->getPlayArea().y - 32 - ((((stageNumber - 1) * 200) <= 1000)?((stageNumber - 1) * 200):(1000))};
            }
            break;

        case 1: // EAST
            if (stageNumber <= 1)
            {
                return {this->getPlayArea().x + this->getPlayArea().width - 32, (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height) + 32};
            } else 
            {
                return {this->getPlayArea().x + this->getPlayArea().width - 32 + ((((stageNumber - 1) * 200) <= 1000)?((stageNumber - 1) * 200):(1000)), (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height) + 32};
            }
            break;
        
        case 2: // SOUTH
            if (stageNumber <= 1)
            {
                return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width) - 32, this->getPlayArea().y + this->getPlayArea().height - 32};
            } else 
            {
                return {(float)GetRandomValue(this->getPlayArea().x, this->getPlayArea().x + this->getPlayArea().width) - 32, this->getPlayArea().y + this->getPlayArea().height - 32 + ((((stageNumber - 1) * 200) <= 1000)?((stageNumber - 1) * 200):(1000))};
            }
            break;
        
        case 3:
            if (stageNumber <= 1)
            {
                return {this->getPlayArea().x - 32, (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height) + 32};
            } else 
            {
                return {this->getPlayArea().x - 32 - ((((stageNumber - 1) * 200) <= 1000)?((stageNumber - 1) * 200):(1000)), (float)GetRandomValue(this->getPlayArea().y, this->getPlayArea().y + this->getPlayArea().height) + 32};
            }
            break;
    }

    return {0, -200};
}

Texture2D Stage::loadSprite() 
{
    return LoadTexture("assets/thebackground_4x4.png");
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