#include <iostream>
#include<vector>
#include <queue>
#include<algorithm>
#include <climits>
#include<tuple>

class Graph {
    bool isOriented;
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj;

public:
    explicit Graph(int V = 0, bool isOriented = true);

    void addEdge(int start, int end, int weight);

    int dijkstra(int start, int end, std::vector<int> &path);

    std::vector<int> bellmanFord(int start);

    int prim();
};

class Graph2 {
    int V;
    std::vector<std::tuple<int, int, int>> edges;
public:
    explicit Graph2(int V = 0);

    void addEdge(int start, int end, int weight);

    std::vector<std::tuple<int, int, int>> kruskal();
};

Graph2::Graph2(int V) : V(V) {}

void Graph2::addEdge(int start, int end, int weight) {
    edges.emplace_back(start, end, weight);
}

Graph::Graph(int V, bool isOriented) : V(V), isOriented(isOriented) {}

void Graph::addEdge(int start, int end, int weight) {
    adj[start].push_back(std::make_pair(end, weight));
    if (!isOriented)
        adj[end].push_back(std::make_pair(start, weight));
}

int Graph::dijkstra(int start, int end, std::vector<int> &path) {
    std::vector<int> distances(V);
    std::vector<int> previous;

    struct vertexAndDistPair {
        int vertex;
        int distFromStart;

        bool operator<(const vertexAndDistPair &other) const {
            return distFromStart > other.distFromStart;
        }

        vertexAndDistPair(int vertex, int distfromStart) : vertex(vertex), distFromStart(distfromStart) {}
    };

    std::priority_queue<vertexAndDistPair> q;

    distances[start] = 0;

    q.push({start, 0});

    while (!q.empty()) {
        vertexAndDistPair cur = q.top();
        q.pop();
        for (int i = 0; i < adj[cur.vertex].size(); ++i) {
            int curNeigh = adj[cur.vertex][i].first;

            if (curNeigh == end) {
                while (end != start) {
                    if (curNeigh != start) {
                        path.push_back(curNeigh);
                        end = previous[curNeigh];
                    }
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
            }

            if (distances[curNeigh] > cur.distFromStart + adj[cur.vertex][i].second) {
                distances[curNeigh] = cur.distFromStart + adj[cur.vertex][i].second;
                q.push({curNeigh, cur.distFromStart + adj[cur.vertex][i].second});

                previous[curNeigh] = cur.vertex;
            }
        }
    }
    return -1;
}

std::vector<int> Graph::bellmanFord(int start) {
    std::vector<int> distances(V, INT_MAX);
    distances[start] = 0;
    for (int t = 0; t < V; ++t) {
        bool isLastIter = t == V - 1;
        for (int i = 0; i < V; ++i) {
            if (distances[i] == INT_MAX)
                continue;
            for (int j = 0; j < adj[i].size(); ++j) {
                if (distances[i] + adj[i][j].second < distances[adj[i][j].first]) {
                    if (isLastIter)
                        throw std::logic_error("Negative cycle!\n");
                    distances[adj[i][j].first] = distances[i] + adj[i][j].second;
                }
            }
        }
    }
}

struct UnionFind {
    std::vector<int> parents;

    explicit UnionFind(int V) : parents(V) {
        for (int i = 0; i < V; ++i)
            parents[i] = i;
    }

    int getRoot(int el) {
        while (parents[el] != el)
            el = parents[el];
        return el;
    }

    inline bool areInOneSet(int el1, int el2) {
        return getRoot(el1) == getRoot(el2);
    }

    inline void Union(int el1, int el2) {
        parents[getRoot(el1)] = getRoot(el2);
    }

};

std::vector<std::tuple<int, int, int>> Graph2::kruskal() {
    std::sort(edges.begin(), edges.end(),
              [](const std::tuple<int, int, int> &lhs, const std::tuple<int, int, int> &rhs) {
                  return std::get<2>(lhs) < std::get<2>(rhs);
              });

    int edgesIncluded = 0;

    UnionFind uf(V);
    
    std::vector<std::tuple<int, int, int>> mst;
    mst.reserve(V);

    for (int i = 0; i < edges.size() && edgesIncluded < V - 1; ++i) {
        auto &curEdge = edges[i];
        int start = std::get<0>(curEdge);
        int dest = std::get<1>(curEdge);
        int weight = std::get<2>(curEdge);

        if (uf.areInOneSet(start, dest)) {
            mst.push_back(curEdge);
        } else {
           uf.Union(start, dest);
        }
    }
    return mst;
}

int Graph::prim() {
    auto comp = [](const std::tuple<int, int, int> &lhs, const std::tuple<int, int, int> &rhs) {
        return std::get<2>(lhs) > std::get<2>(rhs);
    };
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(comp)> q(comp);
    std::vector<int> visited;
    q.emplace(0, 0, 0);
    int addEdges = 0;

    int result = 0;
    while (addEdges < V - 1) {
        auto cur = q.top();
        q.pop();

        if(visited[std::get<1>(cur)])
            continue;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
