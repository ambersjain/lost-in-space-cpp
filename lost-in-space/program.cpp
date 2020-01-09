#include "splashkit.h"
#include "player.h"
#include "planet.h"
#include "lost_in_space.h"
#include <vector>
using std::vector;

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 *
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();
    game_data game_new;
    game_new = new_game();

    while (not quit_requested())
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(game_new.player);

        update_game(game_new);
        draw_game(game_new);
    }
    return 0;
}