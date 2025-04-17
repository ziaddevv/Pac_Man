#pragma once
#include<vector>
#include<map>
#include <iostream>
using namespace std;
struct Node {
    int x, y;
    bool hasFood = true;
    std::vector<Node*> neighbors;
    Node(int x_, int y_) : x(x_), y(y_), hasFood(true) {}
};

class Graph {
private:
    map<pair<int, int>, Node*>nodes;
public:
    void build(const std::vector<std::string>& mapData);
    Node* getNode(int x, int y);
};