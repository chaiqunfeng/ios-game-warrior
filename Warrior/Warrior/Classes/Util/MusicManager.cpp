//
//  MusicManager.cpp
//  Warrior
//
//  Created by Varek Chai on 6/8/13.
//
//

#include "MusicManager.h"
#include "SimpleAudioEngine.h"
//#include "CDAudioManager.h"
#include "GamingLayer.h"
using namespace CocosDenshion;

#define BG_MUSIC_WELCOME        "frontend_01.mp3"
#define BG_MUSIC_LOADING        "loading_01.mp3"

#define BG_MUSIC_01             "Riverboat Gamblers - Blue Ghosts"
#define BG_MUSIC_02             "Heaven's Basement - I Am Electric"
#define BG_MUSIC_03             "Joy Formidable - Little Blimp"
#define BG_MUSIC_04             "Skrillex And The Doors - Breakin A Sweat(Zedd Remix)"
#define BG_MUSIC_05             "Asherel - Shake The Dust"
#define BG_MUSIC_06             "The Who - Won't Get Fooled Again(Cato Remix)"
#define BG_MUSIC_07             "C & D - The Chase"
#define BG_MUSIC_08             "Dispatch - Circles Around The Sun"
#define BG_MUSIC_09             "Green Day - Stop When The Red Lights Flash"
#define BG_MUSIC_10             "Chemical Brothers - Galvanize"
#define BG_MUSIC_11             "Icona Pop - I Love It"
#define BG_MUSIC_12             "Band of Skulls - You're Not Pretty But You Got It Goin On 1"
#define BG_MUSIC_13             "Dead Sara - Weatherman"
#define BG_MUSIC_14             "Beware of Darkness - Howl"
#define BG_MUSIC_15             "Crosses - Telepathy"

#define EFFECT_MUSIC_SHOOT_01           "02zd408.mp3"
#define EFFECT_MUSIC_SHOOT_02           "02zd410.mp3"
#define EFFECT_MUSIC_SHOOT_03           "02zd405.mp3"
#define EFFECT_MUSIC_SPACEGUN_01        "25339_1072_157.MP3"
#define EFFECT_MUSIC_BOMB_01            "02zd006.mp3"

static MusicManager *s_instance = NULL;

MusicManager::MusicManager()
{
    // init array
    m_musicList = CCArray::create();
    m_musicList->retain();
}

MusicManager::~MusicManager()
{
    m_musicList->release();
}

MusicManager *MusicManager::sharedMusicManager()
{
    if (!s_instance)
    {
        s_instance = new MusicManager();
        s_instance->init();
    }
    return s_instance;
}

void MusicManager::init()
{
    m_bInGaming = false;
    m_musicIndex = CC_INVALID_INDEX;
    m_gamingLayer = NULL;
    
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BG_MUSIC_WELCOME);
    SimpleAudioEngine::sharedEngine()->preloadEffect(EFFECT_MUSIC_SHOOT_01);
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.6f);
    
    // make music list
    m_musicList->addObject(CCString::create(BG_MUSIC_01));
    m_musicList->addObject(CCString::create(BG_MUSIC_02));
    m_musicList->addObject(CCString::create(BG_MUSIC_03));
    m_musicList->addObject(CCString::create(BG_MUSIC_04));
    m_musicList->addObject(CCString::create(BG_MUSIC_05));
    m_musicList->addObject(CCString::create(BG_MUSIC_06));
    m_musicList->addObject(CCString::create(BG_MUSIC_07));
    m_musicList->addObject(CCString::create(BG_MUSIC_08));
    m_musicList->addObject(CCString::create(BG_MUSIC_09));
    m_musicList->addObject(CCString::create(BG_MUSIC_10));
    m_musicList->addObject(CCString::create(BG_MUSIC_11));
    m_musicList->addObject(CCString::create(BG_MUSIC_12));
    m_musicList->addObject(CCString::create(BG_MUSIC_13));
    m_musicList->addObject(CCString::create(BG_MUSIC_14));
    m_musicList->addObject(CCString::create(BG_MUSIC_15));
}

void MusicManager::loadingMusic()
{
    m_bInGaming = false;
    m_musicIndex = CC_INVALID_INDEX;
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BG_MUSIC_LOADING, true);
}

void MusicManager::welcomeMusic()
{
    m_bInGaming = false;
    m_musicIndex = CC_INVALID_INDEX;
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BG_MUSIC_WELCOME, true);
}

void MusicManager::randomMusic()
{
    m_bInGaming = true;
    if (m_musicList && m_musicList->count()>0) {
        CCString *song = (CCString *)m_musicList->randomObject();
        m_musicIndex = m_musicList->indexOfObject(song);
        
        char szSong[128] = {0};
        sprintf(szSong, "%s.mp3", song->getCString());
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(szSong, true);
        //CDAudioManager::sharedManager()->setBackgroundMusicCompletionListener:self selector:MusicManager::nextMusic();
    }
}

void MusicManager::nextMusic()
{
    if (m_musicList && m_musicList->count()>0) {
        if (m_musicIndex != CC_INVALID_INDEX) {
            m_musicIndex++;
            if (m_musicIndex >= m_musicList->count()) {
                m_musicIndex = 0;
            }
            
            CCString *song = (CCString *)m_musicList->objectAtIndex(m_musicIndex);
            char szSong[128] = {0};
            sprintf(szSong, "%s.mp3", song->getCString());
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(szSong, true);
        }
        else {
            randomMusic();
        }
    }
}

void MusicManager::shoot()
{
    SimpleAudioEngine::sharedEngine()->playEffect(EFFECT_MUSIC_SHOOT_01);
}

void MusicManager::bomb()
{
    SimpleAudioEngine::sharedEngine()->playEffect(EFFECT_MUSIC_BOMB_01);
}

void MusicManager::setBackgroundVolumn(float volume)
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

void MusicManager::setEffectVolumn(float volume)
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

float MusicManager::getBackgroundVolumn()
{
    return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

float MusicManager::getEffectVolumn()
{
    return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}

bool MusicManager::isInGaming()
{
    return m_bInGaming;
}

CCString *MusicManager::currentMusic()
{
    if (m_musicList && m_musicList->count()>0 && m_musicIndex < m_musicList->count()) {
        CCString *song = (CCString *)m_musicList->objectAtIndex(m_musicIndex);
        return song;
    }
    
    return CCString::create("< Background Music >");
}

void MusicManager::setGamingLayer(GamingLayer *layer)
{
    m_gamingLayer = layer;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void MusicManager::applicationDidEnterBackground()
{
    if (m_gamingLayer) {
        CCLOG("m_gamingLayer->applicationDidEnterBackground()");
        m_gamingLayer->applicationDidEnterBackground();
    }
}

// this function will be called when the app is active again
void MusicManager::applicationWillEnterForeground()
{
    if (m_gamingLayer) {
        CCLOG("m_gamingLayer->applicationWillEnterForeground()");
        m_gamingLayer->applicationWillEnterForeground();
    }
}
