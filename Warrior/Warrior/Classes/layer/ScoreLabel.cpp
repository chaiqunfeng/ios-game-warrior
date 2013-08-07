//
//  ScoreLabel.cpp
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#include "ScoreLabel.h"
#include "UICommon.h"

ScoreLabel::ScoreLabel()
{
    m_iScore = 0;
}

ScoreLabel::~ScoreLabel()
{
}

bool ScoreLabel::init()
{
    if (CCLabelTTF::initWithString("0", "", 20.0f))
    {
        return true;
    }
    return false;
}

void ScoreLabel::updateScore(int addValue)
{
    m_iScore += addValue;
    
    char szScore[128] = {0};
    sprintf(szScore, "%d", m_iScore);
    this->setString(szScore);
    this->setFontSize(40.0f);
    this->scheduleOnce(schedule_selector(ScoreLabel::updateFontSize), 0.5f);
}

void ScoreLabel::updateFontSize(float t)
{
    this->setFontSize(20.0f);
}

int ScoreLabel::getScore()
{
    return m_iScore;
}
