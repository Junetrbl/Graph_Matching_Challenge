/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <algorithm>
#include <stack>

Backtrack::Backtrack() {
    std::cout << "backtrack" << "\n";
}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";
  std::vector<std::pair<int, int>> searchTree;

  // implement your code here.
  int root = query.root;
  std::cout << "root " << root << std::endl;
  for (int i = 0; i < cs.GetCandidateSize(root); i++){
      FindPartialEmbedding(data, query, cs, searchTree, root, cs.GetCandidate(root, i));
  }
}

void Backtrack::FindPartialEmbedding(const Graph &data, const Graph &query, const CandidateSet &cs,
                                     std::vector<std::pair<int, int>>& searchTree, int u, int v) {
//    std::cout << "search Tree Size " << searchTree.size() << "\n";
//    std::cout << "u is " << u << "\n";
//    std::cout << "v is " << v << "\n";

    searchTree.emplace_back(std::pair<int, int>(u, v));
//    std::cout << searchTree.size() << std::endl;


    if (searchTree.size() == query.GetNumVertices()){
        std::cout << "a";
        for (int i = 0; i < searchTree.size(); i++){
            std::cout << " " << searchTree.at(i).second;
        }
        std::cout << std::endl;
        return;
    }

    for (int i = 0; i < query.numChild[u]; i++){
        int uCandidate = query.childQuery[u][i];
        bool visited = false;
        for(int k = 0; k < searchTree.size(); k++){
            if (searchTree.at(k).first == uCandidate){
                visited = true;
                break;
            }
        }
        if (!visited){
            for (int j = 0; j < cs.GetCandidateSize(uCandidate); j++){
                int vCandidate = cs.GetCandidate(uCandidate, j);
//                    std::cout << "uCandidate is " << uCandidate << "\n";
//                    std::cout << "vCandidate is " << vCandidate << "\n";
                if (!data.IsNeighbor(v, vCandidate)){
                    continue;
                }
                FindPartialEmbedding(data, query, cs, searchTree, uCandidate, vCandidate);
                searchTree.pop_back();
            }
        }

    }
}