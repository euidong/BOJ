#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int compare(const string& S, const string& T)
{
    string next_T = T;
    if (S.size() == T.size())
    {
        return S == T ? 1 : 0;
    } else if (*(T.end() - 1) == 'B')
    {
        if (*(next_T.begin()) == 'B')
        {
            reverse(next_T.begin(),  next_T.end());
            next_T.pop_back();
            return compare(S, next_T);
        } else
        {
            return 0;
        }
    } else
    {
        next_T.pop_back();
        if (compare(S, next_T))
        {
            return 1;
        } else if (*next_T.begin() == 'B')
        {
            next_T.push_back('A');
            reverse(next_T.begin(),  next_T.end());
            next_T.pop_back();
            return compare(S, next_T);
        } else
        {
            return 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S, T; cin >> S >> T;

    cout << compare(S, T);


    return 0;
}