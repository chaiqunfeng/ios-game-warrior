//
//  AboutLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/21/13.
//
//

#include "AboutLayer.h"

AboutLayer::AboutLayer()
{
}

AboutLayer::~AboutLayer()
{
}

bool AboutLayer::init()
{
    if (BasicLayer::init())
    {
        // set background image
        setBgImg("option_bg.png");
        
        // top icon
        CCLabelTTF* labelTop = CCLabelTTF::create("关于", "", 56.0f);
        labelTop->setPosition(ccp(getWinSize().width/2, getWinSize().height - 100));
        this->addChild(labelTop);
        
        // about infomation
        CCLabelTTF* labelAuthor = CCLabelTTF::create("This game is made by ChaiQunfeng.", "", 20.0f);
        CCLabelTTF* labelInfo = CCLabelTTF::create("Have a good time!", "", 20.0f);
        CCMenuItemSprite* spAuthor = CCMenuItemSprite::create(labelAuthor, labelAuthor);
        CCMenuItemSprite* spInfo = CCMenuItemSprite::create(labelInfo, labelInfo);
        CCMenu* menu = CCMenu::create(spAuthor,spInfo,NULL);
        menu->setPosition(ccp(getWinSize().width/2, getWinSize().height/2));
        menu->alignItemsVerticallyWithPadding(5.0f);
        this->addChild(menu);
        
        // back icon
        CCLabelTTF* labelResume = CCLabelTTF::create("返回", "", 32.0f);
        CCLabelTTF* labelResume2 = CCLabelTTF::create("返回", "", 36.0f);
        CCMenuItemSprite* spResume = CCMenuItemSprite::create(labelResume, labelResume2, this, menu_selector(AboutLayer::returnCallback));
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCMenu* menuBack = CCMenu::create(spResume,NULL);
        menuBack->setPosition(ccp(size.width/2, 100));
        this->addChild(menuBack);
        
        return true;
    }
    return false;
}

CCScene* AboutLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        AboutLayer* layer = AboutLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void AboutLayer::returnCallback(CCObject* pSender)
{
    CCLOG("onBack");
    CCDirector::sharedDirector()->popScene();
}

