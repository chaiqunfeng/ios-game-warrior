//
//  MusicManager.h
//  Warrior
//
//  Created by Varek Chai on 6/8/13.
//
//

#ifndef __Warrior__MusicManager__
#define __Warrior__MusicManager__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class GamingLayer;
class MusicManager
{
public:
    MusicManager();
    ~MusicManager();
    
    static  MusicManager* sharedMusicManager();
    void loadingMusic();
    void welcomeMusic();
    void randomMusic();
    void nextMusic();
    
    void shoot();
    void bomb();
    
    void setBackgroundVolumn(float volume);
    void setEffectVolumn(float volume);
    float getBackgroundVolumn();
    float getEffectVolumn();
    
    bool isInGaming();
    CCString *currentMusic();
    
    void setGamingLayer(GamingLayer *layer);
    
    /**
     @brief  The function is called when the application enters the background
     @param  the pointer of the application instance
     */
    virtual void applicationDidEnterBackground();
    
    /**
     @brief  The function is called when the application enters the foreground
     @param  the pointer of the application instance
     */
    virtual void applicationWillEnterForeground();
    
private:
    void init();
    CCArray *m_musicList;
    unsigned int m_musicIndex;
    bool m_bInGaming;
    
    // here GamingLayer used for pause game when app go to background
    GamingLayer *m_gamingLayer;
};

#endif /* defined(__Warrior__MusicManager__) */
