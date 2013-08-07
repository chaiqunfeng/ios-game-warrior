//
//  BasicLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/21/13.
//
//

#ifndef __Warrior__BasicLayer__
#define __Warrior__BasicLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class BasicLayer:public CCLayer
{
public:
    BasicLayer();
    ~BasicLayer();
    
    virtual bool init();
    CREATE_FUNC(BasicLayer);
    
    virtual void onEnter();
    
    CCSize getWinSize();
    
    void setBgImg(const char* bgImg);
    
    
};

#endif /* defined(__Warrior__BasicLayer__) */
