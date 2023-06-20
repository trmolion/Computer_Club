#include <fstream>
#include "club.h"
#include "time.h"
#include "visitor_table.h" 

int CheckFlag(int flag, string StrWithError);

int main (int argc, char* argv[]){
    ifstream input;
    if (argc > 1){
        input.open(argv[1], ios_base::in);
        if (!input.is_open()){
            cout << "Error read from file!\n"; 
            perror("Error");
            return 1;
        }
    }
    else {
        cout << "\n\tERROR: \n\t \tNot exist argument Command Line" << endl;
        return 1;
    }
    
    int QuantityTables = -1, PriceHour = -1;
    string buffer;
    TM OpenClub, CloseClub, pasttime;

    club tess;
    int i = 0;
    while (getline(input, buffer)){
        if (buffer.size() <= 0) continue;
        istringstream regist (buffer);
        string token;
        if (i == 0) QuantityTables = atoi (buffer.c_str());
        if (i == 1){
            istringstream buffer_2 (buffer);
            int j = 0;
            while (getline(buffer_2, buffer, ' ')) {
                if (j == 0) OpenClub.ReadTime(buffer);
                if (j == 1) CloseClub.ReadTime(buffer);
                j++;
            } 
        }
        if (i == 2) { 
            PriceHour = atoi(buffer.c_str());
            tess.inputclub(QuantityTables, OpenClub, CloseClub, PriceHour);
        }
        if (i >= 3) {
            int code = 0, numberT = 0;
            int flag = 0;
            string object;
            TM time;
            int j = 0;
            while (getline(regist, token, ' ')){
                if (j == 0){
                    if(time.ReadTime(token)){
                       flag = 4;
                       break; 
                    } 
                    if (time.ComparisonTime(CloseClub)){
                        flag = 2;
                        break;
                    } 
                    if (i == 3) pasttime = time;
                    else if (!time.ComparisonTime(pasttime)){
                        flag = 1;
                        break;
                    } 
                    else pasttime = time;
                }
                if (j == 1) if(!(code = atoi(token.c_str()))){
                   flag = 5; 
                   break;
                } 
                if (j == 2) object = token;
                if (j == 3){
                    numberT = atoi(token.c_str());
                    if ((numberT > QuantityTables) || (numberT <= 0)){
                        flag = 3;
                        break;
                    }
                }
                j++;
            }
            if(flag){
                CheckFlag(flag, buffer);
                input.close();
                return 0;
            } 
            else tess.IncomingEvents(time, code, object, numberT - 1);
        }
        i++;
    }
    if (input.get() == EOF) tess.CloseClub();
    input.close();
    return 0;
}

int CheckFlag(int flag, string StrWithError){
    cout << StrWithError << endl;
    switch (flag)
    {
    case 0:
        return 0;
    case 1:
        cout << "\n\tERROR: \n\t THERE IS NOT A TIMELINE!" << endl;
        return 1;
    case 2:
        cout << "\n\tERROR: \n\t TIME CLOSE UP!" << endl;
        return 2;
    case 3:
        cout << "\n\tERROR: \n\t THERE IS NO SUCH TABLE!" << endl;
        return 3;
    case 4:
        cout << "\n\tERROR: \n\t INCORRECT TIME FORMAT!" << endl;
        return 4;
    case 5:
        cout << "\n\tERROR: \n\t NON-EXIST ID PROCESS!\n" << endl;
        return 5;
    default:
        return 8;
    }
}