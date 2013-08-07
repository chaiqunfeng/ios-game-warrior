//
//  ArchiveHelper.cpp
//  Warrior
//
//  Created by Varek Chai on 5/31/13.
//
//

#include "ArchiveHelper.h"

bool readDocumentFile(string inFileName, string &outContent){
    //第一先获取文件的路径
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + inFileName;
    CCLOG("path = %s",path.c_str());
    
    //创建一个文件指针
    FILE* file = fopen(path.c_str(), "ab+");
    
    if (file) {
        char* buf;  //要获取的字符串
        int len;    //获取的长度
        /*获取长度*/
        fseek(file, 0, SEEK_END);   //移到尾部
        len = ftell(file);          //提取长度
        rewind(file);               //回归原位
        CCLOG("count the file content len = %d",len);
        //分配buf空间
        buf = (char*)malloc(sizeof(char) * len + 1);
        if (!buf) {
            CCLOG("malloc space is not enough.");
            return NULL;
        }
        
        //读取文件
        //读取进的buf，单位大小，长度，文件指针
        int rLen = fread(buf, sizeof(char), len, file);
        buf[rLen] = '\0';
        CCLOG("has read Length = %d",rLen);
        CCLOG("has read content = %s",buf);
        
        //string result = buf;
        outContent= buf;
        fclose(file);
        free(buf);
        return true;
    }
    else
    {
        CCLOG("open file error.");
        return false;
    }
}

bool saveDocumentFile(char *pContent, string pFileName){
    
    // get file path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;
    CCLOG("wanna save file path = %s",path.c_str());
    
    if (!pContent) {
        FILE* file = fopen(path.c_str(), "w");
        if (file) {
            fclose(file);
            return true;
        }
        else{
            CCLOG("fopen fail.");
            return false;
        }
    }
    else {
        FILE* file = fopen(path.c_str(), "w");
        if (file) {
            fputs(pContent, file);
            fclose(file);
            return true;
        }
        else {
            CCLOG("fopen fail.");
            return false;
        }
    }
    
}