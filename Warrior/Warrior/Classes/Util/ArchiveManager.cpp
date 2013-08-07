//
//  ArchiveManager.cpp
//  Warrior
//
//  Created by Varek Chai on 5/31/13.
//
//

#include "ArchiveManager.h"
#include "ArchiveHelper.h"
#include "libjson.h"
#include "cocos2d.h"
USING_NS_CC;

#define ARCHIVE_FILENAME    "score_history.json"

#define ARCHIVE_KILLCOUNT   "ARCHIVE_KILLCOUNT"
#define ARCHIVE_DURATION    "ARCHIVE_DURATION"
#define ARCHIVE_TIME        "ARCHIVE_TIME"

static ArchiveManager* s_instance = NULL;

ArchiveManager::ArchiveManager()
{
}

ArchiveManager::~ArchiveManager()
{
}

ArchiveManager* ArchiveManager::sharedArchiveManager()
{
    if (!s_instance)
    {
        s_instance = new ArchiveManager();
        s_instance->init();
    }
    return s_instance;
}

void ArchiveManager::init()
{
    readFromDB();
}

bool ArchiveManager::addItem(ArchiveItem* item)
{
    if (!item) {
        CCLOG("ArchiveManager::addItem fail, item == NULL");
        return false;
    }
    
    AI_mset::iterator it = m_itemSet.insert(*item);
    
    if (saveToDB())
    {
        return true;
    }
    else {
        m_itemSet.erase(it);
        CCLOG("ArchiveManager::addItem fail, saveToDB fail");
        return false;
    }
}

int ArchiveManager::getItemCount()
{
    return m_itemSet.size();
}

multiset<ArchiveItem, cmp> ArchiveManager::getItemSet()
{
    return m_itemSet;
}

bool ArchiveManager::clearAll()
{
    if (saveDocumentFile(NULL, ARCHIVE_FILENAME))
    {
        m_itemSet.clear();
        return true;
    }
    else {
        CCLOG("ArchiveManager::clearAll fail, saveToDB fail");
        return false;
    }
}

bool ArchiveManager::saveToDB()
{
    CCLOG("ArchiveManager::saveToDB");
    //ArchiveItem* item = ;
    JSONNODE *arrn = json_new(JSON_ARRAY);
    
    for (AI_mset::iterator it = m_itemSet.begin(); it != m_itemSet.end(); ++it) {
        JSONNODE *node = json_new(JSON_NODE);
        json_push_back(node, json_new_i(ARCHIVE_KILLCOUNT, it->killCount));
        json_push_back(node, json_new_i(ARCHIVE_DURATION, it->duration));
        json_push_back(node, json_new_i(ARCHIVE_TIME, it->time));
        
        // add a node to array
        json_push_back(arrn, node);
    }
    
//    JSONNODE *node = json_new(JSON_NODE);
//    json_push_back(node, json_new_i(ARCHIVE_KILLCOUNT, item->killCount));
//    json_push_back(node, json_new_i(ARCHIVE_DURATION, item->duration));
//    json_push_back(node, json_new_i(ARCHIVE_TIME, item->time));

    json_char *jc = json_write_formatted(arrn);
    CCLOG("%s",jc);
    bool bRtn = saveDocumentFile(jc, ARCHIVE_FILENAME);
    json_free(jc);
    
    return bRtn;
}

bool ArchiveManager::readFromDB()
{
    string history;
    
    if (readDocumentFile(ARCHIVE_FILENAME, history)) {
        // clear set first
        m_itemSet.clear();
        
        JSONNODE *node = json_parse(history.c_str());
        
        return parseJson(node);
    }
    else {
        CCLOG("ArchiveManager::readFromDB fail");
        return false;
    }
}

bool ArchiveManager::parseJson(JSONNODE *node)
{
    if (node == NULL){
        printf("Invalid JSON Node1\n");
        return false;
    }
    
    // save to vector first
    vector<int> killCount;
    vector<int> duration;
    vector<time_t> time;
    
    JSONNODE_ITERATOR i = json_begin(node);
    while (i != json_end(node)){
        if (*i == NULL){
            printf("Invalid JSON Node2\n");
            return false;
        }
        
        // recursively call ourselves to dig deeper into the tree
        if (json_type(*i) == JSON_ARRAY || json_type(*i) == JSON_NODE){
            parseJson(*i);
        }
        else {
            // get the node name and value as a string
            json_char *node_name = json_name(*i);
            
            // find out where to store the values
            if (strcmp(node_name, ARCHIVE_KILLCOUNT) == 0){
                json_int_t node_value = json_as_int(*i);
                killCount.push_back(node_value);
                //CCLOG("%d", node_value);
            }
            else if (strcmp(node_name, ARCHIVE_DURATION) == 0){
                json_int_t node_value = json_as_int(*i);
                duration.push_back(node_value);
                //CCLOG("%s", node_value);
                //json_free(node_value);
            }
            else if (strcmp(node_name, ARCHIVE_TIME) == 0){
                json_int_t node_value = json_as_int(*i);
                time.push_back(node_value);
                //CCLOG("%d", node_value);
            }
            
            // cleanup
            json_free(node_name);
        }
        
        //increment the iterator
        ++i;
    }
    
    // vector 2 multiset
    if (killCount.size() == 0 || duration.size() == 0 || time.size() == 0
        || killCount.size() != duration.size() || killCount.size() != time.size())
    {
        printf("Invalid JSON Node3\n");
        return false;
    }
    int size = killCount.size();
    for (int i=0; i<size; i++) {
        ArchiveItem item = {killCount[i],duration[i],time[i]};
        m_itemSet.insert(item);
    }
    
    return true;
}
