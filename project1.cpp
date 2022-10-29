#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
    


int main(){
    string name = "properties.txt";
    string line;
    string address_name;
    pro Prop;
    int tenants;
    char arrs[5][7];
    int counter = 0;
    int month = 0;
    char inp;
    vector<pro> props;
    vector<pro> only_address;
    ifstream fin(name);
    if(!fin.is_open()){
        cout << "Hey";
        return -999;
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
        fin.ignore();
        getline(fin, line);
    }

    cout << "Enter your address. " << endl;
    int size = props.size();
    getline(cin, address_name);
    for(int co = 0; co < size; co++){
        if(props.at(co).address.find(address_name) != string::npos){
            only_address.push_back(props.at(co));
        }
    }
    cin >> inp;
    while(inp != 'q'){
        createMonth(arrs);
        cin >> month;
        for(int c = 0; c < only_address.size(); c++){
            if(only_address.at(c).start_month == month){
                updateMonth(arrs, only_address.at(c).start_day, only_address.at(c).end_day);
            }
        }
        
        /*createMonth(arrs);
        updateMonth(arrs, 5, 9);
        updateMonth(arrs, 12, 17);8*/
        
        for(int x = 0; x < 4; x++){
            for(int xa = 0; xa < 7; xa++){
                cout << arrs[x][xa] << " ";
            }
            cout << endl;
        }
        for(int b = 0; b < 3; b++){
            cout << arrs[4][b] << " ";
        }
        cin >> inp;
    }
    return 0;
}