#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "enum.hpp"
using namespace std;

struct Mixer
{
    const string pathes[4]{"eat.wav", "star.wav", "death.wav", "music.wav"};
    const int volumes[4]{100, 100, 100, 50};
    const ESample Effects[3]{Eat, StarS, Death};
    bool effects{true};
    const ESample Songs[1]{Music1};
    bool songs{true};
    Mix_Chunk **samples;
};

void init_audio(Mixer *mixer);

void close_audio(Mixer *mixer);

void free_sample(Mix_Chunk *sample);

void set_volume(Mixer *mixer, ESample sample, int volume);

void mute_audio_type(Mixer *mixer, int type);

void play(Mixer *mixer, ESample sample);

void play(Mixer *mixer, ESample sample, int duree);