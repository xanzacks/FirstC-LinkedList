//  Zeyu Zhao
//  Assignment_9
//  codeblock for windows
//
//  Created by zhaozeyu on 15/03/2018.
//  Copyright © 2018 zhaozeyu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class node{
private:
    string name;
    int count;
    node* next;
public:
    node(string, node*, int);
    int getcount() const;
    string getname()const;
    node* getnext() const;
    void set_next(node*);
    void counp();
    void counm();
    void mis() const;
    friend ostream& operator<<(ostream&, const node&);
};
node::node(string a, node* b, int c){
    name = a;
    next = b;
    count = c;
}

int node::getcount() const{
    return count;
}

void node::counp(){
    count++;
}

void node::counm(){
    count--;
}

string node::getname() const{
    return name;
}

node* node::getnext() const{
    return next;
}

void node::set_next(node* a){
    next = a;
}
ostream& operator<<(ostream& out, const node& a){
    out<<setw(14)<<left<<a.name<<setfill(' ')<<a.count<<endl;
    return out;
}

class list{
private:
    node* top;
public:
    list();
    ~list();
    node* gettop() const;
    bool remove(string);
    node* find(string) const;
    void coup(string) const;
    void coum(string) const;
    void inserthings(string);
    int getcoun(string) const;
    void printmis(string, int) const;
    friend ostream& operator<<(ostream& , const list&);
};

list::list(){
    top = nullptr;
}

list::~list(){
    node* temp = top;
    while(temp!=nullptr){
        top = top->getnext();
        delete temp;
        temp = top;
    }
}

node* list::gettop() const{
    return top;
}

void list::inserthings(string a)
{
    int judge =0;
    int num = 1;
    node* temp1 = top;
    if(temp1 == nullptr){// When there is nothing in the list
        top = new node(a, top, num);
    }
    else if(temp1 -> getnext() == nullptr){// When there is only one node in the list
        if(temp1 -> getname().compare(a) < 0){
            node* temp = new node(a, temp1 -> getnext(), num);
            temp1 -> set_next(temp);
        }
        else{
            node* temp = new node(a, temp1, num);
            top = temp;
        }
    }
    else{// When there are more than one node in the list
        if(temp1 -> getname().compare(a) > 0){//Put it to the top
            node* temp2 = temp1 -> getnext();
            node* temp = new node(a, temp1, num);
            top = temp;
        }
        else if(temp1 -> getname().compare(a) < 0){
            while(temp1 != nullptr){
                node* temp2 = temp1;
                temp1 = temp1->getnext();
                if(temp1 -> getname().compare(a) > 0){
                    node* temp = new node(a, temp1, num);
                    temp2 -> set_next(temp);
                    judge++;
                    break;
                }
                else if(temp1 -> getnext() == nullptr){
                    node* temp = new node(a, temp1 -> getnext(), num);
                    temp1 -> set_next(temp);
                    break;
                }
            }
        }
    }
}

bool list::remove(string a){
    if(!find(a)){
        cout<<a<<" remove for not being found"<<endl;
        return false;
    }
    node* temp = top;
    node* temp2;
    if(top -> getname() == a){
        top = top->getnext();
        delete temp;
        return true;
    }
    while(temp->getnext()->getname() != a){
        temp = temp -> getnext();
    }
    temp2 = temp -> getnext();
    temp->set_next(temp2->getnext());
    delete temp2;
    return true;
}

node* list::find(string a) const{
    node* temp = top;
    while(temp != nullptr){
        if(temp -> getname() == a){
            return temp;
        }
        temp = temp -> getnext();
    }
    return 0;
}

void list::coup(string a) const{
    node* temp = find(a);
    temp -> counp();
}

void list::coum(string a) const{
    node* temp = find(a);
    temp -> counm();
}

void list::printmis(string a, int b) const{
    cout<<"Bad transaction: "<<a<<" in line #"<<b<<endl;
}

int list::getcoun(string a) const{
    node*temp = find(a);
    return temp->getcount();
}

ostream& operator<<(ostream& out, const list& a){
    node* temp = a.gettop();
    while (temp != 0){
        out<<*temp;
        temp = temp -> getnext();
    }
    return out;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    fin.open("Input File.txt");
    if(!fin.is_open()){
        cout<<"failed to open the file"<<endl;
        exit(-1);
    }
    string text;
    string front;
    string last;
    size_t pos;
    list l;
    int countline = 0;
    while(getline(fin, text)){
        countline++;
        if(fin.eof()){
            break;
        }
        if(text.size()<2){
            continue;
        }
        if(text.size() && text[text.size()-1] == '\r'){
            text.resize(text.size()-1);
        }
        pos = text.find(' ');
        front = text.substr(0,pos);
        last = text.substr(pos+1);
        if(front == "add"){
            if(l.find(last)){
                l.coup(last);
            }
            else{
                l.inserthings(last);
            }
        }
        else if(front == "remove"){
            if(l.find(last)){
                if(l.getcoun(last)>1){
                    l.coum(last);
                }
                else{
                    l.remove(last);
                }
            }
            else{
                cout<<"Unable to remove "<<last<<" in line #"<<countline<<endl;
            }
        }
        else if(front == "print"){
            cout<<endl;
            cout<<"Item       Quantity"<<endl;
            cout<<l<<endl;
            cout<<endl;
        }
        else{
            l.printmis(front, countline);
        }
    }
    return 0;
}
