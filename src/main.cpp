// Anis Hamila et Jules Grenesche
// info7 Snake

// include

#include "game.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Game game;
    Window window;
    string pathMap = "./assets/map/world2.dat";
    bool quit = false; // quitte le jeu si true
    init_game(&game, pathMap);
    cout << game.snake.d << endl;
    cout << game.snake.head;
    init_window(&window, 1000, 800, "Snake");
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
    while(!(keyboard_event(&game, &window, pathMap)))
    {
        move_snake(&window, &game, &delay);
        display_game(&window, &game, TextureBackground, TextureHead, TextureBody, delay);
        if(delay < 200){delay += 10;}
    }

    close_window(&window);
    return 0;
}
