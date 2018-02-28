#include "classes.h"

struct State {
    int cost, prev;
};

Position move_baloon(const Position& p) {

}

vector<vector<vector<int>>> get_cost(const Grid& grid, int V, int T, const vector<pii>& targets,
                                     const vector<vector<char>>& balloons) {

}

int main() {
    read_input(grid, V, B, T, start_cell, targets);

    vector<vector<vector<vector<State>>>> dp;

    vector<vector<vector<int>>> cost = init_cost(grid, targets);


    for (int balloon = 0; balloon < B; ++balloon) {

    }

    return 0;
}