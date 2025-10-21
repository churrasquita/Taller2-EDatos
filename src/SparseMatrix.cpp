#include "SparseMatrix.h"
#include <iostream>

SparseMatrix:: SparseMatrix(){
    start = nullptr; 
}

void SparseMatrix:: add(int value, int xPos, int yPos){
    if(value<=0) return; 

    if(!start){
        start = new Node(value,xPos,yPos); 
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

int SparseMatrix::get(int xPos, int yPos) {
    if (!start){
        std::cout << "The Sparse Matrix is empty." << std::endl;
        return 0;
    }
    Node* auxRow = start;
    while(auxRow  && auxRow->row<xPos){
        auxRow = auxRow ->down;
    }
    if(!auxRow||auxRow->row != xPos) return 0;

    Node* curr = auxRow;
    while(curr && curr->col<yPos){
        curr = curr->right;
    }
    if (!curr||curr->col!=yPos) return 0;
    return curr->data;
}

void SparseMatrix::remove(int xPos, int yPos) {
    if (!start){
        std::cout << "The Sparse Matrix is empty." << std::endl;
        return;
    }

    Node* prevRow = nullptr;
    Node* auxRow = start;
    while (auxRow && auxRow->row < xPos) {
        prevRow = auxRow;
        auxRow = auxRow->down;
    }

    if (!auxRow|| auxRow->row != xPos) return;

    Node* prev = nullptr;
    Node* curr = auxRow;

    while (curr && curr->col < yPos) {
        prev = curr;
        curr = curr->right;
    }

    if (!curr || curr->col != yPos) return;

    if (prev) prev->right = curr->right;
    else {
        if (prevRow) prevRow->down = auxRow->down;
        else start = auxRow->down;
    }

    delete curr;
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
    if (!start){
        std::cout << "The Sparse Matrix is empty." << std::endl;
        return;
    }

    Node* auxRow = start;
    while(auxRow){
        Node* curr = auxRow;
        while (curr) {
            std:: cout << "(" << curr->row << "," << curr->col << "): " << curr->data << std::endl;
            curr = curr->right;
        }
        auxRow = auxRow->down;
    }
}

int SparseMatrix::density(){
    if (!start){
        std::cout << "The Sparse Matrix is empty." << std::endl;
        return 0;
    }

    int count = 0;
    int maxRow = 0, maxCol = 0;
    
    Node* auxRow = start;
    while(auxRow) {
        Node* curr = auxRow;
        while(curr){
            count++;
            if (curr->row > maxRow) maxRow = curr->row;
            if (curr->col > maxCol) maxCol = curr->col;
            curr = curr->right;
        }
        auxRow= auxRow->down;
    }

    int total = (maxRow + 1) * (maxCol + 1);
    if (total == 0) return 0;

    return ((double)count / total) * 100;
}

 SparseMatrix* SparseMatrix:: multiply(SparseMatrix* second){
    SparseMatrix* newMatrix = new SparseMatrix();

    if (!start||!second->start){
        std::cout << "Sparse matrices must have at least one element." << std::endl;
        return newMatrix;
    }
    Node* auxRowFirst = start; 
    while (auxRowFirst) {
        Node* aux1 = auxRowFirst; //aux first matrix
        while (aux1) {
            Node* auxRowSecond= second->start;
            while (auxRowSecond && auxRowSecond->row < aux1->col) {
                auxRowSecond = auxRowSecond->down;
            }

            if (auxRowSecond&& auxRowSecond->row == aux1->col) {
                Node* aux2= auxRowSecond; 
                while(aux2){ //aux second matrix
                    int xPos = auxRowFirst->row; 
                    int yPos = aux2->col;  
                    int product = aux1->data * aux2->data;

                    int prev = newMatrix->get(xPos, yPos);
                    int finalProduct = prev+product; 
                    newMatrix->add(finalProduct, xPos, yPos);

                    aux2 = aux2->right;
                }
            }

            aux1 = aux1->right;
        }

        auxRowFirst= auxRowFirst->down;
    }
    return newMatrix; 
    
}