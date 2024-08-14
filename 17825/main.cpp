#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int solution(const vector<int>& scores, const vector<vector<int>>& map, const vector<int>& dice) {
    queue<vector<int>> q;
    q.push({0,0,0,0,0,0}); // 각 말의 위치, 현재점수, 현재 depth

    while(!q.empty()) {
        const vector<int> cur = q.front();
        const int depth = cur[5];
        if (depth == 10) break;
        q.pop();

        // map을 따라 dice[depth]만큼 이동 (next에 반영)
        // 종료 이상으로 이동하는지 확인
        // - 종료이상이면, 종료 위치로 고정
        // 시작점에 파란화살 존재여부 확인
        // 중간길에는 빨간화살 따라가도록 적용
        // 이미 말이 존재하는지 확인
        // - 존재하면, continue
        // - 존재하지 않으면, 이동
        // 점수 추가 후, depth에 1 더해서 queue에 삽입 (next에 반영)
        for (int i = 0; i < 4; ++i) {
            vector<int> next(cur.begin(), cur.end());
            for (int j = 0; j < dice[depth]; ++j) {
                if (next[i] == 32) break;
                if (j == 0 && map[next[i]].size() == 2) {
                    next[i] = map[next[i]][1];
                } else {
                    next[i] = map[next[i]][0];
                }
            }
            if (next[i] == 32) {
                next[5] += 1;
                q.push(next);
                continue;
            }
            bool already_exist = false;
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                if (next[i] == next[j]) already_exist = true;
            }
            if (!already_exist) {
                next[4] += scores[next[i]];
                next[5] += 1;
                q.push(next);
            }
        }
    }

    int answer = -1;

    for (int i = 0; i < q.size(); ++i) {
        answer = answer < q.front()[4]? q.front()[4] : answer;
        q.pop();
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> scores = {
        0, 2, 4, 6, 8, // 0(시작) ~ 4
        10, 12, 14, 16, 18, // 5 ~ 9
        20, 22, 24, 26, 28, // 10 ~ 14
        30, 32, 34, 36, 38, // 15 ~ 19
        13, 16, 19, 25, 26, 27, 28, // 20 ~ 26
        22, 24, 30, 35, 40, 0, // 27 ~ 32(도착)
    };

    vector<vector<int>> map(33);

    for (int i = 0; i < 19; ++i) {
        map[i].push_back(i+1);
    }
    map[19].push_back(31);
    map[5].push_back(20); // blue line
    map[20].push_back(21);
    map[21].push_back(22);
    map[22].push_back(23);
    map[15].push_back(26); // blue line
    map[26].push_back(25);
    map[25].push_back(24);
    map[24].push_back(23);
    map[10].push_back(27); // blue line
    map[27].push_back(28);
    map[28].push_back(23);
    map[23].push_back(29);
    map[29].push_back(30);
    map[30].push_back(31);
    map[31].push_back(32);

    // blue line이 있을 경우 size = 2이고, blue line은 두 번째 index임.

    vector<int> dice(10);

    for (int i = 0; i < 10; i++) cin >> dice[i];

    cout << solution(scores, map, dice);

    return 0;
}