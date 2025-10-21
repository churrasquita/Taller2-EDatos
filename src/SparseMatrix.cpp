#include "SparseMatrix.h"
#include <iostream>

SparseMatrix:: SparseMatrix(){
    start = nullptr; 
}

void SparseMatrix:: add(int value, int xPos, int yPos){
    if(value<=0) return; 

    if(!start){
        start = new node(value,xPos,yPos); 
        return;
    }
    
    Node* prevRow = nullptr;
    Node* currRow = start;
    while (currRow && currRow->row < xPos) {
        prevRow = currRow;
        currRow = currRow->down;
    }

    if (!currRow || currRow->row > xPos) {
        Node* newRow = new Node(xPos, yPos, value);
        newRow->down = currRow;
        if (prevRow) prevRow->down = newRow;
        else start = newRow;
        return;
    }

    Node* prev = nullptr;
    Node* curr = currRow;
    while (curr && curr->col < yPos) {
        prev = curr;
        curr = curr->right;
    }

    if (curr && curr->col == yPos) {
        curr->data = value;
        return;
    }
    
    Node* newNode = new Node(xPos, yPos, value);
    newNode->right = curr;

    if (prev){
        prev->right = newNode;
    }else{ 
        if (prevRow && prevRow->down == currRow)
            prevRow->down = newNode;
        else
            start = newNode;
        newNode->down = currRow->down;
    }


} 

SparseMatrix:: ~SparseMatrix(){
    Node* row = start;
    while (row) {
        Node* curr = row;
        row = row->down;
        while (curr) {
            Node* temp = curr;
            curr = curr->right;
            delete temp;
        }
    }
}

void SparseMatrix:: printStoredValues(){
    headerNode* rowAux = rowHead;
    while(rowAux){
        Node* aux = rowAux->head;
        while(aux){
            std:: cout<<"("<<aux->row<<","<<aux->col<<"): "<<aux->data<< std:: endl;
            aux = aux->right;
        }
        rowAux = rowAux-> next;
    }
}

int SparseMatrix::density(){
    int count = 0;
    int maxRow = 0, maxCol = 0;
    headerNode* aux = rowHead;
    while(aux){
        Node* current = aux->head;
        while(current){
            count ++;
            if(current->row>maxRow) maxRow = current->row;
            if(current->col>maxCol) maxCol = current ->col;
            current = current->right;
        }
        aux = aux->next;
    }
    if (maxRow == 0 || maxCol == 0) return 0;
    int total = (maxRow + 1) * (maxCol + 1);

    return ((double)count / total)*100;
}

 SparseMatrix* SparseMatrix:: multiply(SparseMatrix* second){
    SparseMatrix* newMatrix = new SparseMatrix();

    headerNode* rowAux = this->rowHead;
    while(rowAux){
        Node* nodeAux = rowAux->head;
        while (nodeAux) {
            headerNode* colSecond = second->findCol(nodeAux->row);
            if(colSecond) {
                Node* nodeSecond = colSecond->head;
                while(nodeSecond) {
                    int xPos = nodeAux->row;
                    int yPos = nodeSecond->col;
                    int value = nodeAux->data*nodeSecond->data;
                    int prev = newMatrix->get(xPos, yPos);
                    newMatrix->add(prev+value, xPos, yPos);
                    nodeSecond = nodeSecond->down;
                }
            }
            nodeAux = nodeAux->right;
        }
        rowAux = rowAux->next;
    }
    return newMatrix; 
    
}