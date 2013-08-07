//
//  WelcomeLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/21/13.
//
//

#include "WelcomeLayer.h"
#include "AboutLayer.h"
//#include "GamingLayer.h"
#include "OptionLayer.h"
#include "RecordLayer.h"
#include "MusicManager.h"
#include "WorldLayer.h"

WelcomeLayer::WelcomeLayer()
{
}

WelcomeLayer::~WelcomeLayer()
{
}

bool WelcomeLayer::init()
{
    if (BasicLayer::init())
    {
        // set background image
        setBgImg("space_bg0.png");
        
        // set game name
        CCLabelTTF* labelGameName = CCLabelTTF::create("地球保卫战", "", 80.0f);//("Defend Earth", "", 80.0f);
        labelGameName->setPosition(ccp(getWinSize().width / 2, getWinSize().height * 4 / 5));
        this->addChild(labelGameName);
        
        // set manu
        CCLabelTTF* labelStart = CCLabelTTF::create("开始", "", 50.0f);
        CCLabelTTF* labelScore = CCLabelTTF::create("排行榜", "", 50.0f);
        CCLabelTTF* labelOption = CCLabelTTF::create("设置", "", 50.0f);
        CCLabelTTF* labelAbout = CCLabelTTF::create("关于", "", 50.0f);
        CCMenuItemSprite* spStart = CCMenuItemSprite::create(labelStart, labelStart, this, menu_selector(WelcomeLayer::newGameCallback));
        CCMenuItemSprite* spScore = CCMenuItemSprite::create(labelScore, labelScore, this, menu_selector(WelcomeLayer::recordCallback));
        CCMenuItemSprite* spOption = CCMenuItemSprite::create(labelOption, labelOption, this, menu_selector(WelcomeLayer::optionCallback));
        CCMenuItemSprite* spAbout = CCMenuItemSprite::create(labelAbout, labelAbout, this, menu_selector(WelcomeLayer::aboutCallback));
        CCMenu* menu = CCMenu::create(spStart, spScore, spOption, spAbout, NULL);
        menu->setPosition(ccp(getWinSize().width/2, getWinSize().height/2));
        menu->alignItemsVerticallyWithPadding(10.0f);
        this->addChild(menu);
        
//        CCMenuItemImage* newGame = CCMenuItemImage::create("btn_newgame.png","btn_newgame.png",this,menu_selector(WelcomeLayer::newGameCallback));
//        
//        CCMenuItemImage* option = CCMenuItemImage::create("btn_option.png","btn_option.png",this,menu_selector(WelcomeLayer::optionCallback));
//
//        CCMenuItemImage* about = CCMenuItemImage::create("btn_about.png","btn_about.png",this,menu_selector(WelcomeLayer::aboutCallback));
//
//        CCMenu* menu2 = CCMenu::create(newGame,option,about,NULL);
//        menu2->setPosition(ccp(getWinSize().width/2, getWinSize().height/2));
//        menu2->alignItemsVerticallyWithPadding(10.0f);
//        this->addChild(menu2);
        
//        // set logo
//        CCSprite* logo = CCSprite::create("logo.png");
//        logo->setPosition(ccp(getWinSize().width/2, getWinSize().height*3/4));
//        this->addChild(logo);
        
        //set exit icon
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(WelcomeLayer::exitCallback) );
        pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 50, 50) );
        
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu);
        
//        //test
//        ArchiveManager *archive = ArchiveManager::sharedArchiveManager();
//        archive->clearAll();
//        ArchiveItem item1 = {11,22,33};
//        ArchiveItem item2 = {10,66,88};
//        archive->addItem(&item1);
//        archive->addItem(&item2);
//        archive->init();
//        int count = archive->getItemCount();
//        CCLOG("getItemCount()-%d",count);
//        multiset<ArchiveItem, cmp> set = archive->getItemSet();
//        for (AI_mset::iterator it = set.begin(); it != set.end(); ++it) {
//            // add a node to array
//            CCLOG("killcount:%d duration: %dtime: %d ",it->killCount, it->duration, it->time);
//        }
        return true;
    }
    
    return false;
}

CCScene* WelcomeLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        WelcomeLayer* layer = WelcomeLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void WelcomeLayer::onEnter()
{
    BasicLayer::onEnter();
}

void WelcomeLayer::newGameCallback(CCObject* pSender)
{
    CCLOG("newGameCallback");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,WorldLayer::scene()));
    
    //MusicManager::sharedMusicManager()->randomMusic();
}

void WelcomeLayer::recordCallback(CCObject* pSender)
{
    CCLOG("recordCallback");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,RecordLayer::scene()));
}

void WelcomeLayer::optionCallback(CCObject* pSender)
{
    CCLOG("optionCallback");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,OptionLayer::scene()));
}

void WelcomeLayer::aboutCallback(CCObject* pSender)
{
    CCLOG("aboutCallback");
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,AboutLayer::scene()));
}

void WelcomeLayer::exitCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    exit(0);
}