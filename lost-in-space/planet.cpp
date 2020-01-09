#include "splashkit.h"
#include "planet.h"
#include "player.h"

bitmap planet_bitmap(planet_kind kind)
{
    switch (kind)
    {
        case MERCURY:
            return bitmap_named("mercury");
        case VENUS:
            return bitmap_named("venus");
        case EARTH:
            return bitmap_named("earth");
        case MARS:
            return bitmap_named("mars");
        case JUPITER:
            return bitmap_named("jupiter");
        case SATURN:
            return bitmap_named("saturn");
        case URANUS:
            return bitmap_named("uranus");
        case NEPTUNE:
            return bitmap_named("neptune");
        case PLUTO:
            return bitmap_named("pluto");
        default:
            return bitmap_named("pluto");
    }
}
/**
 * Creates a new planet in the at the desired x and y coordinates.
 *
 * @param  x,y  The x and y coordinates of the planet
 * @returns     The new planet data
 */
planet_data new_planet(double x, double y)
{
    planet_data result;
    result.kind = static_cast<planet_kind>(rnd(9));
    //draw the bitmap of the selected planet(only default)
    bitmap default_bitmap = planet_bitmap(result.kind);

    //create the planet with any random planet bitmap
    result.planet_sprite = create_sprite(planet_bitmap(result.kind));

    result.planet_visit = false;

    // Position the bitmap using parameters (double x and y)
    sprite_set_x(result.planet_sprite, x);
    sprite_set_y(result.planet_sprite, y);

    //start with a slow velocity
    sprite_set_dy(result.planet_sprite, rnd());
    return result;
}

void draw_planet(const planet_data &planet_to_draw)
{
    draw_sprite(planet_to_draw.planet_sprite);
}

void update_planet(const planet_data &planet_to_update)
{
    update_sprite(planet_to_update.planet_sprite);
}