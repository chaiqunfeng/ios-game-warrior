//
//  GamingLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#ifndef __Warrior__GamingLayer__
#define __Warrior__GamingLayer__

#include <iostream>
#include "BasicLayer.h"

class GamingLayer:public BasicLayer
{
public:
    
    GamingLayer();
    ~GamingLayer();
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GamingLayer);
    
    //virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    //virtual void onExitTransitionDidStart();
    
    void bgScroll(float t);
    void pauseCallback(CCObject* pSender);
    void resumeCallback(CCObject* pSender);
    void replayCallback(CCObject* pSender);
    void gameoverCallback();
    
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
    void performGameOver(CCObject* pSender);
};

#endif /* defined(__Warrior__GamingLayer__) */
