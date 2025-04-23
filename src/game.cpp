#include "game.hpp"

void init_game(Game *game, string filename)
{ // Initie la partie, y compris le monde
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->score = 0;
    game->statut = Begin;
    game->snake.head = (game->world->height / 2) * game->world->width + game->world->width / 2; // On place le Snake au milieu de la grille
    game->snake.d = HAUT;                                                                       // Par defaut il va vers le haut
}

void move_snake(Window *window, Game *game)
{
    switch (game->snake.d)
    {
    case HAUT:
        game->snake.head = game->snake.head - game->world->width;
        break;
    case BAS:
        game->snake.head = game->snake.head + game->world->width;
        break;
    case GAUCHE:
        game->snake.head = game->snake.head - 1;
        break;
    case DROITE:
        game->snake.head = game->snake.head + 1;
        break;
    }
}

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

void display_game(Window *window, Game *game, SDL_Texture *BackGround[5], SDL_Texture *HeadTexture[8])
{ // réinitialise le contenu de la fenetre, dessine la map, le snake puis rafraichit la fenetre
    clear_window(window);
    int case_sizeX = window->width / game->world->width;
    int case_sizeY = window->height / game->world->height;
    set_color(&window->background, 255, 255, 255, 255);
    // On dessine le background
    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        draw_texture(window, BackGround[0], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
    }
    // On dessine les pastilles
    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        switch (game->world->grid[i])
        {
        case Statut(R):
            draw_texture(window, BackGround[1], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        case Statut(G):
            draw_texture(window, BackGround[2], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        case Statut(B):
            draw_texture(window, BackGround[3], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        case Statut(Star):
            draw_texture(window, BackGround[4], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            break;
        default:
            break;
        }
    }

    // on dessine le snake
    switch (game->snake.d)
    {
    case HAUT:
        draw_texture(window, HeadTexture[2], (game->snake.head % game->world->width * case_sizeX), (game->snake.head / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        break;
    case BAS:
        draw_texture(window, HeadTexture[0], (game->snake.head % game->world->width * case_sizeX), (game->snake.head / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        break;
    case GAUCHE:
        draw_texture(window, HeadTexture[1], (game->snake.head % game->world->width * case_sizeX), (game->snake.head / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        break;
    case DROITE:
        draw_texture(window, HeadTexture[4], (game->snake.head % game->world->width * case_sizeX), (game->snake.head / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        break;
    default:
        break;
    }

    set_color(&window->foreground, 0, 0, 0, 255);
    string scr = "Score:" + to_string(game->score);
    draw_fill_rectangle(window, 0, window->height - case_sizeY, window->width, case_sizeY);
    draw_text(window, scr, 0, window->height - case_sizeY);
    refresh_window(window);
    SDL_Delay(1000);
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
                game->snake.d = DROITE;
                return false;
            case SDLK_LEFT:
                game->snake.d = GAUCHE;
                return false;
            case SDLK_UP:
                game->snake.d = HAUT;
                return false;
            case SDLK_DOWN:
                game->snake.d = BAS;
                return false;

            default:
                return false;
                break;
            }
        }
    }
    return false;
}