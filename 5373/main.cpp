#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Cube {
private:
    vector<vector<vector<char>>> sides;
    void rotate(const int no, const int wise) {
        rotate_side(no, wise);
        rotate_around(no, wise);
    }

    void rotate_side(const int no, const int wise) {
        vector<vector<char>> n_side(3, vector<char>(3));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (wise == 0) {
                    n_side[i][j] = sides[no][2-j][i];
                } else {
                    n_side[i][j] = sides[no][j][2-i];
                }
            }
        }
        sides[no] = n_side;
    }
    void rotate_around(const int no, const int wise) {
        vector<char> temp(3);
        if (no == 0) { // 위(0)
            // 앞(2) < 오른(5) < 뒤(3) < 왼(4) < 앞(2)
            if (wise == 0) {
                temp[0] = sides[2][0][0];
                temp[1] = sides[2][0][1];
                temp[2] = sides[2][0][2];
                sides[2][0][0] = sides[5][0][0];
                sides[2][0][1] = sides[5][0][1];
                sides[2][0][2] = sides[5][0][2];
                sides[5][0][0] = sides[3][0][0];
                sides[5][0][1] = sides[3][0][1];
                sides[5][0][2] = sides[3][0][2];
                sides[3][0][0] = sides[4][0][0];
                sides[3][0][1] = sides[4][0][1];
                sides[3][0][2] = sides[4][0][2];
                sides[4][0][0] = temp[0];
                sides[4][0][1] = temp[1];
                sides[4][0][2] = temp[2];
            }
            // 앞(2) < 왼(4) < 뒤(3) < 오른(5) < 앞(2)
            else {
                temp[0] = sides[2][0][0];
                temp[1] = sides[2][0][1];
                temp[2] = sides[2][0][2];
                sides[2][0][0] = sides[4][0][0];
                sides[2][0][1] = sides[4][0][1];
                sides[2][0][2] = sides[4][0][2];
                sides[4][0][0] = sides[3][0][0];
                sides[4][0][1] = sides[3][0][1];
                sides[4][0][2] = sides[3][0][2];
                sides[3][0][0] = sides[5][0][0];
                sides[3][0][1] = sides[5][0][1];
                sides[3][0][2] = sides[5][0][2];
                sides[5][0][0] = temp[0];
                sides[5][0][1] = temp[1];
                sides[5][0][2] = temp[2];
            }
        }
        else if (no == 1) { // 아래(1)
            // 앞(2) < 왼(4) < 뒤(3) < 오른(5) < 앞(2)
            if (wise == 0) {
                temp[0] = sides[2][2][0];
                temp[1] = sides[2][2][1];
                temp[2] = sides[2][2][2];
                sides[2][2][0] = sides[4][2][0];
                sides[2][2][1] = sides[4][2][1];
                sides[2][2][2] = sides[4][2][2];
                sides[4][2][0] = sides[3][2][0];
                sides[4][2][1] = sides[3][2][1];
                sides[4][2][2] = sides[3][2][2];
                sides[3][2][0] = sides[5][2][0];
                sides[3][2][1] = sides[5][2][1];
                sides[3][2][2] = sides[5][2][2];
                sides[5][2][0] = temp[0];
                sides[5][2][1] = temp[1];
                sides[5][2][2] = temp[2];
            }
            // 앞(2) < 오른(5) < 뒤(3) < 왼(4) < 앞(2)
            else {
                temp[0] = sides[2][2][0];
                temp[1] = sides[2][2][1];
                temp[2] = sides[2][2][2];
                sides[2][2][0] = sides[5][2][0];
                sides[2][2][1] = sides[5][2][1];
                sides[2][2][2] = sides[5][2][2];
                sides[5][2][0] = sides[3][2][0];
                sides[5][2][1] = sides[3][2][1];
                sides[5][2][2] = sides[3][2][2];
                sides[3][2][0] = sides[4][2][0];
                sides[3][2][1] = sides[4][2][1];
                sides[3][2][2] = sides[4][2][2];
                sides[4][2][0] = temp[0];
                sides[4][2][1] = temp[1];
                sides[4][2][2] = temp[2];
            }
        }
        else if (no == 2) { // 앞(2)
            // 위(0) < 왼(4) < 아래(1) < 오른(5) < 위(0)
            if (wise == 0) {
                temp[0] = sides[0][2][0];
                temp[1] = sides[0][2][1];
                temp[2] = sides[0][2][2];
                sides[0][2][0] = sides[4][2][2];
                sides[0][2][1] = sides[4][1][2];
                sides[0][2][2] = sides[4][0][2];
                sides[4][2][2] = sides[1][0][2];
                sides[4][1][2] = sides[1][0][1];
                sides[4][0][2] = sides[1][0][0];
                sides[1][0][2] = sides[5][0][0];
                sides[1][0][1] = sides[5][1][0];
                sides[1][0][0] = sides[5][2][0];
                sides[5][0][0] = temp[0];
                sides[5][1][0] = temp[1];
                sides[5][2][0] = temp[2];
            }
            // 위(0) < 오른(5) < 아래(1) < 왼(4) < 위(0)
            else {
                temp[0] = sides[0][2][0];
                temp[1] = sides[0][2][1];
                temp[2] = sides[0][2][2];
                sides[0][2][0] = sides[5][0][0];
                sides[0][2][1] = sides[5][1][0];
                sides[0][2][2] = sides[5][2][0];
                sides[5][0][0] = sides[1][0][2];
                sides[5][1][0] = sides[1][0][1];
                sides[5][2][0] = sides[1][0][0];
                sides[1][0][2] = sides[4][2][2];
                sides[1][0][1] = sides[4][1][2];
                sides[1][0][0] = sides[4][0][2];
                sides[4][2][2] = temp[0];
                sides[4][1][2] = temp[1];
                sides[4][0][2] = temp[2];
            }
        }
        else if (no == 3) { // 뒤(3)
            // 위(0) < 오른(5) < 아래(1) < 오른(4) < 위(0)
            if (wise == 0) {
                temp[0] = sides[0][0][0];
                temp[1] = sides[0][0][1];
                temp[2] = sides[0][0][2];
                sides[0][0][0] = sides[5][0][2];
                sides[0][0][1] = sides[5][1][2];
                sides[0][0][2] = sides[5][2][2];
                sides[5][0][2] = sides[1][2][2];
                sides[5][1][2] = sides[1][2][1];
                sides[5][2][2] = sides[1][2][0];
                sides[1][2][2] = sides[4][2][0];
                sides[1][2][1] = sides[4][1][0];
                sides[1][2][0] = sides[4][0][0];
                sides[4][2][0] = temp[0];
                sides[4][1][0] = temp[1];
                sides[4][0][0] = temp[2];
            }
            // 위(0) < 오른(4) < 아래(1) < 왼(5) < 위(0)
            else {
                temp[0] = sides[0][0][0];
                temp[1] = sides[0][0][1];
                temp[2] = sides[0][0][2];
                sides[0][0][0] = sides[4][2][0];
                sides[0][0][1] = sides[4][1][0];
                sides[0][0][2] = sides[4][0][0];
                sides[4][2][0] = sides[1][2][2];
                sides[4][1][0] = sides[1][2][1];
                sides[4][0][0] = sides[1][2][0];
                sides[1][2][2] = sides[5][0][2];
                sides[1][2][1] = sides[5][1][2];
                sides[1][2][0] = sides[5][2][2];
                sides[5][0][2] = temp[0];
                sides[5][1][2] = temp[1];
                sides[5][2][2] = temp[2];
            }
        }
        else if (no == 4) { // 왼
            // 앞(2) < 위(0) < 뒤(3) < 아래(1) < 앞(2)
            if (wise == 0) {
                temp[0] = sides[2][0][0];
                temp[1] = sides[2][1][0];
                temp[2] = sides[2][2][0];
                sides[2][0][0] = sides[0][0][0];
                sides[2][1][0] = sides[0][1][0];
                sides[2][2][0] = sides[0][2][0];
                sides[0][0][0] = sides[3][2][2];
                sides[0][1][0] = sides[3][1][2];
                sides[0][2][0] = sides[3][0][2];
                sides[3][2][2] = sides[1][0][0];
                sides[3][1][2] = sides[1][1][0];
                sides[3][0][2] = sides[1][2][0];
                sides[1][0][0] = temp[0];
                sides[1][1][0] = temp[1];
                sides[1][2][0] = temp[2];
            }
            // 앞(2) < 아래(1) < 뒤(3) < 위(0) < 앞(2)
            else {
                temp[0] = sides[2][0][0];
                temp[1] = sides[2][1][0];
                temp[2] = sides[2][2][0];
                sides[2][0][0] = sides[1][0][0];
                sides[2][1][0] = sides[1][1][0];
                sides[2][2][0] = sides[1][2][0];
                sides[1][0][0] = sides[3][2][2];
                sides[1][1][0] = sides[3][1][2];
                sides[1][2][0] = sides[3][0][2];
                sides[3][2][2] = sides[0][0][0];
                sides[3][1][2] = sides[0][1][0];
                sides[3][0][2] = sides[0][2][0];
                sides[0][0][0] = temp[0];
                sides[0][1][0] = temp[1];
                sides[0][2][0] = temp[2];
            }
        }
        else if (no == 5) { // 오른(5)
            // 앞(2) < 아래(1) < 뒤(3) < 위(0) < 앞(2)
            if (wise == 0) {
                temp[0] = sides[2][0][2];
                temp[1] = sides[2][1][2];
                temp[2] = sides[2][2][2];
                sides[2][0][2] = sides[1][0][2];
                sides[2][1][2] = sides[1][1][2];
                sides[2][2][2] = sides[1][2][2];
                sides[1][0][2] = sides[3][2][0];
                sides[1][1][2] = sides[3][1][0];
                sides[1][2][2] = sides[3][0][0];
                sides[3][2][0] = sides[0][0][2];
                sides[3][1][0] = sides[0][1][2];
                sides[3][0][0] = sides[0][2][2];
                sides[0][0][2] = temp[0];
                sides[0][1][2] = temp[1];
                sides[0][2][2] = temp[2];
            }
            // 앞(2) < 위(0) < 뒤(3) < 아래(1) < 앞(2)
            else {
                temp[0] = sides[2][0][2];
                temp[1] = sides[2][1][2];
                temp[2] = sides[2][2][2];
                sides[2][0][2] = sides[0][0][2];
                sides[2][1][2] = sides[0][1][2];
                sides[2][2][2] = sides[0][2][2];
                sides[0][0][2] = sides[3][2][0];
                sides[0][1][2] = sides[3][1][0];
                sides[0][2][2] = sides[3][0][0];
                sides[3][2][0] = sides[1][0][2];
                sides[3][1][0] = sides[1][1][2];
                sides[3][0][0] = sides[1][2][2];
                sides[1][0][2] = temp[0];
                sides[1][1][2] = temp[1];
                sides[1][2][2] = temp[2];
            }
        }
    }
public:
    Cube() {
        sides = {
            vector<vector<char>>(3, vector<char>(3, 'w')), // 위
            vector<vector<char>>(3, vector<char>(3, 'y')), // 아래
            vector<vector<char>>(3, vector<char>(3, 'r')), // 앞
            vector<vector<char>>(3, vector<char>(3, 'o')), // 뒤
            vector<vector<char>>(3, vector<char>(3, 'g')), // 왼
            vector<vector<char>>(3, vector<char>(3, 'b')), // 오른
        };
    }
    void rotate(const string& op) {
        int no, wise;
        switch (op[0]) {
            case 'U':
                no = 0;
                break;
            case 'D':
                no = 1;
                break;
            case 'F':
                no = 2;
                break;
            case 'B':
                no = 3;
                break;
            case 'L':
                no = 4;
                break;
            case 'R':
                no = 5;
                break;
            default:
                no = 0;
                break;
        }
        switch (op[1]) {
            case '+': wise = 0; break;
            case '-': wise = 1; break;
            default: wise = 0; break;
        }
        rotate(no, wise);
    }
    vector<vector<char>> get_head() {
        return sides[0];
    }
};


vector<vector<char>> solution(const vector<string>& ops) {
    // 위, 아래, 앞, 뒤, 왼, 오른
    Cube cube;
    for (int i = 0; i < ops.size(); ++i) {
        cube.rotate(ops[i]);
    }
    return cube.get_head();
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T, N_OP;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> N_OP;
        vector<string> ops(N_OP);
        for (int j = 0; j < N_OP; ++j) {
            cin >> ops[j];
        }
        vector<vector<char>> head = solution(ops);
        for (int m = 0; m < 3; ++m) {
            for (int n = 0; n < 3; ++n) {
                cout << head[m][n];
            }
            cout << '\n';
        }
    }

    return 0;
}