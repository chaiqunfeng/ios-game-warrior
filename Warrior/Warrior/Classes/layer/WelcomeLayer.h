//
//  WelcomeLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/21/13.
//
//

#ifndef __Warrior__WelcomeLayer__
#define __Warrior__WelcomeLayer__

#include <iostream>
#include "BasicLayer.h"

class WelcomeLayer:public BasicLayer
{
public:
    
    WelcomeLayer();
    ~WelcomeLayer();
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(WelcomeLayer);
    
    virtual void onEnter();
    
    void newGameCallback(CCObject* pSender);
    void recordCallback(CCObject* pSender);
    void optionCallback(CCObject* pSender);
    void aboutCallback(CCObject* pSender);
    void exitCallback(CCObject* pSender);
    
};

#endif /* defined(__Warrior__WelcomeLayer__) */
