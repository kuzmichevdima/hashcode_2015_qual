#include "classes.h"

struct State {
    int cost, prev;
};

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
    for (auto& t : targets) {
        for (auto & pos : get_coverage(t)) {
            ++res[0][pos.fi][pos.se];
        }
    }

    for (int t = 1; t <= T; ++t) {
        for (int x = 0; x < grid.R; x++) {
            for (int y = 0; y < grid.C; y++) {
                res[t][x][y] = res[t - 1][x][y];
                for (auto& b : balloons) {
                    auto pos = start_cell;

                }
            }
        }
    }


}

int main() {
    read_input();

    vector<vector<vector<vector<State>>>> dp;

    vector<vector<vector<int>>> cost = get_cost({});


    for (int balloon = 0; balloon < B; ++balloon) {

    }

    return 0;
}