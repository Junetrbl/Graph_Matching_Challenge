/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <algorithm>

Backtrack::Backtrack() {
    std::cout << "backtrack" << "\n";
}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";
  std::vector<std::pair<int, int>> searchTree;

  // implement your code here.
  std::vector<std::pair<int, int>> M;
  int* visited = new int[data.GetNumVertices()];
  memset(visited, 0, sizeof(int) * data.GetNumVertices());
  FindPartialEmbedding(data, query, cs, M, visited);
}
void Backtrack::FindPartialEmbedding(const Graph &data, const Graph &query,
                                     const CandidateSet &cs, std::vector<std::pair<int, int>> M, int* visited){

    if (M.size() == query.GetNumVertices()){
        std::cout << "a ";
        for (int i = 0; i < M.size(); i++){
            std::cout << M.at(i).second << " ";
        }
        std::cout << std::endl;
    }

    else if (M.size() == 0){
        for (int i = 0; i < cs.GetCandidateSize(query.root); i++){
            M.push_back(std::pair<int, int>(query.root, cs.GetCandidate(query.root, i)));
            visited[cs.GetCandidate(query.root, i)] = 1;
            FindPartialEmbedding(data, query, cs, M, visited);
            visited[cs.GetCandidate(query.root, i)] = 0;
        }
    }

    else {
        int u = ExtendableVertex(query, M);
        std::vector<int> CmU = ExtendableCandidate(data, query, cs, M, u);
        for (int v : CmU){
            std::vector<std::pair<int, int>> newM;
            newM.resize(M.size());
            std::copy(M.begin(), M.end(), newM.begin());
            newM.push_back(std::pair<int, int>(u, v));
            visited[v] = 1;
            FindPartialEmbedding(data, query, cs, newM, visited);
            visited[v] = 0;
        }
    }
}

int IsInM(std::vector<std::pair<int, int>> M, int vertex, bool first){
    if (first){
        for (int i = 0 ; i < M.size(); i++){
            if (M.at(i).first == vertex){
                return M.at(i).second;
            }
        }
        return -1;
    } else {
        for (int i = 0 ; i < M.size(); i++){
            if (M.at(i).second == vertex){
                return M.at(i).first;
            }
        }
        return -1;
    }
}

int Backtrack::ExtendableVertex(const Graph &query, std::vector<std::pair<int, int>> M){
    for (int i = 0; i < query.GetNumVertices(); i++){
        if (IsInM(M, i, true) != -1){
            continue;
        }
        bool parentInM = true;
        for (int j = 0; j < query.numParent[i]; j++){
            if (IsInM(M, query.parentQuery[i][j], true) == -1){
                parentInM = false;
                break;
            }
        }
        if (parentInM){
            return i;
        }
    }
    return -1;
}

std::vector<int> Backtrack::ExtendableCandidate(const Graph &data, const Graph &query, const CandidateSet &cs,
                                     std::vector<std::pair<int, int>> M, int u) {
    std::vector<int> Cm;
    int parentNum = query.numParent[u];
    std::vector<int> parentVs;
    for (int i = 0; i < parentNum; i++){
        int parentU = query.parentQuery[u][i];
        int parentV = IsInM(M, parentU, true);
        parentVs.push_back(parentV);
    }
    for (int i = 0; i < cs.GetCandidateSize(u); i++){
        bool isConnected = true;
        for (int j = 0; j < parentNum; j++){
            if (!data.IsNeighbor(parentVs.at(j), cs.GetCandidate(u, i))){
                isConnected = false;
                break;
            }
        }
        if (isConnected){
            Cm.push_back(cs.GetCandidate(u, i));
        }
    }
    return Cm;
}
//
//void Backtrack::FindPartialEmbedding(const Graph &data, const Graph &query, const CandidateSet &cs,
//                                     std::vector<std::pair<int, int>>& searchTree, int u, int v, bool& backtrack) {
////    std::cout << "search Tree Size " << searchTree.size() << "\n";
////    std::cout << "u is " << u << "\n";
////    std::cout << "v is " << v << "\n";
//
//    std::pair<int, int> newPair = std::pair<int, int>(u, v);
//
//    bool exists = false;
//    for(int k = 0; k < searchTree.size(); k++){
//        if (searchTree.at(k).first == newPair.first && searchTree.at(k).second == newPair.second){
//            exists = true;
//            break;
//        }
//    }
//    if (!exists){
//        searchTree.emplace_back(std::pair<int, int>(u, v));
////        std::cout << "a";
////        for (int i = 0; i < searchTree.size(); i++){
////            std::cout << " " << searchTree.at(i).second;
////        }
////        std::cout << std::endl;
//    }
////    std::cout << searchTree.size() << std::endl;
//
//
//    if (searchTree.size() == query.GetNumVertices()){
//        std::cout << "a";
//        for (int i = 0; i < searchTree.size(); i++){
//            std::cout << " " << searchTree.at(i).second;
//        }
//        std::cout << std::endl;
//        return;
//    }
//
//    for (int i = 0; i < query.numChild[u]; i++){
//        int uCandidate = query.childQuery[u][i];
//        bool uVisited = false;
//        for(int k = 0; k < searchTree.size(); k++){
//            if (searchTree.at(k).first == uCandidate){
//                uVisited = true;
//                break;
//            }
//        }
//        if (uVisited){
//            continue;
//        }
//        for (int j = 0; j < cs.GetCandidateSize(uCandidate); j++){
//            int vCount = cs.GetCandidateSize(uCandidate);
//            int vCandidate = cs.GetCandidate(uCandidate, j);
//            bool visited = false;
//            for(int k = 0; k < searchTree.size(); k++){
//                if (searchTree.at(k).second == vCandidate){
//                    visited = true;
//                    break;
//                }
//            }
//            if (visited){
//                vCount--;
//                continue;
//            }
////                    std::cout << "uCandidate is " << uCandidate << "\n";
////                    std::cout << "vCandidate is " << vCandidate << "\n";
//            if (!data.IsNeighbor(v, vCandidate)){
//                vCount--;
//                continue;
//            }
//            FindPartialEmbedding(data, query, cs, searchTree, uCandidate, vCandidate, backtrack);
//            vCount--;
//            if (vCount == 0){
//                searchTree.pop_back();
//            }
//        }
//    }
