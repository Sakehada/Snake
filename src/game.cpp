#include "game.hpp"

void init_game(Game *game, string filename)
{ // Initie la partie, y compris le monde
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->score = 0;
    game->statut = Begin;
    game->snake.head = (game->world->height / 2) * game->world->width + game->world->width / 2; // On place le Snake au milieu de la grille
    game->snake.d = HAUT;                                                                       // Par defaut il va vers le haut
    game->snake.neck = new Body;
    game->snake.neck->type = NBODY;
    game->snake.queue = game->snake.neck;
    game->directions[0] = -game->world->width;
    game->directions[1] = game->world->width;
    game->directions[2] = -1;
    game->directions[3] = 1;
}

void move_snake(Window *window, Game *game)
{
    Block nextBlock;
    int pos;
    pos = game->snake.head + game->directions[game->snake.d];
    feed(game, game->world->grid[pos], pos);
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

    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        draw_texture(window, BackGround[0], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY); // On dessine le background
        switch (game->world->grid[i])                                                                                                              // On dessine les pastilles
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

void feed(Game *game, BodyType type, Direction pos){
    Body* a = new Body;
    a->type = type;  
    a->pos = game->snake.head;
    game->snake.head = pos;
    game->snake.queue =
    Body* temp = game->snake.neck;
    int i = abs(game->snake.neck.pos - game->snake.head.pos);
    for(int j = 0; j < i; j++){
        temp = temp->previous;

    }
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