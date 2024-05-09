#include <functional>
#include <queue>
#include <utility>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <climits>

using namespace std;

class UnionFind{
    unordered_map<int, int> parent;
    unordered_map<int, int> size;
    public:
        UnionFind() {}

        void create_set(int u){
            parent[u] = u;
            size[u] = 1;
        }

        int find_set(int u){
            if (parent[u] == u) return u;
            return parent[u] = find_set(parent[u]);
        }

        void union_set(int u, int v){
            u = find_set(u);
            v = find_set(v);
            if (u != v){
                if (size[u] > size[v]){
                    parent[v] = u;
                    size[u]+= size[v];
                }else {
                    parent[u] = v;
                    size[v]+= size[u];
                }
            }
        }
};

class Graph{
    private:
        // detect cycle in un-directed graph
        static bool ud_detect_cycle_dfs(const vector<vector<int>>& adj, vector<bool>& visited, int u, int parent){
            visited[u] = true;
            for (const int& v: adj[u]){
                if (v == parent)continue;
                if (visited[v] || ud_detect_cycle_dfs(adj, visited, v, u))return true;
            }
            return false;
        }
        
        using int2 = pair<int,int>;
        static bool ud_detect_cycle_bfs(const vector<vector<int>>& adj, vector<bool>& visited, int u){
            queue<int2> q;
            q.push({u, -1});
            visited[u] = true;
            while (!q.empty()){
                auto item = q.front();q.pop();
                int u = item.first;
                int parent = item.second;
                for (const int& v: adj[u]){
                    if (v == parent)continue;
                    if (visited[v]) return true;
                    visited[v] = true;
                    q.push({v, u});
                }
            }
            return false;
        }

        static bool directed_detect_cycle_dfs(const vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& in_stack, int u, int parent){
            visited[u] = true;
            in_stack[u] = true;
            for (const int& v: adj[u]){
                if (v == parent)continue;
                if (visited[v] && in_stack[v]) return true;
                else if (!visited[v] && directed_detect_cycle_dfs(adj, visited, in_stack, v, u)) return true;
            }
            in_stack[u] = false;
            return false;
        }
        
        static bool is_bipartite(const vector<vector<int>>& adj, vector<int>& color, int u, int color_with){
            color[u] = color_with;
            int new_color = (color_with + 1)%2;
            for (const int& v: adj[u]){
                if (color[v] == color_with) return false;
                else if (color[v] == -1 && !is_bipartite(adj, color, v, new_color)) return false;
            }
            return true;
        }
    public:
        static vector<vector<int>> get_adjacency_list(const vector<vector<int>>& matrix){
            int N = matrix.size();
            vector<vector<int>> list(N);
            for (int i=0;i<N;i++){
                for (int j=0;j<N;j++){
                    if (matrix[i][j] == 1){
                        list[i].push_back(j);
                    }
                }
            }
            return list;
        }

        // detect cycle in un-directed graph
        static bool ud_detect_cycle_dfs(const vector<vector<int>>& adj){
            int N = adj.size();
            vector<bool> visited(N, false);
            for (int u=0;u<N;u++){
                if (!visited[u] && ud_detect_cycle_dfs(adj, visited, u, -1))return true;
            }
            return false;
        }

        static bool ud_detect_cycle_bfs(const vector<vector<int>>& adj){
            int N = adj.size();
            vector<bool> visited(N, false);
            for (int u=0;u<N;u++){
                if (!visited[u] && ud_detect_cycle_bfs(adj, visited, u)) return true;
            }
            return false;
        }

        static bool ud_detect_cycle_union_find(const vector<vector<int>>& adj){
            int N = adj.size();
            UnionFind uf;
            for (int u=0;u<N;u++)uf.create_set(u);
            for (int u=0;u<N;u++){
                for (const int& v: adj[u]){
                    if (v > u){
                        int leader_u = uf.find_set(u);
                        int leader_v = uf.find_set(v);
                        if (leader_u == leader_v) return true;
                        uf.union_set(u, v);
                    }
                }
            }
            return false;
        }

        static bool directed_detect_cycle_dfs(const vector<vector<int>>& adj){
            int N = adj.size();
            vector<bool> visited(N, false), in_stack(N, false);
            for (int u=0;u<N;u++){
                if (!visited[u] && directed_detect_cycle_dfs(adj, visited, in_stack, u, -1)) return true;
            }
            return false;
        }

        static bool directed_detect_cycle_bfs(const vector<vector<int>>& adj){
            int N = adj.size();
            vector<int> in_order(N, 0);
            for (int u=0;u<N;u++){
                for (const int& v: adj[u])in_order[v]++;
            }
            queue<int> q;
            int count{0};
            for (int u=0;u<N;u++){
                if (in_order[u] == 0){
                    q.push(u);
                    count++;
                }
            }
            while (!q.empty()){
                int u = q.front();q.pop();
                for (const int& v: adj[u]){
                    in_order[v]--;
                    if (in_order[v] == 0){
                        count++;
                        q.push(v);
                    }
                }
            }
            return count != N;
        }

        static bool is_bipartite(const vector<vector<int>>& adj){
            int N = adj.size();
            vector<int> color(N, -1);
            for (int u=0;u<N;u++){
                if (color[u] == -1 && !is_bipartite(adj, color, u, 0)) return false;
            }
            return true;
        }

        // calculate shortest path on weight graph
        // adj: u -> [u, weight]
        static vector<int> shortest_path(const vector<vector<pair<int, int>>>& adj, int source){
            int N = adj.size();
            vector<int> dist(N, INT_MAX);
            priority_queue<int2, vector<int2>, greater<int2>> q;
            q.push({0, source});
            dist[source] = 0;
            while (!q.empty()){
                auto item = q.top();q.pop();
                int u = item.second;
                int d = item.first;
                for (auto e: adj[u]){
                    int v = e.first;
                    int w = e.second;
                    if (d + w < dist[v]){
                        dist[v] = d + w;
                        q.push({d + w, v});
                    }
                }
            }
            return dist;
        }
};

int main(){
    {
        // Test case 1: Graph without cycle
        vector<vector<int>> graph1 = {
            {1, 2},
            {0, 3},
            {0, 3},
            {1, 2}
        };
        assert(Graph::ud_detect_cycle_dfs(graph1));
        assert(Graph::ud_detect_cycle_bfs(graph1));
        assert(Graph::ud_detect_cycle_union_find(graph1));

        // Test case 2: Graph with cycle
        vector<vector<int>> graph2 = {
            {1, 2},
            {0, 3},
            {0, 4},
            {1},
            {2}
        };
        assert(!Graph::ud_detect_cycle_dfs(graph2));
        assert(!Graph::ud_detect_cycle_bfs(graph2));
        assert(!Graph::ud_detect_cycle_union_find(graph2));

        {
            // Test case 1: Directed acyclic graph
            vector<vector<int>> dag = {
                {1},
                {2},
                {},
                {0}
            };
            assert(!Graph::directed_detect_cycle_dfs(dag));

            // Test case 2: Directed graph with cycle
            vector<vector<int>> graph_with_cycle = {
                {1},
                {2},
                {0}
            };
            assert(Graph::directed_detect_cycle_dfs(graph_with_cycle));
        }
        {
            // Test case 1: Bipartite graph
            vector<vector<int>> bipartite_graph = {
                {1, 3},
                {0, 2},
                {1, 3},
                {0, 2}
            };
            assert(Graph::is_bipartite(bipartite_graph));

            // Test case 2: Non-bipartite graph
            vector<vector<int>> non_bipartite_graph = {
                {1, 2, 3},
                {0, 2},
                {0, 1, 3},
                {0, 2}
            };
            assert(!Graph::is_bipartite(non_bipartite_graph));
        }
        {
            // Weighted graph representation
            vector<vector<pair<int, int>>> weighted_graph = {
                {{1, 5}, {2, 3}},
                {{0, 5}, {2, 2}, {3, 6}},
                {{0, 3}, {1, 2}, {3, 7}},
                {{1, 6}, {2, 7}}
            };

            assert(Graph::shortest_path(weighted_graph, 0) == vector<int>({0, 5, 3, 10}));
        }
    }
}