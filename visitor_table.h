#pragma once
#ifndef VISITOR_TABLE_H_
    #define VISITOR_TABLE_H_
    #include "time.h"
    struct Table{
        bool OpenClose;  //1 - занят, 0 - свободен
        TM OpenTable, CloseTable;
        TM WorkTime; 
        int SummTime();
    };

    struct Visitor{ 
        int NumberTable;
        bool InOutSide; //true - в клубе, false - вне клуба
        std::string name;
    };
#endif