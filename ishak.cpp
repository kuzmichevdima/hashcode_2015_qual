#include "classes.h"

struct PosT {
    int t, x, y, h, score;
	PosT() :
		t(0),
		x(0),
		y(0),
		h(0),
		score(0) {}
    PosT(int t, int x, int y, int h, int score) : t(t), x(x), y(y), h(h), score(score) {}
};
typedef vector<vector<vector<vector<PosT>> > > DP;
typedef vector<vector<vi >> Cost;
typedef vector<vector<vector<pii>>> Nei;
typedef vector<vector<vector<bool> > > Covered;


inline void upd(int t, int x, int y, int h, int tfr, int xfr, int yfr, int hfr, DP& dp, const Cost& cost) {
    //fprintf(stderr, "upd %d %d %d %d\n", t, x, y, h);
    int new_score = dp[tfr][xfr][yfr][hfr].score + cost[t][x][y];
    if (new_score > dp[t][x][y][h].score) {
        dp[t][x][y][h] = {tfr, xfr, yfr, hfr, new_score};
    }
}

void get_cost(Cost& cost, const Covered& covered) {
    forn(t, T)
        forn(x, grid.R)
            forn(y, grid.C)
                cost[t][x][y] = 0;
    forn(x, grid.R)
        forn(y, grid.C) {
            for (pii target : targets)
                if (covers({x, y}, target))
                    forn(t, T)
                        cost[t][x][y] += !covered[t][target.fi][target.se];
        }
}

void update_covered(Covered& covered, const PosT& pos, const Nei& neighbors) {
    for (pii nei : neighbors[pos.x][pos.y]) {
        covered[pos.t][nei.fi][nei.se] = true;
    }
}

int normy(int y) {
    if (y < 0)
        y += grid.C;
    if (y >= grid.C)
        y -= grid.C;
    return y;
}

vector<char> AddBaloon(const Solution& sol) {
    Nei neighbors(grid.R);
    forn(x, grid.R) {
        neighbors[x].resize(grid.C);
        forn(y, grid.C) {
            forn(i, grid.R)
                forn(j, grid.C)
                    if (covers({x, y}, {i, j})) {
                        neighbors[x][y].pb({i, j});
                    }
        }
    }
    Covered covered(T + 1);
    Cost cost(T + 1);
    forn(t, T + 1) {
        covered[t].resize(grid.R);
        cost[t].resize(grid.R);
        forn(x, grid.R) {
            covered[t][x].resize(grid.C);
            cost[t][x].resize(grid.C);
        }
    }
    assert((int)sol.size() == T);
    vector<Position> pos(B);
    forn(i, B) {
        pos[i].x = start_cell.fi;
        pos[i].y = start_cell.se;
    }
    vector<bool> in_range(B, true);
    forn(turn, T) {
        forn(bal, B) {
            int delta_h = sol[turn][bal];
            pos[bal].h += delta_h;
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
                else {
                    update_covered(covered, {turn + 1, pos[bal].x, pos[bal].y, pos[bal].h, 0}, neighbors);
                }
            }
        }
    }
    DP dp(T + 1);
    forn(t, T + 1) {
        dp[t].resize(grid.R);
        forn(x, grid.R) {
            dp[t][x].resize(grid.C);
            forn(y, grid.C) {
                dp[t][x][y].resize(grid.A + 1);
            }
        }
    }

    forn(t, T + 1)
        forn(x, grid.R)
            forn(y, grid.C)
                forn(h, grid.A + 1)
                    dp[t][x][y][h].score = 0;
    dp[0][start_cell.fi][start_cell.se][0] = {0, 0, 0, 0, 1};
    PosT best_pos;
    get_cost(cost, covered);
    forn(t, T + 1) {
        forn(x, grid.R)
            forn(y, grid.C)
                forn(h, grid.A + 1)
                    if (dp[t][x][y][h].score) {
                        if (dp[t][x][y][h].score > best_pos.score) {
                            best_pos = {t, x, y, h, dp[t][x][y][h].score};
                        }
                        if (t == T)
                            continue;
                        fore(deltah, -1, 1) {
                            int newh = h + deltah;
                            if (newh < 0 || newh > grid.A || (newh == 0 && deltah == -1))
                                continue;
                            int newx, newy;
                            if (newh != 0) {
                                newx = x + grid.wind[newh - 1][x][y].fi;
                                newy = normy(y + grid.wind[newh - 1][x][y].se);
                            } else {
                                newx = x;
                                newy = y;
                            }
                            if (newx < 0 || newx >= grid.R)
                                continue;
                            upd(t + 1, newx, newy, newh, t, x, y, h, dp, cost);
                        }
                    }
    }
    vector<char> result(T);
    assert(best_pos.score > 0);
    while(best_pos.t > 0) {
        PosT new_pos = dp[best_pos.t][best_pos.x][best_pos.y][best_pos.h];
        result[best_pos.t - 1] = best_pos.h - new_pos.h;
        best_pos = new_pos;
    }
    return result;
}

int main() {
    //freopen("sample", "r", stdin);
    read_input();
    Solution sol(T);
    forn(i, T)
        sol[i].resize(B);
    Nei neighbors(grid.R);
    forn(x, grid.R) {
        neighbors[x].resize(grid.C);
        forn(y, grid.C) {
            forn(i, grid.R)
                forn(j, grid.C)
                    if (covers({x, y}, {i, j})) {
                        neighbors[x][y].pb({i, j});
                    }
        }
    }
    Covered covered(T + 1);
    Cost cost(T + 1);
    forn(t, T + 1) {
        covered[t].resize(grid.R);
        cost[t].resize(grid.R);
        forn(x, grid.R) {
            covered[t][x].resize(grid.C);
            cost[t][x].resize(grid.C);
        }
    }
    DP dp(T + 1);
    forn(t, T + 1) {
        dp[t].resize(grid.R);
        forn(x, grid.R) {
            dp[t][x].resize(grid.C);
            forn(y, grid.C) {
                dp[t][x][y].resize(grid.A + 1);
            }
        }
    }

    forn(b, B) {
        fprintf(stderr, "b = %d", b);
        forn(t, T + 1)
            forn(x, grid.R)
                forn(y, grid.C)
                    forn(h, grid.A + 1)
                        dp[t][x][y][h].score = 0;
        dp[0][start_cell.fi][start_cell.se][0] = {0, 0, 0, 0, 1};
        PosT best_pos;
        get_cost(cost, covered);
        /*forn(t, T)
            forn(x, grid.R)
                forn(y, grid.C)
                    printf("cost[%d][%d][%d] = %d\n", t, x, y, cost[t][x][y]);*/
        printf("b = %d\n", b);
        forn(t, T + 1) {
            forn(x, grid.R)
                forn(y, grid.C)
                    forn(h, grid.A + 1)
                        if (dp[t][x][y][h].score) {
                            if (dp[t][x][y][h].score > best_pos.score) {
                                best_pos = {t, x, y, h, dp[t][x][y][h].score};
                            }
                            //printf("t = %d x = %d y = %d h = %d\n", t, x, y, h);
                            if (t == T)
                                continue;
                            fore(deltah, -1, 1) {
                                int newh = h + deltah;
                                if (newh < 0 || newh > grid.A || (newh == 0 && deltah == -1))
                                    continue;
                                int newx, newy;
                                if (newh != 0) {
                                    newx = x + grid.wind[newh - 1][x][y].fi;
                                    newy = normy(y + grid.wind[newh - 1][x][y].se);
                                } else {
                                    newx = x;
                                    newy = y;
                                }
                                if (newx < 0 || newx >= grid.R)
                                    continue;
                                upd(t + 1, newx, newy, newh, t, x, y, h, dp, cost);
                            }
                        }
        }
        fprintf(stderr, "best score = %d\n", best_pos.score);
        assert(best_pos.score > 0);
        while(best_pos.t > 0) {
            update_covered(covered, best_pos, neighbors);
            PosT new_pos = dp[best_pos.t][best_pos.x][best_pos.y][best_pos.h];
            sol[best_pos.t - 1][b] = best_pos.h - new_pos.h;
            best_pos = new_pos;
        }
    }
    forn(t, T)
        printf("%d\n", sol[t][0]);
    printf("score = %d\n", calc_score(sol));
}

