//
//  WorldLayer.h
//  Warrior
//
//  Created by Varek Chai on 6/24/13.
//
//

#ifndef __Warrior__WorldLayer__
#define __Warrior__WorldLayer__

#include <iostream>
#include "BasicLayer.h"

class WorldLayer:public BasicLayer
{
public:
    
    WorldLayer();
    ~WorldLayer();
    
    virtual bool init();
    
    static CCScene* scene();
    
    void AsiaCallback(CCObject* pSender);
    void newGameCallback(CCObject* pSender);
    void returnCallback(CCObject* pSender);
    
    CREATE_FUNC(WorldLayer);
    
private:
    void addCity(char *cityName, int tag, CCPoint po, SEL_MenuHandler selector);
    void selectEffect(char *cityName, CCPoint po);
    void selectEffectRemove(CCNode *pSender);
};

#endif /* defined(__Warrior__WorldLayer__) */
