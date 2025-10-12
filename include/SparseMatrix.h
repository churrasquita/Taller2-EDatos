#pragma once
#include "headerNode.h"
class SparseMatrix {
    private:
        headerNode* rowHead;
        headerNode* colHead;
        int totalRows, totalCol;
        headerNode* findCreateCol(int yPos);
        headerNode* findCreateRow(int xPos);
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