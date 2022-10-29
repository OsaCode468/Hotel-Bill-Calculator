#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct pro{
string address;
double price;
int start_month;
int start_day;
int end_month;
int end_day;
};

void createMonth(char arr[5][7]){
    for(int x = 0; x < 4; x++){
            for(int xa = 0; xa < 7; xa++){
                arr[x][xa] = '*';
            }
        }
        for(int b = 0; b < 3; b++){
            arr[4][b] = '*';
        }
}

void updateMonth(char arr[5][7], int start_d, int end_d){
    int counter = 1;
    for(int x = 0; x < 4; x++){
            for(int xa = 0; xa < 7; xa++){
                if(counter >= start_d && counter <= end_d){
                    if(counter % 7 == 0 || (counter - 1) % 7 == 0){
                        arr[x][xa] = 'D';
                        counter++;
                    }
                    else{
                    arr[x][xa] = 'B';
                    counter++;
                    }
                }
                else{
                    counter++;
                }
            }
        }
        for(int b = 0; b < 3; b++){
            if(counter >= start_d && counter <= end_d){
                    if(counter % 7 == 0 || (counter - 1) % 7 == 0){
                        arr[4][b] = 'D';
                        counter++;
                    }
                    else{
                    arr[4][b] = 'B';
                    counter++;
                    }
                }
                else{
                    counter++;
                }
            }
        }
    
void printMonth(char arr[5][7]){
    for(int x = 0; x < 4; x++){
                for(int xa = 0; xa < 7; xa++){
                    cout << arr[x][xa] << " ";
                }
                cout << endl;
            }
            for(int b = 0; b < 2; b++){
                cout << arr[4][b] << " ";
            }
            cout << arr[4][2];
            cout << endl;
        }
double getTotal(char arr[5][7], double prices){
    int d = 0;
    int b = 0;
    double total = 0;
     for(int x = 0; x < 4; x++){
            for(int xa = 0; xa < 7; xa++){
                if(arr[x][xa] == 'B'){
                    b++;
                }
                if(arr[x][xa] == 'D'){
                    d++;
                }
            }
        }
        for(int ba = 0; ba < 3; ba++){
            if(arr[4][ba] == 'B'){
                b++;
            }
            if(arr[4][ba] == 'D'){
                d++;
            }
        }
    total = ((b * prices) + (2 * (d * prices)));
    return total;
}
int main(){
    string name = "properties.txt";
    string line;
    string address_name = "hi";
    bool cond = true;
    bool cond2 = true;
    pro Prop;
    int tenants;
    char arrs[5][7];
    string months[12] = {"January" , "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int counter = 0;
    int other_counter = 0;
    int month = 0;
    int month_counter = 0;
    int s_m, s_d, e_m, e_d;
    double total = 0;
    double argus_price = 0;
    char inp = 'k';
    vector<pro> props;
    vector<pro> only_address;
    ifstream fin(name);
    ofstream fout("yearly.txt");
    cout << setprecision(2) << fixed;
    fout << setprecision(2) << fixed;
    if(!fin.is_open()){
        cout << "Hey";
        return 123;
    }
    while(!fin.eof()){
        getline(fin, Prop.address);
        fin >> Prop.price;
        fin >> tenants;
        for(int x = 0; x < tenants; x++){
            fin >> Prop.start_month;
            fin >> Prop.start_day;
            fin >> Prop.end_month;
            fin >> Prop.end_day;  
            props.push_back(Prop); 
        }
        fin.ignore(1, '\n');
        getline(fin, line);
    }
    
    while(address_name != "exit"){
        cout << "Enter the address of the property you want to book or exit to exit:" << endl;
        int size = props.size();
        getline(cin, address_name);
        if(address_name == "exit"){
            break;
        }
        ///cout << address_name << endl;
        for(int co = 0; co < size; co++){
            if(props.at(co).address.find(address_name) != string::npos){
                only_address.push_back(props.at(co));
            }
        }
        while(inp!='q'){
            other_counter = 0;
            cout << "Enter an option:" << endl;
            cout << "1. Show the calendar of the property on a given month" << endl;
            cout << "2. Book a period of time for a given property" << endl;
            cout << "q. Quit" << endl;
            cin >> inp;
            ///cout << inp << endl;
            if(inp == 'q'){
                cond2 = false;
                break;
            }
            else if(inp == '1'){
            createMonth(arrs);
            cout << "Enter the month number:" << endl;
            cin >> month;
            int counts = only_address.size();
            if(month > 0 && month < 13){
                for(int c = 0; c < counts; c++){
                    if(only_address.at(c).start_month == month){
                        updateMonth(arrs, only_address.at(c).start_day, only_address.at(c).end_day);
                    }
                }
                printMonth(arrs);
                cout << endl;
            }
            else{
                cout << "Invalid month number" << endl;
            }
                                                        }
            else if(inp == '2'){
                cond = true;
                cout << "Enter the start month and day:" << endl;
                cin >> s_m >> s_d;
                cout << "Enter the end month and day:" << endl;
                cin >> e_m >> e_d;
                if(s_m <= 0 || s_m > 12  || e_m <= 0 || e_m > 12){
                    cout << "Invalid month number" << endl;
                    cond2 = false;
                }
                else if(s_d <= 0 || s_d > 31  || e_d <= 0 || e_d > 31){
                    cout << "Invalid day number" << endl;
                    cond2 = false;
                }
                int counts = only_address.size();

                for(int c = 0; c < counts; c++){
                if(only_address.at(c).start_month == s_m){
                    if((only_address.at(c).start_day <= s_d && only_address.at(c).end_day >= s_d) || (only_address.at(c).start_day <= e_d && only_address.at(c).end_day >= e_d)){
                        cond = false;
                        cout << "Date range has dates that are already booked!" << endl;
                    }
                }
            }
            if(cond == true && cond2 == true){
                cout << "Booked!" << endl; 
                Prop.address= only_address.at(0).address;
                Prop.price = only_address.at(0).price;
                Prop.start_month = s_m;
                Prop.start_day = s_d;
                Prop.end_month = e_m;
                Prop.end_day = e_d;
                only_address.push_back(Prop);
                props.push_back(Prop);
            }
            }
            else{
                cout << "Invalid option" << endl;
            }
        }
        cin.ignore(1, '\n');
        inp = 'j';
    }

    fout << "Address: Argus Street 12311" << endl;
    for(int x = 0; x < 12; x++){
        createMonth(arrs);
        for(int xa = 0; xa < props.size(); xa++){
            if(props.at(xa).address.find("Argus") != string::npos){
                argus_price = props.at(xa).price;
                if(props.at(xa).start_month == x + 1){
                    updateMonth(arrs, props.at(xa).start_day, props.at(xa).end_day);
                    month_counter++;
                }
            }
        }
        if(month_counter > 0){
        fout << months[x] << ": " << getTotal(arrs, argus_price) << endl;
        for(int x = 0; x < 4; x++){
                for(int xa = 0; xa < 7; xa++){
                    fout << arrs[x][xa] << " ";
                }
                fout << endl;
            }
            for(int b = 0; b < 2; b++){
                fout << arrs[4][b] << " ";
            }
            fout << arrs[4][2];
            fout << endl;
            fout << endl;
        ///fout << getTotal(arrs, argus_price) << endl;
        total += getTotal(arrs, argus_price);
        }
        month_counter = 0;
    }
    
    fout << "Total: $" << total << endl;
    fout << endl;
    total = 0;
 
    fout << "Address: Valentine Lane 21422" << endl;
    for(int x = 0; x < 12; x++){
        createMonth(arrs);
        for(int xa = 0; xa < props.size(); xa++){
            if(props.at(xa).address.find("Valentine") != string::npos){
                argus_price = props.at(xa).price;
                if(props.at(xa).start_month == x + 1){
                    updateMonth(arrs, props.at(xa).start_day, props.at(xa).end_day);
                    month_counter++;
                }
            }
        }
        if(month_counter > 0){
        fout << months[x] << ": " << getTotal(arrs, argus_price) << endl;
        for(int x = 0; x < 4; x++){
                for(int xa = 0; xa < 7; xa++){
                    fout << arrs[x][xa] << " ";
                }
                fout << endl;
            }
            for(int b = 0; b < 2; b++){
                fout << arrs[4][b] << " ";
            }
            fout << arrs[4][2];
            fout << endl;
            fout << endl;
        ///fout << getTotal(arrs, argus_price) << endl;
        total += getTotal(arrs, argus_price);
        }
        month_counter = 0;
    }

    fout << "Total: $" << total << endl;
    fout << endl;
    total = 0;
 
    fout << "Address: Agnus Dr. 12311" << endl;
    for(int x = 0; x < 12; x++){
        createMonth(arrs);
        for(int xa = 0; xa < props.size(); xa++){
            if(props.at(xa).address.find("Agnus") != string::npos){
                argus_price = props.at(xa).price;
                if(props.at(xa).start_month == x + 1){
                    updateMonth(arrs, props.at(xa).start_day, props.at(xa).end_day);
                    month_counter++;
                }
            }
        }
        if(month_counter > 0){
        fout << months[x] << ": " << getTotal(arrs, argus_price) << endl;
        for(int x = 0; x < 4; x++){
                for(int xa = 0; xa < 7; xa++){
                    fout << arrs[x][xa] << " ";
                }
                fout << endl;
            }
            for(int b = 0; b < 2; b++){
                fout << arrs[4][b] << " ";
            }
            fout << arrs[4][2];
            fout << endl;
            fout << endl;
        ///fout << getTotal(arrs, argus_price) << endl;
        total += getTotal(arrs, argus_price);
        }
        month_counter = 0;
    }
    
    fout << "Total: $" << total << endl;
    fout << endl;
    total = 0;
    fout << "Address: Cullen Rd 6790" << endl;
    for(int x = 0; x < 12; x++){
        createMonth(arrs);
        for(int xa = 0; xa < props.size(); xa++){
            if(props.at(xa).address.find("Cullen") != string::npos){
                argus_price = props.at(xa).price;
                if(props.at(xa).start_month == x + 1){
                    updateMonth(arrs, props.at(xa).start_day, props.at(xa).end_day);
                    month_counter++;
                }
            }
        }
        if(month_counter > 0){
        fout << months[x]  << ": " << getTotal(arrs, argus_price) << endl;
        for(int x = 0; x < 4; x++){
                for(int xa = 0; xa < 7; xa++){
                    fout << arrs[x][xa] << " ";
                }
                fout << endl;
            }
            for(int b = 0; b < 2; b++){
                fout << arrs[4][b] << " ";
            }
            fout << arrs[4][2];
            fout << endl;
            fout << endl;
        ///fout << getTotal(arrs, argus_price) << endl;
        total += getTotal(arrs, argus_price);
        }
        month_counter = 0;
    }
    fout << "Total: $" << total << endl;
    fout << endl;
    fin.close();
    fout.close();
    return 0;
}