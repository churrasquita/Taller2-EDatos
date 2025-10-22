#include "NodeMatrix.h"

#include <iostream>
#include <ctime>
#include <random>

using namespace std;

NodeMatrix* head = nullptr;
NodeMatrix* currentMx = nullptr;
int mxCount = 0;

void addValue(){
    if(!head){
        cout<<"First of all, create at least one Sparse Matrix"<<endl;
        return;
    }
    cout<<"Let's add values to Sparse Matrix!"<<endl;
    cout<<"(You're working with the matrix #"<<currentMx->index<<")"<<endl;
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
    currentMx->matrix->add(value, xPos, yPos); 
    cout<<"Added value: ("<<xPos<<","<<yPos<<"): "<<value<<endl;
    
}

void getValue(){
    if(!head){
        cout<<"First of all, create at least one Sparse Matrix"<<endl;
        return;
    }
    cout << "Let's find the value!" << endl;
    cout<<"(You're working with the matrix #"<<currentMx->index<<")"<<endl;
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
    int value = currentMx->matrix->get(xPos,yPos);
    if(value == 0){
        cout<<"The coordinates doesn't exist!"<<endl;
    }
    else cout<<"("<<xPos<<","<<yPos<<"): "<<currentMx->matrix->get(xPos,yPos)<<endl;

}

void removeValue(){
    cout<<endl; 
    if(!head){
        cout<<"First of all, create at least one Sparse Matrix"<<endl;
        return;
    }
    cout << "Let's remove a value!" << endl;
    cout<<"(You're working with the matrix #"<<currentMx->index<<")"<<endl;
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
    currentMx->matrix->remove(xPos,yPos);
}

void multiplyMx(){
    cout<<endl; 
    if(!head||!head->next){
        cout<<"There must be at least two matrices to be multiplied"<<endl;
        return;
    }
    cout<<"Let's multiply two sparse matrices of the system!"<<endl;
    cout<<"REMEMBER! Order matters AxB != BxA"<<endl;
    cout<<"First, choose two matrices: "<<endl;

    cout << "Enter index of first matrix: ";
    int a; cin >> a;
    cout << "Enter index of second matrix: ";
    int b;cin >> b;

    NodeMatrix* aux1 = head;
    NodeMatrix* aux2 = head;
    while(aux1 && aux1->index!=a){
        aux1 = aux1->next;
    }
    while(aux2&& aux2->index!=a){
        aux2=aux2->next;
    }
    if(!aux1||!aux2){
        cout<<"Invalid index."<<endl;
        return;
    }
    SparseMatrix* newMatrix = aux1->matrix->multiply(aux2->matrix);
    mxCount++;
    NodeMatrix* newNode = new NodeMatrix(newMatrix, mxCount);

    NodeMatrix* aux = head;
    while (aux->next != nullptr)
        aux = aux->next;
    aux->next = newNode;
    cout<<"Sparse Matrix resulting from multiplication"<<endl;
    newMatrix->printStoredValues();
}

void getDensity(){
    cout<<endl; 
    if(!head){
        cout<<"First of all, create at least one Sparse Matrix"<<endl;
        return;
    }
    cout<<"(You're working with the matrix #"<<currentMx->index<<")"<<endl;
    int density = currentMx->matrix->density();
    if(density==0){
        cout<<"The Sparse Matrix is empty!"<<endl;
    }
    else cout<<"The density of the current Sparse Matrix: "<<density<< "%"<<endl;
}

void createMatrix(){
    cout<<endl; 
    SparseMatrix* newMatrix = new SparseMatrix();
    mxCount++;
    NodeMatrix* newNode= new NodeMatrix(newMatrix, mxCount);

    if (head == nullptr) {
        head = newNode;
    } else {
        NodeMatrix* aux = head;
        while (aux->next != nullptr)
            aux = aux->next;
        aux->next = newNode;
    }
    currentMx = newNode;
    cout<<"New Matrix created! index: "<<mxCount<<endl;
}

void selectMx(){
    cout<<endl; 
    if(!head){
        cout<<"First of all, create at least one Sparse Matrix."<<endl;
        return;
    }
    cout << "Available matrices: " << endl;
    NodeMatrix* aux = head;
    while (aux != nullptr) {
        cout << "- Matrix: " << aux->index << endl;
        aux = aux->next;
    }
    cout << "Select the matrix index to be the current one: " << endl;
    cout << "> ";
    int indexCurrent; cin >> indexCurrent; 

    aux = head;
    while(aux && aux->index!= indexCurrent){
        aux = aux->next; 
    }
    if(!aux){
        cout<<"Invalid index. Try again."<<endl;
        return; 
    }
    currentMx = aux;
    cout<<"Selection complete. You're working with #"<<currentMx->index<< " SparseMatrix"<<endl;
}

void printValues(){
    cout<<endl; 
    cout << "Let's print the values!" << endl;
    cout<<"(You're working with the matrix #"<<currentMx->index<<")"<<endl;
    currentMx->matrix->printStoredValues();
}
int main() {
    cout<<"Welcome!!"<<endl;
    cout<<"We're gonna try the Sparse Matrix program!"<<endl;
    string op = " "; 

    while(op!="9"){
        cout<<endl; 
        cout<<"Numbers of matrices in the system: "<< mxCount<<endl;
        cout<<"---- MENU ----"<<endl;
        cout<<"1) Create Sparse Matrix"<<endl;
        cout<<"2) Add value to the current Sparse Matrix"<<endl;
        cout<<"3) Get value of the current Sparse Matrix"<<endl;
        cout<<"4) Remove value of the current Sparse Matrix"<<endl;
        cout<<"5) Print stored values of the current Sparse Matrix"<<endl;
        cout<<"6) Get current Sparse Matrix density "<<endl;
        cout<<"7) Multiply with another Sparse Matrix "<<endl;
        cout<<"8) Change current matrix"<<endl;
        cout<<"9) Exit "<<endl;
        cout<<">> ";
        cin>>op; 

        if(op == "1") createMatrix();
        else if(op=="2") addValue();
        else if(op=="3") getValue();
        else if(op == "4") removeValue();
        else if(op == "5") printValues(); 
        else if(op == "6") getDensity();
        else if(op == "7") multiplyMx();
        else if(op == "8") selectMx();
        else if(op == "9"){
            cout<<"See u later!"<<endl;
        }else{
            cout<<"Invalid option, pls try again :("<<endl;
            cout<<endl; 
        }
    }
 
    return 0;
}