#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
struct coffeeinfo
{
    int no;
    string coffee_name;
    float price;
    int quantity;
    coffeeinfo *next;
};
struct List
{
    int n;
    coffeeinfo *top;
    coffeeinfo *bot;
};
List* emptylist(){
    List *ls;
    ls=new List();
    ls->n=0;
    ls->top = NULL;
    ls->bot = NULL;
    return ls;
}
void addinfo(List *ls, int newno, string newcoffee_name, float newprice,int newquantity){
    coffeeinfo *e;
    ofstream file("History.txt",ios::app);
        file<<newno<<" ";
        file<<newcoffee_name<<" ";
        file<<newprice<<" ";
        file<<newquantity<<" ";
        file<<newprice*newquantity<<" ";
        file<<date<<"\n";
    e=new coffeeinfo();
    e->no=newno;
    e->coffee_name=newcoffee_name;
    e->price=newprice;
    e->quantity=newquantity;
    e->next = ls->top;
    ls->top = e;
    if(ls->n==0)
    ls->bot=e;
    ls->n = ls->n + 1;
}
void display_coffeeinfo(List *ls){
    coffeeinfo *tmp;
    tmp=ls->top;
    cout<<left<<setw(5)<<"No"<<setw(20)<<"Item-Name"<<setw(15)<<"Price($)"<<setw(8)<<"Quantity"<<"\n";
    while (tmp!=NULL){
        cout<<left<<setw(5)<<tmp->no<<setw(20)<<tmp->coffee_name<<setw(15)<<tmp->price<<setw(8)<<tmp->quantity<<"\n";
        tmp=tmp->next;
    }
}
// void insert_end(List *ls,int endno,string endcoffee_name,float endprice,int endquantity){
//     if(ls->n==0){
//         addinfo(ls, endno,endcoffee_name,endprice,endquantity);
//     }else{
//         coffeeinfo *e;
//         e=new coffeeinfo();
//         e->no=endno;
//         e->coffee_name=endcoffee_name;
//         e->price=endprice;
//         e->quantity=endquantity;
//         e->next=NULL;

//         ls->bot->next=e;
//         ls->bot=e;
//         ls->n=ls->n+1;
//     }
// }
void delete_be(List* ls){
    coffeeinfo *tmp;
    tmp=ls->top;
    ls->top = ls->top->next;
    delete tmp;
    if(ls->n==1)
    ls->bot=NULL;
    ls->n = ls->n-1;
}
void delete_all(List* ls){
    while (ls->n>0)
    {
        delete_be(ls);
    }
    
}
// void delete_spec(List* a,int i){
//     coffeeinfo *tmp;
//     while(tmp!=NULL){
//         if(tmp->no == i){
//             tmp = tmp->next->next;
//         }
//         tmp=tmp->next;
//     }
// }
void search(List *ls,int x,string y,int z,int l){
    coffeeinfo *tp;
    tp=ls->top;
    int c=0;
    while(tp!=NULL){
        if(tp->no==x){
            c=c+1;
        }
        tp=tp->next;
    }
    if(c==0)
    cout<<"NO FOUND";
    else
    cout<<"FOUND "<<c<<"";
}


