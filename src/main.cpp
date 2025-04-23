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
    SDL_Texture *TextureHead[8] = {HeadDownClose, HeadLeftClose, HeadUpClose, HeadRightClose, HeadDownOpen, HeadLeftOpen, HeadUpOpen, HeadRightOpen};
    SDL_Texture *TextureBody[3] = {BodyRed, BodyGreen, BodyBlue};
    game.snake.d = BAS;
    for (int i = 0; i < 5; i++)
    {
        move_snake(&window, &game);
        display_game(&window, &game, TextureBackground, TextureHead);
    }
    close_window(&window);
    return 0;
}
