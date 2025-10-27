/*
 * Author: Madhav V.
 * It is ok to share my code anonymously for educational purpose
 */

#include <bits/stdc++.h>
#define MAX_V 10000
#define ld long double
#define vvi vector<vector<int>>
#define vvl vector<vector<long>>
#define vi  vector<int>
#define ll long long
#define EPS 1e-6
#define BIG_PRIME 127

using namespace std;

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

void create(int testNum) {
        ofstream infile("rand_tc" + to_string(testNum) + ".in");
        ofstream txtfile("rand_tc" + to_string(testNum) + ".txt");

        txtfile << "This test case was randomly generated. The things we *purposefully* considered were integer overflow and many many edges.\n";
        txtfile.close();
        int n = rand() % MAX_V;
        infile << n << "\n";
        int m = (rand() % max(((((n * n) - n) / 2) - (n - 1)), 1));
        m = (m < 0 ? 0 : m);
        m += n - 1;
        vector<int> V(n, 0);
        for (int i = 0; i < n; i++) {
                V[i] = i;
                infile << "v" << i << "\n";
        }

        int lucky = rand() % MAX_V;
        for (int i = 0; i < lucky; i++) {
                next_permutation(V.begin(), V.end());
        }

        // We're gonna make 1 gauranteed tree by ordering the vertices randomly
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
                edges.push_back(make_tuple(V[i], V[i + 1], rand() % (LLONG_MAX / (2 * n))));
        }

        for (int i = n - 1; i < m; i++) {
                edges.push_back(make_tuple(rand() % n, rand() % n, rand() % (LLONG_MAX / (2 * n))));
        }

        for (int i = 0; i < lucky; i++) {
                next_permutation(edges.begin(), edges.end());
        }

        infile << m << "\n";

        for (auto e : edges) {
                infile << "v" << get<0>(e) << " v" << get<1>(e) << " " << get<2>(e) << "\n";
        }

        int preconnections = rand() % (rand() % (rand() % (rand() % n - 1) + 1) + 1) + 1; // Not actually sure if this does anything but the idea was that I generally want not too many frees

        for (int i = 0; i < lucky / preconnections; i++) {
                next_permutation(V.begin(), V.end());
        }

        infile << preconnections << "\n";
        for (int i = 0; i < preconnections; i++) {
                infile << "v" << V[i] << " v" << V[i + 1] << "\n";
        }
        infile.close();
}

void solve(int testNum) {
        ofstream outfile("rand_tc" + to_string(testNum) + ".out");
        ifstream infile;
        string in = "./rand_tc" + to_string(testNum) + ".in";
        infile.open(in);
        int n;
        map<string, int> names;
        int p = 0;
        string line;
        getline(infile, line);
        n = stoi(line);
        for (int i = 0; i < n; i++) {
                getline(infile, line);
                names[line] = p++;
        }
        int u,v, c;
        int m;
        getline(infile, line);
        m = stoi(line);
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < m; i++) {
                getline(infile, line);
                vector<string> args = split(line, ' ');
                u = names[args[0]];
                v = names[args[1]];
                c = stoi(args[2]);
                edges.push_back(make_tuple(c, u, v));

        }
        int x;
        getline(infile, line);
        x = stoi(line);
        for (int i = 0; i < x; i++) {
                getline(infile, line);
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
        outfile << ret;
        outfile.close();
        infile.close();
}

int main() {
        for (int i = 1; i <= BIG_PRIME; i++) {
                create(i);
                solve(i);
        }
}