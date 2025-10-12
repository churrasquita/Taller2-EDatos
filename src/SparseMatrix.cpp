#include "SparseMatrix.h"
#include <iostream>

SparseMatrix:: SparseMatrix(){
    rowHead = nullptr;
    colHead = nullptr;
}

headerNode* SparseMatrix:: findCreateRow(int xPos){
    if (!rowHead || xPos < rowHead->index) {
        headerNode* newHead = new headerNode(xPos);
        newHead->next = rowHead;
        rowHead = newHead;
        return newHead;
    }
        headerNode* aux = rowHead;
        while (aux->next && aux->next->index < xPos)
            aux = aux->next;
        if (aux->next && aux->next->index == xPos)
            return aux->next;
        headerNode* newHead = new headerNode(xPos);
        newHead->next = aux->next;
        aux->next = newHead;
        return newHead;
}
headerNode* SparseMatrix:: findCreateCol(int yPos){
    if (!colHead || yPos < colHead->index) {
        headerNode* newHead = new headerNode(yPos);
        newHead->next = colHead;
        colHead = newHead;
        return newHead;
    }
        headerNode* aux = colHead;
        while (aux->next && aux->next->index < yPos)
            aux = aux->next;
        if (aux->next && aux->next->index == yPos)
            return aux->next;
        headerNode* newHead = new headerNode(yPos);
        newHead->next = aux->next;
        aux->next = newHead;
        return newHead;
}

void SparseMatrix:: add(int value, int xPos, int yPos){
    if(value == 0) return;

    headerNode* rowHead = findCreateRow(xPos);
    headerNode* colHead = findCreateCol(yPos);
    Node* newNode = new Node(xPos, yPos, value);

    if(!rowHead->head || !rowHead->head->col>yPos){
        newNode->right = rowHead->head;
        rowHead->head = newNode;
    } else{
        Node* aux = rowHead->head;
        while(aux->right && aux->right->col < yPos){
            aux = aux ->right;
        } if(aux->down && aux->down->row == xPos) return;
        newNode->down = aux ->down;
        aux -> down = newNode;
    }
} 

SparseMatrix:: ~SparseMatrix(){
    headerNode* rowAux = rowHead;
    while(rowAux){
        Node* nodeAux = rowAux-> head;
        while(nodeAux){
            Node* temp = nodeAux;
            nodeAux = nodeAux->right;
            delete temp;
        }
        headerNode* tempRow= rowAux;
        rowAux = rowAux->next;
        delete tempRow;
    }
    headerNode* colAux = colHead;
    while(colAux){
        headerNode* tempCol = colAux;
        colAux = colAux->next;
        delete tempCol;
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