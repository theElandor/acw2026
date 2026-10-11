#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
#include <set>
using namespace std;
pair<string, int> bfs(string start, map<string, vector<string>> &G){
    queue<pair<string, int>> Q;
    Q.push(make_pair(start, 0));
    set<string> visited;
    visited.insert(start);
    int max_hops = -1;
    string farthest = "";
    while (!Q.empty()){
        pair<string, int> current = Q.front(); Q.pop();
        string current_node = current.first;
        int current_hops = current.second;
        if(current_hops > max_hops){
            max_hops = current_hops;
            farthest = current_node;
        }
        for(int i = 0; i < G[current_node].size(); i++){
            if(visited.find(G[current_node][i]) == visited.end()){
                visited.insert(G[current_node][i]);
                Q.push(make_pair(G[current_node][i], current_hops+1));
            }
        }
    }
    return make_pair(farthest, max_hops);
}
int main(int argc, char **argv){
    ifstream is(argv[1]);
    map<string, vector<string>> G;
    vector<pair<string,string>> edges;
    string u,v,separator;
    string start = "";
    while(is.peek() != EOF){
        is>>u>>separator>>v;
        if(start == "") {start = u;}
        G[u].push_back(v);
        G[v].push_back(u);
        edges.emplace_back(u, v);
    }
    // 1) BFS and keep farthest point
    auto [farthest, max_hops] = bfs(start, G);
    cout<<"started from: "<<start<<endl;
    cout<<"Farthest point: "<<farthest<<endl;
    cout<<max_hops<<endl;
    // 2) BFS again from farthest point and find the diameter of the tree!
    cout<<"started from: "<<farthest<<endl;
    auto [farthest_2, max_hops_2] = bfs(farthest, G);
    cout<<"Farthest point: "<<farthest_2<<endl;
    cout<<max_hops_2<<endl;
    return 0;
}