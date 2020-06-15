#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600

// Distance from where virus spreads.
#define SPREADING_DISTANCE 40
// Number of tiles displayed on the screen (including EnemyTile)
#define NUMBER_OF_TILES 5
// We add the offset to the object.
#define IMAGE_HEIGHT_OFFSET 10

// Which character is selected in the main screen
#define FROG_SELECTED 0
#define PINK_M_SELECTED 1
#define V_GUY_SELECTED 2

#define V_GUY_FRAME_X 180
#define V_GUY_FRAME_Y 210
#define FROG_FRAME_X 330
#define FROG_FRAME_Y 210
#define P_M_FRAME_X 480
#define P_M_FRAME_Y 210


// -------------------- MOVING BACKGROUND ---------------------------
// How many frames we skip before moving down the background.
#define BG_FRAMES_SKIPPED 1
// How quickly background moves vertically.
#define BG_MOVING_SPEED 1


// -------------------- VIRUS ---------------------------
// How fast virus follows the player.
#define VIRUS_SPEED 1


// -------------------- PLAYER ---------------------------
// How fast player moves to left/right.
#define PLAYER_SIDE_MOVEMENT_SPEED 2

// Maximum vertical speed that player can posses.
#define PLAYER_V_SPEED_CAP 2

// How fast player moves vertically on initialization.
#define PLAYER_DEFAULT_V_SPEED 2

// Gravity defines how fast player speed decreases, it creates falling effect.
#define PLAYER_GRAVITY 0.25

// Wall bounce decreases player speed.
#define PLAYER_WALL_BOUNCE 0.95

// Defines how much our speed increases from boucing off the tile.
#define PLAYER_TILE_BOUNCE 4.8

#define PLAYER_INITIAL_X 380
#define PLAYER_INITIAL_Y 300

// -------------------- DIRECTIONS ---------------------------
#define NW 100
#define SE 101
#define SW 102
#define NE 103
#define N 104
#define S 105
#define W 106
#define E 107

// -------------------- FILE READING ---------------------------
#define SCORES_FILE "scores.txt"
#define PLAYER_FILE "player.txt"


// -------------------- TILE CONSTANTS ---------------------------

// Tile speed after player boucnes off the tile.
#define TILE_Y_SPEED 2
// Horizontal tile speed, is set randomly after reinitializing the tile.
#define TILE_X_SPEED 0.5
// Constant by which we decrease tile speed with each DoUpdate() call.
#define TILE_SPEED_DECREASE 0.01

// Speed of tiles after player bounces off the tile.
#define TILE_SPEED_AFTER_BOUNCE 1

// Probability that tiles gets horizontal speed
// We set speed if (rand() % P_TILE_X_SPEED == 0)
#define P_TILE_X_SPEED 4


// -------------------- ENEMY TILE ---------------------------
// How fast tiles moves after being released.
#define ENEMY_TILE_Y_SPEED 1

// How fast is loses its speed.
#define ENEMY_TILE_SPEED_DECREASE 0.001

// When virus is released (y coordinate).
#define VIRUS_RELEASE_Y 100


// -------------------- HAND SANITIZER TILE ---------------------------

// How long hand sanitizer protects the player.
#define SANITIZATION_TICKS 5000