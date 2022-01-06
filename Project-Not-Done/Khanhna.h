
using namespace std;

struct Node{

    int CoffeeID;
    int data;

    Node *next;
};
struct List
{
    int n;

    Node *head;
    Node *tail;

};
List* CreateEmtylist()
{
    List *ls;
    ls = new List;

    ls -> n = 0;
    ls -> head = NULL;
    ls -> tail = NULL;

    return ls;
};
void writeData(List *ls)
{
    // Open file
    fstream file;
    file.open("dataHistory.txt", ios::out);
    if (!file)
    {
        cout << "File is not exist!" << endl;
    }
    else
    {
        Node *e;
        e = ls->head;
        while (e != NULL)
        {
            file <<"\n"<<"ID product "<<"  "<<"Number of cup"<<endl;
            file << e->CoffeeID << "\t\t" << e->data;
            e = e->next;
            if (e != NULL){
                file<<"\n";
            }
        }
    }
    file.close();
}
void AddList(List *ls, int CoffeeID, int data)
{
    Node *e = new Node;

    e-> CoffeeID = CoffeeID;
    e-> data = data;
    e-> next = ls -> head;

    ls->head = e;
    writeData(ls);
}
void DisplayInfor(List *ls)
{
    if( ls != NULL)
    {
        Node *e;
        e = ls -> head;
        cout<<" \n Here is the order of customer : \n\n";
        while(e != NULL)
        {
            cout<<" ID product : "<<e->CoffeeID<<endl;
            cout<<" Number of cup  : "<<e->data<<"\n"<<endl;
            e = e->next;
        }
    }
    else{
        cout<<" End of list!!"<<endl;
    }

}

void readData(List *ls)
{
    // Open file
    fstream file;
    file.open("dataHistory.txt", ios::in);
    if (!file)
    {
        cout << "File is not exist!" << endl;
    }
    else
    {
        int ID;
        int data;
        while (!file.eof())
        {
            file >> ID;
            file >> data;
            AddList(ls, ID, data);
        }
    }
    file.close();
}

