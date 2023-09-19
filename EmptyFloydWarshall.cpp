#include <iostream>
#include <iomanip>
#include <omp.h>
#include <cmath>

using namespace std;

// A 'simple' procedure for printing a formatted matrix
void printMatrix(int** graph, int size) {
    int i = 0, j = 0;
    ios state(nullptr);
    state.copyfmt(cout);
    cout << "\n      ";
    for (i = 0; i < size; i++){
        int strLength = int(log10(i));
        cout << setw(4-strLength) << "V" << i;
    }
    cout << "\n";
    for (i = 0; i < size; i++) {
        int strLength = 0;
        if (i > 0)
            strLength = int(log10(i));
        cout <<  "V" << i;
        for (j = 0; j < size; j++) {
            cout << setw(5-strLength) << graph[i][j];
            strLength = 0;
        }
        cout << "\n";
    }
    cout << "\n";
    cout.copyfmt(state);
}


// computes a distance matrix (i.e., all-pairs shortest paths) using the Floyd-Warshall algorithm. 
void floydWarshall(int** graph, int size) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// creates a random graph of |size| vertices
void createRandomGraph(int** graph, int size) {
    int i = 0, j = 0;
    for (i = 0; i < size; i++)  
        for (j = 0; j < size; j++)  
            graph[i][j] = 0;
    // Random adjacency matrix  
    for (i = 0; i < size-1; i++)
        for (j = i+1; j < size; j++)
            if (rand() % 2 == 0)
                graph[i][j] = graph[j][i] = 0;
            else
                graph[i][j] = graph[j][i] = 1;
}

// creates a toy graph of 10 vertices
void createToyGraph10(int** graph, int size) { //set size to 10
    int i=0, j=0;
    // A zeroed matrix
    for (i = 0; i < size; i++)  
        for (j = 0; j < size; j++)  
            graph[i][j] = 0;  
    // Adjacency matrix 
    graph[0][1] = graph[1][0] = 1;
    graph[0][2] = graph[2][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[1][3] = graph[3][1] = 1;
    graph[1][4] = graph[4][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[1][5] = graph[5][1] = 1;
    graph[4][5] = graph[5][4] = 1;
    graph[4][6] = graph[6][4] = 1;
    graph[6][5] = graph[5][6] = 1;
    graph[7][6] = graph[6][7] = 1;
    graph[8][7] = graph[7][8] = 1;
    graph[9][8] = graph[8][9] = 1;
//                                  V0  V1  V2  V3  V4  V5  V6  V7  V8  V9
//     0------2------3          V0   0   1   1   0   0   0   0   0   0  0
//      \     |     /           V1   1   0   1   1   1   1   0   0   0  0
//       \    |    /            V2   1   1   0   1   0   0   0   0   0  0
//        \   |   /             V3   0   1   1   0   0   0   0   0   0  0
//         \  |  /              V4   0   1   0   0   0   1   1   0   0  0
//          \ | /               V5   0   1   0   0   1   0   1   0   0  0
//            1		            V6   0   0   0   0   1   1   0   1   0  0
//           / \                V7   0   0   0   0   0   0   1   0   1  0
//          /   \               V8   0   0   0   0   0   0   0   1   0  1
//         /     \              V9   0   0   0   0   0   0   0   0   1  0
//        /       \
//       /         \
//      5----------4
//      \           /           
//       \         /            
//        \       /             
//         \     /              
//          \   /               
//            6	    
//            |
//            |
//            7
//            |
//            |
//            8
//            |
//            |
//            9
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {
    const int SIZE = 10; // Number of vertices of a given graph   

    srand(time(0)); // set a random seed for random graphs.

    // allocate memory for the adjacency matrix of a (large) graph.
    int** graph = new int*[SIZE];
    int i = 0, j = 0;
    for (i = 0; i < SIZE; i++)
         graph[i] = new int[SIZE];
    


    createRandomGraph(graph, SIZE);
    printMatrix(graph, SIZE);
    
    

    // releases allocated memory
    for (int i = 0; i < SIZE; i++)
        delete[] graph[i];
    delete[] graph; 
  
    return 0;
}