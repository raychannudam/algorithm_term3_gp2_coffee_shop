#include<iostream>
#include"Linklist.h"
#include"Get_menu.h"
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctime>
#include<windows.h>
#include<iomanip>
#include"Udam.h"
using namespace std;
int compareFunction(string s1, string s2){
    int x = s1.compare(s2);
    if (x != 0){
            return 0;
        if (x > 0)
            return 0;
        else
            return 0;
    }
    else
        return 1;
}
void pre(int tab){
    for(int i=0;i<tab;i++)
    cout<<"\t";
}
int insert_random(int low,int high){
        int num = (rand()%(high - low + 1)) + low;
        return num;
}
void printbill(){
    List *L;
    fstream file("random.txt",ios::app);
    srand(time(0));
    time_t ttime=time(0);
    tm* local_time = localtime(&ttime);
    int line;
    int t = insert_random(1,10000);
    file<<t<<" ";
    while(!file.eof()){
        file>>line;
        if(line==t)
        printbill();
        else break;
    }
    cout<<left<<"Date : "<<local_time->tm_mday<<"/"<<1 + local_time->tm_mon<<"/"<<1900 + local_time->tm_year<<"\t\t\t"<<"Time : "<<local_time->tm_hour<<":"<<local_time->tm_min<<":"<<local_time->tm_sec << endl;
    cout<<"Payment ID : "<<t<<"\n";
    cout<<"You Have Been order\n";
}
void Admin_panel(){
    List *L;
    L=emptylist();
    ifstream file("Admin-info.txt");
    ifstream history("History.txt",ios::app);
    ofstream coffee_list("Coffee-List.txt",ios::app);
    string username,password,user_file,user_pass;
    string no[50],coffeename[50],price[50],quantity[50];
    string num,name,price_1;
    int tmp=0,l=0,k=1;
    float total;
    system("cls");pre(2);cout<<"---Admin Panel ----\n";
    cout<<"\tEnter your username : ";
    cin>>username;
    cout<<"\tEnter Password : ";
    cin>>password;
    while(!file.eof()){
        getline(file,user_file);
        getline(file,user_pass);
        if(compareFunction(username,user_file) && compareFunction(password,user_pass)){
            do{
                system("cls");
                adminchoise:
                cout<<"==> Main-Menu 0\n";
                pre(2);cout<<"---- Admin Panel option ----\n";
                cout<<"1. Total Cash \n";
                cout<<"2. Add Coffee Item\n";
                cout<<"3. Delete Item\n";
                cout<<"4. Update Item\n";
                cout<<"5. View Menu\n";
                cout<<"6. Update admin detail\n";
                cout<<"7. View Report\n";
                cout<<"8. View Employee\n";
                cout<<"9. Exit\n";
                cout<<"Input 1-9 : ";
                int adminchoise;
                fflush(stdin); cin>>adminchoise;
                        if(adminchoise>=1 && adminchoise<=9){
                            tmp=0;
                            if(adminchoise==1){
                                while(!history.eof()){
                                    history>>no[l]; history>>coffeename[l]; history>>price[l]; history>>quantity[l];
                                    l++;
                                }
                                for(int j=0;j<l-1;j++)
                                    total += stof(price[j])*stoi(quantity[j]);
                                system("cls");pre(2);cout<<"Total Cash : "<<total<<"$\n";
                                Sleep(3000);
                                system("cls");
                                goto adminchoise;
                            }
                            if(adminchoise==2){
                                int t=0,item;
                                system("cls");
                                addcoffee:
                                    cout<<"\t"<<"--->Your menu<---\n";
                                    cout<<"No\tItem-Name\tPrice\n";
                                    getmenu();
                                    cout<<"\nYou're now adding new item to this above menu\n";
                                    cout<<"\nEnter No : "; cin>>num;
                                    cout<<"Enter Item-Name : "; cin>>name;
                                    cout<<"Enter Price : "; cin>>price_1;
                                    cout<<"You about to add this Item to the list, Press 1 to confirm : "; cin>>t;
                                    if(t==1){
                                        coffee_list.is_open();
                                        coffee_list<<"\n"<<num<<" ";
                                        coffee_list<<name<<" ";
                                        coffee_list<<price_1<<"$";
                                        coffee_list.close();
                                        system("cls");
                                    }else system("cls");goto adminchoise;
                                    cout<<"Add another item ?. 1-Yes , 0-No : ";cin>>item;
                                    if(item==1){
                                        system("cls");
                                        goto addcoffee;
                                    }else{
                                    system("cls");goto adminchoise;
                                    }
                            }
                            if(adminchoise==3){
                                fstream list_coffee;
                                list_coffee.open("Coffee-List.txt");
                                int id[50],i=0,t=0;
                                string coffee_name[50],price_delete[50];
                                while (!list_coffee.eof())
                                {
                                    list_coffee>>id[i];
                                    list_coffee>>coffee_name[i];
                                    list_coffee>>price_delete[i];
                                    i++;
                                }list_coffee.close();
                                cout<<"Enter No of item that you want to delete : \n";
                                cin>>t;
                                fstream delete_;
                                delete_.open("Coffe-List.txt",ios::out);
                                for(int l=0;l<i;l++){
                                    if(l==t-1){
                                    list_coffee<<id[l+1];
                                    list_coffee<<coffee_name[l+1];
                                    list_coffee<<price_delete[l+1];
                                    }else{
                                        list_coffee<<id[l];
                                        list_coffee<<coffee_name[l];
                                        list_coffee<<price_delete[l];
                                    }
                                }
                            }
                            if(adminchoise==4){

                            }
                            if(adminchoise==5){
                                system("cls");
                                getmenu();
                                Sleep(3000);system("cls");
                                goto adminchoise;
                            }
                            if(adminchoise==6){
                                string new_user,new_pass,old_user,old_pass,tmp_user;
                                int tem,i=0,counter=0;
                                fstream myfile;
                                myfile.open("Admin-info.txt");
                                string tmp_1[50],tmp_2[50];
                                while(!myfile.eof()){
                                        myfile>>tmp_1[i];
                                        myfile>>tmp_2[i];
                                        i++;
                                    }
                                myfile.close();
                                adminchange:
                                cout<<"1. Change Username\n";
                                cout<<"2. Change Password\n";
                                cout<<"Enter 1-2 and 0 to exit : ";cin>>tem;
                                if(tem==1){
                                    string info_user,info_pass;
                                    cout<<"You're about to change your username\n";
                                    cout<<"Enter your current Password : ";cin>>old_pass;
                                    for(int t=0;t<i;t++){
                                    if(compareFunction(old_pass,tmp_2[t])){
                                        cout<<"Enter new username : ";cin>>new_user;
                                        tmp_1[t]=new_user;
                                        tmp_2[t]=old_pass;
                                        counter=1;
                                        break;
                                        }else{counter=0;}
                                    }
                                    if(counter==1){
                                        cout<<"You Successfully change your username";
                                    }else if (counter==0){
                                        system("cls");cout<<"Incorrect Password\n";
                                        Sleep(3000); goto adminchange;
                                    }
                                    myfile.open("Admin-info.txt",ios::out);
                                    myfile.clear();
                                    for(int k=0;k<i;k++){
                                        myfile<<tmp_1[k]<<endl;
                                        myfile<<tmp_2[k]<<endl;
                                    }myfile.close();
                                }else if(tem==2){
                                    string info_user,info_pass;
                                    cout<<"You're about to change your Password\n";
                                    cout<<"Enter your current Password : ";cin>>old_pass;
                                    for(int t=0;t<i;t++){
                                    if(compareFunction(old_pass,tmp_2[t])){
                                        cout<<"Enter new Password : ";cin>>new_pass;
                                        tmp_2[t]=new_pass;
                                        counter=1;
                                        break;
                                        }else{counter=0;}
                                    }
                                    if(counter==1){
                                        cout<<"You Successfully change your username";
                                    }else if (counter==0){
                                        system("cls");cout<<"Incorrect Password\n";
                                        Sleep(3000); goto adminchange;
                                    }
                                    myfile.open("Admin-info.txt",ios::out);
                                    myfile.clear();
                                    for(int k=0;k<i;k++){
                                        myfile<<tmp_1[k]<<endl;
                                        myfile<<tmp_2[k]<<endl;
                                    }myfile.close();
                                }
                            }
                            if(adminchoise==7){
                                int option;
                                cout<<"Select your option: ";
                                cout<<"Type 1 to get report by date, type 2 to get all report.";
                                cin>>option;
                                string date;
                                switch (option)
                                {
                                case 1:
                                    cout<<"Enter date: ";
                                    cin>>date;
                                    int *result = getReportByDate("History.txt", date);
                                    break;
                                case 2:
                                    getAllReport("History.txt");
                                    int *result;
                                    break;
                                default:
                                    cout<<"Error!";
                                    break;
                                }
                            }
                            if(adminchoise==8){
                                fstream employee;
                                string name[500],tmp[500];
                                int i=0;
                                employee.open("Employee-info.txt");
                                while(!employee.eof()){
                                    employee>>name[i];
                                    employee>>tmp[i];
                                    i++;
                                }
                                system("cls");
                                cout<<"\t\t---- Employee Name ----\n";
                                for(int t=0;t<i;t++){
                                    cout<<"\t"<<name[t]<<"\n";
                                }
                                Sleep(3000);system("cls");
                                goto adminchoise;
                            }
                            if(adminchoise==9) k=0;
                        }
                        else{
                                tmp=1;
                                cout<<"Wrong input try again";
                            }
            }while(k!=0);
        }
    }
}
void Employee_panel(){
    List *L;
    L=emptylist();
    ifstream file ("Employee-info.txt");
    ifstream file_menu ("Coffee-List.txt");
    ofstream history ("History.txt",ios::app);
    ifstream outfile("History.txt");
    string username,user_file,password,user_pass,order_file;
    int quantity,order_no,payment;
    double total;
    int confirm=0,exit=1,p,t=0;
    string no[50],coffename[50],price[50];
    do{
        employee:
    cout<<"==> 0 Back \n";
    pre(2);cout<<"---- Employee Panel option ----\n\n";
    cout<<"\t1. Login and Place order\n";
    cout<<"\t2. Sign up\n\n";
    cout<<"Input 1-0 : ";
    cin>>t;
        if(t==1){
            system("cls");
            cout<<"==> 0 Back \n";
            pre(2);cout<<"---- Employee Login Panel ----\n";
            cout<<"\n\tEnter your username : ";
            cin>>username;
            if(username=="0" || password=="0"){system("cls");goto employee;}
            cout<<"\tEnter Password : ";
            cin>>password;
            system("cls");
            if(password=="0"){system("cls");goto employee;}
            while(!file.eof()){
                getline(file,user_file);
                getline(file,user_pass);
                file.close();
                if(compareFunction(username,user_file) && compareFunction(password,user_pass)){
                    do{
                        order:
                        cout<<"==> 0 Back \n";
                        cout<<"\t\tNo\tItem-Name\tPrice\n";
                        getmenu();
                        do{
                            cout<<"\n\tPlace order : "; cin>>order_no;
                            cout<<"\tEnter the Quantity : "; cin>>quantity;
                            int i=0;
                            if(order_no==0){system("cls");goto employee;}
                                while(!file_menu.eof()){
                                    file_menu>>no[i]; file_menu>>coffename[i]; file_menu>>price[i];
                                    i++;
                                }
                                addinfo(L,stoi(no[order_no-1]),coffename[order_no-1],stof(price[order_no-1]),quantity);
                                total += stof(price[order_no-1])*quantity;
                                cout<<"Enter 1 To Place more order and 0 to finish order : ";
                                cin>>p;
                                if(p==1){
                                system("cls");goto order;}
                        }while(p!=0);
                            system("cls");
                            display_coffeeinfo(L);    
                            cout<<"\nTotal : "<<total<<"$"<<endl;
                            order_no=0;
                            cout<<"\nEnter number 1 to confirm order and 0 back to menu : "; cin>>confirm;
                            if(confirm==0){
                                system("cls");goto order;
                            }
                            if(confirm==1){
                                    int t;
                                    cout<<"\tOrder Complete waiting to be serve\n";
                                    cout<<"Press any number to Print the customer Invoice and 1 to skip : ";
                                    cin>>t;
                                    system("cls");
                                    if(t!=1){
                                        printbill();
                                        display_coffeeinfo(L);
                                        cout<<"\nTotal : "<<total<<"$\n";
                                    }
                                    history<<no[order_no-1];
                                    history<<coffename[order_no-1];
                                    history<<price[order_no-1];
                                    history<<quantity;
                                    delete_all(L);
                                    loop:
                                    do{
                                        cout<<"\nEnter 0 Back to main menu and 1 Logout : ";
                                        cin>>exit;
                                        system("cls");
                                        if(exit!=1 && exit!=0) cout<<"Wrong input";
                                        else if(exit==1) break;
                                    }while(exit!=0);
                            }else{cout<<"\tOrder not complete\n";total=0;delete_all(L);goto loop;}
                        
                    }while(exit!=1);
                }else{
                Employee_panel();
                }
            }
        }else if(t==2){
            system("cls");
            string name_employee,password_employee;
            cout<<"==> 0 Back\n";
            cout<<"\t\t---- Sign up Panel ----\n\n";
            cout<<"Enter Username : ";
            cin>>name_employee;
            if(name_employee=="0" || password_employee=="0" ) {system("cls"); goto employee;}
            else{
                int i=0,counter=0;
                string arr1[50],arr2[50];
                fstream employee;
                employee.open("Employee-info.txt",ios::out);
                while(!employee.eof()){
                    employee>>arr1[i];
                    employee>>arr2[i];
                    i++;
                }employee.close();
                check:
                for(int t=0;t<i;t++){
                    if(compareFunction(name_employee,arr1[t])){
                        counter=1;
                        break;
                    }
                    else counter=0;
                }
                if(counter==1){
                    system("cls");
                    cout<<"\t\tThis username is already exist\n";
                    cout<<"\n\n\t\tEnter new username : ";
                    cin>>name_employee;
                    goto check;
                }else{cout<<"Enter Password : ";
                    cin>>password_employee;
                    system("cls");
                    cout<<"\n\n\n\tSign up Success ! \n";
                    Sleep(2000);
                    system("cls");
                }
                employee.open("Employee-info.txt",ios::app);
                employee<<name_employee<<endl;
                employee<<password_employee<<endl;
                employee.close();
            }
        }else if(t==0) system("cls");
        else cout<<"Wrong input";
    }while(t!=0);
}
int main(){
    int t;
    do{
        choich:
    cout<<"\t----- Welcome to Our coffee Management System -----\n\n";
    cout<<"\t1. Employee Panel\n";
    cout<<"\t2. Admin Panel\n";
    cout<<"\t3. Exit to Program\n";
    cout<<"\nInput 1-3 : ";
    cin>>t;
        if(t==1){
            system("cls");
            Employee_panel();
        }
        else if(t==2){
            system("cls");
            Admin_panel();
        }
        else if(t==3){
            system("cls");
            cout<<"\t\tThank for using our Program ";
            break;
        }
        else{
            system("cls");
            cout<<"Wrong Input";
            Sleep(3000);
            goto choich;
        }
    }while(t!=3);
}