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
    string pathMap = "./assets/map/world.dat";
    Game game;
    Window window;
    init_game(&game, pathMap);
    init_window(&window, 1000, 800, "Boule");
    bool quit = false; // quitte le jeu si true
    int speedRatio = 5; // ratio entre la vitesse de la raquette et celle de la balle
    int i = 0; // iteration de la boucle principale
    while (!quit)
    {
        if (game.score == game.scrWin)
        {
            game.statut = Win;
        }
        switch (game.statut)
        {
        case Begin:
            game.ball_y = game.racket_y - 1;
            quit = keyboard_event(&game, &window, pathMap);
            display_game(&window, &game);
            break;
        case Pause:
            quit = keyboard_event(&game, &window, pathMap);
            display_game(&window, &game);
            break;
        case Play:
            quit = keyboard_event(&game, &window, pathMap);
            if(! (i % speedRatio)){ move_ball(&window, &game); i = 1;}        
            display_game(&window, &game);
            break;
        case GameOver:
            set_color(&window.foreground, 250, 0, 0, 250);
            set_color(&window.background, 0, 0, 0, 250);
            draw_text(&window, "C'est perdu", window.width / 2, window.height / 2);
            draw_text(&window, "Q pour quitter", window.width / 2, (window.height + window.height / 10) / 2);
            draw_text(&window, "R pour reset", window.width / 2, (window.height + window.height / 5) / 2);
            refresh_window(&window);
            quit = keyboard_event(&game, &window, pathMap);
            break;
        case Win:
            set_color(&window.foreground, 0, 250, 0, 250);
            set_color(&window.background, 0, 0, 0, 250);
            draw_text(&window, "Victoire", window.width / 2, window.height / 2);
            draw_text(&window, "Q pour quitter", window.width / 2, (window.height + window.height / 10) / 2);
            draw_text(&window, "R pour reset", window.width / 2, (window.height + window.height / 5) / 2);
            refresh_window(&window);
            quit = keyboard_event(&game, &window, pathMap);
            break;
        default:
            break;
        }

        i++;
        SDL_Delay(100 - game.ball_speed);
    }
    return 0;
}
