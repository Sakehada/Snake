#include "window.hpp"
#include "window_audio.hpp"

void set_color(SDL_Color *dst, int r, int g, int b, int a)
{
    dst->r = r;
    dst->b = b;
    dst->g = g;
    dst->a = a;
}

void set_color(SDL_Color *dst, const SDL_Color *src)
{
    dst->a = src->a;
    dst->r = src->r;
    dst->b = src->b;
    dst->g = src->g;
}

void clear_window(Window *window)
{
    // Select the background color
    SDL_SetRenderDrawColor(window->sdl_renderer,
                           window->background.r,
                           window->background.g,
                           window->background.b,
                           window->background.a);
    // We fill the window
    SDL_RenderClear(window->sdl_renderer);
}

void draw_fill_rectangle(Window *window, int x, int y, int w, int h)
{
    SDL_SetRenderDrawColor(window->sdl_renderer,
                           window->foreground.r,
                           window->foreground.g,
                           window->foreground.b,
                           window->foreground.a);
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_RenderFillRect(window->sdl_renderer, &rectangle);
}

void refresh_window(Window *window)
{
    SDL_RenderPresent(window->sdl_renderer);
}

void init_window(Window *window, int width, int height, string title)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {

        cerr << "Could not initialize SDL2: error " << SDL_GetError() << endl;
        SDL_Quit();
    }
    window->width = width;
    window->height = height;
    int ret = SDL_CreateWindowAndRenderer(width, height, 0, &window->sdl_window, &window->sdl_renderer);
    if (ret < 0)
    {
        cerr << " Could not create SDL window: error " << SDL_GetError() << endl;
        SDL_Quit();
    }
    SDL_SetWindowTitle(window->sdl_window, title.c_str());
    // Initialise SDL_TTF for TTF font rendering
    if (TTF_Init() == -1)
    {
        cout << "Could not initialize SDL_TTF: error " << TTF_GetError() << endl;
        SDL_Quit();
    }
    // Sp ́ecifie la police
    window->sdl_font = TTF_OpenFont("assets/police/VeraMono.ttf", 20);
    if (window->sdl_font == NULL)
    {
        cout << "Could not load font: error " << TTF_GetError() << endl;
        SDL_Quit();
    }

    window->mixer = new Mixer;
    init_audio(window->mixer);
    play(window->mixer, Music2);

}
void close_window(Window *window)
{
    SDL_DestroyWindow(window->sdl_window);
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_Quit();
}

SDL_Texture *load_image(Window *window, string str)
{
    SDL_Surface *surface = IMG_Load(str.c_str());
    if (surface == nullptr)
    {
        cerr << "Erreur SDL_Image : " << IMG_GetError();
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        cerr << "Erreur lors de la creation d’une textture `a partir d’une surface" << endl;
        return nullptr;
    }
    return texture;
}
void draw_texture(Window *window, SDL_Texture *texture, int x, int y, int w, int h)
{
    SDL_Rect box;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    SDL_RenderCopy(window->sdl_renderer, texture, NULL, &box);
}

void draw_text(Window *window, string str, int x, int y)
{
    SDL_Surface *surface = TTF_RenderText_Shaded(window->sdl_font, str.c_str(), window->foreground, window->background);
    // If an error occured
    if (surface == NULL)
    {
        cout << "Could not init the SDL surface for TTF: " << TTF_GetError() << endl;
        exit(0);
    }
    // Retrieve width and height of the surface
    int h = surface->h;
    int w = surface->w;
    // Make a SDL Texture from the Surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    // Free the SDL surface
    SDL_FreeSurface(surface);
    // Dispaly an error if we cannot make the texture
    if (texture == nullptr)
    {
        cout << "Could not init the SDL Texture for TTF: " << SDL_GetError() << endl;
        SDL_Quit();
    }
    draw_texture(window, texture, x, y, w, h);
    SDL_DestroyTexture(texture);
}