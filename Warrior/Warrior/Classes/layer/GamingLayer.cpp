//
//  GamingLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#include "GamingLayer.h"
#include "UICommon.h"
#include "ScoreLabel.h"
#include "TimerLabel.h"
#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include "PlaneManager.h"
#include "GameOverLayer.h"
#include "MusicManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

GamingLayer::GamingLayer()
{
}

GamingLayer::~GamingLayer()
{
}

bool GamingLayer::init()
{
    if (BasicLayer::init())
    {
        // set background image
        CCSprite* bg1 = CCSprite::create("space_bg1.png");
        CCSprite* bg2 = CCSprite::create("space_bg1.png");
        
        bg1->setAnchorPoint(CCPointZero);
        bg2->setAnchorPoint(CCPointZero);
        
        bg1->setPosition(CCPointZero);
        bg2->setPosition(ccp(0, getWinSize().height));
        
        this->addChild(bg1,MIN_ZORDER,GAMING_TAG_BG1);
        this->addChild(bg2,MIN_ZORDER,GAMING_TAG_BG2);
        
        // bg scroll schedule
        this->schedule(schedule_selector(GamingLayer::bgScroll), 0.04f);
        
        // score label
        CCLabelTTF* labelScore = CCLabelTTF::create("击落", "", 20.0f);
        labelScore->setAnchorPoint(ccp(0, 0.5f));
        labelScore->setPosition(ccp(20, getWinSize().height - 20));
        this->addChild(labelScore);
        
        ScoreLabel* score = ScoreLabel::create();
        score->setAnchorPoint(ccp(0, 0.5f));
        score->setPosition(ccp(80, getWinSize().height - 20));
        this->addChild(score, GAMING_ZORDER_LAYER, GAMING_TAG_LABEL_SCORE);
        
        // timer label
        CCLabelTTF* labelDuration = CCLabelTTF::create("用时", "", 20.0f);
        labelDuration->setAnchorPoint(ccp(0, 0.5f));
        labelDuration->setPosition(ccp(160, getWinSize().height - 20));
        this->addChild(labelDuration);
        
        TimerLabel* timer = TimerLabel::create();
        timer->setAnchorPoint(ccp(0, 0.5f));
        timer->setPosition(ccp(220, getWinSize().height - 20));
        timer->startTimer();
        this->addChild(timer, GAMING_ZORDER_LAYER, GAMING_TAG_LABEL_TIMER);
        
        // add plane
        this->addChild(PlaneManager::create(), PLANE_ZORDER_LAYER, GAMING_TAG_LAYER_PLANEMGR);
        
        // pause icon
        CCLabelTTF* labelPause = CCLabelTTF::create("暂停", "", 32.0f);
        CCLabelTTF* labelPause2 = CCLabelTTF::create("暂停", "", 36.0f);
        CCMenuItemSprite* spPause = CCMenuItemSprite::create(labelPause, labelPause2, this, menu_selector(GamingLayer::pauseCallback));
        CCMenu* menu = CCMenu::create(spPause,NULL);
        menu->setPosition(ccp(getWinSize().width/2, getWinSize().height - 100));
        menu->setOpacity(100);
        this->addChild(menu,GAMING_ZORDER_LAYER,PAUSE_TAG_MENU);
        
        // pause layer, enable = false
        PauseLayer* pauseLayer = PauseLayer::create();
        pauseLayer->setAnchorPoint(CCPointZero);
        pauseLayer->setPosition(CCPointZero);
        pauseLayer->setVisible(false);
        this->addChild(pauseLayer,PAUSE_ZORDER_LAYER,PAUSE_TAG_LAYER);
        
        // gameover layer, enable = false
        GameOverLayer* gameoverLayer = GameOverLayer::create();
        gameoverLayer->setAnchorPoint(CCPointZero);
        gameoverLayer->setPosition(CCPointZero);
        gameoverLayer->setVisible(false);
        this->addChild(gameoverLayer,PAUSE_ZORDER_LAYER,GAMEOVER_TAG_LAYER);
        
        // show GameOver label
        CCLabelTTF* labelGameOver = CCLabelTTF::create("游戏结束", "", 54.0f);
        labelGameOver->setPosition(ccp(getWinSize().width/2, getWinSize().height/2));
        labelGameOver->setVisible(false);
        this->addChild(labelGameOver, GAMING_ZORDER_LAYER, GAMING_TAG_LABLE_GAMEOVER);
        
        return true;
    }
    return false;
}

CCScene* GamingLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        GamingLayer* layer = GamingLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void GamingLayer::onEnterTransitionDidFinish()
{
    MusicManager::sharedMusicManager()->setGamingLayer(this);
    
    BasicLayer::onEnterTransitionDidFinish();
}

void GamingLayer::onExit()
{
    MusicManager::sharedMusicManager()->setGamingLayer(NULL);
    
    BasicLayer::onExit();
}

void GamingLayer::bgScroll(float t)
{
    CCSprite* bg1 = (CCSprite*)getChildByTag(GAMING_TAG_BG1);
    CCSprite* bg2 = (CCSprite*)getChildByTag(GAMING_TAG_BG2);
    
    bg1->setPositionY(bg1->getPositionY()-1);
    bg2->setPositionY(bg1->getPositionY()+getWinSize().height);
    
    if (bg2->getPositionY()<=0)
    {
        bg1->setPositionY(0);
        bg2->setPositionY(bg1->getPositionY()+getWinSize().height);
    }
}

void GamingLayer::pauseCallback(CCObject* pSender)
{
    CCLOG("GamingLayer::pauseCallback");
    // disable pause when game over
    if (getChildByTag(GAMEOVER_TAG_LAYER)->isVisible() || getChildByTag(GAMING_TAG_LABLE_GAMEOVER)->isVisible()) {
        return;
    }
    
    // show pause layer
    getChildByTag(PAUSE_TAG_LAYER)->setVisible(true);
    
    // pause the game
    CCDirector::sharedDirector()->pause();
    
    // disable the pause icon
    CCMenu* pManu = (CCMenu*)getChildByTag(PAUSE_TAG_MENU);
    pManu->setEnabled(false);
    pManu->setVisible(false);
    
    // disable touch of plane
    PlaneManager *mgr = (PlaneManager *)getChildByTag(GAMING_TAG_LAYER_PLANEMGR);
    mgr->setPlayerTouchEnabled(false);
    
    // pause music
    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    //SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void GamingLayer::resumeCallback(CCObject* pSender)
{
    CCLOG("GamingLayer::resumeCallback");
    CCMenu* pMenu = (CCMenu*)getChildByTag(PAUSE_TAG_MENU);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    
    // disable touch of plane
    PlaneManager *mgr = (PlaneManager *)getChildByTag(GAMING_TAG_LAYER_PLANEMGR);
    mgr->setPlayerTouchEnabled(true);
    
    // resume the game
    CCDirector::sharedDirector()->resume();
    
    // resume music
    //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    //SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void GamingLayer::replayCallback(CCObject* pSender)
{
    // resume the game
    CCDirector::sharedDirector()->resume();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f,GamingLayer::scene()));
    
    MusicManager::sharedMusicManager()->randomMusic();
}

void GamingLayer::gameoverCallback()
{
    // show GameOver label
    CCLabelTTF *labelGameOver = (CCLabelTTF*)getChildByTag(GAMING_TAG_LABLE_GAMEOVER);
    labelGameOver->setVisible(true);
    
    this->scheduleOnce(schedule_selector(GamingLayer::performGameOver), 3.0f);
    
    MusicManager::sharedMusicManager()->randomMusic();
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void GamingLayer::applicationDidEnterBackground()
{
    // do nothing 
}

// this function will be called when the app is active again
void GamingLayer::applicationWillEnterForeground()
{
    // pause the game
    this->scheduleOnce(schedule_selector(GamingLayer::pauseCallback), 0.01f);
}

void GamingLayer::performGameOver(CCObject* pSender)
{
    CCLabelTTF *labelGameOver = (CCLabelTTF*)getChildByTag(GAMING_TAG_LABLE_GAMEOVER);
    labelGameOver->setVisible(false);
    
    // show game over layer
    getChildByTag(GAMEOVER_TAG_LAYER)->setVisible(true);
}
