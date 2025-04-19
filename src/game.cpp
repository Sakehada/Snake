#include "game.hpp"

void init_game(Game *game, string filename)
{ // Initie la partie, y compris le monde
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->score = 0;

    /*
     *directions[HAUT] = -game->world->width;
     *directions[BAS] = game->world->width;
     *directions[GAUCHE] = -1;
     *directions[DROITE] = 1;*/
}

/*
void move_snake(Window *window, Game *game)
{ // bouge la balle
    Block *detect_d = &game->world->grid[getId(game->ball_x, game->ball_y + game->ball_dy, game->world->width)]; // Block du haut ou du bas
    bool diagTest = true;
    switch (*detect_y) // gestion du block y
    {
    case Empty:
        break;
    case Lose:
        diagTest = false;
        game->statut = GameOver;
        break;
    case Type1:
        diagTest = false;
        game->ball_dy = -game->ball_dy;
        *detect_y = Empty;
        play(window->mixer, Break, 500);
        game->score = game->score + 1;
        break;
    case Type2:
        diagTest = false;
        game->ball_dy = -game->ball_dy;
        *detect_y = Type1;
        play(window->mixer, Bong, 500);
        game->score = game->score + 1;
        break;
    case Border:
        diagTest = false;
        play(window->mixer, Bong, 500);
        game->ball_dy = -game->ball_dy;
        break;
    }

    switch (*detect_x) // gestion du block x
    {
    case Empty:
        break;
    case Lose:
        diagTest = false;
        game->statut = GameOver;
        return;
        break;
        case Type1:
        diagTest = false;
        game->ball_dx = -game->ball_dx;
        *detect_x = Empty;
        play(window->mixer, Break, 500);
        game->score = game->score + 1;
        return;
        break;
    case Type2:
        diagTest = false;
        game->ball_dx = -game->ball_dx;
        *detect_x = Type1;
        play(window->mixer, Bong, 500);
        game->score = game->score + 1;
        return;
        break;
    case Border:
        play(window->mixer, Bong, 500);
        game->ball_dx = -game->ball_dx;
        return;
        break;
    }
    if(diagTest){ // si le block x et le block y est vide, gere le block de diagonale
        switch(*detect_xy){ // gestion du block y
            case Empty:
                break;
            case Lose:
                game->statut = GameOver;
                return;
                break;
            case Type1:
                play(window->mixer, Break, 500);
                *detect_xy = Empty;
                game->ball_dx = -game->ball_dx;
                game->ball_dy = -game->ball_dy;
                game->score = game->score + 1;
                return;
                break;
            case Type2:
                play(window->mixer, Bong, 500);
                *detect_xy = Type1;
                game->ball_dx = -game->ball_dx;
                game->ball_dy = -game->ball_dy;
                game->score = game->score + 1;
                return;
                break;
            case Border:
                play(window->mixer, Bong, 500);
                game->ball_dx = -game->ball_dx;
                game->ball_dy = -game->ball_dy;
                return;
                break;

        }

    }
    if (game->racket_y == game->ball_y + game->ball_dy) // gestion de la collision avec la raquette
    {
        if (game->racket_x == game->ball_x)
        {
            game->ball_dy = -1;
        }
        else if (game->racket_x == game->ball_x - 1 || game->racket_x == game->ball_x - game->racket_half_width)
        {
            game->ball_dy = -1;
            game->ball_dx = 1;
        }
        else if (game->racket_x == game->ball_x + 1 || game->racket_x == game->ball_x + game->racket_half_width)
        {
            game->ball_dy = -1;
            game->ball_dx = -1;
        }
    }

    game->ball_x += game->ball_dx;
    game->ball_y += game->ball_dy;
}

*/

void change_statut(Statut *statut)
{ // change le statut du jeu en fonction du statut actuel
    switch (*statut)
    {
    case Begin:
        *statut = Statut(Play);
        break;
    case Play:
        *statut = Statut(Pause);
        break;
    case Pause:
        *statut = Statut(Play);
        break;
    case Win:
        *statut = Statut(Begin);
    case GameOver:
        *statut = Statut(Begin);
        break;
    }
}

void display_game(Window *window, Game *game, SDL_Texture *FoodRed, SDL_Texture *FoodBlue, SDL_Texture *FoodGreen, SDL_Texture *FoodStar, SDL_Texture *BackgroundTux)
{ // réinitialise le contenu de la fenetre, dessine la map, la balle et la raquette puis rafraichit la fenetre
    clear_window(window);
    int case_sizeX = window->width / game->world->width;
    int case_sizeY = window->height / game->world->height;
    set_color(&window->background, 255, 255, 255, 255);
    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        draw_texture(window, BackgroundTux, (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
    }
    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        switch (game->world->grid[i])
        {
        case Statut(R):
            draw_texture(window, FoodRed, (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        case Statut(G):
            draw_texture(window, FoodGreen, (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        case Statut(B):
            draw_texture(window, FoodBlue, (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        case Statut(Star):
            draw_texture(window, FoodStar, (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        default:
            break;
        }
    }

    set_color(&window->foreground, 0, 0, 0, 255);
    string scr = "Score:" + to_string(game->score);
    draw_fill_rectangle(window, 0, window->height - case_sizeY, window->width, case_sizeY);
    draw_text(window, scr, 0, window->height - case_sizeY);
    refresh_window(window);
    SDL_Delay(2000);
    close_window(window);
}

bool keyboard_event(Game *game, Window *window, string pathMap) // regarde les actions du clavier
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_KEYDOWN)
        {
            SDL_KeyboardEvent key_event = event.key;
            switch (key_event.keysym.sym)
            {
            case SDLK_q: // pour quitter
                cout << "q" << endl;
                return true;
            case SDLK_m: // mute la musique
                mute_audio_type(window->mixer, 1);
                return false;
            case SDLK_s: // mute les bruits
                mute_audio_type(window->mixer, 0);
                return false;
            case SDLK_r: // reset
                cout << "Reset" << endl;
                game->statut = Statut(Pause);
                init_game(game, pathMap);
                return false;
            case SDLK_SPACE: // Pause
                change_statut(&(game->statut));
                return false;
            case SDLK_RIGHT: // Deplacer la raquette

                return false;
            case SDLK_LEFT:

                return false;
            default:
                return false;
                break;
            }
        }
    }
    return false;
}