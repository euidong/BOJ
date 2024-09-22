#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int idx;
    vector<pair<Node*, int>> children;
    Node* parent;
    Node(const int idx)
    {
        this->idx = idx;
    }

    void add_child(Node *child, const int dist)
    {
        children.push_back(make_pair(child, dist));
    }

    void make_tree(const vector<vector<pair<int, int>>>& nodes)
    {
        for (int i = 0; i < nodes[this->idx].size(); ++i)
        {
            const int child_idx = nodes[this->idx][i].first;
            const int dist = nodes[this->idx][i].second;
            if (parent != nullptr && parent->idx == child_idx) continue;
            Node* child = new Node(child_idx);
            child->parent = this;
            child->make_tree(nodes);
            this->add_child(child, dist);
        }
    }

    // leaf에서 leaf 까지의 거리 or leaf에서 root까지의 거리
    // child 중에서 가장 거리가 큰 두개의 길이의 합.
    int calc_diameter(int& max_dist)
    {
        if (this->children.size() == 0)
            return 0;
        if (this->children.size() == 1)
        {
            const int dist = this->children[0].second + this->children[0].first->calc_diameter(max_dist);
            max_dist = max(max_dist, dist);
            return dist;
        }
        vector<int> dists(this->children.size());
        for (int i = 0; i < this->children.size(); ++i)
            dists[i] = this->children[i].second + this->children[i].first->calc_diameter(max_dist);
        sort(dists.begin(), dists.end());
        max_dist = max(max_dist, dists[dists.size() - 1] + dists[dists.size() - 2]);
        return dists[dists.size()-1];
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int V; cin >> V; // V <= 100,000

    int node_idx, child_idx, dist;

    vector<vector<pair<int, int>>> nodes(V);

    for (int i = 0; i < V; ++i) // time complexity : 2V
    {
        cin >> node_idx;
        cin >> child_idx;
        while (child_idx != -1)
        {
            cin >> dist;
            nodes[node_idx-1].push_back(make_pair(child_idx-1, dist));
            cin >> child_idx;
        }
    }

    Node *root = new Node(0);
    root->make_tree(nodes); // time complexity : 2V

    int max_dist = 0;
    root->calc_diameter(max_dist); // time complexity :
    cout << max_dist;

    return 0;
}

// 1
// 3 (2)
// 4 (3)
// 2 (4) 5 (6)