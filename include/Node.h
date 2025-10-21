class Node{
    public: 
        int row;
        int col;
        int data;
        Node* right;
        Node* down;
        Node(int data, int row, int col);
        ~Node();
};