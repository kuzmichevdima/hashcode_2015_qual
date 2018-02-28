#include "classes.h"

const int inf = 100000000;

struct State {
    int cost;
    Position prev;

    State() {
        cost = -inf;
    }

    void relax(int new_cost, const Position& last) {
        if (cost < new_cost) {
            cost = new_cost;
            prev = last;
        }
    }
};

Solution transpose(const Solution& sol) {
    Solution res(sol[0].size(), vector<char>(sol.size()));
    for (int i = 0; i < sol.size(); i++) {
        for (int j = 0; j < sol[0].size(); ++j) {
            res[j][i] = sol[i][j];
        }
    }
    return res;
}

vector<pii> get_coverage(const pii& pos) {
    vector<pii> res;
    for (int x = pos.first - V; x <= pos.first + V; ++x) {
        if (x < 0 || x >= grid.R) {
            continue;
        }
        for (int Y = pos.second - V; Y <= pos.second + V; ++Y) {
            int y = Y;
            if (y < 0) {
                y += grid.C;
            } else if (y >= grid.C) {
                y -= grid.C;
            }
            int deltay = abs(y - pos.second);
            int col_dist = min(deltay, grid.C - deltay);
            int tmp = sqr(x - pos.fi) + sqr(col_dist);
            if (tmp <= V * V) {
                res.emplace_back(x, y);
            }
        }
    }
    return res;
}


vector<vector<vector<int>>> get_cost(const vector<vector<char>>& balloons) {
    vector<vector<vector<int>>> res(T, vector<vector<int>>(grid.R, vector<int>(grid.C)));

    Position start_position;
    start_position.x = start_cell.first;
    start_position.y = start_cell.second;
    start_position.h = 0;
    vector<Position> ballons_pos(balloons.size(), start_position);
    for (int t = 0; t < T; ++t) {
        vector<vector<bool>> covered(grid.R, vector<bool>(grid.C));
        forn (i, balloons.size()) {
            ballons_pos[i] = ballons_pos[i].move_ballon(balloons[i][t]);
            if (ballons_pos[i].h != 0) {
                for (auto &pos : get_coverage({ballons_pos[i].x, ballons_pos[i].y})) {
                    covered[pos.fi][pos.se] = true;
                }
            }
        }

        for (auto& tar : targets) {
            if (!covered[tar.fi][tar.se]) {
                for (auto &pos : get_coverage(tar)) {
                    ++res[t][pos.fi][pos.se];
                }
            }
        }
    }
    return res;


}

int main() {
    freopen("/Users/tkhismatullin/github/hashcode_2015_qual/final_round.in.txt", "r", stdin);

    read_input();
    int sum = 0;

    vector<vector<vector<int>>> cost = get_cost({});
    Solution sol;
    for (int balloon = 0; balloon < B; ++balloon) {
        cerr << "ballon " << balloon << endl;
        vector<vector<vector<vector<State>>>> dp(T + 1,
                                                 vector<vector<vector<State>>> (grid.R,
                                                 vector<vector<State>> (grid.C,
                                                 vector<State> (grid.A + 1)))
                                                );
        dp[0][start_cell.first][start_cell.second][0].cost = 0;
        for (int t = 0; t < T; ++t) {
            for (int x = 0; x < grid.R; ++x) {
                for (int y = 0; y < grid.C; ++y) {
                    for (int h = 0; h <= grid.A; ++h) {
                        int cur_cost = dp[t][x][y][h].cost;
                        if (cur_cost == -inf) {
                            continue;
                        }
                        Position pos({x, y, h});
                        if (h > 1) {
                            Position down = pos.move_ballon(-1);
                            if (down.h != -1)
                                dp[t + 1][down.x][down.y][down.h].relax(cur_cost + cost[t][down.x][down.y], pos);
                        }
                        if (h < grid.A) {
                            Position up = pos.move_ballon(1);
                            if (up.h != -1)
                                dp[t + 1][up.x][up.y][up.h].relax(cur_cost + cost[t][up.x][up.y], pos);
                        }
                        Position stay = pos.move_ballon();
                        if (stay.h != 0) {
                            if (stay.h != -1)
                                dp[t + 1][stay.x][stay.y][stay.h].relax(cur_cost + cost[t][stay.x][stay.y], pos);
                        } else {
                            if (stay.h != -1)
                                dp[t + 1][stay.x][stay.y][stay.h].relax(cur_cost, pos);
                        }
                    }
                }
            }
        }
        int max_cost = -1;
        Position pos;
        for (int x = 0; x < grid.R; ++x) {
            for (int y = 0; y < grid.C; ++y) {
                for (int h = 0; h <= grid.A; ++h) {
                    int cur_cost = dp[T][x][y][h].cost;
                    if (cur_cost > max_cost) {
                        max_cost = cur_cost;
                        pos = {x, y, h};
                    };
                }
            }
        }
        int t = T;
        sol.emplace_back();
        assert(max_cost != -1);
        while (t > 0) {
            Position prev = dp[t][pos.x][pos.y][pos.h].prev;
            assert(abs(pos.h - prev.h) <= 1);
            sol.back().emplace_back(pos.h - prev.h);
            pos = prev;
            --t;
        }
        assert(pos.x == start_cell.fi && pos.y == start_cell.se);
        reverse(sol.back().begin(), sol.back().end());
        cost = get_cost(sol);
        sum += max_cost;
        cerr << "Score: " << max_cost << " " << "Sum: " << sum << endl;
    }

    cerr << "Dima score: " << calc_score(transpose(sol)) << endl;


    return 0;
}