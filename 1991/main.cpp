#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Tree {
public:
    char name;
    Tree* left;
    Tree* right;
    Tree(char in_name, Tree* in_left, Tree* in_right) {
        name = in_name;
        left = in_left;
        right = in_right;
    }

    void travel(int method) {
        if (method == 0) {
            cout << name;
            if (left != nullptr) left->travel(method);
            if (right != nullptr) right->travel(method);
        } else if (method == 1) {
            if (left != nullptr) left->travel(method);
            cout << name;
            if (right != nullptr) right->travel(method);
        } else {
            if (left != nullptr) left->travel(method);
            if (right != nullptr) right->travel(method);
            cout << name;
        }
    }

    void add_node(Tree node) {
        if (name == node.name) {
            left = node.left;
            right = node.right;
            return;
        }
        if (left != nullptr)
            left->add_node(node);
        if (right != nullptr)
            right->add_node(node);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<vector<char>> nodes(N, vector<char>(3));
    for (int i = 0; i < N; ++i) {
        cin >> nodes[i][0] >> nodes[i][1] >> nodes[i][2];
    }
    sort(nodes.begin(), nodes.end());

    auto root = Tree('A', nullptr, nullptr);

    for (int i = 0; i < N; ++i) {
        auto node = Tree(nodes[i][0], nullptr, nullptr);
        if (nodes[i][1] != '.')
            node.left = new Tree(nodes[i][1], nullptr, nullptr);
        if (nodes[i][2] != '.')
            node.right = new Tree(nodes[i][2], nullptr, nullptr);
        root.add_node(node);
    }

    for (int i = 0; i < 3; ++i) {
        root.travel(i);
        cout << '\n';
    }

    return 0;
}