//
//  Medicine.h
//  Warrior
//
//  Created by Varek Chai on 6/17/13.
//
//

#ifndef __Warrior__Medicine__
#define __Warrior__Medicine__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class Medicine:public CCSprite
{
public:
    
    Medicine();
    ~Medicine();
    
    virtual bool init(bool small);
    static Medicine *create(bool small);
    
    float bloodCapacity();
    void setReceived();
    bool isReceived();
    
private:
    void blinkCallback(float t);
    void removeCallback(float t);
    
    bool m_bReceived;
    float m_fBloodCapacity;
};

#endif /* defined(__Warrior__Medicine__) */
