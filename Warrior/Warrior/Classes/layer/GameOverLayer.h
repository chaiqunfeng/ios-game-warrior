//
//  GameOverLayer.h
//  Warrior
//
//  Created by Varek Chai on 6/5/13.
//
//

#ifndef __Warrior__GameOverLayer__
#define __Warrior__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class GameOverLayer:public CCLayerColor
{
public:
    
    GameOverLayer();
    ~GameOverLayer();
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameOverLayer);
    
    void replayCallback(CCObject* pSender);
    void scoreBoardCallback(CCObject* pSender);
    void menuCallback(CCObject* pSender);
    
    void setGameResult(int score, int duration, time_t time);
};

#endif /* defined(__Warrior__GameOverLayer__) */
