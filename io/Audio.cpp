#include "Audio.hpp"
#include "Debug.hpp"
#include "resource/Sound.hpp"
#include "resource/Music.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#undef PlaySound

namespace io
{

Audio::Audio(int samples)
{
    if (!al_install_audio()) {
        Throw("Failed to install audio");
    }

    if (!al_init_acodec_addon()) {
        Throw("Failed to initialize acodec addon");
    }

    if (!al_reserve_samples(samples)) {
        Throw("Failed to setup voice and mixer");
    }
}

void Audio::PlaySound(Sound sound, float volume, float pan, float speed)
{
    al_play_sample(sound.get(), volume, pan, speed, ALLEGRO_PLAYMODE_ONCE, 0);
}

void Audio::PlayMusic(Music music, bool loop, float volume)
{
    al_rewind_audio_stream(music.get());
    al_set_audio_stream_playmode(music.get(), loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE);
    al_set_audio_stream_gain(music.get(), volume);
    al_set_audio_stream_playing(music.get(), true);
}

void Audio::StopMusic(Music music)
{
    al_drain_audio_stream(music.get());
}

void Audio::SetVolume(float volume)
{
    al_set_mixer_gain(al_get_default_mixer(), volume);
}

}