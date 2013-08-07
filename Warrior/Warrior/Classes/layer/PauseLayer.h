//
//  PauseLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#ifndef __Warrior__PauseLayer__
#define __Warrior__PauseLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class PauseLayer:public CCLayerColor
{
public:
    
    PauseLayer();
    ~PauseLayer();
    
    virtual bool init();
    static CCScene* scene();
    void resumeCallback(CCObject* pSender);
    void replayCallback(CCObject* pSender);
    void optionCallback(CCObject* pSender);
    void menuCallback(CCObject* pSender);
    
    CREATE_FUNC(PauseLayer);
    
};

#endif /* defined(__Warrior__PauseLayer__) */
