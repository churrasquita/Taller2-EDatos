#include "SparseMatrix.h"
#include <iostream>

SparseMatrix:: SparseMatrix(){
    rowHead = nullptr;
    colHead = nullptr;
}

headerNode* SparseMatrix:: findRow(xPos){
    headerNode* aux = rowHead;
    while(aux && aux->index != xPos){
        aux = aux->next;
    }
    return aux; 
}

headerNode* SparseMatrix:: findCol(yPos){
    headerNode* aux = colHead;
    while(aux && aux->index != yPos){
        aux = aux->next;
    }
    return aux; 
}

// por implementar 
void SparseMatrix :: remove(int xPos, int yPos){
    if(!rowHead || !colHead) return; 

    headerNode* rowAux = rowHead; 
    while(rowAux && rowAux ->index != xPos){
        rowAux = rowAux->next;
    }
    if (!rowAux) return; 

}


int SparseMatrix:: get(int xPos, int yPos){
    headerNode* row = findRow(xPos); 
    if(!row) return 0;

    Node* current = row -> rowNext;
    while(current && current->y < yPos){
        current = current -> right;
    }
    if(current && current ->y == yPos){
        return current->data; 
    }
    return 0;
}

headerNode* SparseMatrix:: createRow(int xPos){
    if (!rowHead) {
        rowHead = new headerNode(xPos);
        return rowHead;
    }
    headerNode* aux = rowHead;
    headerNode* prev = nullptr;

    while (aux && aux->index < xPos) {
        prev = aux;
        aux = aux->next;
    }
    if (aux && aux->index == xPos)
        return aux;

    headerNode* newHead = new headerNode(xPos);
    if (!prev) {
        newHead->next = rowHead;
        rowHead = newHead;
    } else {
        newHead->next = aux;
        prev->next = newHead;
    }
    return newHead;
}
headerNode* SparseMatrix:: createCol(int yPos){
    if (!colHead){
        colHead= new headerNode(yPos);
        return colHead;
    }
        headerNode* aux = colHead;
        headerNode* prev = nullptr; 
        while (aux && aux->index< yPos){
            prev = aux; 
            aux = aux->next;
        }
        if (aux && aux->index == yPos){
            return aux; 
        }
        headerNode* newHead = new headerNode(yPos);
        if(!prev){
            newHead->next= colHead;
            colHead = newHead;
        } else{
            newHead->next = aux;
            prev->next = newHead;
        }
        return newHead;
}

void SparseMatrix:: add(int value, int xPos, int yPos){
    if(value == 0) return;

    headerNode* rowHead = createRow(xPos);
    headerNode* colHead = createCol(yPos);
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

int SparseMatrix::density(){
    int count = 0;
    int maxRow = 0, maxCol = 0;
    headerNode* aux = rowHead;
    while(aux){
        Node* current = aux->next;
        while(current){
            count ++;
            if(curr->row>maxRow) maxRow = current->row;
            if(curre->col>maxCol) maxCol = current ->col;
            current = current->right;
        }
        aux = aux->next;
    }
    if (maxRow == 0 || maxCol == 0) return 0;
    int total = (maxRow + 1) * (maxCol + 1);
    return count / total;
}