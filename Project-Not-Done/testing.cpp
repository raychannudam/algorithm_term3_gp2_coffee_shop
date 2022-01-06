#include <iostream>
#include <fstream>

using namespace std;

struct OrderItem{
    string itemId;
    string itemTitle;
    float itemPrice=0;
    float itemQuantity=0;
    float itemTotalPrice=0;
    string orderDate;
};

struct Item{
    string itemId;
    string itemTitle;
    float itemPrice;
};

//return a int number
int countLine(string filename){
    int numberOfLine=0;
    string id, title, orderDate;
    float price, quantity, totalPrice;
    fstream file;
    file.open(filename, ios::in);
    while (!file.eof())
    {
        file>>id>>title>>price>>quantity>>totalPrice>>orderDate;
        numberOfLine = numberOfLine + 1;
    }
    file.close();
    return numberOfLine;
}

int countLineInItemFile(string filename){
    int numberOfLine=0;
    string id, title;
    float price;
    fstream file;
    file.open(filename, ios::in);
    while (!file.eof())
    {
        file>>id>>title>>price;
        numberOfLine = numberOfLine + 1;
    }
    file.close();
    return numberOfLine;
}

//return array of object
OrderItem* readFromFile(string filename, int index){
    OrderItem* output = new OrderItem[index];
    string id, title, orderDate;
    float price, quantity, totalPrice;
    int counter = 0;
    fstream file;
    file.open(filename, ios::in);
    while (!file.eof())
    {
        file>>id>>title>>price>>quantity>>totalPrice>>orderDate;
        output[counter].itemId = id;
        output[counter].itemTitle = title;
        output[counter].itemPrice = price;
        output[counter].itemQuantity = quantity;
        output[counter].itemTotalPrice = totalPrice;
        output[counter].orderDate = orderDate;
        counter+=1;
    }
    file.close();
    return output;
}

//return array of item
Item* readFromFileItem(string filename, int index){
    Item *itemList = new Item[index];
    fstream file;
    file.open(filename, ios::in);
    string id, title;
    int counter = 0;
    float price;
    while(!file.eof()){
        file>>id>>title>>price;
        itemList[counter].itemId = id;
        itemList[counter].itemTitle = title;
        itemList[counter].itemPrice = price;
        counter+=1;
    }
    return itemList;
}

//return true or false
bool isFileExisted(string filename){
    fstream file;
    file.open(filename);
    if(file.is_open()){
        file.close();
        return true;
    }
    file.close();
    return false;
}

//after excecute return true or false
//orderitem
bool generateReport(string filename, OrderItem orderItem){
    fstream file;
    file.open(filename, ios::out);
    file<<endl<<orderItem.itemId<<" "<<orderItem.itemTitle<<" "<<orderItem.itemPrice<<" "<<orderItem.itemQuantity<<" "<<orderItem.itemTotalPrice<<" "<<orderItem.orderDate;
    file.close();
    return true;
}

//after excecute return true or false
bool updateReport(string filename, OrderItem orderItem){
    if(!isFileExisted(filename)){
        cout<<"file is not existed. generating..."<<endl;
        bool isGenerated = generateReport(filename, orderItem);
        cout<<"Completed!"<<endl;
        return isGenerated;
    }else{

        cout<<"file is existed"<<endl;
        //count number of index
        int index = countLine(filename);
        cout<<"found: "<<index<<" index."<<endl;

        //copy from file to a list
        OrderItem *orderItemList;
        orderItemList = readFromFile(filename, index);
        cout<<"copyed from file to a list..."<<endl;

        //adding new element to a list - copy to temporary list
        int newIndex = index+1;
        OrderItem tempOrderItemList[newIndex];
        for(int i=0; i<index; i++){
            tempOrderItemList[i].itemId = orderItemList[i].itemId;
            tempOrderItemList[i].itemTitle = orderItemList[i].itemTitle;
            tempOrderItemList[i].itemPrice = orderItemList[i].itemPrice;
            tempOrderItemList[i].itemQuantity = orderItemList[i].itemQuantity;
            tempOrderItemList[i].itemTotalPrice = orderItemList[i].itemTotalPrice;
            tempOrderItemList[i].orderDate = orderItemList[i].orderDate;
        }
        tempOrderItemList[index].itemId = orderItem.itemId;
        tempOrderItemList[index].itemTitle = orderItem.itemTitle;
        tempOrderItemList[index].itemPrice = orderItem.itemPrice;
        tempOrderItemList[index].itemQuantity = orderItem.itemQuantity;
        tempOrderItemList[index].itemTotalPrice = orderItem.itemTotalPrice;
        tempOrderItemList[index].orderDate = orderItem.orderDate;
        cout<<"adding new element to a list - copied to temporary list"<<endl;

        //copy back from a list into file
        fstream file;
        file.open(filename, ios::out);
        cout<<"copying back from a temp list into file"<<endl;
        for (int i=0; i<newIndex; i++){
            file<<endl<<tempOrderItemList[i].itemId<<" "<<tempOrderItemList[i].itemTitle<<" "<<tempOrderItemList[i].itemPrice<<" "<<tempOrderItemList[i].itemQuantity<<" "<<tempOrderItemList[i].itemTotalPrice<<" "<<tempOrderItemList[i].orderDate;
        }
        cout<<"Completed"<<endl;
        file.close();

    }
    return true;
}

//excecute and return arrray of int contiant 2 elements [totalQuantityByDate, totalProfitByDate]
int * getReportByDate(string filename, string date){

    cout<<"file is existed"<<endl;
    //count number of index
    int index = countLine(filename);
    cout<<"found: "<<index<<" index in total"<<endl;

    //copy from file to a list
    OrderItem *orderItemList;
    orderItemList = readFromFile(filename, index);
    cout<<"copyed from file to a list..."<<endl;

    //find number of index of the same date in file
    int dateIndex = 0;
    for (int i=0; i<index; i++){
        if (orderItemList[i].orderDate == date){
            dateIndex+=1;
        }
    }
    cout<<"found: "<<dateIndex<<" index that purchesed in date: "<<date<<endl;

    //copy the item in the same date in to nother list
    int counter=0;
    OrderItem orderItemListByDate[dateIndex];
    for (int i=0; i<index; i++){
        if(orderItemList[i].orderDate == date){
            orderItemListByDate[counter].itemId = orderItemList[i].itemId;
            orderItemListByDate[counter].itemTitle = orderItemList[i].itemTitle;
            orderItemListByDate[counter].itemPrice = orderItemList[i].itemPrice;
            orderItemListByDate[counter].itemQuantity = orderItemList[i].itemQuantity;
            orderItemListByDate[counter].itemTotalPrice = orderItemList[i].itemTotalPrice;
            orderItemListByDate[counter].orderDate = orderItemList[i].orderDate;
            counter+=1;
        }
    }
    cout<<"copied the item in the same date in to another list"<<endl;

    //calculate total profit all item by date
    int *output = new int[2];
    int totalQuanityByDate =0;
    float totalProfitByDate=0;
    for (int i=0; i<dateIndex; i++){
        totalQuanityByDate = totalQuanityByDate + orderItemListByDate[i].itemQuantity;
    }
    for (int i=0; i<dateIndex; i++){
        totalProfitByDate = totalProfitByDate + orderItemListByDate[i].itemTotalPrice;
    }
    // cout<<"Total Quanitiy By Date: "<<totalQuanityByDate<<" cups."<<endl;
    // cout<<"Total Profit By Date: "<<totalProfitByDate<<" dollars."<<endl;
    output[0] = totalQuanityByDate;
    output[1] = totalProfitByDate;
    return output;
}

//excecute and return arrray of int contiant 2 elements [totalQuantity, totalProfit]
int * getAllReport(string filename){

    cout<<"file is existed"<<endl;
    //count number of index
    int index = countLine(filename);
    cout<<"found: "<<index<<" index in total"<<endl;

    //copy from file to a list
    OrderItem *orderItemList;
    orderItemList = readFromFile(filename, index);
    cout<<"copyed from file to a list..."<<endl;

    //calculate total profit since the first order
    int *output = new int[2];
    int totalQuanity =0;
    float totalProfit=0;
    for (int i=0; i<index; i++){
        totalQuanity = totalQuanity + orderItemList[i].itemQuantity;
    }
    for (int i=0; i<index; i++){
        totalProfit = totalProfit + orderItemList[i].itemTotalPrice;
    }
    // cout<<"Total Quanitiy: "<<totalQuanity<<" cups."<<endl;
    // cout<<"Total Profit: "<<totalProfit<<" dollars."<<endl;
    output[0] = totalQuanity;
    output[1] = totalProfit;
    return output;
}

OrderItem* getReportByAllItem(string itemFilename, string historyFilename){

    int indexInHistory = countLine(historyFilename);

    OrderItem *orderItemList;
    orderItemList = readFromFile(historyFilename, indexInHistory);

    int indexInItem = countLineInItemFile(itemFilename);

    Item* itemList;
    itemList = readFromFileItem(itemFilename, indexInItem);

    OrderItem* orderItemList1 = new OrderItem[indexInItem];
    
    for(int i=0; i<indexInItem; i++){
        orderItemList1[i].itemId = itemList[i].itemId;
        orderItemList1[i].itemTitle = itemList[i].itemTitle;
        orderItemList1[i].itemPrice = itemList[i].itemPrice;
        orderItemList1[i].itemQuantity = 0;
        orderItemList1[i].itemTotalPrice = 0;
        orderItemList1[i].orderDate = "N/A";
    }

    for(int i=0; i<indexInItem; i++){
        int counter1 = 0;
        for(int j=0; j<indexInHistory; j++){
            if(itemList[i].itemId == orderItemList[j].itemId){
                orderItemList1[i].itemId = orderItemList[j].itemId;
                orderItemList1[i].itemTitle = orderItemList[j].itemTitle;
                orderItemList1[i].itemPrice = orderItemList[j].itemPrice;
                orderItemList1[i].itemQuantity = orderItemList1[i].itemQuantity + orderItemList[j].itemQuantity;
                orderItemList1[i].itemTotalPrice = orderItemList1[i].itemTotalPrice + orderItemList[j].itemTotalPrice;
            }
        }
    }

    return orderItemList1;


}

int main(){
    int index1 = countLineInItemFile("Coffee-List.txt");
    int index0 = countLine("History.txt");
    OrderItem *orderItemList;
    orderItemList = readFromFile("History.txt", index0);
    Item *itemList;
    itemList = readFromFileItem("Coffee-List.txt", index1);
    for(int i=0; i<index1; i++){
        cout<<itemList[i].itemId<<endl;
    }
    cout<<"---------"<<endl;
    for(int i=0; i<index0; i++){
        cout<<orderItemList[i].itemId<<endl;
    }
    cout<<"---------"<<endl;
    OrderItem *orderItemListReport;
    orderItemListReport = getReportByAllItem("Coffee-List.txt", "History.txt");
    for(int i=0; i<index1; i++){
        cout<<orderItemListReport[i].itemTitle<<" "<<orderItemListReport[i].itemQuantity<<" "<<orderItemListReport[i].itemTotalPrice<<endl;
    }
    return 0;
}