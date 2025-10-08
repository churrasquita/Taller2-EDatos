#pragma once
#include "Node.h"
#include "headerNode.h"
class SparseMatrix {
    private:
        Header* rowHead;
        Header* colHead;
        int totalRows, totalCol;
        headerNode* findCreateCol(yPos);
        headerNode* findCreateRow(xPos);
    public:
        SparseMatrix();
        void add(int value, int xPos, int yPos);
        int get(int xPos, int yPos);
        void remove(int xPos, int yPos);
        void printStoredValues();
        int density();
        SparseMatrix* multiply(SparseMatrix* second);
        ~SparseMatrix();
};