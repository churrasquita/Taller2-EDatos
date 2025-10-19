#include "SparseMatrix.h"
#include <iostream>

SparseMatrix:: SparseMatrix(){
    rowHead = nullptr;
    colHead = nullptr;
}

headerNode* SparseMatrix:: findRow(int xPos){
    headerNode* aux = rowHead;
    while(aux && aux->index != xPos){
        aux = aux->next;
    }
    return aux; 
}

headerNode* SparseMatrix:: findCol(int yPos){
    headerNode* aux = colHead;
    while(aux && aux->index != yPos){
        aux = aux->next;
    }
    return aux; 
}

void SparseMatrix :: remove(int xPos, int yPos){
    if(!rowHead || !colHead){
        std:: cout<<"The SparseMatrix is empty"<< std:: endl;
        return; 
    }
    headerNode* rowAux = rowHead; 
    while(rowAux && rowAux ->index != xPos){
        rowAux = rowAux->next;
    }
    if (!rowAux){
        std:: cout<<"Invalid coordinates."<< std:: endl;
        return; 
    }
    Node* curr = rowAux->head;
    Node* prev = nullptr;
    while(curr && curr->col != yPos){
        prev = curr;
        curr = curr->right; 
    }
    if(!curr){
        std:: cout<<"Invalid coordinates."<< std:: endl;
        return;
    }
    if(prev){
        prev->right = curr->right;
    } else{
        rowAux->head = curr->right;
    }
    headerNode* colAux = colHead;
    while(colAux && colAux->index != yPos){
        colAux = colAux->next;
    }
    if(colAux){
        Node* currCol = colAux->head; 
        Node* prevCol = nullptr;
        while(currCol && currCol->row!= xPos){
            prevCol = currCol;
            currCol= currCol->down;
        }
        if(currCol){
            if(prevCol){
                prevCol->down = currCol->down;
            }else{
                colAux-> head = currCol->down;
            }
        }
    }
    delete curr; 
    std:: cout<<"Value successfully removed."<< std:: endl;
}

int SparseMatrix:: get(int xPos, int yPos){
    headerNode* row = findRow(xPos); 
    if(!row) return 0;

    Node* current = row -> head;
    while(current && current->col < yPos){
        current = current -> right;
    }
    if(current && current ->col == yPos){
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
    colHead = nullptr; 
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