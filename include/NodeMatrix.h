#pragma once
#include "SparseMatrix.h"
class NodeMatrix{
    public:
        SparseMatrix* matrix;
        int index;
        NodeMatrix* next;
        NodeMatrix(SparseMatrix* matrix, int index);
        ~NodeMatrix();
};