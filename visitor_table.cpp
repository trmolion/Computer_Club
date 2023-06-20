#include "visitor_table.h"

int Table::SummTime(){
        int counter = 0;
        WorkTime = OpenTable.CalculationTime(CloseTable);
        if (WorkTime.minutes > 0) counter = WorkTime.hour + 1;
        else counter = WorkTime.hour;
        return counter;
}
