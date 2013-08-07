//
//  BasicLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/21/13.
//
//

#include "BasicLayer.h"

BasicLayer::BasicLayer()
{}

BasicLayer::~BasicLayer()
{}

bool BasicLayer::init()
{
    if (CCLayer::init())
    {
        return true;
    }
    return false;
}

void BasicLayer::onEnter()
{
    CCLayer::onEnter();
}

CCSize BasicLayer::getWinSize()
{
    return CCDirector::sharedDirector()->getWinSize();
}

void BasicLayer::setBgImg(const char* bgImg)
{
    CCSprite* sp = CCSprite::create(bgImg);
    if (sp)
    {
        sp->setPosition(ccp(getWinSize().width/2, getWinSize().height/2));
        this->addChild(sp);
    }
    
}