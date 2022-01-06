#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;
int getmenu(){
    string line;
    ifstream myfile("Coffee-List.txt");
    int i=0;
    string no[50],coffeename[50],price[50];
    if(myfile.is_open()){
        while(!myfile.eof()){
            myfile>>no[i];
            myfile>>coffeename[i];
            myfile>>price[i];
            cout<<"\t\t"<<left<<setw(5)<<no[i]<<setw(20)<<coffeename[i]<<setw(15)<<price[i]<<"\n";
        }
        myfile.close();
    }
}