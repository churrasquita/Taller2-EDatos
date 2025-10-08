#include "Nodo.h"

Node:: Node(int row, int col, int data){
    this-> row = row;
    this-> col = col;
    this-> data = data;
    this-> right = nullptr;
    this-> down = nullptr;
}