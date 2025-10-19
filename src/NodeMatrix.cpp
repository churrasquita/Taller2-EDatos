#include "NodeMatrix.h"

NodeMatrix:: NodeMatrix(SparseMatrix* matrix, int index){
    this->index = index;
    this-> matrix = matrix;
    this->next = nullptr;
}
NodeMatrix:: ~NodeMatrix(){
    delete matrix; 
    matrix = nullptr; 
}