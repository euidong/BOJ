#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> rotate(const vector<int>& gear, const int d) {
    const int n = gear.size();
    vector<int> r_gear(n);
    int adder;
    if (d == 1) {
        adder = n - 1;
    } else {
        adder = 1;
    }
    for (int i = 0; i < n; ++i) {
        r_gear[i] = gear[(i + adder) % n];
    }
    return r_gear;
}

int solution(vector<vector<int>> gears, const vector<pair<int, int>>& ops) {
    const int op_n = ops.size();

    for (int i = 0; i < op_n; ++i) {
        const int target = ops[i].first;
        const int d = ops[i].second;

        vector<pair<int, int>> candidate;
        candidate.push_back(make_pair(target, d));
        int prev_d = d;
        for (int j = target; j < gears.size() - 1; ++j) {
            if(gears[j][2] != gears[j+1][6]) {
                candidate.push_back(make_pair(j+1, -prev_d));
            } else {
                break;
            }
            prev_d = -prev_d;
        }
        prev_d = d;
        for (int j = target; j > 0; --j) {
            if (gears[j][6] != gears[j-1][2]) {
                candidate.push_back(make_pair(j-1, -prev_d));
            } else {
                break;
            }
            prev_d = -prev_d;
        }
        for (int j = 0; j < candidate.size(); ++j) {
            const int gear_idx = candidate[j].first;
            const int direction = candidate[j].second;
            gears[gear_idx] = rotate(gears[gear_idx], direction);
        }
    }

    int answer = 0;

    for (int i = 0; i < gears.size(); ++i) {
        if (gears[i][0] == 1) {
            answer += pow(2,i);
        }
    }

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<int>> gears;
    for (int _ = 0; _ < 4; _++) {
        string input;
        cin >> input;
        vector<int> gear;
        for (int i = 0; i < input.size(); ++i) {
            gear.push_back(input[i] - '0');
        }
        gears.push_back(gear);
    }
    int K;
    cin >> K;

    vector<pair<int, int>> ops;
    for (int i = 0; i < K; ++i) {
        int g_idx, op_idx;
        cin >> g_idx >> op_idx;
        ops.push_back(make_pair(g_idx - 1, op_idx));
    }

    cout << solution(gears, ops) << '\n';

    return 0;
}