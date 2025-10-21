#include "Node.h"

Node:: Node(int data, int row, int col){
    this-> row = row;
    this-> col = col;
    this-> data = data;
    this-> right = nullptr;
    this-> down = nullptr;
}
Node:: ~Node(){}