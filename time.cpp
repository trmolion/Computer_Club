#include "time.h"

bool TM::ComparisonTime(TM SecondTime){
    int minutesFirst = hour * 60 + minutes;
    int minutesSecond = SecondTime.hour * 60 + SecondTime.minutes;
    if (minutesFirst >= minutesSecond) return 1;
    else return 0;
}
TM TM::CalculationTime(TM SecondTime){
    TM difftime; 
    int minutesFirst = hour * 60 + minutes;
    int minutesSecond = SecondTime.hour * 60 + SecondTime.minutes;\
    int diffminutes = minutesSecond - minutesFirst;
    difftime.hour = diffminutes / 60;
    difftime.minutes = diffminutes % 60;
    return difftime;
}

bool TM::ReadTime(std::string time){
    std::istringstream st (time);
    std::string timeS;
    int i = 0;
    while (getline(st, timeS, ':')){
        if (i == 0) if(((hour = stoi(timeS)) < 0) || ((hour = stoi(timeS)) >= 24)) return 1;
        if (i == 1) if(((minutes = stoi(timeS)) < 0) || ((minutes = stoi(timeS)) >= 60)) return 1;
        i++;
    }
    st.clear();
    return 0;
}

std::string TM::ShowTime(){
    std::string time;
    if (hour < 10){
        time += "0" + std::to_string(hour) + ":";
    }
    else time += std::to_string(hour) + ":";
    if (minutes < 10){
        time += "0" + std::to_string(minutes) + " ";
    }
    else time += std::to_string(minutes) + " ";
    return time;
}
