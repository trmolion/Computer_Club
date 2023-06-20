#include "club.h"


void club::CloseClub(){
    sort(visitors.begin(), visitors.end(), [](Visitor First, Visitor Second){return First.name[0] < Second.name[0];});
    while(visitors.size() > 0) ID_11(close, visitors[0].name);  
    for (int i = 0; i < tables.size(); i++){
        cout << i + 1  << " " << tables[i].SummTime() * priceHour << " " << tables[i].WorkTime.ShowTime() << endl;
    }
}

void club::inputclub (int QuantityTables, TM OpenTime, TM CloseTime, int PriceHour){
    quantTab = QuantityTables;
    tables.reserve(quantTab);           
    for (int i = 0; i < quantTab; i++){     
        tables.push_back(Table());          
        tables[i].OpenClose = false;           
    }                                    
    priceHour = PriceHour;
    open.hour = OpenTime.hour;
    open.minutes = OpenTime.minutes;
    close.hour = CloseTime.hour;
    close.minutes = CloseTime.minutes;
    cout << open.ShowTime() << endl;
}

void club::IncomingEvents(TM TimeEvent, int CodeEvent, string ObejctEvent, int NumberTable){
    switch (CodeEvent){
    case 1:
        cout << TimeEvent.ShowTime() << " " << CodeEvent << " " << ObejctEvent << endl;
        ID_1(TimeEvent, ObejctEvent);
        break;
    case 2:
        cout << TimeEvent.ShowTime() << " " << CodeEvent << " " << ObejctEvent << " " << NumberTable + 1 << endl;
        ID_2(TimeEvent, ObejctEvent, NumberTable);
        break;
    case 3:
        cout << TimeEvent.ShowTime() <<  " " << CodeEvent << " "  << ObejctEvent << endl;
        ID_3(TimeEvent, ObejctEvent);
        break;
    case 4:
        cout << TimeEvent.ShowTime() << " " << CodeEvent << " " << ObejctEvent << endl;
        ID_4(TimeEvent, ObejctEvent);
        break;
    default:
        cout << "\n\tTHIS CODE NOT EXIST" << endl;
        break;
    }
}

void club::ID_1(TM TimeEvent, string ObjectEvent){
    if (TimeEvent.ComparisonTime(open) == 0){
        ID_13(TimeEvent, "NotOpenYet");
        return;
    }
    auto it = find_if(visitors.begin(), visitors.end(),[&Object = ObjectEvent](Visitor First){return First.name == Object;});
    if(it != visitors.end()) ID_13(TimeEvent, "YouShallNotPass");
    else visitors.push_back({-1, true, ObjectEvent});    
}

void club::ID_2(TM TimeEvent, string ObjectEvent, int NumberTable){
    auto it = find_if(visitors.begin(), visitors.end(),[&Object = ObjectEvent](Visitor First){return First.name == Object;});
    if(it == visitors.end()) ID_13(TimeEvent, "ClientUnknown");
    else if (tables[NumberTable].OpenClose == 1) {
        ID_13 (TimeEvent, "PlaceIsBusy");
        return;
    }
    else {
        (*it).NumberTable =NumberTable;
        tables[NumberTable].OpenClose = true;
        tables[NumberTable].OpenTable = TimeEvent;
    }
}

void club::ID_3(TM TimeEvent, string ObjectEvent){
    auto it = find_if(tables.begin(), tables.end(),[](Table table){return table.OpenClose == 0;});
    if (it != tables.end()){
        ID_13(TimeEvent, "ICanWaitNoLonger");
        return;
    }
    if (waiting.size() >= quantTab){
        ID_11(TimeEvent, ObjectEvent);
        return;
    }
    else{
        waiting.push_back({-1, true, ObjectEvent});
        auto it = find_if(visitors.begin(), visitors.end(),[&Object = ObjectEvent](Visitor vis){return vis.name== Object;});
        if (it != visitors.end()) visitors.erase(it);
    } 
}

void club::ID_4(TM TimeEvent, string ObjectEvent){ 
    auto it = find_if(visitors.begin(), visitors.end(),[&Object = ObjectEvent](Visitor First){return First.name == Object;});
    if(it == visitors.end()) ID_13(TimeEvent, "ClientUnknown");
    else {
            if(waiting.size() > 0){
            (*it).name = waiting[0].name;
            ID_12(TimeEvent, (*it).name, (*it).NumberTable);
        }
        else{
            tables[(*it).NumberTable].CloseTable = TimeEvent;
            visitors.erase(it);
        }
    }
}

void club::ID_11(TM TimeEvent, string ObjectEvent){
    auto it = find_if(visitors.begin(),visitors.end(),[&Object = ObjectEvent](Visitor vis){return vis.name == Object;});
    if (it != visitors.end()){
        tables[(*it).NumberTable].CloseTable = TimeEvent;
        visitors.erase(it);
    }
    cout << TimeEvent.ShowTime() << " 11 " << ObjectEvent <<  endl;
}

void club::ID_12(TM TimeEvent, string ObjectEvent, int NumberTable){
    waiting.erase(waiting.begin());
    cout << TimeEvent.ShowTime() << " 12 " << ObjectEvent << " " << NumberTable + 1 << endl;
}

void club::ID_13(TM TimeEvent, string messeage){
    cout << TimeEvent.ShowTime() << " 13 " << messeage << endl;
}
