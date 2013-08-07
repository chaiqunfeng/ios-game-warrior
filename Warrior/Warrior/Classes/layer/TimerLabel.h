//
//  TimerLabel.h
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#ifndef __Warrior__TimerLabel__
#define __Warrior__TimerLabel__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class TimerLabel:public CCLabelTTF
{
public:
    
    TimerLabel();
    ~TimerLabel();
    
    virtual bool init();
    CREATE_FUNC(TimerLabel);
    void startTimer();
    void stopTimer();
    int getDuration();
    
private:
    void heartBeat(float t);
    int m_iDuration;
    
};

#endif /* defined(__Warrior__TimerLabel__) */
