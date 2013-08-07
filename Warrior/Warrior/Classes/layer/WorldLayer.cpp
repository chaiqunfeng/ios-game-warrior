//
//  WorldLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 6/24/13.
//
//

#include "WorldLayer.h"
#include "MusicManager.h"
#include "GamingLayer.h"
#include "UICommon.h"

WorldLayer::WorldLayer()
{
}

WorldLayer::~WorldLayer()
{
}

bool WorldLayer::init()
{
    if (BasicLayer::init())
    {
        // set background image
        setBgImg("world_gray768_1024.png");
        addCity("Africa", City_TAG_AFRICA, ccp(400, 495), menu_selector(WorldLayer::newGameCallback));
        addCity("Europe", City_TAG_EUROPE, ccp(390, 645), menu_selector(WorldLayer::newGameCallback));
        addCity("Asia", City_TAG_ASIA, ccp(565, 705), menu_selector(WorldLayer::newGameCallback));
        addCity("Australia", City_TAG_AUSTRALIA, ccp(660, 350), menu_selector(WorldLayer::newGameCallback));
        addCity("North America", City_TAG_NORTHAMERICA, ccp(190, 630), menu_selector(WorldLayer::newGameCallback));
        addCity("South America", City_TAG_SOUTHAMERICA, ccp(250, 355), menu_selector(WorldLayer::newGameCallback));
        
        // back icon
        CCLabelTTF* labelResume = CCLabelTTF::create("返回", "", 32.0f);
        CCLabelTTF* labelResume2 = CCLabelTTF::create("返回", "", 36.0f);
        CCMenuItemSprite* spResume = CCMenuItemSprite::create(labelResume, labelResume2, this, menu_selector(WorldLayer::returnCallback));
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCMenu* menuBack = CCMenu::create(spResume,NULL);
        menuBack->setPosition(ccp(size.width/2, 100));
        this->addChild(menuBack);
        
        return true;
    }
    return false;
}

CCScene* WorldLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        WorldLayer* layer = WorldLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void WorldLayer::returnCallback(CCObject* pSender)
{
    CCLOG("onBack");
    CCDirector::sharedDirector()->popScene();
}

void WorldLayer::AsiaCallback(CCObject* pSender)
{
    CCLOG("AsiaCallback");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,GamingLayer::scene()));
    
    MusicManager::sharedMusicManager()->randomMusic();
    
    selectEffect("Asia", ((CCMenu *)pSender)->getPosition());
}

void WorldLayer::newGameCallback(CCObject* pSender)
{
    CCLOG("newGameCallback");
    // TODO:
    CCMenuItemSprite *sp = (CCMenuItemSprite *)pSender;
    CCNode *nd = sp->getNormalImage();
    int tag = City_TAG_ASIA;//nd->getTag();
    char *cityName = NULL;//nd->getString;
    switch (tag) {
        case City_TAG_ASIA:
            cityName = "Asia";
            break;
        case City_TAG_AFRICA:
            cityName = "Africa";
            break;
        case City_TAG_AUSTRALIA:
            cityName = "Australia";
            break;
        case City_TAG_EUROPE:
            cityName = "Europe";
            break;
        case City_TAG_SOUTHAMERICA:
            cityName = "South America";
            break;
        case City_TAG_NORTHAMERICA:
            cityName = "North America";
            break;
        default:
            return;
            break;
    }
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,GamingLayer::scene()));
    
    MusicManager::sharedMusicManager()->randomMusic();
    
    selectEffect(cityName, sp->getPosition());
}

void WorldLayer::addCity(char *cityName, int tag, CCPoint po, SEL_MenuHandler selector)
{
    // back icon
    CCLabelTTF* label = CCLabelTTF::create(cityName, "", 16.0f);
    //CCLabelTTF* label2 = CCLabelTTF::create(cityName, "", 20.0f);
    CCMenuItemSprite* sp = CCMenuItemSprite::create(label, label, this, selector);
    sp->setTag(tag);
    
    CCMenu* menu = CCMenu::create(sp,NULL);
    menu->setPosition(po);
    this->addChild(menu);
}

void WorldLayer::selectEffect(char *cityName, CCPoint po)
{
    CCLabelTTF *labelTip = CCLabelTTF::create(cityName, "", 16.0f);
    labelTip->setPosition(po);
    this->addChild(labelTip);
    CCScaleBy *scaleby = CCScaleBy::create(0.3f, 5.0f);
    CCFadeOut *fadeout = CCFadeOut::create(0.5f);
    
    // callback
    CCCallFuncN* callback = CCCallFuncN::create(this, callfuncN_selector(WorldLayer::selectEffectRemove));
    
    labelTip->runAction(CCSequence::create(scaleby, fadeout, callback, NULL));
}

void WorldLayer::selectEffectRemove(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
}
