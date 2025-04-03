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
    init_game(&game, pathMap);
    init_window(&window, 1000, 800, "Boule");
    bool quit = false; // quitte le jeu si true
    while (!quit)
    {

    } 
    return 0;
}
