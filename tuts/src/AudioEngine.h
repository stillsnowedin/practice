#ifndef __tuts__AudioEngine__
#define __tuts__AudioEngine__

#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include <map>

class SoundEffect {
public:
    friend class AudioEngine;
    void play(int loops = 0);
private:
    Mix_Chunk* m_chunk = nullptr;
};

class Music {
public:
    friend class AudioEngine;
    void play(int loops = -1);
    static void pause();
    static void stop();
    static void resume();
private:
    Mix_Music* m_music = nullptr;
};

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    void init();
    void destroy();
    SoundEffect loadSoundEffect(const std::string& filePath);
    Music loadMusic(const std::string& filePath);
//    void playSoundEffect(const std::string& file);
//    void playMusic(const std::string& file);
    
private:
    std::map<std::string, Mix_Chunk*> m_effectMap;
    std::map<std::string, Mix_Music*> m_musicMap;
    bool m_initialized = false;
};

#endif /* defined(__tuts__AudioEngine__) */
