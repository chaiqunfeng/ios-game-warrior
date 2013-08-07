//
//  ArchiveManager.h
//  Warrior
//
//  Created by Varek Chai on 5/31/13.
//
//

#ifndef __Warrior__ArchiveManager__
#define __Warrior__ArchiveManager__

#include <iostream>
#include <set>
using namespace std;

struct ArchiveItem
{
    int killCount;
    int duration;
    time_t time;
};

struct cmp
{
    bool operator()(const ArchiveItem&a,const ArchiveItem&b)
    {
        return a.killCount > b.killCount ||
        (a.killCount == b.killCount && a.duration > b.duration) ||
        ((a.killCount == b.killCount && a.duration == b.duration && a.time > b.time));
    }
};

typedef multiset<ArchiveItem, cmp> AI_mset;
class ArchiveManager
{
public:
    
    ArchiveManager();
    ~ArchiveManager();
    
    static  ArchiveManager* sharedArchiveManager();
    void init();
    
    bool addItem(ArchiveItem* item);
    int getItemCount();
    AI_mset getItemSet();
    bool clearAll();
    
private:
    
    bool parseJson(void *node);
    bool saveToDB();
    bool readFromDB();
    
    AI_mset m_itemSet;
};

#endif /* defined(__Warrior__ArchiveManager__) */
