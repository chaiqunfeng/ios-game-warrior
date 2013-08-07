//
//  ScoreLabel.h
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#ifndef __Warrior__ScoreLabel__
#define __Warrior__ScoreLabel__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class ScoreLabel:public CCLabelTTF
{
public:
    
    ScoreLabel();
    ~ScoreLabel();
    
    virtual bool init();
    CREATE_FUNC(ScoreLabel);
    
    void updateScore(int addValue = 1);
    int getScore();
    
private:
    void updateFontSize(float t);
    
    int m_iScore;
};

#endif /* defined(__Warrior__ScoreLabel__) */
