// Jules Grenesche
// Séance 1 info7

// include
#include <cmath>
#include <random>
#include "game.hpp"
#include "window.hpp"
#include "world.hpp"

using namespace std;
struct Ball
{
    int x;
    int y;
    int dx;
    int dy;
};

int main(int argc, char **argv)
{
    Game game;
    Window window;
    string pathMap = "../assets/map/placeholder.txt";
    init_game(&game, pathMap);
    init_window(&window, 1000, 800, "Boule");
    SDL_Texture *FoodRed = load_image(&window, "../assets/sprite/food_red.png");
    SDL_Texture *FoodBlue = load_image(&window, "../assets/sprite/food_blue.png");
    SDL_Texture *FoodGreen = load_image(&window, "../assets/sprite/food_green.png");
    SDL_Texture *FoodStar = load_image(&window, "../assets/sprite/food_star.png");
    SDL_Texture *BackgroundTux = load_image(&window, "../assets/sprite/background.png");
    bool quit = false; // quitte le jeu si true
    while (!quit)
    {
    }
    return 0;
}
