//
//  PauseLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#include "PauseLayer.h"
#include "GamingLayer.h"
#include "UICommon.h"
#include "SimpleAudioEngine.h"
#include "OptionLayer.h"
#include "MusicManager.h"

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
{
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 50)))
    {
        // resume icon
        CCLabelTTF* labelResume = CCLabelTTF::create("继续", "", 32.0f);
        CCLabelTTF* labelResume2 = CCLabelTTF::create("继续", "", 36.0f);
        CCMenuItemSprite* spResume = CCMenuItemSprite::create(labelResume, labelResume2, this, menu_selector(PauseLayer::resumeCallback));
        
        // replay icon
        CCLabelTTF* labelReplay = CCLabelTTF::create("重新开始", "", 32.0f);
        CCLabelTTF* labelReplay2 = CCLabelTTF::create("重新开始", "", 36.0f);
        CCMenuItemSprite* spReplay = CCMenuItemSprite::create(labelReplay, labelReplay2, this, menu_selector(PauseLayer::replayCallback));
        
        // option icon
        CCLabelTTF* labelOption = CCLabelTTF::create("设置", "", 32.0f);
        CCLabelTTF* labelOption2 = CCLabelTTF::create("设置", "", 36.0f);
        CCMenuItemSprite* spOption = CCMenuItemSprite::create(labelOption, labelOption2, this, menu_selector(PauseLayer::optionCallback));
        
        // menu icon
        CCLabelTTF* labelMenu = CCLabelTTF::create("返回菜单", "", 32.0f);
        CCLabelTTF* labelMenu2 = CCLabelTTF::create("返回菜单", "", 36.0f);
        CCMenuItemSprite* spMenu = CCMenuItemSprite::create(labelMenu, labelMenu2, this, menu_selector(PauseLayer::menuCallback));
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCMenu* menu = CCMenu::create(spResume, spReplay, spOption, spMenu, NULL);
        menu->alignItemsVerticallyWithPadding(10.0f);
        menu->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(menu);
        
        return true;
    }
    return false;
}

CCScene* PauseLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        PauseLayer* layer = PauseLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void PauseLayer::resumeCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::resumeCallback");
    // unvisiable self
    this->setVisible(false);
    
    // callback
    GamingLayer* pLayer = (GamingLayer*)getParent();
    pLayer->resumeCallback(pSender);
}

void PauseLayer::replayCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::replayCallback");
    this->setVisible(false);
    
    // callback
    GamingLayer* pLayer = (GamingLayer*)getParent();
    pLayer->replayCallback(pSender);
}

void PauseLayer::optionCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::optionCallback");
    CCDirector::sharedDirector()->pushScene(OptionLayer::scene());
}

void PauseLayer::menuCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::menuCallback");
    this->setVisible(false);
    
    // resume the game
    CCDirector::sharedDirector()->resume();
    // return to menu
    CCDirector::sharedDirector()->popScene();
    
    MusicManager::sharedMusicManager()->welcomeMusic();

}