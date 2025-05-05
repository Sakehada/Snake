#include "game.hpp"

void init_game(Game *game, string filename) // Initialise un nouveau monde
{
    game->mixer = new Mixer;
    init_audio(game->mixer);
    play(game->mixer, Music1);
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->score = 0;
    game->statut = Begin;
    game->snake.head = (game->world->height / 2) * game->world->width + game->world->width / 2; // On place le Snake au milieu de la grille
    game->snake.d = HAUT;                                                                       // Par defaut il va vers le haut
    game->snake.neck = new Body;                                                                // On initie le cou et la queue à un body de type Empty
    game->snake.neck->type = NBODY;
    game->snake.queue = new Body;
    game->snake.queue->type = NBODY;
    game->directions[0] = -game->world->width;                                                  // On initie le tableau de directions en fonction de la taille du tableau
    game->directions[1] = game->world->width;
    game->directions[2] = -1;
    game->directions[3] = 1;
}

void load_game(Game *game, string filename) // Charge une sauvegarde
{
    game->mixer = new Mixer;                                                                   // On initie l'audio du jeu                            
    init_audio(game->mixer);
    play(game->mixer, Music1);                                                                 // On lance la musique
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
                    break;
                }
                write(game->world, k, i, b);
            }
        }
        game->directions[0] = -game->world->width;                      // On initie le tableau de directions en fonction de la taille du tableau
        game->directions[1] = game->world->width;
        game->directions[2] = -1;
        game->directions[3] = 1;
        game->statut = Play;
        fic >> game->score; // on prend le score
        fic >> game->snake.head; // On prend la position de la tete
        game->snake.d = HAUT; // On met par defaut la position haut
        game->statut = Play;
        int taille;
        char Type;
        fic >> taille; // On prend la taille du snake
        cout << taille;
        Body *ptrcurrent = game->snake.neck;
        ptrcurrent = new Body;
        for (int i = 0; i < taille; i++) // Pour le nombre de Body du snake
        {
            // On alloue de la memoire
            if (i == 0) // Si c est le 1er element il devient le neck
            {
                game->snake.neck = ptrcurrent;
                ptrcurrent->previous = NULL;
            }
            fic >> ptrcurrent->pos; // On prend la position du body
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

            Body *ptrPrevious = ptrcurrent;
            ptrcurrent->previous = new Body;
            ptrcurrent = ptrcurrent->previous;
            ptrcurrent->next = ptrPrevious;
        }
        game->snake.queue = ptrcurrent;
    }
    else
    {
        cout << "impossible de lire le fichier : " << filename << endl;
    }
}

void save_game(Game *game, string pathSave)
{
    // sauvegarde du monde

    FILE *fp = fopen(pathSave.c_str(), "w");
    stringstream ss;
    ss << game->world->width;
    string line;
    ss >> line;
    fputs(line.c_str(), fp);
    fputs("\n", fp);
    ss.clear();
    ss << game->world->height;
    ss >> line;
    fputs(line.c_str(), fp);
    fputs("\n", fp);
    ss.clear();

    for (int i = 0; i < game->world->height * game->world->width; i++)
    {
        if (i != 0 && i % (game->world->width) == 0)
        {
            fputs("\n", fp);
        }
        switch (game->world->grid[i])
        {
        case Empty:
            fputs(".", fp);
            break;
        case R:
            fputs("R", fp);
            break;
        case G:
            fputs("G", fp);
            break;
        case B:
            fputs("B", fp);
            break;
        case Star:
            fputs("S", fp);
            break;

        default:
            break;
        }
    }

    fputs("\n", fp);
    ss << game->score; // sauvegarde le score
    ss >> line;
    fputs(line.c_str(), fp);
    fputs("\n", fp);
    ss.clear();
    ss << game->snake.head; // l'emplacement de tete
    ss >> line;
    fputs(line.c_str(), fp);
    fputs("\n", fp);
    ss.clear();

    int count = 0;
    Body *ptr = game->snake.neck;
    while (ptr != NULL) // Compte il y a de body
    {
        count++;
        ptr = ptr->previous;
    }
    ss << count;
    ss >> line;
    fputs(line.c_str(), fp);
    fputs("\n", fp);
    ss.clear();
    ptr = game->snake.neck;
    for (int i = 0; i < count; i++) // Pour chaque body
    {
        ss << ptr->pos;
        ss >> line;
        fputs(line.c_str(), fp);
        fputs("\n", fp);
        ss.clear();
        switch (ptr->type)
        {
        case NBODY:
            fputs("N", fp);
            fputs("\n", fp);
            break;
        case RBODY:
            fputs("R", fp);
            fputs("\n", fp);
            break;
        case GBODY:
            fputs("G", fp);
            fputs("\n", fp);
            break;
        case BBODY:
            fputs("B", fp);
            fputs("\n", fp);
            break;
        default:
            break;
        }
        ptr = ptr->previous;
    }
    fclose(fp);
}

void feed(Game *game, Block type, int pos)  // Fait grandir le snake, vide la case et fait apparaitre une nourriture du meme type
{
    play(game->mixer, Eat, 500);    // Joue le son de manger pendant 500ms
    Body *a = new Body;             // Initie le body du type de la nourriture
    cout << "A " << a << endl; 
    a->type = (BodyType)type;
    a->pos = game->snake.head;      // Definis la position du body au niveau de la tete.
    if (game->snake.queue->type == NBODY)   // Si le corps est vide, on définis la tete et le cou comme étant le nouveau body
    {
        game->snake.queue = a;  
        game->snake.neck = a;
    }
    else    // Sinon, on définit le cou comme étant le body précédent du nouveau body 
    {
        a->previous = game->snake.neck; 
        game->snake.neck->next = a;
        game->snake.neck = a;
    }
    game->snake.head = pos; // On avance la tete à la position de la nourriture
    game->world->grid[pos] = Empty;
    game->score++;
    spawn(game, type);                                      // fait apparaitre une nourriture du meme type
}

void move_snake(Window *window, Game *game, int *delay) // Fait avancer le serpent en fonction de sa direction 
{
    int pos = game->snake.head + game->directions[game->snake.d];
    if ((pos % game->world->width == 0 && game->snake.d == DROITE) || (pos % game->world->width == game->world->width - 1 && game->snake.d == GAUCHE) || pos > game->world->width * game->world->height || pos < 0)
    { // Si la position est en dehors de la map, la partie est perdue.
        game->statut = GameOver;
        play(game->mixer, Death, 800);
        // GAME OVER
    }
    else
    {
        Body *temp = game->snake.neck;
        Body *temp2 = game->snake.queue;
        switch (game->world->grid[pos]) // regarde le type de la case sur laquelle va le snake
        {
        case Star:
            play(game->mixer, StarS, 700);
            *delay = 100;
            spawn(game, game->world->grid[pos]); // Fait spawn une nouvelle étoile
            game->world->grid[pos] = Empty;
            while (temp->previous != nullptr && temp->previous->previous != nullptr)    // Si le body actuel a encore 2 body précedents 
            {
                if (temp->type == temp->previous->type) 
                {
                    if (temp->type == temp->previous->previous->type)
                    {
                        game->score += 3;   // Ajoute 3 points de score lorsque l'étoile détruit 1 trio de body

                        if (temp->previous->previous->previous == nullptr)
                        {
                            if (temp->next == nullptr)   // Si le trio n'a pas d'element precedent et suivant, on définis le corps comme étant vide
                            {
                                Body *vide = new Body;
                                vide->type = NBODY;
                                game->snake.queue = vide;
                                game->snake.neck = vide;
                            }
                            else   // Si le trio n'a pas d'élement précédent et a un élement suivant, on définis la queue comme étant l'élément suivant
                            {
                                game->snake.queue = temp->next;
                                game->snake.queue->previous = nullptr;
                            }
                        }
                        else
                        {
                            if (temp->next == nullptr)  // Si le trio a un element précédent et n'a pas d'element suivant, on définis l'élement précédent comme étant le cou.
                            {
                                game->snake.neck = temp->previous->previous->previous;
                                game->snake.neck->next = nullptr;
                            }
                            else    // Si le trio a un element précedent et suivant, on raccorde les deux elements
                            {
                                temp->next->previous = temp->previous->previous->previous;
                                temp->previous->previous->previous->next = temp->next;
                            }
                        }

                        delete temp->previous->previous;     // Supprime le trio
                        delete temp->previous;
                        delete temp;
                        return;
                    }
                    else
                    {
                        temp = temp->previous->previous; // recule de 2 body
                    }
                }
                else
                {  
                    temp = temp->previous; // recule de 1 body
                }
            }
            return;
        case Empty: // Si la case est vide, on avance le snake et, si la tete heurte un élement du corps, on perds la partie.

            while (temp2->next != nullptr)
            {
                if(temp2->pos == pos){
                    game->statut = GameOver;
                    return;
                }
                temp2->pos = temp2->next->pos;
                temp2 = temp2->next;
            }
            temp2->pos = game->snake.head;
            game->snake.head = pos;
            return;
        default:
            cout << "defaut" << endl;
            feed(game, game->world->grid[pos], pos);    // si le block n'est pas empty ou star, fait grandir le snake et y ajoutant un body du type du block
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
    int case_sizeX = window->width / game->world->width; // Définis la taille des cases en fonction du nombre de cases
    int case_sizeY = window->height / game->world->height;
    set_color(&window->background, 255, 255, 255, 255);

    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        // rend le fond d'écran
        draw_texture(window, BackGround[0], (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY); // On dessine le background
        switch (game->world->grid[i]) // rend chaque case en fonction du type de block                                                                                                     // On dessine les pastilles
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

    switch (game->snake.manger) // dessine la tete en fonction du statut du snake (mange ou non) et de sa direction
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
        while (temp != nullptr && temp->type != NBODY)  // Dessine le corps du snake
        {
            draw_texture(window, BodyTexture[temp->type], (temp->pos % game->world->width * case_sizeX), (temp->pos / game->world->width * case_sizeY), case_sizeX, case_sizeY);
            temp = temp->previous;
        }
    }

    set_color(&window->foreground, 0, 0, 0, 255); // Dessine le score
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
                game->statut = Save;
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
bool keyboard_eventBreak(Game *game, Window *window, string pathMap)
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
                game->statut = Save;
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
                change_statut(&(game->statut));
                return false;
            default:
                return false;
                break;
            }
        }
    }
    return false;
}

bool checkBody(Game *game, int pos) // vérifie qu'un body du snake n'est pas à la position en paramètre
{
    Body *temp = game->snake.neck;
    while (temp != nullptr)
    {
        if (temp->pos == pos)
        {
            return true;
        }
        temp = temp->previous;
    }
    return false;
}

void spawn(Game *game, Block type)  // fait spawn un block du type en paramètre à un endroit vide aléatoire.
{
    int rngpos;
    do
    {
        rngpos = rand() % (game->world->height * game->world->width);
    } while (game->world->grid[rngpos] != Empty || checkBody(game, rngpos));
    game->world->grid[rngpos] = type;
}