# Globals
Variables that affect all aspects of gameplay should be global and static as well if used within classes.

- int Stage Number - Starts at 0, incremented upon generation of a new stage, used for difficulty scaling and score.
- float Border Shrink Rate - float for how much the border radius should shrink (per second).
- Circle (for now) Border - circle representing border, radius shrinks based on rate, and increases a set amount per kill, if player is not colliding with this circle, they will be dead

# Classes
Anything that will be used more than once should be put into a class.

## Player
Variables:
- Texture2D playerSprite (can be a sheet)
- Rectangle hitbox
- Vector2 position
- int directionFacing (8 directions, identified from 0-7 clockwise, only if we have sprites for each direction)
- float moveSpeed
- float attackCooldown
- float invulnTime

Function descriptions:
- movePlayer() called once per frame to move the player based on input, also updates direction based on input
- drawPlayer() called once per frame to draw the player at the current position
- attack() called on input for an attack, initiates combat with enemy or destroys projectiles either with rays or a shaped hitbox we create in direction of cursor 
- drawAttack() called for the duration of attack animation/existence to draw it
- processCooldowns() called once per frame to count down attack cooldown and any invuln time
- finisher() called upon enemy blocking (**Combat** state), requires player to input a direction that is not blocked with outcome depending on that

## Enemy
Variables:
- Texture2D enemySprite (can be a sheet)
- Rectangle hitbox
- Vector2 position
- int directionFacing (8 directions, identified from 0-7 clockwise, only if we have sprites for each direction) (want to make face player)
- float moveSpeed
- float value

Function descriptions:
- moveEnemy() called once per frame to move the enemy towards the player, also updates the direction based on player position
- drawEnemy() called once per frame to draw the enemy at the current position
- block() called upon getting hit, returns a direction this enemy chooses to block
- drawBlock() called once per frame in **Combat** state, draws block indicator
- killed() called on hit after finisher, kills this enemy, increases border based on value

## Projectile
Variables:
- Texture2D projectileSprite
- Rectangle hitbox
- Vector2 position
- float rotation
- Vector2 direction (where it is moving) (moveSpeed substitute)
- float value (in case we want projectiles to also increase border slightly)

Function descriptions:
- moveProjectile() called once per frame to move projectile based on direction
- drawProjectile() called once per frame to draw projectile at the current position and with rotation based on direction
- killed() called on hit, kills this projectile, increases border based on value

## Stage (still thinking about this one)
Variables:
- int maxEnemies
- int maxProjectiles
- int initialEnemies
- float enemyRespawnTime
- float projectileRespawnTime
- ENUM for biome???

Function descriptions:
- populate() called on stage gen, creates initial enemies
- 

# States
States will be ENUMS, and will determine what is processed and what is drawn at any given time **during the game**
Remember that each state can do something **on change** and also continuously while inside of it, as described below.
Keep in mind that we can also jump to any state at any time, as these states are not 100% sequential.
Do note that I am also keeping these to one word for simplicity in referencing them.

- **Generation** - This state will be used when we transition to a new stage. We can increment the stage count, generate the stage, and populate it *upon switching to this state*, unsure if we need to stay on it any longer. This is not done during the **Playing** state because we will be re-entering that state multiple times per state after finishing **Combat**.

- **Playing** - This state will be used for when the game is in progress. We can grant the player some invulnerability *upon switching to this state*, and then handle projectile and further enemy generation while still on this state.

- **Combat** - This state will be used for when we are in combat with a specific enemy. This ensures we pause projectile processing, enemy generation, and we can even adjust border shrink rate and lock the player during this state.

- **Death** - This state will be used when the player touches the border or it expands over them. Perhaps we can use this state to process an animation or delete objects.

- **Purgatory** - This state does nothing (for now) and will be used while we are on the **MainMenu**, **Options**, and **Recap** screens.

# Screen
Screens will also be ENUMS that represent entire screens and usually act as a division between game and menus.

- **MainMenu** - The main menu of the game featuring buttons for start, exit, and options (to view controls and adjust volume).

- **Options** - Screen for showing controls and the volume slider.

- **Game** - Main game screen for playing the game.

- **Recap** - Screen for showing score, stage number, maybe time too, after a run