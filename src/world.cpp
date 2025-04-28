#include "world.hpp"

void init_world(World *world, int w, int h)
{ // Initie la grille du monde ainsi que sa hauteur et sa largeur
    world->height = h;
    world->width = w;
    world->grid = new Block[w * h];
    for (int i = 0; i < h * w; i++)
    {
        world->grid[i] = Empty;
    }
}

void free_world(World *world)
{ // Supprime la grille du monde
    delete[] world->grid;
}

void write(World *world, int x, int y, Block b)
{ // modifie le block à l'emplacement (x;y)
    int i = getId(x, y, world->width);
    if (i < 0 or i > world->height * world->width)
    {
        cout << "Erreur de coordonnee" << endl;
        return;
    }
    else
    {
        world->grid[i] = b;
    }
}

void display(World *world)
{ // Affiche dans la sortie le monde actuellement chargé
    for (int i = 0; i < world->height * world->width; i++)
    {
        if (i != 0 && i % (world->width) == 0)
        {
            cout << endl;
        }
        switch (world->grid[i])
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
}

int getId(int x, int y, int w)
{ // Retourne l'id dans la grid 1D à partir de sa position x, y et de la largeur de la grid
    return y * w + x;
}

void init_world_from_file(World *world, string filename)
{ // Charge le monde à partir d'un fichier
    ifstream fic(filename.c_str());
    if (fic)
    {
        fic >> world->width;
        fic >> world->height;

        init_world(world, world->width, world->height);
        string line;
        for (int i = 0; i < world->height; i++)
        {
            fic >> line;
            Block b;
            for (int k = 0; k < world->width; k++)
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
                write(world, k, i, b);
            }
        }
    }
    else
    {
        cout << "impossible de lire le fichier : " << filename << endl;
    }
}

void FoodPlacement(World *world)
{
    bool r = 0, g = 0, b = 0, s = 0;
    for (int i = 0; i < world->width * world->height; i++)
    {
        switch (world->grid[i])
        {
        case R:
            r = 1;
            break;
        case G:
            g = 1;
            break;
        case B:
            b = 1;
            break;
        case Star:
            s = 1;
            break;
        default:
            break;
        }
    }
    if (r == 0)
    {
        int i = rand() % (world->height * world->width);
        while (world->grid[i] != Empty)
        {
            i = (i + i) % (world->height * world->width);
        }
        world->grid[i] = R;
    }
    if (b == 0)
    {
        int i = rand() % (world->height * world->width);
        while (world->grid[i] != Empty)
        {
            i = (i + i) % (world->height * world->width);
        }
        world->grid[i] = B;
    }
    if (g == 0)
    {
        int i = rand() % (world->height * world->width);
        while (world->grid[i] != Empty)
        {
            i = (i + i) % (world->height * world->width);
        }
        world->grid[i] = G;
    }
    if (s == 0)
    {
        int i = rand() % (world->height * world->width);
        while (world->grid[i] != Empty)
        {
            i = (i + i) % (world->height * world->width);
        }
        world->grid[i] = Star;
    }
}