#pragma once
#include "headerNode.h"

class SparseMatrix {
    
    private:
        headerNode* rowHead;
        headerNode* colHead;
        headerNode* createCol(int yPos);
        headerNode* createRow(int xPos);
        headerNode* findRow(int xPos);
        headerNode* findCol(int yPos);
        
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