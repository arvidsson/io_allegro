#pragma once

namespace io
{

class Sound;
class Music;

class Audio
{
public:
    /*
        Initializes audio and reserves a number of samples to be used.
    */
    Audio(int samples = 32);

    /*
        Playback
    */
    void PlaySound(Sound sound, float volume = 1.0f, float pan = 0.0f, float speed = 1.0f);
    void PlayMusic(Music music, bool loop = false, float volume = 1.0f);
    void StopMusic(Music music);
    void SetVolume(float volume);
};

}