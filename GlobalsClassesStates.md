# Globals
Variables that affect all aspects of gameplay should be global and static as well if used within classes.

- Stage Number - Starts at 0, incremented upon generation of a new stage, used for difficulty scaling and score.

# Classes
Anything that will be used more than once should be put into a class.

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