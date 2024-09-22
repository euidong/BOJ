#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
    char c;
    Node* next;
    Node* prev;
    Node(const char c)
    {
        this->c = c;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    string str; cin >> str;
    Node *root = new Node(str[0]);
    Node *cursor = root;
    for (int i = 1; i < str.size(); ++i)
    {
        cursor->next = new Node(str[i]);
        cursor->next->prev = cursor;
        cursor = cursor->next;
    }

    string bomb; cin >> bomb;

    cursor = root;
    const int bomb_size = (int)bomb.size();
    while(cursor != nullptr)
    {
        // 1. 해당 위치에서 폭발 문자열이 있는지 확인
        bool is_same = true;
        auto checker = cursor;
        for (int i = 0; i < bomb_size; ++i)
        {
            if (checker == nullptr || checker->c != bomb[i])
            {
                is_same = false;
                break;
            }
            checker = checker->next;
        }
        // 2. 없으면 한칸 전진
        if (!is_same)
        {
            cursor = cursor->next;
            continue;
        }
        // 아무 문자열도 안남음, 현재 cursor가 시작점, 현재 끝이 종료지점인 경우
        if (cursor->prev == nullptr && checker == nullptr)
        {
            root = nullptr;
            break;
        }
        // 현재 지점이 끝인 경우
        if (checker == nullptr)
        {
            cursor->prev->next = nullptr;
            break;
        }

        // cursor만 시작점인 경우
        if (cursor->prev == nullptr)
        {
            checker->prev = nullptr;
            root = checker;
            cursor = checker;
            continue;
        }

        // 그렇지 않은 경우
        cursor->prev->next = checker;
        checker->prev = cursor->prev;
        cursor = checker;

        for (int i = 0; i < bomb_size-1; ++i)
        {
            if (cursor->prev == nullptr) break;
            cursor = cursor->prev;
        }
    }

    if (root == nullptr) cout << "FRULA";
    while (root != nullptr)
    {
        cout << root->c;
        root = root->next;
    }

    return 0;
}