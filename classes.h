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

typedef vector<vector<char>> Solution;

struct Grid {
    int R, C, A;
    vector<vector<vector<pii>>> wind;
};

Grid grid;

struct Position {
    int x, y, h;
    Position move_ballon(int h_delta = 0) {
        Position res = *this;
        assert(!(h == 0 && h_delta == -1));
        res.h += h_delta;
        assert(res.h <= grid.A);
        const pii& w = (res.h == 0? pii(0, 0) : grid.wind[res.h - 1][x][y]);
        res.x += w.first;
        res.y += w.second;
        if (res.y < 0) {
            res.y += grid.C;
        } else if (res.y >= grid.C) {
            res.y -= grid.C;
        }
        if (!(res.x >= 0 && res.x < grid.R)) {
            res.h = -1; // hack
        }
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

int sqr(int x) {
    return x * x;
}

int calc_score(const Solution& sol) {
    vector<Position> pos(B);
    forn(i, B) {
        pos[i].x = start_cell.fi;
        pos[i].y = start_cell.se;
    }
    int score = 0;
    vector<bool> in_range(B, true);
    forn(turn, T) {
        forn(bal, B) {
            int delta_h = sol[turn][bal];
            pos[bal].h += delta_h;
            //printf("turn = %d bal = %d delta_h = %d h = %d \n", turn, bal, delta_h, pos[bal].h);
            if (pos[bal].h < 0 || pos[bal].h > grid.A || (pos[bal].h == 0 && delta_h == -1)) {
                printf("bad height %d for baloon %d after turn %d\n. Go fuck yourself", pos[bal].h, bal, turn); 
                exit(1);
            }
            if (in_range[bal] && pos[bal].h > 0) {
                pii delta = grid.wind[pos[bal].h - 1][pos[bal].x][pos[bal].y];
                pos[bal].x += delta.fi;
                pos[bal].y = (pos[bal].y + delta.se + grid.C) % grid.C;
                if (pos[bal].x < 0 || pos[bal].x >= grid.R)
                    in_range[bal] = false;
            }
        }
        for(pii target : targets) {
            bool covered = false;
            forn(bal, B) if (in_range[bal] && pos[bal].h > 0) {
                int deltay = abs(pos[bal].y - target.se);
                int col_dist = min(deltay, grid.C - deltay);
                int tmp = sqr(pos[bal].x - target.fi) + sqr(col_dist);
                if (tmp <= V * V) {
                    covered = true;
                    break;
                }
            }
            if (covered)
                score++;
        }
    }
    return score;
}
