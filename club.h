#pragma once
#ifndef CLUB_H_
    #define CLUB_H_
    #include <algorithm>
    #include <iostream>
    #include <vector>
    #include "time.h"
    #include "visitor_table.h"
    using namespace std;
    class club{
    private:
        int quantTab;
        int priceHour;
        TM open, close;
        vector <Table> tables;
        vector <Visitor> visitors;
        vector <Visitor> waiting;
    public:
        //club();
        //~club();

        void CloseClub();

        void inputclub (int QuantityTables, TM OpenTime, TM CloseTime, int PriceHour);
        
        void IncomingEvents(TM TimeEvent, int CodeEvent, string ObejctEvent, int NumberTable);

        void ID_1(TM TimeEvent, string ObjectEvent);
        void ID_2(TM TimeEvent, string ObjectEvent, int NumberTable);
        void ID_3(TM TimeEvent, string ObjectEvent);
        void ID_4(TM TimeEvent, string ObjectEvent);
        void ID_11(TM TimeEvent, string ObjectEvent);
        void ID_12(TM TimeEvent, string ObjectEvent, int NumberTable);
        void ID_13(TM TimeEvent, string messeage);
    };
#endif
