//
//  OptionLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#include "OptionLayer.h"
#include "UICommon.h"
#include "MusicManager.h"
#include "CCControlSlider.h"
USING_NS_CC_EXT;

OptionLayer::OptionLayer()
{
}

OptionLayer::~OptionLayer()
{
}

bool OptionLayer::init()
{
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 50)))
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* bg1 = CCSprite::create("option_bg.png");
        bg1->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(bg1);
        
        // top icon
        CCLabelTTF* labelTop = CCLabelTTF::create("设置", "", 56.0f);
        labelTop->setPosition(ccp(size.width/2, size.height - 100));
        this->addChild(labelTop);
        
        // song icon
        CCString *music = MusicManager::sharedMusicManager()->currentMusic();
        CCLabelTTF* labelCurSong = CCLabelTTF::create(music->getCString(), "", 20.0f);
        labelCurSong->setPosition(ccp(size.width/2, size.height - 300));
        this->addChild(labelCurSong, MIN_ZORDER, OPTION_TAG_LABEL_SONG);
        
        // next song icon
        CCLabelTTF* labelNextSong = CCLabelTTF::create("播放下一曲", "", 32.0f);
        CCLabelTTF* labelNextSong2 = CCLabelTTF::create("播放下一曲", "", 36.0f);
        CCMenuItemSprite* spNextSong = CCMenuItemSprite::create(labelNextSong, labelNextSong2, this, menu_selector(OptionLayer::nextSongCallback));
        
        CCMenu* menuOption = CCMenu::create(spNextSong, NULL);
        //menu->alignItemsVerticallyWithPadding(10.0f);
        menuOption->setPosition(ccp(size.width/2, size.height - 350));
        this->addChild(menuOption);
        
        // return icon
        CCLabelTTF* labelReturn = CCLabelTTF::create("返回", "", 32.0f);
        CCLabelTTF* labelReturn2 = CCLabelTTF::create("返回", "", 36.0f);
        CCMenuItemSprite* spReturn = CCMenuItemSprite::create(labelReturn, labelReturn2, this, menu_selector(OptionLayer::returnCallback));
        
        CCMenu* menu = CCMenu::create(spReturn, NULL);
        //menu->alignItemsVerticallyWithPadding(10.0f);
        menu->setPosition(ccp(size.width/2, 100));
        this->addChild(menu);
        
        // background icon
        CCLabelTTF* labelBackgroundMusic = CCLabelTTF::create("背景音乐", "", 20.0f);
        labelBackgroundMusic->setPosition(ccp(size.width/2, size.height - 450));
        this->addChild(labelBackgroundMusic, MIN_ZORDER, OPTION_TAG_LABEL_SONG);
        
        // background slider
        CCControlSlider *slider = CCControlSlider::create("metal-slider-track400_20.png","metal-slider-progress400_20.png" ,"metal-slider-handle30_30.png");
        slider->setPosition(ccp(size.width / 2, size.height - 500) );
        slider->setMinimumValue(0.0f);
        slider->setMaximumValue(1.0f); 
        slider->setValue(MusicManager::sharedMusicManager()->getBackgroundVolumn());
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::backgroundSliderCallback), CCControlEventValueChanged);
        this->addChild(slider, MIN_ZORDER, OPTION_TAG_SLIDER_BACKGROUND);
        
        // background mute icon
        CCSprite* spBgMute = CCSprite::create("sound-mute30_30.png");
        CCSprite* spBgMute2 = CCSprite::create("sound-mute50_50.png");
        CCMenuItemSprite* ispBgMute = CCMenuItemSprite::create(spBgMute, spBgMute2, this, menu_selector(OptionLayer::backgroundMuteCallback));
        CCMenu* menuBgMute = CCMenu::create(ispBgMute, NULL);
        menuBgMute->setPosition(ccp(size.width/2 - 200 - 50, size.height - 500));
        this->addChild(menuBgMute);
        
        // effect icon
        CCLabelTTF* labelEffectMusic = CCLabelTTF::create("游戏音效", "", 20.0f);
        labelEffectMusic->setPosition(ccp(size.width/2, size.height - 600));
        this->addChild(labelEffectMusic);
        
        // effect slider
        CCControlSlider *eslider = CCControlSlider::create("metal-slider-track400_20.png","metal-slider-progress400_20.png" ,"metal-slider-handle30_30.png");
        eslider->setPosition(ccp(size.width / 2, size.height - 650) );
        eslider->setMinimumValue(0.0f);
        eslider->setMaximumValue(1.0f);
        eslider->setValue(MusicManager::sharedMusicManager()->getEffectVolumn());
        eslider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::effectSliderCallback), CCControlEventValueChanged);
        this->addChild(eslider, MIN_ZORDER, OPTION_TAG_SLIDER_EFFECT);
        
        // effect mute icon
        CCSprite* spEffectMute = CCSprite::create("sound-mute30_30.png");
        CCSprite* spEffectMute2 = CCSprite::create("sound-mute50_50.png");
        CCMenuItemSprite* ispEffectMute = CCMenuItemSprite::create(spEffectMute, spEffectMute2, this, menu_selector(OptionLayer::effectMuteCallback));
        CCMenu* menuEffectMute = CCMenu::create(ispEffectMute, NULL);
        menuEffectMute->setPosition(ccp(size.width/2 - 200 - 50, size.height - 650));
        this->addChild(menuEffectMute);
        
        return true;
    }
    return false;
}

CCScene* OptionLayer::scene()
{
    CCScene* sc = NULL;
    do {
        sc = CCScene::create();
        CC_BREAK_IF(!sc);
        
        OptionLayer* layer = OptionLayer::create();
        CC_BREAK_IF(!layer);
        
        sc->addChild(layer);
    } while (0);
    
    return sc;
}

void OptionLayer::onEnter()
{
    CCLayerColor::onEnter();
    // update the name of the song
    CCString *music = MusicManager::sharedMusicManager()->currentMusic();
    CCLabelTTF *labelCurSong = (CCLabelTTF *)getChildByTag(OPTION_TAG_LABEL_SONG);
    labelCurSong->setString(music->getCString());
}

void OptionLayer::returnCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void OptionLayer::nextSongCallback(CCObject* pSender)
{
    MusicManager::sharedMusicManager()->nextMusic();
    // update the name of the song
    CCString *music = MusicManager::sharedMusicManager()->currentMusic();
    CCLabelTTF *labelCurSong = (CCLabelTTF *)getChildByTag(OPTION_TAG_LABEL_SONG);
    labelCurSong->setString(music->getCString());
}

void OptionLayer::backgroundSliderCallback(CCObject* pSender)
{
    CCControlSlider *pSliderCtl = (CCControlSlider *)pSender;
    
    float scale = pSliderCtl->getValue();
    
    CCLog("CCControlSlider value = %f",scale);
    
    MusicManager::sharedMusicManager()->setBackgroundVolumn(scale);
}

void OptionLayer::effectSliderCallback(CCObject* pSender)
{
    CCControlSlider *pSliderCtl = (CCControlSlider *)pSender;
    
    float scale = pSliderCtl->getValue();
    
    CCLog("CCControlSlider value = %f",scale);
    
    MusicManager::sharedMusicManager()->setEffectVolumn(scale);
}

void OptionLayer::backgroundMuteCallback(CCObject* pSender)
{
    CCControlSlider *pSliderCtl = (CCControlSlider *)getChildByTag(OPTION_TAG_SLIDER_BACKGROUND);
    if (pSliderCtl) {
        pSliderCtl->setValue(0);
    }
}

void OptionLayer::effectMuteCallback(CCObject* pSender)
{
    CCControlSlider *pSliderCtl = (CCControlSlider *)getChildByTag(OPTION_TAG_SLIDER_EFFECT);
    if (pSliderCtl) {
        pSliderCtl->setValue(0);
    }
}