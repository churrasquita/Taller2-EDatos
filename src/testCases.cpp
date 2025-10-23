#include "SparseMatrix.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

void runTestCases(){
    int elements[] = {50, 50, 250, 250, 500, 500, 1000, 1000, 5000, 5000};
    srand(time(0)); 

    for(int i = 0; i<10; i++) {
        std::cout<<std::endl;
        std::cout<<"Test #" << i+1 <<std::endl; 
        std::cout<<"- Amount of data: " << elements[i]<<std::endl;
        if(i%2== 0) std::cout<<"- Density ~40%"<<std::endl;
        else std::cout<<"- Density ~70%"<<std::endl;
        std::cout<<std::endl;

        SparseMatrix* spMatrix1 = new SparseMatrix();
        SparseMatrix* spMatrix2 = new SparseMatrix();

        int n = elements[i];
        int* xPos = new int[n];
        int* yPos = new int[n];
        int* value = new int[n];

        int factor;
        if(i % 2 == 0){ //low density (~40%)
            factor = 5; 
        }else{ //high density (~70%)
            factor = 2; 
        }
        //random values
        for (int j = 0; j < n; j++) {
            xPos[j] = rand() % (n*factor);  
            yPos[j] = rand() % (n*factor); 
            value[j] = rand() % 100 + 1;       
        }

        //add
        clock_t start = clock();
        for(int j = 0; j < n; j++) {
            spMatrix1->add(value[j], xPos[j], yPos[j]);
        }
        clock_t end = clock();
        double timeAdd = 1000.0*double(end-start)/CLOCKS_PER_SEC;
        std::cout<<"Time add algorithm: " <<timeAdd<< " ms"<<std::endl;
    
        //get
        start = clock();
        for (int j = 0; j < n; j++) {
            spMatrix1->get(xPos[j], yPos[j]);
        }
        end = clock();
        double timeGet = 1000.0 * double(end-start)/CLOCKS_PER_SEC;
        std::cout<< "Time get algorithm: " <<timeGet<< " ms"<<std::endl;

        // multiply -> mx2
        for (int j = 0; j < n; j++) {
            int xPos2 = rand() % (n * factor);
            int yPos2 = rand() % (n * factor);
            int value2 = rand() % 100 + 1;
            spMatrix2->add(value2, xPos2, yPos2);
        }
        start = clock();
        SparseMatrix* resultM = spMatrix1->multiply(spMatrix2);
        end = clock();
        double timeMult = 1000.0*double(end-start)/CLOCKS_PER_SEC;
        std::cout<<"Time multiply algorithm: "<<timeMult<<" ms"<<std::endl;

        // density
        start = clock();
        int density = spMatrix1->density();
        end = clock();
        double timeDens = 1000.0*double(end-start)/CLOCKS_PER_SEC;
        std::cout<< "Time density algorithm: " <<timeDens<<" ms " << "(real density of mx: "<<density<<"%)"<<std::endl;

        delete spMatrix1;
        delete spMatrix2;
        delete resultM;
        delete[] xPos;
        delete[] yPos;
        delete[] value;
    }
    std::cout<<std::endl;
    std::cout <<"End of test cases."<<std::endl;
}
