#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

#ifndef WINDOW_HPP
#define WINDOW_HPP

struct Mixer;

struct Window
{
    Mixer* mixer;
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    int width;
    int height;
    SDL_Color background;
    SDL_Color foreground;
    TTF_Font *sdl_font;
};

void set_color(SDL_Color *dst, int r, int g, int b, int a);
void set_color(SDL_Color *dst, const SDL_Color *src);

void init_window(Window *window, int width, int height, string title);
void close_window(Window *window);
void clear_window(Window *window);
void draw_fill_rectangle(Window *window, int x, int y, int w, int h);
void refresh_window(Window *window);
SDL_Texture *load_image(Window *window, string image);
void draw_texture(Window *window, SDL_Texture *texture, int x, int y, int w, int h);
void draw_text(Window *window, string text, int x, int y);

#endif