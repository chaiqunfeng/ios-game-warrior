//
//  Effects.cpp
//  Warrior
//
//  Created by Varek Chai on 5/27/13.
//
//

#include "Effects.h"
#include "UICommon.h"

static Effects* s_instance = NULL;

Effects* Effects::sharedEffects()
{
    if (!s_instance)
    {
        s_instance = new Effects();
        s_instance->preload();
    }
    return s_instance;
}

void Effects::preload()
{
    // sprite frame
    CCSpriteFrame *frame1 = CCSpriteFrame::create("explosion50_new.png", CCRectMake(0, 0, 12, 14));
    CCSpriteFrame *frame2 = CCSpriteFrame::create("explosion75_new.png", CCRectMake(0, 0, 18, 21));
    CCSpriteFrame *frame3 = CCSpriteFrame::create("explosion100_new.png", CCRectMake(0, 0, 24, 27));
    CCSpriteFrame *frame4 = CCSpriteFrame::create("explosion125_new.png", CCRectMake(0, 0, 30, 33));
    CCSpriteFrame *frame5 = CCSpriteFrame::create("explosion150_new.png", CCRectMake(0, 0, 36, 40));
    
    // animation
    CCAnimation* animation = CCAnimation::create();
    animation->setDelayPerUnit(0.2f);
    animation->addSpriteFrame(frame1);
    animation->addSpriteFrame(frame2);
    animation->addSpriteFrame(frame3);
    animation->addSpriteFrame(frame4);
    animation->addSpriteFrame(frame5);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, AN_EXPLOSION);
    
}

void Effects::boom(CCNode* target, CCPoint point)
{
    CCLOG("Effects::boom");
    // add a sprite
    CCSprite* sp = CCSprite::create();
    target->addChild(sp);
    sp->setPosition(point);
    
    // callback
    CCCallFuncN* callback = CCCallFuncN::create(sp, callfuncN_selector(Effects::boomCallback));
    
    // get animation
    CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(AN_EXPLOSION);
    CCAnimate* animate = CCAnimate::create(animation);
    
    // run animation
    sp->runAction(CCSequence::create(animate,callback,NULL));
}

void Effects::boomCallback(CCNode* pNode)
{
    CCLOG("Effects::boomCallback");
    // release node
    pNode->removeFromParentAndCleanup(true);
}