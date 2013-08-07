//
//  AboutLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/21/13.
//
//

#ifndef __Warrior__AboutLayer__
#define __Warrior__AboutLayer__

#include <iostream>
#include "BasicLayer.h"

class AboutLayer:public BasicLayer
{
public:
    
    AboutLayer();
    ~AboutLayer();
    
    virtual bool init();
    
    static CCScene* scene();
    
    void returnCallback(CCObject* pSender);
    
    CREATE_FUNC(AboutLayer);
};

#endif /* defined(__Warrior__AboutLayer__) */
