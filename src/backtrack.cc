/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <algorithm>

Backtrack::Backtrack()
{
    //    std::cout << "backtrack" << "\n";
}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs)
{
    std::cout << "t " << query.GetNumVertices() << "\n";
    std::vector<std::pair<int, int>> searchTree;

    // implement your code here.
    std::vector<std::pair<int, int>> M;
    int *visited = new int[data.GetNumVertices()];
    memset(visited, 0, sizeof(int) * data.GetNumVertices());
    FindPartialEmbedding(data, query, cs, M, visited);
}
int cnt = 0;
void Backtrack::FindPartialEmbedding(const Graph &data, const Graph &query,
                                     const CandidateSet &cs, std::vector<std::pair<int, int>> M, int *visited)
{

    if (M.size() == query.GetNumVertices())
    {
        std::cout << "a ";
        for (int i = 0; i < query.GetNumVertices(); i++)
        {
            std::cout << IsInM(M, i, true) << " ";
        }
        std::cout << std::endl;
        cnt++;
        std::cout << cnt << std::endl;
    }

    else if (M.size() == 0)
    {
        for (int i = 0; i < cs.GetCandidateSize(query.root); i++)
        {
            M.push_back(std::pair<int, int>(query.root, cs.GetCandidate(query.root, i)));
            visited[cs.GetCandidate(query.root, i)] = 1;
            FindPartialEmbedding(data, query, cs, M, visited);
            visited[cs.GetCandidate(query.root, i)] = 0;
        }
    }

    else
    {
        int u = ExtendableVertex(query, M);
        std::priority_queue<int, std::vector<int>, std::greater<int>> CmU = ExtendableCandidate(data, query, cs, M, u);
        while (!CmU.empty())
        {
            int v = CmU.top();
            CmU.pop();
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

int Backtrack::IsInM(std::vector<std::pair<int, int>> M, int vertex, bool first)
{
    if (first)
    {
        for (int i = 0; i < M.size(); i++)
        {
            if (M.at(i).first == vertex)
            {
                return M.at(i).second;
            }
        }
        return -1;
    }
    else
    {
        for (int i = 0; i < M.size(); i++)
        {
            if (M.at(i).second == vertex)
            {
                return M.at(i).first;
            }
        }
        return -1;
    }
}

int Backtrack::ExtendableVertex(const Graph &query, std::vector<std::pair<int, int>> M)
{
    for (int i = 0; i < query.GetNumVertices(); i++)
    {
        if (IsInM(M, i, true) != -1)
        {
            continue;
        }
        bool parentInM = true;
        for (int j = 0; j < query.numParent[i]; j++)
        {
            if (IsInM(M, query.parentQuery[i][j], true) == -1)
            {
                parentInM = false;
                break;
            }
        }
        if (parentInM)
        {
            return i;
        }
    }
    return -1;
}

std::priority_queue<int, std::vector<int>, std::greater<int>> Backtrack::ExtendableCandidate(const Graph &data, const Graph &query, const CandidateSet &cs,
                                                                                             std::vector<std::pair<int, int>> M, int u)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> Cm;
    int parentNum = query.numParent[u];
    std::vector<int> parentVs;
    for (int i = 0; i < parentNum; i++)
    {
        int parentU = query.parentQuery[u][i];
        int parentV = IsInM(M, parentU, true);
        parentVs.push_back(parentV);
    }
    for (int i = 0; i < cs.GetCandidateSize(u); i++)
    {
        if (IsInM(M, cs.GetCandidate(u, i), false) != -1)
        {
            continue;
        }
        bool isConnected = true;
        for (int j = 0; j < parentNum; j++)
        {
            if (!data.IsNeighbor(parentVs.at(j), cs.GetCandidate(u, i)))
            {
                isConnected = false;
                break;
            }
        }
        if (isConnected)
        {
            Cm.push(cs.GetCandidate(u, i));
        }
    }
    return Cm;
}