//
//  OptionLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#ifndef __Warrior__OptionLayer__
#define __Warrior__OptionLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class OptionLayer:public CCLayerColor
{
public:
    
    OptionLayer();
    ~OptionLayer();
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(OptionLayer);
    
    virtual void onEnter();
    
    void returnCallback(CCObject* pSender);
    void nextSongCallback(CCObject* pSender);
    void backgroundSliderCallback(CCObject* pSender);
    void effectSliderCallback(CCObject* pSender);
    void backgroundMuteCallback(CCObject* pSender);
    void effectMuteCallback(CCObject* pSender);
};

#endif /* defined(__Warrior__OptionLayer__) */
