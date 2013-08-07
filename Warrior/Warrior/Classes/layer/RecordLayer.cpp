//
//  RecordLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 6/6/13.
//
//

#include "RecordLayer.h"
#include "ArchiveManager.h"

RecordLayer::RecordLayer()
{
}

RecordLayer::~RecordLayer()
{
}

bool RecordLayer::init()
{
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 50)))
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* bg1 = CCSprite::create("option_bg.png");
        bg1->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(bg1);
        
        // top icon
        CCLabelTTF* labelTop = CCLabelTTF::create("排行榜", "", 56.0f);
        labelTop->setPosition(ccp(size.width/2, size.height - 100));
        this->addChild(labelTop);
        
        CCLabelTTF* labelTitle = CCLabelTTF::create("------------ 击落 ------------ 用时 ------------ 时间 ------------", "", 24.0f);
        labelTitle->setPosition(ccp(size.width/2, size.height - 200));
        this->addChild(labelTitle);
        
        // reset icon
        CCLabelTTF* labelReset = CCLabelTTF::create("重置", "", 16.0f);
        CCLabelTTF* labelReset2 = CCLabelTTF::create("重置", "", 20.0f);
        CCMenuItemSprite* spReset = CCMenuItemSprite::create(labelReset, labelReset2, this, menu_selector(RecordLayer::resetCallback));
        CCMenu* menuReset = CCMenu::create(spReset, NULL);
        //menuReset->alignItemsVerticallyWithPadding(10.0f);
        menuReset->setPosition(ccp(size.width * 3 / 4, size.height - 100));
        this->addChild(menuReset);
        
        // return icon
        CCLabelTTF* labelReturn = CCLabelTTF::create("返回", "", 32.0f);
        CCLabelTTF* labelReturn2 = CCLabelTTF::create("返回", "", 36.0f);
        CCMenuItemSprite* spReturn = CCMenuItemSprite::create(labelReturn, labelReturn2, this, menu_selector(RecordLayer::returnCallback));
        
        CCMenu* menuRtn = CCMenu::create(spReturn, NULL);
        //menu->alignItemsVerticallyWithPadding(10.0f);
        menuRtn->setPosition(ccp(size.width/2, 100));
        this->addChild(menuRtn);
        
        // load record from db
        ArchiveManager *archive = ArchiveManager::sharedArchiveManager();
        
        multiset<ArchiveItem, cmp> set = archive->getItemSet();
        AI_mset::iterator it = set.begin();
        for (int i = 0; i < 10; i++) {
            if (it == set.end()) {
                break;
            }
            addRecord(*it, i);
            
            it++;
        }
        
        return true;
    }
    return false;
}

CCScene* RecordLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        RecordLayer* layer = RecordLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void RecordLayer::resetCallback(CCObject* pSender)
{
    ArchiveManager *archive = ArchiveManager::sharedArchiveManager();
    archive->clearAll();
}

void RecordLayer::returnCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void RecordLayer::addRecord(ArchiveItem item, int index)
{
    char szKillcount[128] = {0};
    sprintf(szKillcount, "%d", item.killCount);
    
    char szDuration[128] = {0};
    tm tDuration = {0};
    tDuration.tm_sec = item.duration%60;
    tDuration.tm_min = (item.duration/60)%60;
    tDuration.tm_hour = (item.duration/3600)%24;
    strftime(szDuration, sizeof(szDuration), "%T", &tDuration);
    
    char szTime[128] = {0};
    struct tm *tblock;
    tblock = localtime(&item.time);
    strftime(szTime, sizeof(szTime), "%F %X", tblock);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* labelKillcount = CCLabelTTF::create(szKillcount, "", 20.0f);
    labelKillcount->setPosition(ccp(size.width / 4, size.height - 250 - index * 50));
    
    CCLabelTTF* labelDuration = CCLabelTTF::create(szDuration, "", 20.0f);
    labelDuration->setPosition(ccp(size.width / 2, size.height - 250 - index * 50));
    
    CCLabelTTF* labelTime = CCLabelTTF::create(szTime, "", 20.0f);
    labelTime->setPosition(ccp(size.width * 3 / 4, size.height - 250 - index * 50));
    
    this->addChild(labelKillcount);
    this->addChild(labelDuration);
    this->addChild(labelTime);
}