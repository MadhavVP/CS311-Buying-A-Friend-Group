/*
 * Author: Madhav V.
 * It is ok to share my code anonymously for educational purpose
 */

#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define vvi vector<vector<int>>
#define vvl vector<vector<long>>
#define vi  vector<int>
#define ll long long
#define EPS 1e-6

vector<string> split(const string& s, char d) {
        vector<string> ret;
        string tok;
        istringstream stream(s);

        while (getline(stream, tok, d)) {
                ret.push_back(tok);
        }

        return ret;
}

int bfs(vector<tuple<int,int,int>> edges, int n) {
        vvi adj(n, vector(0,0));
        for (auto x : edges) {
                int u = get<1>(x);
                int v = get<2>(x);
                adj[u].push_back(v);
                adj[v].push_back(u);
        }
        vector<int> visited(n, 0);
        queue<int> q;
        q.push(0);
        visited[0] = 1;
        int i = 1;
        while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int x : adj[v]) {
                        if (visited[x] == 0) {
                                i++;
                                visited[x]++;
                                q.push(x);
                        }
                }
        }
        return (i == n ? 1 : 0);
}

void solve() {
        int n;
        cin >> n;
        map<string, int> names;
        int p = 0;
        string line;
        getline(cin, line);
        for (int i = 0; i < n; i++) {
                getline(cin, line);
                names[line] = p++;
        }
        int u,v, c;
        int m;
        cin >> m;
        getline(cin, line);
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < m; i++) {
                getline(cin, line);
                vector<string> args = split(line, ' ');
                u = names[args[0]];
                v = names[args[1]];
                c = stoi(args[2]);
                edges.push_back(make_tuple(c, u, v));

        }
        int x;
        cin >> x;
        getline(cin, line);
        for (int i = 0; i < x; i++) {
                getline(cin, line);
                vector<string> args = split(line, ' ');
                u = names[args[0]];
                v = names[args[1]];
                edges.push_back(make_tuple(0, u ,v));
        }
        ll ret = LLONG_MAX;
        vector<int> ep(edges.size(), 1);
        for (int i = 0; i < n - 1; i++) {
                ep[i] = 0;
        }
        // Student brute forces all possible combinations of edges to make a tree, returns the min
        do {
                vector<tuple<int, int, int>> selectedEdges;
                ll cost = 0;
                for (int i = 0; i < edges.size(); i++) {
                        if (ep[i] == 0) {
                                selectedEdges.push_back(edges[i]);
                                cost += get<0>(edges[i]);
                        }
                }
                if (bfs(selectedEdges, n)) {
                        ret = min(ret, cost);
                }
        } while (next_permutation(ep.begin(), ep.end()));
        cout << ret;
}

int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        //      int t;
        //      cin >> t;
        //      while (t--)
        solve();
}