#include "game.hpp"

void init_game(Game *game, string filename) // New game
{                                           // Initie la partie, y compris le monde
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->score = 0;
    game->statut = Begin;
    game->snake.head = (game->world->height / 2) * game->world->width + game->world->width / 2; // On place le Snake au milieu de la grille
    game->snake.d = HAUT;                                                                       // Par defaut il va vers le haut
    game->snake.neck = new Body;
    game->snake.neck->type = NBODY;
    game->snake.queue = new Body;
    game->snake.queue->type = NBODY;
    game->directions[0] = -game->world->width;
    game->directions[1] = game->world->width;
    game->directions[2] = -1;
    game->directions[3] = 1;
}

void load_game(Game *game, string filename)
{
    game->world = new World;

    cout << "etape 1" << endl;
    ifstream fic(filename.c_str());
    if (fic)
    {
        fic >> game->world->width;
        fic >> game->world->height;

        init_world(game->world, game->world->width, game->world->height);
        cout << "etape 2" << endl;
        string line;
        for (int i = 0; i < game->world->height; i++)
        {
            fic >> line;
            Block b;
            for (int k = 0; k < game->world->width; k++)
            {

                switch (line[k])
                {
                case '.':
                    b = Empty;
                    break;
                case 'R':
                    b = R;
                    break;
                case 'G':
                    b = G;
                    break;
                case 'B':
                    b = B;
                    break;
                case 'S':
                    b = Star;
                    break;
                default:
                    cout << "Erreur de lecture de la map: " << line[k] << endl;
                    return;
                }
                write(game->world, k, i, b);
            }
        }
        game->directions[0] = -game->world->width;
        game->directions[1] = game->world->width;
        game->directions[2] = -1;
        game->directions[3] = 1;
        game->statut = Play;
        cout << "etape 3" << endl;
        fic >> game->score; // on prend le score
        cout << "etape 4" << endl;
        fic >> game->snake.head; // On prend la position de la tete
        cout << "etape 5" << endl;
        game->snake.d = HAUT; // On met par defaut la position haut
        cout << "etape 6" << endl;
        game->statut = Play;
        cout << "etape 7" << endl;
        int taille;
        char Type;
        fic >> taille; // On prend la taille du snake
        cout << taille;
        Body *ptrcurrent = game->snake.neck;
        cout << "etape 8" << endl;
        ptrcurrent = new Body;
        cout << "etape 9" << endl;
        for (int i = 0; i < taille; i++) // Pour le nombre de Body du snake
        {
            cout << i + "etape" << endl;
            // On alloue de la memoire
            cout << i + "etape 1" << endl;
            if (i == 0) // Si c est le 1er element il devient le neck
            {
                game->snake.neck = ptrcurrent;
                cout << i + "etape 2" << endl;
                ptrcurrent->previous = NULL;
            }
            fic >> ptrcurrent->pos; // On prend la position du body
            cout << i + "etape 3" << endl;
            fic >> Type; // On prend le type du body
            switch (Type)
            {
            case 'R':
                ptrcurrent->type = RBODY;
                break;
            case 'G':
                ptrcurrent->type = GBODY;
                break;
            case 'B':
                ptrcurrent->type = BBODY;
                break;
            case 'N':
                ptrcurrent->type = NBODY;
                break;
            }
            cout << i + "etape 4" << endl;

            Body *ptrPrevious = ptrcurrent;
            ptrcurrent->next = new Body;
            ptrcurrent = ptrcurrent->next;
            ptrcurrent->previous = ptrPrevious;
            cout << i + "etape 5" << endl;
        }
        game->snake.queue = ptrcurrent;
        cout << "etape 6" << endl;
    }
    else
    {
        cout << "impossible de lire le fichier : " << filename << endl;
    }
}

void save_game(Game *game, string pathSave)
{
    // sauvegarde du monde
    cout << game->world->width << endl;
    cout << game->world->height << endl;
    for (int i = 0; i < game->world->height * game->world->width; i++)
    {
        if (i != 0 && i % (game->world->width) == 0)
        {
            cout << endl;
        }
        switch (game->world->grid[i])
        {
        case Empty:
            cout << '.';
            break;
        case R:
            cout << 'R';
            break;
        case G:
            cout << 'G';
            break;
        case B:
            cout << 'B';
            break;
        case Star:
            cout << 'S';
            break;

        default:
            break;
        }
    }
    cout << endl;
    cout << game->score << endl;      // sauvegarde le score
    cout << game->snake.head << endl; // l'emplacement de tete
    int count = 0;
    Body *ptr = game->snake.neck;
    while (ptr != NULL) // Compte il y a de body
    {
        count++;
        ptr = ptr->next;
    }
    cout << count << endl;
    ptr = game->snake.neck;
    for (int i = 0; i < count; i++) // Pour chaque body
    {
        cout << ptr->pos << endl;
        switch (ptr->type)
        {
        case NBODY:
            cout << 'N' << endl;
            break;
        case RBODY:
            cout << 'R' << endl;
            break;
        case GBODY:
            cout << 'G' << endl;
            break;
        case BBODY:
            cout << 'B' << endl;
            break;
        default:
            break;
        }
    }
}

void feed(Game *game, Block type, int pos)
{
    Body *a = new Body;
    cout << "A " << a << endl;
    a->type = (BodyType)type;
    a->pos = game->snake.head;  
    if(game->snake.queue->type == NBODY){
        game->snake.queue = a;
        game->snake.neck = a;
    }else{
        a->previous = game->snake.neck;
        game->snake.neck->next = a;
        game->snake.neck = a;
    }    
    game->snake.head = pos;
    game->world->grid[pos] = Empty;
    game->score += 1;
    spawn(game, type);
}

void move_snake(Window *window, Game *game, int *delay)
{
    cout << "Debut move" << endl;
    int pos = game->snake.head + game->directions[game->snake.d];
    if ((pos % game->world->width == 0 && game->snake.d == DROITE) || (pos % game->world->width == game->world->width - 1 && game->snake.d == GAUCHE)  || pos > game->world->width * game->world->height){
        game->statut = GameOver;
        // GAME OVER
    }
    else
    {
        Body *temp = game->snake.neck;
        Body *temp2 = game->snake.queue;
        switch (game->world->grid[pos])
        {
        case Star:
            *delay = 100;
            spawn(game, game->world->grid[pos]);
            game->world->grid[pos] = Empty;
            while (temp->previous != nullptr && temp->previous->previous != nullptr)
            {
                if (temp->type == temp->previous->type)
                {
                    if (temp->type == temp->previous->previous->type)
                    {   
                        game->score += 3;
                        
                        if(temp->previous->previous->previous == nullptr){
                            if(temp->next == nullptr){    
                                Body* vide = new Body;
                                vide->type = NBODY;                      
                                game->snake.queue = vide;
                                game->snake.neck = vide;
                            }else{
                                game->snake.queue = temp->next;
                                game->snake.queue->previous = nullptr;
                            }
                            
                        }else{
                            if(temp->next == nullptr){
                                game->snake.neck = temp->previous->previous->previous;
                                game->snake.neck->next = nullptr;
                            }else{
                                temp->next->previous = temp->previous->previous->previous;
                                temp->previous->previous->previous->next = temp->next;
                            }
                        }

                        delete temp->previous->previous;
                        delete temp->previous;
                        delete temp;
                        
                        cout << "NECK " << game->snake.neck << " QUEUE " << game->snake.queue << endl;
                        return;
                    }
                    else
                    {
                        temp = temp->previous->previous;
                    }
                }
                else
                {
                    temp = temp->previous;
                }
            }
            return;
        case Empty:

            while (temp2->next != nullptr)
            {
                temp2->pos = temp2->next->pos;
                temp2 = temp2->next;
            }
            temp2->pos = game->snake.head;
            game->snake.head = pos;
            
            return;
        default:
            cout << "defaut" << endl;
            feed(game, game->world->grid[pos], pos);
            cout << "passer" << endl;
            break;
        }
    }
    cout << "fin move" << endl;
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
    case GameOver:
        *statut = Statut(Begin);
        break;
    }
}

void display_game(Window *window, Game *game, SDL_Texture *BackGround[5], SDL_Texture *HeadTexture[8], SDL_Texture *BodyTexture[3], int delay)
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

    switch (game->snake.manger)
    {
    case true:
        draw_texture(window, HeadTexture[game->snake.d + 4], (game->snake.head % game->world->width * case_sizeX), (game->snake.head / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        break;
    case false:
        draw_texture(window, HeadTexture[game->snake.d], (game->snake.head % game->world->width * case_sizeX), (game->snake.head / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        break;
    }

    Body *temp = game->snake.neck;
    if (temp->type != NBODY)
    {
        while (temp != nullptr && temp->type != NBODY)
        {
            draw_texture(window, BodyTexture[temp->type], (temp->pos % game->world->width * case_sizeX), (temp->pos / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            temp = temp->previous;
        }
    }

    set_color(&window->foreground, 0, 0, 0, 255);
    string scr = "Score:" + to_string(game->score);
    draw_fill_rectangle(window, 0, window->height - case_sizeY, window->width, case_sizeY);
    draw_text(window, scr, 0, window->height - case_sizeY);
    refresh_window(window);
    SDL_Delay(delay);
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
                return true;
            case SDLK_m: // mute la musique
                mute_audio_type(window->mixer, 1);
                return false;
            case SDLK_s: // sauvegarde
                save_game(game, "ol");
                return false;
            case SDLK_r: // reset
                game->statut = Begin;
                return false;
            case SDLK_l: // oad menu
                game->statut = Load;
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

bool keyboard_eventBegin(Game *game, Window *window, int *counter, bool *select) // regarde les actions du clavier
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
                return true;
            case SDLK_f: // Selection
                *select += 1;
                return false;
            case SDLK_UP:
                if (*counter > 1)
                {
                    *counter -= 1;
                }
                return false;
            case SDLK_DOWN:
                if (*counter < 2)
                {
                    *counter += 1;
                }
                return false;

            default:
                return false;
                break;
            }
        }
    }
    return false;
}

bool keyboard_eventLoad(Game *game, Window *window, int *counter, bool *select) // regarde les actions du clavier
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
                return true;
            case SDLK_f: // Selection
                *select += 1;
                return false;
            case SDLK_r: // Selection
                game->statut = Begin;
                return false;
            case SDLK_UP:
                if (*counter > 1)
                {
                    *counter -= 1;
                }
                return false;
            case SDLK_DOWN:
                if (*counter < 4)
                {
                    *counter += 1;
                }
                return false;

            default:
                return false;
                break;
            }
        }
    }
    return false;
}

bool keyboard_eventGameOver(Game *game, Window *window) // regarde les actions du clavier
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
                return true;

            case SDLK_r:
                game->statut = Begin;
                return false;
            default:
                return false;
                break;
            }
        }
    }
    return false;
}

bool checkBody(Game *game, int pos){
    Body* temp = game->snake.neck;
    while(temp != nullptr){
        if(temp->pos == pos){
            return true;
        }
        temp = temp->previous;
    }
    return false;
}

void spawn(Game *game, Block type){
    int rngpos;
    do{
        rngpos = rand() % (game->world->height * game->world->width);
    }while(game->world->grid[rngpos] != Empty || checkBody(game, rngpos));
    game->world->grid[rngpos] = type;
}