#include "AudioEngine.h"
#include "Errors.h"

void SoundEffect::play(int loops) {
    if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
        if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
            fatalError("[SoundEffect] Mix_PlayChannel error: " + std::string(Mix_GetError()));
        }
    }
}

void Music::play(int loops) {
    if (Mix_PlayMusic(m_music, loops) == -1) {
        fatalError("[Music] Mix_PlayMusic error: " + std::string(Mix_GetError()));
    }
}

void Music::pause() {
    Mix_PauseMusic();
}

void Music::stop() {
    Mix_HaltMusic();
}

void Music::resume() {
    Mix_ResumeMusic();
}

AudioEngine::AudioEngine() {
}

AudioEngine::~AudioEngine() {
    
}

void AudioEngine::init() {
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
        fatalError("[AudioEngine] Mix_Init error: " + std::string(Mix_GetError()));
    }
    
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        fatalError("[AudioEngine] Mix_OpenAudio error: " + std::string(Mix_GetError()));
    }
    
    m_initialized = true;
}

void AudioEngine::destroy() {
    if (m_initialized) {
        m_initialized = false;
        Mix_Quit();
    }
}

SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
    SoundEffect effect;
    auto it = m_effectMap.find(filePath);
    
    if (it == m_effectMap.end()) {
        Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
        if (chunk == nullptr)
            fatalError("[AudioEngine] Mix_LoadWAV error: " + std::string(Mix_GetError()));
        
        effect.m_chunk = chunk;
        m_effectMap[filePath] = chunk;
    } else {
        effect.m_chunk = it->second;
    }
    
    return effect;
}

Music AudioEngine::loadMusic(const std::string& filePath) {
    Music music;
    auto it = m_musicMap.find(filePath);
    
    if (it == m_musicMap.end()) {
        Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
        if (mixMusic == nullptr)
            fatalError("[AudioEngine] Mix_LoadMUS error: " + std::string(Mix_GetError()));
        
        music.m_music = mixMusic;
        m_musicMap[filePath] = mixMusic;
    } else {
        music.m_music = it->second;
    }
    
    return music;
}