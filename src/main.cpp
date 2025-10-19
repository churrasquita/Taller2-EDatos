#include "SparseMatrix.h"
#include <iostream>
using namespace std;

SparseMatrix* sMatrix = new SparseMatrix ();
SparseMatrix* currentMx = sMatrix;

void addValue(){
    cout<<"Let's add values to SparseMatrix!"<<endl;
    cout<<"- Value (integer > 0): "<<endl;
    int value; cin>>value;
    while(value<=0){
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- Value (integer > 0): "<<endl;
        cin>>value;
    }
    cout<<"- xPos: "<<endl;
    cout<<"> ";
    int xPos;cin>>xPos;

    while(xPos<0){
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- xPos (integer > -1): "<<endl;
        cin>>xPos;
    }
    cout<<"- yPos: "<<endl;
    cout<<"> ";
    int yPos;cin>>yPos;

    while(yPos<0){
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- yPos (integer > -1): "<<endl;
        cin>>yPos;
    }
    sMatrix->add(value, xPos, yPos); 
    
}

void getValue(){
    cout << "Let's find the value!" << endl;
    cout << "Enter the X-Pos:" << endl;
    cout << "> ";
    int xPos; cin >> xPos;

    while (xPos <=0) {
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- xPos (integer > -1): "<<endl;
        cin>>xPos;
    }

    cout<<"- yPos: "<<endl;
    cout<<"> ";
    int yPos;cin>>yPos;

    while(yPos<0){
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- yPos (integer > -1): "<<endl;
        cin>>yPos;
    }
    int value = currentMx->get(xPos,yPos);
    if(value == 0){
        cout<<"The coordinates doesn't exist!"<<endl;
    }
    else cout<<"("<<xPos<<","<<yPos<<"): "<<currentMx->get(xPos,yPos)<<endl;

}

void removeValue(){
    cout << "Let's remove the value!" << endl;
    cout << "Enter the X-Pos:" << endl;
    cout << "> ";
    int xPos; cin >> xPos;

    while (xPos <=0) {
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- xPos (integer > -1): "<<endl;
        cin>>xPos;
    }

    cout<<"- yPos: "<<endl;
    cout<<"> ";
    int yPos;cin>>yPos;

    while(yPos<0){
        cout<<"Invalid value! Try again: "<<endl;
        cout<<"- yPos (integer > -1): "<<endl;
        cin>>yPos;
    }
    currentMx->remove(xPos,yPos);
}

void multiplyMx(){
    //por implementar
}

void getDensity(){
    int density = currentMx->density();
    if(density==0){
        cout<<"The SparseMatrix is empty!"<<endl;
    }
    else cout<<"The density of the current SparseMatrix: "<<density<< "%"<<endl;
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
        else if(op == "5") getDensity();
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