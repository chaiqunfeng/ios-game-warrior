//
//  ArchiveHelper.h
//  Warrior
//
//  Created by Varek Chai on 5/31/13.
//
//

#ifndef __Warrior__ArchiveHelper__
#define __Warrior__ArchiveHelper__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

// if the file not exist, create a new one
bool readDocumentFile(string inFileName, string &outContent);

// if pContent == NULL, empty the file
bool saveDocumentFile(char* pContent,string pFileName);

#endif /* defined(__Warrior__ArchiveHelper__) */
