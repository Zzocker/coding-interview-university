#include <bits/stdc++.h>

using namespace std;

template <typename T> void print(const vector<T>& A){
    for (auto a: A)cout << a << ' ';
    cout << endl;
}

// graph representation
// 1. Adjacency Matrix SC O(n*n), good if we want to find does an edge exists between node u and v
// 2. Adjacency List : Good for sparse graph SC O(n + m)

vector<int> bfs(const vector<vector<int>>& list, int start);
int connected_components(const vector<vector<int>>& list);
void shortest_path(const vector<int>& parent, int start, int end);

int main(){
    vector<vector<int>> list{
        {},
        {2,3}, // 1
        {1,3,5,4}, // 2
        {7,8,5,2,1}, // 3
        {2,5}, // 4
        {4,2,3,6}, // 5
        {5}, // 6
        {3,8}, // 7
        {3,7}, // 8
        {10}, // 9
        {9}, // 10
        {12}, // 11
        {11,13}, // 12
        {12}, // 13
    };

    auto parent = bfs(list, 1);
    shortest_path(parent, 1, 6);
    int components = connected_components(list);
    cout << "Total connected components in graph is " << components << endl;
}

void process_vertex(int v){
    cout << "process vertex : "<< v << endl;
}

void process_edge(int v, int u){
    cout << "process edge : " << v << "---" << u << endl;
}

void shortest_path(const vector<int>& parent, int start, int end){
    int len = 0;
    int dest = end;
    while (start != end){
        end = parent[end];
        len++;
    }
    cout << "shortest path between " << start << " and " << dest  << " is " << len << endl;
}

// O(|V| + |E|)
vector<int> bfs(const vector<vector<int>>& list, vector<bool>& discovered, int start){
    int n = list.size(); // |V|
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(start);
    discovered[start] = true;
    while (!q.empty()){
        int v = q.front();q.pop();
        process_vertex(v);
        for (auto u: list[v]){
            if (!discovered[u]){
                discovered[u] = true;
                parent[u] = v;
                process_edge(v, u);
                q.push(u);
            }
        }
    }
    return parent;
}

vector<int> bfs(const vector<vector<int>>& list, int start){
    vector<bool> discoverd(list.size(), false);
    return bfs(list, discoverd, start);
}

int connected_components(const vector<vector<int>>& list){
    vector<bool> discovered(list.size(), false);
    int c{0};
    for (int v=1;v<list.size();v++){
        if (!discovered[v]){
            c++;
            bfs(list, discovered, v);
        }
    }
    return c;
}