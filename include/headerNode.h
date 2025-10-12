#include "Node.h"
class headerNode{
    public:
        int index;
        Node* head;
        headerNode* next;
        headerNode(int index);
        ~headerNode();
};