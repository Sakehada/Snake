// Anis Hamila et Jules Grenesche
// info7 Snake

// include
#include <cmath>
#include <random>
#include "game.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Game game;
    Window window;
    string pathMap = "./assets/map/world2.dat";
    init_game(&game, pathMap);
    init_window(&window, 1000, 800, "Snake");
    SDL_Texture *FoodRed = load_image(&window, "./assets/sprite/food_red.png");
    SDL_Texture *FoodBlue = load_image(&window, "./assets/sprite/food_blue.png");
    SDL_Texture *FoodGreen = load_image(&window, "./assets/sprite/food_green.png");
    SDL_Texture *FoodStar = load_image(&window, "./assets/sprite/food_star.png");
    SDL_Texture *BackgroundTux = load_image(&window, "./assets/sprite/background.png");

    display_game(&window, &game, FoodRed, FoodBlue, FoodGreen, FoodStar, BackgroundTux);
    bool quit = false; // quitte le jeu si true
    while (!quit)
    {
    }
    return 0;
}
