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

struct Grid {
    int R, C, A;
    vector<vector<vi>> wind;
};

void read_input(Grid& grid, int& V, int& B, int&T, pii& start_cell, vector<pii>& targets) {
    cin >> grid.R >> grid.C >> grid.A;
    int targets_cnt;
    cin >> targets_cnt >> V >> B >> T >> start_cell.fi >> start_cell.se;
    targets.resize(targets_cnt);
    forn(i, targets_cnt) {
        cin >> targets[i].fi >> targets[i].se;
    }
    grid.wind.resize(grid.A);
    forn(i, grid.A) {
        grid.wind[i].resize(grid.R);
        forn(j, grid.R) {
            grid.wind[i][j].resize(grid.C);
            forn(k, grid.C)
                cin >> grid.wind[i][j][k];
        }
    }
}
