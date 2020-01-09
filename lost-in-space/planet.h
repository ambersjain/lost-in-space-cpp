#ifndef LOST_IN_SPACE_PLANET
#define LOST_IN_SPACE_PLANET

#include "splashkit.h"
#include <vector>

using namespace std;

/**
 * Different options for the kind of planet.
 * Adjusts the image used.
 */
enum planet_kind
{
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    PLUTO
};

/**
 * The planet data keeps track of all of the information related to the planet.
 *
 * @field   planet_sprite   The planet's sprite - used to track position and movement
 * @field   planet_visit    If the planet visited, true, if not, false.
 * @field   kind            Current kind of planet ship
 */
struct planet_data
{
    sprite planet_sprite;
    bool planet_visit;
    planet_kind kind;
};

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 *
 * @param player_to_update      The player being updated
 */
bitmap planet_bitmap(planet_kind kind);

/**
 * Creates a new planet in the at the desired x and y coordinates.
 *
 * @param  x,y  The x and y coordinates of the planet
 * @returns     The new planet data
 */
planet_data new_planet(double x, double y);

/**
 * Draws the planet to the screen.
 *
 * @param planet_to_draw    The planet to draw to the screen
 */

void draw_planet(const planet_data &planet_to_draw);

/**
 * Actions a step update of the planet.
 *
 * @param planet_to_update      The planet being updated
 */
void update_planet(const planet_data &planet_to_update);

#endif