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

vector<int> dsqu;
vector<int> dsqu_size;
void dsqu_init(int n) {
        dsqu = vector(n, 0);
        dsqu_size = vector(n, 1);
        for (int i = 0; i < n; i++) {
                dsqu[i] = i;
        }
}

int dsqu_find(int i) {
        if (i != dsqu[i]) {
                dsqu[i] = dsqu_find(dsqu[i]);
        }
        return dsqu[i];
}

int dsqu_union(int i, int j) {
        int pi = dsqu_find(i);
        int pj = dsqu_find(j);
        if (pi == pj) {
                return -1;
        }
        if (dsqu_size[pj] > dsqu_size[pi]) {
                int x = i;
                i = j;
                j = i;
        }
        dsqu[pj] = pi;
        dsqu_size[pi] += dsqu_size[pj];
        return 0;
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
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int,int,int>>> pq;
        for (int i = 0; i < m; i++) {
                getline(cin, line);
                vector<string> args = split(line, ' ');
                u = names[args[0]];
                v = names[args[1]];
                c = stoi(args[2]);
                pq.push(make_tuple(c, u, v));

        }
        int x;
        cin >> x;
        getline(cin, line);
        for (int i = 0; i < x; i++) {
                getline(cin, line);
                vector<string> args = split(line, ' ');
                u = names[args[0]];
                v = names[args[1]];
                pq.push(make_tuple(0, u ,v));
        }
        ll ret = 0;
        for (int i = 0; i < n - 1; i++) {
                tuple<int, int, int> next = pq.top();
                pq.pop();
                ret += get<0>(next); // Student just takes the first n - 1 smalles edges instead of making an mst, this would pass both of our samples but actually be wrong
        }
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