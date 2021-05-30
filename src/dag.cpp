//
// Created by 박윤수 on 2021/05/28.
//

#include "dag.h"
#include <cfloat>
#include <queue>


Dag::Dag(Graph q, Graph G){
    this->q = q;
    this->G = G;
    this->root = findRoot();
    buildDAG(q, G);
}

Dag::~Dag() {

}

int Dag::findRoot() {
    this->root = -1;
    double argmin = DBL_MAX;

    for (int i = 0; i < q.GetNumVertices(); i++){
        double C_ini_size = 0;
        for (int j = 0; j < G.GetNumVertices() ; j++){
            if (q.GetLabel(i) == G.GetLabel(j) && q.GetDegree(i) <= G.GetDegree(j)){
                C_ini_size++;
            }
        }
        if (C_ini_size/q.GetDegree(i) < argmin){
            argmin = C_ini_size/q.GetDegree(i);
            this->root = i;
        }
    }

    return this->root;
}

void Dag::buildDAG(Graph q, Graph G) {
    //allocate memory for dag data structure
    if( this->childQuery == NULL ) {
        this->childQuery = new int*[q.GetNumVertices()];
        for(int i = 0; i < q.GetNumVertices(); ++i)
            this->childQuery[i] = NULL;
    }
    if( parentQuery == NULL ) {
        parentQuery = new int*[q.GetNumVertices()];
        for(int i = 0; i < q.GetNumVertices(); ++i)
            parentQuery[i] = NULL;
    }
    if( numChild == NULL )
        numChild = new int[q.GetNumVertices()];
    if( numParent == NULL )
        numParent = new int[q.GetNumVertices()];

    for (int i = 0; i < q.GetNumVertices(); i++){
        numChild[i] = 0;
        numParent[i] = 0;
    }

    for(int i = 0; i <q.GetNumVertices(); ++i) {
        if( childQuery[i] != NULL) {
            delete[] childQuery[i];
            childQuery[i] = NULL;
        }
        childQuery[i] = new int[q.GetDegree(i)];
        std::cout << "vertex " << i << " label " << q.GetLabel(i) << " degree " << q.GetDegree(i) << "\n";

        if( parentQuery[i] != NULL ) {
            delete[] parentQuery[i];
            parentQuery[i] = NULL;
        }
        parentQuery[i] = new int[q.GetDegree(i)];
    }

//////////////////
//construct dag data structure
    char* popped = new char[q.GetNumVertices()];
    memset(popped, 0, sizeof(char) * q.GetNumVertices());
    char* visited = new char[q.GetNumVertices()];
    memset(visited, 0, sizeof(char) * q.GetNumVertices());
    int* queue = new int[q.GetNumVertices()];
    int currQueueStart = 0;
    int currQueueEnd = 1;
    int nextQueueEnd = 1;

    //visit root
    root = findRoot();
    visited[root] = 1;
    popped[root] = 1;
    queue[0] = root;

    //BFS traversal using queue
    while(true) {
        std::stable_sort(queue + currQueueStart, queue + currQueueEnd, sortByDegreeQuery);
        std::stable_sort(queue + currQueueStart, queue + currQueueEnd, sortByLabelFreqQuery);
        while( currQueueStart != currQueueEnd ) {
            int currNode = queue[ currQueueStart ];
            ++currQueueStart;
            popped[currNode] = 1;
            std::cout << currNode << " ";

            for(int i = q.GetNeighborStartOffset(currNode); i < q.GetNeighborEndOffset(currNode); ++i) {
                int childNode = q.GetNeighbor(i);
                if(popped[childNode] == 0) {
                    childQuery[currNode][ numChild[currNode] ] = childNode;
                    parentQuery[childNode][ numParent[childNode] ] = currNode;

                    ++numChild[currNode];
                    ++numParent[childNode];
                }
                if(visited[childNode] == 0) {
                    visited[childNode] = 1;
                    queue[nextQueueEnd] = childNode;
                    ++nextQueueEnd;
                }
            }
        }

        if(currQueueEnd == nextQueueEnd) //no nodes have been pushed in
            break;

        currQueueStart = currQueueEnd;
        currQueueEnd = nextQueueEnd;
    }
    std::cout << std::endl;
    delete[] popped;
    delete[] visited;
    delete[] queue;
}
