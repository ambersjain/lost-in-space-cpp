#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "planet.h"
#include "player.h"

#include <string>
#include <vector>
using std::vector;
using namespace std;

#define LEVEL_TIME 20000.00

struct game_data
{
    player_data player;
    vector<planet_data> planets;
    timer game_timer;
};
/**
 * Generates planets at random positions and player at the center
 *
 * @param game          game_data struct
 * @param width         width of screen
 * @param height        height of screen
 * @param num_planets   number of planets
 */
void setup_level(game_data &game, int width, int height, int num_planets);
//Initialises new game
game_data new_game();
/**
 * draws all planets and Display
 * @param game          game data struct
 */
void draw_game(game_data &game);
/**
 * Updates game data
 * @param game          game data struct
 */
void update_game(game_data &game);
/**
 * Returns index of the closest index
 *
 * @param player        player_struct
 * @param planets       planets vector
 */
int closest_planet_index(const player_data &player, const vector<planet_data> &planets);
/**
 * Checks if player sprite and planet sprite has collided.
 * @param game          game data struct
 */
void check_collisions(game_data &game);

#endif