#include <iostream>
#include<vector>
#include<queue>
#include<stack>
#include<tuple>

class Graph {
    std::vector<std::vector<int>> adj;
    const bool oriented;
    const int V;
public:
    explicit Graph(int V, bool oriented = true);

    void addEdge(int start, int end);

    std::vector<int> BFS(int start);

    int shortestPath(int start, int end);

    std::vector<int> DFS(int start);

    std::vector<int> DFSRec(int start);

    bool containsCycle();

    std::vector<int> TopologicalSort();

    bool isConnected();

    bool isBiParted();

    std::vector<std::vector<int>> getStronglyConnectedComponents();

    Graph getTranspose();

private:
    bool contains_cycle_rec(int start, std::vector<bool> &visited, std::vector<bool> &inStack);

    void dfs_rec_help(int start, std::vector<bool> &visited, std::vector<int> &result);

    void topological_sort_help(int start, std::vector<bool> &visited, std::stack<int> &s);

    bool is_bi_parted_help(int start, std::vector<int> &visited);

};

Graph::Graph(int V, bool oriented) : adj(V), V(V), oriented(oriented) {
    if(V<=0)
        throw std::exception();
}

void Graph::addEdge(int start, int end) {
    adj[start].push_back(end);
    if (!oriented)
        adj[end].push_back(start);
}

int Graph::shortestPath(int start, int end) {
    std::vector<bool> visited(V, false);
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(start, 0));
    visited[start] = true;

    while (!q.empty()) {
        int curVertex = q.front().first;
        int curDistance = q.front().second;
        q.pop();
        if (curVertex == end)
            return curDistance;
        for (int neighbour : adj[curVertex]) {
            if (visited[neighbour])
                continue;
            q.push(std::make_pair(neighbour, curDistance + 1));
            visited[neighbour] = true;
        }
    }
    return -1;
}

std::vector<int> Graph::BFS(int start) {
    std::vector<bool> visited(V, false);
    std::vector<int> result;
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int curVertex = q.front();
        q.pop();
        result.push_back(curVertex);
        for (int neighbour : adj[curVertex]) {
            if (visited[neighbour])
                continue;
            q.push(neighbour);
            visited[neighbour] = true;
        }
    }
    return result;
}

std::vector<int> Graph::DFS(int start) {
    std::vector<bool> visited(V, false);
    std::vector<int> result;
    std::stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        if (visited[cur])
            continue;
        visited[cur] = true;
        result.push_back(cur);
        for (auto neighbour : adj[cur])
            s.push(neighbour);
    }
    return result;
}

std::vector<int> Graph::DFSRec(int start) {
    std::vector<bool> visited(V, false);
    std::vector<int> result;
    dfs_rec_help(start, visited, result);
    return result;
}

void Graph::dfs_rec_help(int start, std::vector<bool> &visited, std::vector<int> &result) {
    visited[start] = true;
    result.push_back(start);
    for (int neigh : adj[start])
        if (!visited[neigh])
            dfs_rec_help(neigh, visited, result);
}

bool Graph::containsCycle() {
    if (!oriented)
        throw std::exception();
    std::vector<bool> visited(V, false);
    std::vector<bool> inStack(V, false);

    for (int i = 0; i < V; ++i)
        if (contains_cycle_rec(i, visited, inStack))
            return true;
    return false;
}

bool Graph::contains_cycle_rec(int start, std::vector<bool> &visited, std::vector<bool> &inStack) {
    if (!visited[start]) {
        visited[start] = true;
        inStack[start] = true;

        for (int neigh : adj[start]) {
            if (!visited[neigh] && contains_cycle_rec(neigh, visited, inStack))
                return true;
            if (inStack[neigh])
                return true;
        }
    }
    inStack[start] = false;
    return false;
}

std::vector<int> Graph::TopologicalSort() {
    std::vector<bool> visited(V, false);
    std::stack<int> s;
    for (int i = 0; i < V; ++i)
        if (!visited[i])
            topological_sort_help(i, visited, s);
    std::vector<int> result(V);
    for (int i = 0; i < V; ++i) {
        result[i] = s.top();
        s.pop();
    }
    return result;
}

void Graph::topological_sort_help(int start, std::vector<bool> &visited, std::stack<int> &s) {
    visited[start] = true;

    for (int neigh : adj[start])
        if (!visited[neigh])
            topological_sort_help(neigh, visited, s);
    s.push(start);
}

bool Graph::isConnected() {
    if (oriented)
        throw std::exception();
    return this->DFS(0).size() == V;
}

bool Graph::isBiParted() {
    if (oriented)
        throw std::exception();
    std::vector<int> visited(V, false);
    for (int i = 0; i < V; ++i)
        if (visited[i] == 0 && is_bi_parted_help(i, visited))
            return true;
    return false;
}

//0 -> not visited
//1 -> white
//2 -> black
bool Graph::is_bi_parted_help(int start, std::vector<int> &visited) {
    std::queue<int> q;
    q.push(start);
    visited[start] = 1;
    while (!q.empty()) {
        int cur = q.front();
        int curColor = visited[cur];
        q.pop();
        for (int neigh : adj[cur]) {
            if (visited[neigh] == curColor)
                return false;
            if (visited[neigh] != 0)
                continue;
            q.push(neigh);
            visited[neigh] = curColor == 1 ? 2 : 1;
        }
    }
    return true;
}

Graph Graph::getTranspose() {
    Graph result(V);

    for(int i=0;i<adj.size();++i)
        for(int j=0;j<adj[i].size();++j)
            result.addEdge(adj[i][j],i);
    return result;
}

std::vector<std::vector<int>> Graph::getStronglyConnectedComponents() {
    std::vector<int> topo = TopologicalSort();

    Graph transposedGraph = getTranspose();

    std::vector<bool> visited(V);

    std::vector<std::vector<int>> result;

    for(int i : topo) {
        std::vector<int> currStrConCom;
        if(!visited[i])
            transposedGraph.dfs_rec_help(i,visited,currStrConCom);
        result.push_back(currStrConCom);
    }
    return result;
}

int main() {
    Graph g(7, false);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);;
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 6);
    Graph g1(8, true);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(2, 3);;
    g1.addEdge(3, 4);
    g1.addEdge(3, 5);
    g1.addEdge(5, 6);
    g1.addEdge(3, 7);

    std::vector<int> result = g.BFS(0);
    std::cout << "BFS: ";
    for (int &a : result)
        std::cout << a << ' ';
    std::cout << "\nShortest path from 0 to 3: ";
    std::cout << g.shortestPath(0, 3) << std::endl;
    result = g.DFS(0);
    std::cout << "DFS: ";
    for (int &a : result)
        std::cout << a << ' ';
    std::cout << "\nDFS_REC: ";
    result = g.DFSRec(0);
    for (int &a : result)
        std::cout << a << ' ';
    std::cout << "\nContains cycle: ";
    std::cout << g1.containsCycle() << std::endl;
    result = g.TopologicalSort();
    std::cout << "Topological sort: ";
    for (int &a : result)
        std::cout << a << ' ';
    std::cout << "\nIs connected: " << g.isConnected() << "\n";
    std::cout << "BiParted: " << g.isBiParted() << '\n';
    std::cout<<"Strongly connected components:";
    auto res  = g1.getStronglyConnectedComponents();
    for(int i=0;i<res.size();++i) {
        for (int j = 0; j < res.size(); ++j)
            std::cout << res[i][j] << ' ';
        std::cout<<'\n';
    }
    return 0;
}
