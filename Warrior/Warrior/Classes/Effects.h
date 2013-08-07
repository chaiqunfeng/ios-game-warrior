//
//  Effects.h
//  Warrior
//
//  Created by Varek Chai on 5/27/13.
//
//

#ifndef __Warrior__Effects__
#define __Warrior__Effects__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;


class Effects
{
public:
    static  Effects* sharedEffects();
    
    void preload();
    
    void boom(CCNode* target, CCPoint point);
    
    void boomCallback(CCNode* pNode);
};

#endif /* defined(__Warrior__Effects__) */
