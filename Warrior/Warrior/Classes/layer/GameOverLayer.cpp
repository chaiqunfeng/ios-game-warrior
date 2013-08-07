//
//  GameOverLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 6/5/13.
//
//

#include "GameOverLayer.h"
#include "GamingLayer.h"
#include "UICommon.h"
#include "RecordLayer.h"
#include "MusicManager.h"

GameOverLayer::GameOverLayer()
{
}

GameOverLayer::~GameOverLayer()
{
}

bool GameOverLayer::init()
{
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 50)))
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
//        // show GameOver icon
//        CCLabelTTF* labelGameOver = CCLabelTTF::create("游戏结束", "", 54.0f);
//        labelGameOver->setPosition(ccp(size.width/2, size.height/2));
//        this->addChild(labelGameOver);
        
        CCLabelTTF* labelScore = CCLabelTTF::create("得分：0", "", 54.0f);
        labelScore->setPosition(ccp(size.width/2, size.height*8/10));
        this->addChild(labelScore, GAMING_ZORDER_LAYER, GAMEOVER_TAG_LABEL_SCORE);
        
        CCLabelTTF* labelDuration = CCLabelTTF::create("时间：00:00:00", "", 54.0f);
        labelDuration->setPosition(ccp(size.width/2, size.height*7/10));
        this->addChild(labelDuration, GAMING_ZORDER_LAYER, GAMEOVER_TAG_LABEL_DURATION);
        
        CCLabelTTF* labelTime = CCLabelTTF::create("", "", 54.0f);
        labelTime->setPosition(ccp(size.width/2, size.height*6/10));
        this->addChild(labelTime, GAMING_ZORDER_LAYER, GAMEOVER_TAG_LABEL_TIME);
        labelTime->setVisible(false);
        
        // replay icon
        CCLabelTTF* labelReplay = CCLabelTTF::create("再玩一次", "", 32.0f);
        CCLabelTTF* labelReplay2 = CCLabelTTF::create("再玩一次", "", 36.0f);
        CCMenuItemSprite* spReplay = CCMenuItemSprite::create(labelReplay, labelReplay2, this, menu_selector(GameOverLayer::replayCallback));
        
        // score board icon
        CCLabelTTF* labelScoreBoard = CCLabelTTF::create("排行榜", "", 32.0f);
        CCLabelTTF* labelScoreBoard2 = CCLabelTTF::create("排行榜", "", 36.0f);
        CCMenuItemSprite* spScoreBoard = CCMenuItemSprite::create(labelScoreBoard, labelScoreBoard2, this, menu_selector(GameOverLayer::scoreBoardCallback));
        
        // menu icon
        CCLabelTTF* labelMenu = CCLabelTTF::create("返回菜单", "", 32.0f);
        CCLabelTTF* labelMenu2 = CCLabelTTF::create("返回菜单", "", 36.0f);
        CCMenuItemSprite* spMenu = CCMenuItemSprite::create(labelMenu, labelMenu2, this, menu_selector(GameOverLayer::menuCallback));
        
        CCMenu* menu = CCMenu::create(spReplay, spScoreBoard, spMenu, NULL);
        menu->alignItemsVerticallyWithPadding(10.0f);
        menu->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(menu);
        
        return true;
    }
    return false;
}

CCScene* GameOverLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        GameOverLayer* layer = GameOverLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void GameOverLayer::replayCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::replayCallback");
    this->setVisible(false);
    
    // callback
    GamingLayer* pLayer = (GamingLayer*)getParent();
    pLayer->replayCallback(pSender);
}

void GameOverLayer::scoreBoardCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::optionCallback");
    menuCallback(pSender);
    CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.5f,RecordLayer::scene()));
}

void GameOverLayer::menuCallback(CCObject* pSender)
{
    CCLOG("PauseLayer::menuCallback");
    this->setVisible(false);
    
    // resume the game
    CCDirector::sharedDirector()->resume();
    // return to menu
    CCDirector::sharedDirector()->popScene();
    
    MusicManager::sharedMusicManager()->welcomeMusic();
}

void GameOverLayer::setGameResult(int score, int duration, time_t time)
{
    CCLabelTTF *labelScore = (CCLabelTTF *)getChildByTag(GAMEOVER_TAG_LABEL_SCORE);
    CCLabelTTF *labelDuration = (CCLabelTTF *)getChildByTag(GAMEOVER_TAG_LABEL_DURATION);
    CCLabelTTF *labelTime = (CCLabelTTF *)getChildByTag(GAMEOVER_TAG_LABEL_TIME);
    
    char szScore[128] = {0};
    sprintf(szScore, "击落 %d", score);
    
    char szDuration[128] = {0};
    tm tDuration = {0};
    tDuration.tm_sec = duration%60;
    tDuration.tm_min = (duration/60)%60;
    tDuration.tm_hour = (duration/3600)%24;
    if (tDuration.tm_hour) {
        sprintf(szDuration, "用时 %d°%d'%d\"", tDuration.tm_hour, tDuration.tm_min, tDuration.tm_sec);
    }
    else if (tDuration.tm_min) {
        sprintf(szDuration, "用时 %d'%d\"", tDuration.tm_min, tDuration.tm_sec);
    }
    else {
        sprintf(szDuration, "用时 %d\"", tDuration.tm_sec);
    }
    //strftime(szDuration, sizeof(szDuration), "%T", &tDuration);
    
    char szTime[128] = {0};
    struct tm *tblock;
    tblock = localtime(&time);
    strftime(szTime, sizeof(szTime), "时间 %F %X", tblock);

    labelScore->setString(szScore);
    labelDuration->setString(szDuration);
    labelTime->setString(szTime);
}
