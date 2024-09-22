#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node
{
public:
    vector<pair<Node*, int>> children;
    int node_id;
    Node* parent;

    Node (Node* parent, const int node_id) {
        this->node_id = node_id;
        this->parent = parent;
    }

    bool add_child(Node* child, const int parent_id, const int dist)
    {
        if (parent_id == this->node_id)
        {
            child->parent = this;
            this->children.push_back(make_pair(child, dist));
            return true;
        }

        for (const auto & c : this->children)
            if (c.first->add_child(child, parent_id, dist))
                return true;
        return false;
    }

    int calc_diameter(int &max_diameter)
    {
        int max_dist = 0;
        for (const auto & child : this->children)
        {
            const int cur_dist = child.first->calc_diameter(max_diameter) + child.second;
            if (max_diameter < cur_dist + max_dist)
                max_diameter = cur_dist + max_dist;
            if (max_dist < cur_dist)
                max_dist = cur_dist;
        }
        return max_dist;
    }
};


int solution(const int n, const vector<vector<int>>& edges)
{
    Node *root = new Node(nullptr, 1);
    queue<vector<int>> q;
    for (const auto & edge: edges) q.push(edge);


    while(!q.empty())
    {
        const vector<int> edge = q.front();
        q.pop();
        Node *node = new Node(nullptr, edge[1]);
        if (!(root->add_child(node, edge[0], edge[2])))
            q.push(edge);
    }

    int diameter = 0;
    root->calc_diameter(diameter);

    return diameter;
}



int main()
{
    // 각 leaf 끼리의 거리를 구하는 게 관건인 문제
    // 1. floyd warshall 을 이용할까? <- 메모리 초과
    // 2. 리프 노드에서 시작해서 좌우 합이 최대인지 확인 최대면 업데이트 아니면 좌우중 최댓값 선택
    // node = n, edge = n-1

    int n; cin >> n; // 1 <= n <= 10,000
    vector<vector<int>> edges(n-1);
    int a, b, c;
    for (int i = 0 ; i < n-1; ++i)
    {
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }

    cout << solution(n, edges);

    return 0;
}