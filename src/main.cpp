// Anis Hamila et Jules Grenesche
// info7 Snake

// include

#include "game.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Game game;
    Window window;
    string pathMapNewGame = "./assets/map/world2.dat";
    bool quit = false; // quitte le jeu si true
    init_window(&window, 1000, 800, "Snake");
    game.statut = Begin;
    SDL_Texture *FoodRed = load_image(&window, "./assets/sprite/food_red.png");
    SDL_Texture *FoodBlue = load_image(&window, "./assets/sprite/food_blue.png");
    SDL_Texture *FoodGreen = load_image(&window, "./assets/sprite/food_green.png");
    SDL_Texture *FoodStar = load_image(&window, "./assets/sprite/food_star.png");
    SDL_Texture *BackgroundTux = load_image(&window, "./assets/sprite/background.png");
    SDL_Texture *HeadUpClose = load_image(&window, "./assets/sprite/head_close_up.png");
    SDL_Texture *HeadUpOpen = load_image(&window, "./assets/sprite/head_open_up.png");
    SDL_Texture *HeadLeftClose = load_image(&window, "./assets/sprite/head_close_left.png");
    SDL_Texture *HeadLeftOpen = load_image(&window, "./assets/sprite/head_open_left.png");
    SDL_Texture *HeadDownClose = load_image(&window, "./assets/sprite/head_close_down.png");
    SDL_Texture *HeadDownOpen = load_image(&window, "./assets/sprite/head_open_down.png");
    SDL_Texture *HeadRightClose = load_image(&window, "./assets/sprite/head_close_right.png");
    SDL_Texture *HeadRightOpen = load_image(&window, "./assets/sprite/head_open_right.png");
    SDL_Texture *BodyRed = load_image(&window, "./assets/sprite/body_red.png");
    SDL_Texture *BodyGreen = load_image(&window, "./assets/sprite/body_green.png");
    SDL_Texture *BodyBlue = load_image(&window, "./assets/sprite/body_blue.png");
    SDL_Texture *TextureBackground[5] = {BackgroundTux, FoodRed, FoodGreen, FoodBlue, FoodStar};
    SDL_Texture *TextureHead[8] = {HeadUpClose, HeadDownClose, HeadLeftClose, HeadRightClose, HeadUpOpen, HeadDownOpen, HeadLeftOpen, HeadRightOpen};
    SDL_Texture *TextureBody[3] = {BodyRed, BodyGreen, BodyBlue};
    int delay = 200;
    int counter;
    bool select;
    counter = 1;
    select = false;
    stringstream str;
    string score;
    while (!quit)
    {
        switch (game.statut)    // Vérifie le statut du jeu
        {
        case Begin: // affiche le menu de démarrage
            clear_window(&window);
            set_color(&window.foreground, 250, 250, 250, 250);
            set_color(&window.background, 0, 0, 0, 250);
            draw_text(&window, "-->", (window.width / 3) - 40, counter * window.height / 3);
            draw_text(&window, "New game", window.width / 3, window.height / 3);
            draw_text(&window, "Load game", window.width / 3, 2 * window.height / 3);
            draw_text(&window, "Q pour quitter, Haut/bas curseur, f Select, r= reset", 0, window.height - 25);
            refresh_window(&window);
            quit = keyboard_eventBegin(&game, &window, &counter, &select); // regarde les actions du clavier
            if (select == 1)
            {
                switch (counter)
                {
                case 1:
                    init_game(&game, pathMapNewGame);
                    game.statut = Play;
                    break;
                case 2:
                    game.statut = Load;
                    select = false;
                    counter = 1;
                    break;
                }
            }
            break;

        case Load:  // Affiche le menu de chargement

            clear_window(&window);
            set_color(&window.foreground, 250, 250, 250, 250);
            set_color(&window.background, 0, 0, 0, 250);
            draw_text(&window, "-->", (window.width / 3) - 40, counter * window.height / 5);
            draw_text(&window, "Game 1", window.width / 3, window.height / 5);
            draw_text(&window, "Game 2", window.width / 3, 2 * window.height / 5);
            draw_text(&window, "Game 3", window.width / 3, 3 * window.height / 5);
            draw_text(&window, "Game 4", window.width / 3, 4 * window.height / 5);
            refresh_window(&window);
            quit = keyboard_eventLoad(&game, &window, &counter, &select);
            if (select == 1)
            {
                switch (counter)
                {
                case 1:
                    load_game(&game, "./assets/map/Save1.txt");
                    game.statut = Play;
                    break;
                case 2:
                    load_game(&game, "./assets/map/Save2.txt");
                    game.statut = Play;
                    break;
                case 3:
                    load_game(&game, "./assets/map/Save3.txt");
                    game.statut = Play;
                    break;
                case 4:
                    load_game(&game, "./assets/map/Save4.txt");
                    game.statut = Play;
                    break;
                }
            }
            break;
        case Save:  // affiche le menu de sauvegarde
            clear_window(&window);
            set_color(&window.foreground, 250, 250, 250, 250);
            set_color(&window.background, 0, 0, 0, 250);
            draw_text(&window, "Save :", window.width / 3, 0);
            draw_text(&window, "-->", (window.width / 3) - 40, counter * window.height / 5);
            draw_text(&window, "Game 1", window.width / 3, window.height / 5);
            draw_text(&window, "Game 2", window.width / 3, 2 * window.height / 5);
            draw_text(&window, "Game 3", window.width / 3, 3 * window.height / 5);
            draw_text(&window, "Game 4", window.width / 3, 4 * window.height / 5);
            refresh_window(&window);
            quit = keyboard_eventLoad(&game, &window, &counter, &select);
            if (select == 1)
            {
                switch (counter)
                {
                case 1:
                    save_game(&game, "./assets/map/Save1.txt");
                    game.statut = Play;
                    break;
                case 2:
                    save_game(&game, "./assets/map/Save2.txt");
                    game.statut = Play;
                    break;
                case 3:
                    save_game(&game, "./assets/map/Save3.txt");
                    game.statut = Play;
                    break;
                case 4:
                    save_game(&game, "./assets/map/Save4.txt");
                    game.statut = Play;
                    break;
                }
            }
            break;
        case Play:  // affiche le jeu en cours
            clear_window(&window);
            move_snake(&window, &game, &delay);
            display_game(&window, &game, TextureBackground, TextureHead, TextureBody, delay);
            quit = keyboard_event(&game, &window, pathMapNewGame);
            if (delay < 200)
            {
                delay += 10;
            }
            break;

        case GameOver:   // affiche le menu de défaite

            str << game.score;
            str >> score;
            clear_window(&window);
            draw_text(&window, "Game Over", (window.width / 3) - 40, window.height / 5);
            draw_text(&window, "Votre score: " + score, (window.width / 3) - 40, 2 * window.height / 5);
            draw_text(&window, "R pour recommencer", (window.width / 3) - 40, 3 * window.height / 5);
            draw_text(&window, "Q pour quitter", (window.width / 3) - 40, 4 * window.height / 5);
            refresh_window(&window);
            quit = keyboard_eventGameOver(&game, &window);
            str.clear();
            counter = 1;
            select = false;

            break;

        case Pause: // Affiche le menu de pause
            draw_text(&window, "Load menu = l", (window.width / 3) - 40, window.height / 10);
            draw_text(&window, "R = Reset", (window.width / 3) - 40, 2 * window.height / 10);
            draw_text(&window, "Save menu = S", (window.width / 3) - 40, 3 * window.height / 10);
            draw_text(&window, "Pause", (window.width / 3) - 40, 2 * 4 * window.height / 10);
            refresh_window(&window);
            quit = keyboard_eventBreak(&game, &window, pathMapNewGame);
            counter = 1;
            select = false;
            break;

        default:
            break;
        }
    }

    close_window(&window);
    return 0;
}
