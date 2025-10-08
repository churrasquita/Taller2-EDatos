#include "SparseMatrix.h"

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
headerNode* SparseMatrix:: findCreateCol(int xPos){

}

void SparseMatrix:: add(int value, int xPos, int yPos){
    if(value == 0) return;
    headerNode* rowHead = findCreateRow(xPos);
    headerNode* colHead = findCreateCol(yPos);
    Node* newNode = new Node(xPos, yPos, value);

} 