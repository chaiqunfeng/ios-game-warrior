//
//  UICommon.h
//  Warrior
//
//  Created by Varek Chai on 5/22/13.
//
//

#ifndef Warrior_UICommon_h
#define Warrior_UICommon_h

enum E_PlaneType
{
    e_pt_player = 0,
    e_pt_enemy_1,
    e_pt_enemy_2,
    e_pt_enemy_boss1,
};

//-------------------blood/demage/medicine------------------------

#define BLOOD_PLAYER                 10
#define BLOOD_ENEMY1                 20
#define BLOOD_ENEMY2                 10
#define BLOOD_BOSS1                  1000
#define BLOOD_BOSS1_MISSILE          25

#define DEMAGE_PLAYER_BULLET         5
#define DEMAGE_ENEMY_BULLET          1

//#define DEMAGE_ENEMY1_BULLET         5
//#define DEMAGE_ENEMY2_BULLET         5
//#define DEMAGE_BOSS1_BULLET          5

#define DEMAGE_ENEMY_PLANE           2
#define DEMAGE_BOSS1_MISSILE         3

#define MEDICINE_BLOOD_CAPACITY_SMALL               3
#define MEDICINE_BLOOD_CAPACITY_BIG                 5

//-------------------tag------------------------
// Gaming tag
#define GAMING_TAG_BG1              1001
#define GAMING_TAG_BG2              1002
#define GAMING_TAG_LABLE_GAMEOVER   1003
#define GAMING_TAG_LABEL_TIMER      1004
#define GAMING_TAG_LABEL_SCORE      1005
#define GAMING_TAG_LAYER_PLANEMGR   1006

// Pause tag
#define PAUSE_TAG_LAYER             2001
#define PAUSE_TAG_MENU              2002

// Game Over tag
#define GAMEOVER_TAG_LAYER            3001
#define GAMEOVER_TAG_LABEL_DURATION   3002
#define GAMEOVER_TAG_LABEL_SCORE      3003
#define GAMEOVER_TAG_LABEL_TIME       3004

// Option tag
#define OPTION_TAG_LABEL_SONG         4001
#define OPTION_TAG_SLIDER_BACKGROUND  4002
#define OPTION_TAG_SLIDER_EFFECT      4003

// City tag
#define City_TAG_ASIA                 5001
#define City_TAG_AFRICA               5002
#define City_TAG_AUSTRALIA            5003
#define City_TAG_EUROPE               5004
#define City_TAG_SOUTHAMERICA         5005
#define City_TAG_NORTHAMERICA         5006

//-------------------zOrder---------------------
#define MIN_ZORDER                  0

// Plane zOrder
#define PLANE_ZORDER_LAYER          1

// Gaming zOrder
#define GAMING_ZORDER_LAYER         2

// Pause zOrder
#define PAUSE_ZORDER_LAYER          10

//-------------sprite frame name----------------
// bullet
#define SFN_BULLET_PLAYER           "SFN_BULLET_PLAYER"
#define SFN_BULLET_ENEMY1           "SFN_BULLET_ENEMY1"
#define SFN_BULLET_ENEMY2           "SFN_BULLET_ENEMY2"
#define SFN_BULLET_BOSS1            "SFN_BULLET_BOSS1"

// plane
#define SFN_PLANE_ENEMY1            "SFN_PLANE_ENEMY1"
#define SFN_PLANE_ENEMY2            "SFN_PLANE_ENEMY2"
#define SFN_PLANE_BOSS1             "SFN_PLANE_BOSS1"

// explosion
#define SFN_EXPLOSION50                 "SFN_EXPLOSION50"
#define SFN_EXPLOSION75                 "SFN_EXPLOSION75"
#define SFN_EXPLOSION100                "SFN_EXPLOSION100"
#define SFN_EXPLOSION125                "SFN_EXPLOSION125"
#define SFN_EXPLOSION150                "SFN_EXPLOSION150"

//----------------animation name--------------------
// explosion
#define AN_EXPLOSION                 "AN_EXPLOSION"

#endif
