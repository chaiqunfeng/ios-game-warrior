//
//  TimerLabel.cpp
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#include "TimerLabel.h"
#include "UICommon.h"

TimerLabel::TimerLabel()
{
    m_iDuration = 0;
}

TimerLabel::~TimerLabel()
{
}

bool TimerLabel::init()
{
    if (CCLabelTTF::initWithString("00:00:00", "", 20.0f))
    {
        return true;
    }
    return false;
}

void TimerLabel::startTimer()
{
    m_iDuration = 0;
    this->schedule(schedule_selector(TimerLabel::heartBeat), 1.0f);
}

void TimerLabel::stopTimer()
{
    this->unschedule(schedule_selector(TimerLabel::heartBeat));
}

int TimerLabel::getDuration()
{
    return m_iDuration;
}

void TimerLabel::heartBeat(float t)
{
    char szTime[128] = {0};
    m_iDuration++;
    
    tm time = {0};
    time.tm_sec = m_iDuration%60;
    time.tm_min = (m_iDuration/60)%60;
    time.tm_hour = (m_iDuration/3600)%24;
    
    strftime(szTime, sizeof(szTime), "%T", &time);
    this->setString(szTime);

}
