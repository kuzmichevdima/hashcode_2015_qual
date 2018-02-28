#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>
#include "classes.h"

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: <inp> <out> \n");
        exit(1);
    }
    freopen(argv[1], "r", stdin);
    read_input();
    freopen(argv[2], "r", stdin);
    Solution sol(T);
    forn(i, T) {
        sol[i].resize(B);
        forn(j, B) {
            int d;
            assert(scanf("%d", &d) == 1);
            sol[i][j] = d;
        }
    }
    cout << calc_score(sol);
}

