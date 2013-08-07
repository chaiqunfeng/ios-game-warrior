//
//  PlayerPlaneLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#include "PlayerPlaneLayer.h"
//#include "GamingLayer.h"
#include "PlaneManager.h"
#include "UICommon.h"
#include "BulletLayer.h"

PlayerPlaneLayer::PlayerPlaneLayer()
{
}

PlayerPlaneLayer::~PlayerPlaneLayer()
{
}

bool PlayerPlaneLayer::init(BulletLayer* bullet)
{
    if (PlaneLayer::init(e_pt_player, bullet))
    {
        // animation
        CCAnimation* animation = CCAnimation::create();
        animation->setDelayPerUnit(0.5f);
        animation->addSpriteFrame(CCSpriteFrame::create("plane.png", CCRectMake(0, 0, 40, 43)));
        animation->addSpriteFrame(CCSpriteFrame::create("plane2.png", CCRectMake(0, 0, 40, 43)));
        CCAnimate* animate = CCAnimate::create(animation);
        m_spPlane->runAction(CCRepeatForever::create(animate));
        
        // touch
        this->setTouchEnabled(true);
        
        // fire!
        fire();
        
//        // blood
//        CCSprite * spBloodBG = CCSprite::create("blood_bg.png");
//        if (spBloodBG)
//        {
//            spBloodBG->setAnchorPoint(ccp(0,1));
//            spBloodBG->setPosition(ccp(getWinSize().width - 20 - 238, getWinSize().height - 30));
//            this->addChild(spBloodBG);
//        }
//        
//        m_spBlood = CCSprite::create("blood_red.png");
//        if (m_spBlood)
//        {
//            m_spBlood->setAnchorPoint(ccp(0,1));
//            m_spBlood->setPosition(ccp(getWinSize().width - 20 - 238, getWinSize().height - 30));
//            this->addChild(m_spBlood);
//        }
        
        return true;
    }
    
    return false;
}

PlayerPlaneLayer* PlayerPlaneLayer::create(BulletLayer* bullet)
{
    PlayerPlaneLayer *pRet = new PlayerPlaneLayer();
    if (pRet && pRet->init(bullet))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayerPlaneLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
//    GamingLayer* parent = (GamingLayer*)getParent()->getParent();
//    CCMenu* pManu = (CCMenu*)parent->getChildByTag(PAUSE_TAG_MENU);
//    
//    CCPoint point = pTouch->getLocation();
//    float fX = pManu->getPositionX();
//    float fY = pManu->getPositionY();
//    float fWidth = 100;
//    float fHeight = 50;
//    CCLOG("x=%f,y=%f,w=%f,h=%f",fX,fY,fWidth,fHeight);
//    CCRect rc = CCRectMake(fX-fWidth/2, fY-fHeight/2, fWidth, fHeight);
//    if (rc.containsPoint(point))
//    {
//        return false;
//    }
    
    return true;
}

void PlayerPlaneLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_spPlane)
    {
        CCPoint pt = m_spPlane->getPosition();
        pt.x += pTouch->getLocation().x - pTouch->getPreviousLocation().x;
        pt.y += pTouch->getLocation().y - pTouch->getPreviousLocation().y;
        m_spPlane->setPosition(pt);
    }
}

void PlayerPlaneLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_spPlane)
    {
        CCPoint pt = m_spPlane->getPosition();
        pt.x += pTouch->getLocation().x - pTouch->getPreviousLocation().x;
        pt.y += pTouch->getLocation().y - pTouch->getPreviousLocation().y;
        m_spPlane->setPosition(pt);
    }
}

void PlayerPlaneLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,PLANE_ZORDER_LAYER,true);//(this,INT_MIN+1,true);
}



