#include "splashkit.h"
#include "player.h"
#include "planet.h"
#include "lost_in_space.h"

/**
 * The ship bitmap function converts a ship kind into a
 * bitmap that can be used.
 *
 * Not exposed by the header.
 *
 * @param kind  The kind of ship you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return bitmap_named("aquarii");
    case GLIESE:
        return bitmap_named("gliese");
    default:
        return bitmap_named("pegasi");
    }
}
/**
 * Displays the score, location and distance as text
 *
 * @param planet  Any planet data input
 * @param player  Any player data input
 *
 */

void draw_hud(const vector<planet_data> &planets, const player_data &player)
{
    game_data game;
    int planet_index = closest_planet_index(player, planets);
    //x and y are the position coordinates of player sprite
    float x = sprite_x(player.player_sprite);
    float y = sprite_y(player.player_sprite);
    //To store the center points of both planet and player
    point_2d planet_center, player_center;
    planet_center = center_point(planets[planet_index].planet_sprite);
    player_center = center_point(player.player_sprite);
    //Calculate distance between center of planet and center of player
    //float point_point_distance(const point_2d &pt1, const point_2d &pt2)
    float distance;
    distance = point_point_distance(planet_center, player_center);
    //container for the whole draw thing
    fill_rectangle(COLOR_WHITE, 5, 40, 280, 40, option_to_screen());
    //draw some text
    draw_text("SCORE: " + to_string(player.score), COLOR_BLACK, 5, 50, option_to_screen());
    draw_text("LOCATION: " + to_string(x) + ", " + to_string(y), COLOR_BLACK, 5, 60, option_to_screen());
    draw_text("DISTANCE TO CLOSEST PLANET: " + to_string(distance), COLOR_BLACK, 5, 70, option_to_screen());
    //draw bar
    draw_bitmap("bar_white_fill", 0, 0, option_to_screen());

    double percentage = (LEVEL_TIME - timer_ticks("TIMER"));
    double percentage_remaining = percentage / LEVEL_TIME;
    if (percentage < 0)
    {
        percentage = 0;
    }
    double bar_width = bitmap_width("green_bar_lines") * percentage_remaining;
    write_line(bar_width);
    write_line(percentage_remaining);
    write_line("timer is: " + to_string(timer_ticks("TIMER")));
    //drawing_options option_part_bmp(double x, double y, double w, double h)
    draw_bitmap("green_bar_lines", 0, 0, option_part_bmp(0, 0, bar_width, bitmap_height("green_bar_lines"), option_to_screen()));
}

player_data new_player()
{
    player_data result;
    result.score = 0;
    bitmap default_bitmap = ship_bitmap(AQUARII);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    result.player_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.player_sprite, ship_bitmap(GLIESE), "GLIESE");
    sprite_add_layer(result.player_sprite, ship_bitmap(PEGASI), "PEGASI");

    // Default to layer 0 = Aquarii so hide others
    sprite_hide_layer(result.player_sprite, 1);
    sprite_hide_layer(result.player_sprite, 2);

    result.kind = AQUARII;

    // Position in the centre of the initial screen
    sprite_set_x(result.player_sprite, (screen_width() - sprite_width(result.player_sprite)) / 2);
    sprite_set_y(result.player_sprite, (screen_height() - sprite_width(result.player_sprite)) / 2);

    return result;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player_to_update.player_sprite);

    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    // Test if the player is outside the area and move the camera
    // the player will appear to stay still and everything else
    // will appear to move :)

    // Test top/bottom of screen
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
}

/**
 * Switch the ship kind - will adjust which layer is hidden/shown
 */
void player_switch_to_ship(player_data &player, ship_kind target)
{
    // only do this if there is a change
    if (player.kind != target)
    {
        // show then hide layers
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(player.kind));

        // remember what is currently shown
        player.kind = target;
    }
}

void handle_input(player_data &player)
{
    // Allow the player to switch ships
    if (key_typed(NUM_1_KEY))
        player_switch_to_ship(player, AQUARII);
    if (key_typed(NUM_2_KEY))
        player_switch_to_ship(player, GLIESE);
    if (key_typed(NUM_3_KEY))
        player_switch_to_ship(player, PEGASI);

    // Handle movement - rotating left/right and moving forward/back
    float dx = sprite_dx(player.player_sprite);
    float rotation = sprite_rotation(player.player_sprite);

    // Allow rotation with left/right keys
    if (key_down(LEFT_KEY))
        sprite_set_rotation(player.player_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(player.player_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys - typed to give step increases
    if (key_typed(DOWN_KEY))
        sprite_set_dx(player.player_sprite, dx - PLAYER_SPEED);
    if (key_typed(UP_KEY))
        sprite_set_dx(player.player_sprite, dx + PLAYER_SPEED);
}
