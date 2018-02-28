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

int sqr(int x) {
    return x * x;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: <inp> <out> \n");
        exit(1);
    }
    freopen(argv[1], "r", stdin);
    Grid grid;
    pii start_cell;
    vector<pii> targets;
    int rad, B, T;
    read_input(grid, rad, B, T, start_cell, targets);
    freopen(argv[2], "r", stdin);
    vector<Position> pos(B);
    forn(i, B) {
        pos[i].x = start_cell.fi;
        pos[i].y = start_cell.se;
    }
    int score = 0;
    vector<bool> in_range(B, true);
    forn(turn, T) {
        forn(bal, B) {
            int delta_h;
            assert(scanf("%d", &delta_h) == 1);
            pos[bal].h += delta_h;
            //printf("turn = %d bal = %d delta_h = %d h = %d \n", turn, bal, delta_h, pos[bal].h);
            if (pos[bal].h < 0 || pos[bal].h > grid.A || (pos[bal].h == 0 && delta_h == -1)) {
                printf("bad height %d for baloon %d after turn %d\n. Go fuck yourself", pos[bal].h, bal, turn); 
                exit(1);
            }
            if (in_range[bal]) {
                pii delta = grid.wind[pos[bal].h - 1][pos[bal].x][pos[bal].y];
                pos[bal].x += delta.fi;
                pos[bal].y = (pos[bal].y + delta.se + grid.C) % grid.C;
                if (pos[bal].x < 0 || pos[bal].x >= grid.R)
                    in_range[bal] = false;
            }
        }
        for(pii target : targets) {
            bool covered = false;
            forn(bal, B) if (in_range[bal]) {
                int deltay = abs(pos[bal].y - target.se);
                int col_dist = min(deltay, grid.C - deltay);
                int tmp = sqr(pos[bal].x - target.fi) + sqr(col_dist);
                if (tmp <= rad * rad) {
                    covered = true;
                    break;
                }
            }
            if (covered)
                score++;
        }
    }
    printf("%d\n", score);
}

