#include <iostream>
#include <vector>

using namespace std;

long long solution(const int N, const int B, const int C, const vector<int>& applicants) {
    long long answer = N;
    for (int i = 0; i < applicants.size(); ++i) {
        const int applicant = applicants[i] - B;
        if (applicant > 0) {
            if (applicant % C != 0) {
                answer += 1;
            }
            answer += applicant / C;
        }
    }
    return answer;
}

int main() {
    int N, B, C;
    vector<int> applicants;

    cin >> N;

    for (int i = 0; i < N; ++i) {
        int applicant;
        cin >> applicant;
        applicants.push_back(applicant);
    }
    cin >> B >> C;
    cout << solution(N, B, C, applicants) << '\n';
    return 0;
}