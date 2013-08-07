//
//  RecordLayer.h
//  Warrior
//
//  Created by Varek Chai on 6/6/13.
//
//

#ifndef __Warrior__RecordLayer__
#define __Warrior__RecordLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

struct ArchiveItem;
class RecordLayer:public CCLayerColor
{
public:
    
    RecordLayer();
    ~RecordLayer();
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(RecordLayer);
    
    void resetCallback(CCObject* pSender);
    void returnCallback(CCObject* pSender);
    
private:
    void addRecord(ArchiveItem item, int index);
};

#endif /* defined(__Warrior__RecordLayer__) */
