#include "SparseMatrix.h"
#include <iostream>
using namespace std;

SparseMatrix* sMatrix = new SparseMatrix ();

void addValue(){ // por implementar
    

}

void getValue(){
    //por implementar
}

void removeValue(){
    //por implementar
}

void multiplyMx(){
    //por implementar
}

int main() {
    cout<<"Welcome!!"<<endl;
    cout<<"We're gonna try the Sparse Matrix program!"<<endl;
    string op = " "; 

    while(op!="7"){
        cout<<"---- MENU ----"<<endl;
        cout<<"1) Add value "<<endl;
        cout<<"2) Get value "<<endl;
        cout<<"3) Remove value "<<endl;
        cout<<"4) Print stored values "<<endl;
        cout<<"5) Get matrix density "<<endl;
        cout<<"6) Multiply with another Sparse Matrix "<<endl;
        cout<<"7) Exit "<<endl;
        cout<<">> ";
        cin>>op; 

        if(op == "1") addValue();
        else if(op=="2") getValue();
        else if(op == "3") removeValue();
        else if(op == "4") sMatrix->printStoredValues();
        else if(op == "5") sMatrix->density();
        else if(op == "6") multiplyMx();
        else if(op == "7"){
            cout<<"See u later!"<<endl;
        }else{
            cout<<"Invalid option, pls try again :("<<endl;
            cout<<endl; 
        }
    }
 
    return 0;
}