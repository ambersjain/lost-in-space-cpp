#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "planet.h"

#include <vector>
using std::vector;
using namespace std;

//Generates planets at random positions and player at the center
void setup_level(game_data &game, int width, int height, int num_planets)
{
    reset_timer("TIMER");
    //Position in the centre of the initial screen using height and width
    sprite_set_x(game.player.player_sprite, (width - sprite_width(game.player.player_sprite)) / 2);
    sprite_set_y(game.player.player_sprite, (height - sprite_width(game.player.player_sprite)) / 2);

    //creating indicated(num_planets) number of random planets
    for (int i = 0; i < num_planets; i++)
    {
        //new_planet(double x, double y), generating random values of x and y coordinates
        game.planets.push_back(new_planet(rnd(3000), rnd(3000)));
    }
}

game_data new_game()
{
    game_data game;
    //storing new_player() inside game_data
    game.player = new_player();
    game.game_timer = create_timer("TIMER");
    //reset_timer("TIMER");
    start_timer(game.game_timer);
    setup_level(game, 3000, 3000, 10);
    return game;
}

void draw_game(game_data &game)
{
    int planet_index = closest_planet_index(game.player, game.planets);
    //draw everything
    clear_screen(COLOR_BLACK);

    draw_hud(game.planets, game.player);

    // Draw planet
    for (int i = 0; i < game.planets.size(); i++)
    {
        draw_planet(game.planets[i]);
    }
    // as well as the player who can move
    draw_player(game.player);
    check_collisions(game);
    refresh_screen(60);
}

void update_game(game_data &game)
{
    update_player(game.player);
    for (int i = 0; i < game.planets.size(); i++)
    {
        update_planet(game.planets[i]);
    }
}

//returns index of closest planet to the player
int closest_planet_index(const player_data &player, const vector<planet_data> &planets)
{
    //If All the planets have been visited
    int index = -1;
    //The distance from the first planet as a reference
    point_2d player_center = center_point(player.player_sprite);
    point_2d test_center = center_point(planets[0].planet_sprite);
    vector_2d player_to_test = vector_point_to_point(player_center, test_center);

    double test_distance = vector_magnitude(player_to_test);
    double distance = test_distance;

    for (int i = 1; i < planets.size(); i++)
    {
        if (planets[i].planet_visit == false)
        {
            test_center = center_point(planets[i].planet_sprite);
            player_to_test = vector_point_to_point(player_center, test_center);
            test_distance = vector_magnitude(player_to_test);

            if (test_distance < distance || index == -1)
            {
                distance = test_distance;
                index = i;
            }
        }
    }
    return index;
}

void check_collisions(game_data &game)
{
    for (int i = 0; i < game.planets.size(); i++)
    {
        if (sprite_collision(game.player.player_sprite, game.planets[i].planet_sprite))
        {
            if (game.planets[i].planet_visit == false)
            {
                game.planets[i].planet_visit = true;
                game.player.score++;
                load_sound_effect("yes", "yes.wav");
                play_sound_effect("yes");
                reset_timer("TIMER");
            }
        }
    }
    if (closest_planet_index(game.player, game.planets) == -1)
    {
        setup_level(game, 3000, 3000, 5);
    }
}
