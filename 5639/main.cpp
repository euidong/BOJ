#include <iostream>
#include <vector>

using namespace std;


class Node
{
public:
    Node* left;
    Node* right;
    int num;

    Node(Node* left, Node* right, int num)
    {
        this->left = left;
        this->right = right;
        this->num = num;
    }

    void add_node(const int num)
    {
        // 왼
        if (this->num > num)
        {
            if (this->left == nullptr)
                this->left = new Node(nullptr, nullptr, num);
            else
                this->left->add_node(num);
        }
        // 오른
        else
        {
            if (this->right == nullptr)
                this->right = new Node(nullptr, nullptr, num);
            else
                this->right->add_node(num);
        }
    }

    void print_back_order()
    {
        if (this->left != nullptr)
            this->left->print_back_order();
        if (this->right != nullptr)
            this->right->print_back_order();
        cout << this->num << '\n';
    }
};

// 50 30 24 5 28 45 98 52 60 (루트 왼쪽 오른쪽)
// 5 28 24 45 30 60 52 98 50 (왼쪽 오른쪽 루트)

// 50
// 30 24 5 28 45 (30 (24 5 28) (45))
// 98 52 60


//

int main()
{
    int num; scanf("%d", &num);

    Node *root = new Node(nullptr, nullptr, num);

    while(scanf("%d", &num)!=EOF)
        root->add_node(num);

    root->print_back_order();

    return 0;
}