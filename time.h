#pragma once
#ifndef TIME_H_
    #define TIME_H_
    #include <sstream>
    #include <string>
    struct TM{
        int hour = -1;
        int minutes = -1;

        bool ComparisonTime(TM SecondTime);
        bool ReadTime(std::string time);
        TM CalculationTime(TM SecondTime);
        std::string ShowTime();
    };
#endif