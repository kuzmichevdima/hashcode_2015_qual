#pragma once
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
    vector<vector<vector<pii>>> wind;
};

Grid grid;

struct Position {
    int x, y, h;
    Position move_ballon(int h_delta = 0) {
        Position res = *this;
        res.h += h_delta;
        assert(res.h <= grid.A);
        const pii& w = grid.wind[h][x][y];
        res.x += w.first;
        res.y += w.second;
        return res;
    }
};

pii start_cell;
vector<pii> targets;
int V, B, T; // V - coverage radius, B - number of balloons, T - turns


void read_input() {
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
                cin >> grid.wind[i][j][k].fi >> grid.wind[i][j][k].se;
        }
    }
}
