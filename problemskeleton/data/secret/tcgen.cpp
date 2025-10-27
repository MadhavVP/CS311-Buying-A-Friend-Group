/*
 * Author: Madhav V.
 * It is ok to share my code anonymously for educational purpose
 */

 #include <bits/stdc++.h>
#define MAX_V 10
using namespace std;
int main() {
        int n = rand() % MAX_V;
        cout << n << "\n";
        int m = (rand() % (int) floor(((pow(n, 2) - n) / 2) - (n - 1)));
        m = (m < 0 ? 0 : m);
        m += n - 1;
        vector<int> V(n, 0);
        for (int i = 0; i < n; i++) {
                V[i] = i;
                cout << "v" << i << "\n";
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

        cout << m << "\n";

        for (auto e : edges) {
                cout << "v" << get<0>(e) << " v" << get<1>(e) << " " << get<2>(e) << "\n";
        }

        int preconnections = rand() % (rand() % (rand() % (rand() % n - 1) + 1) + 1) + 1; // Not actually sure if this does anything but the idea was that I generally want not too many frees

        for (int i = 0; i < lucky / preconnections; i++) {
                next_permutation(V.begin(), V.end());
        }

        cout << preconnections << "\n";
        for (int i = 0; i < preconnections; i++) {
                cout << "v" << V[i] << " v" << V[i + 1] << "\n";
        }
}