#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        n += 2;
        vector<vector<int>> portal;
        int sourceX, sourceY, desX, desY, cost;
        cin >> sourceX >> sourceY;
        cin >> desX >> desY;
        // We can also consider them as portal, going in and out in the same position with 0 cost
        portal.push_back({sourceX, sourceY, sourceX, sourceY, 0});
        portal.push_back({desX, desY, desX, desY, 0});
        for (int i = 1; i < n - 1; i++)
        {
            int inX, inY, outX, outY;
            cin >> inX >> inY >> outX >> outY >> cost;
            // As warmholes are bidirectional, 2 porals can be imagined just inverting the gateway. 
            portal.push_back({inX, inY, outX, outY, cost});
            portal.push_back({outX, outY, inX, inY, cost});
        }
        int totalNodes = portal.size();
        vector<pair<int, int>> adjacencyList[totalNodes];
        vector<bool> visited(totalNodes, false);
        vector<int> distance(totalNodes, INT_MAX);
        //It will actually take O(n^2) time.  
        for (int i = 0; i < totalNodes; i++)
        {
            for (int j = i + 1; j < totalNodes; j++)
            {
                //weight1 is the cost required from 1st portals assumed exit point to reach 2nd portal's assumed entering point, and notice that upon reaching a entering point, we will be transferred to the exit point via the warmhole. 
                //weight2 is the cost required from 2nd portals assumed exit point to reach 1st portal's assumed entering point.
                int weight1 = abs(portal[i][2] - portal[j][0]) + abs(portal[i][3] - portal[j][1]) + portal[j][4];
                int weight2 = abs(portal[j][2] - portal[i][0]) + abs(portal[j][3] - portal[i][1]) + portal[i][4];
                adjacencyList[i].push_back({j, weight1});
                adjacencyList[j].push_back({i, weight2});
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({0, 0});
        distance[0] = 0;
        while (!q.empty())
        {
            int u = q.top().second;
            q.pop();
            if (visited[u])
                continue;
            visited[u] = true;
            for (auto p : adjacencyList[u])
            {
                int v = p.first;
                int w = p.second;
                if (distance[u] + w < distance[v])
                {
                    distance[v] = distance[u] + w;
                    q.push({distance[v], v});
                }
            }
        }
        cout << distance[1] << endl;
    }
}

/*
We will given a source, a destination, and some warmholes to ease transferring from one point to another. We are asked to return the minimum distance for reaching the destination from the source

Observation 1: 
Source and destination can also be considered a warmhole where the entry and the exit points are the same with 0 cost. 

Observation 2: 
warmholes are bidirectional, so we can consider any gate as either entry or exit point. 

Observation 3: 
It is not mandatory to use the given warmholes to reach destination. 

Observation 4:
Suppose we will use two warmhole consecutively. So from the exit point of the first warmhole, we have to travel the distance to the entry point of the 2nd warmhole without any help of other warmhole. Upon reaching the entry point of the 2nd warmhole, we will be transferred to the exit point only considering the cost assigned to that warmhole(not distance, notice that). 

Observation 5: 
To reach a warmhole to itself, it will only need the assigned cost to it. But to reach a warmhole to another, we have to consider observation 4

2 key conditions satisfied here when we calculate minimum path from source to destination using dijkstra: 
1. It is not necessary to use all the nodes 
2. there is one source and destination given for which we have to find minimum cost

Notice that we can imagine the warmholes as nodes in a graph. 

So in this solution, first we have considered the source and destination points also as warmholes. 
Thus everything is happening between 2 warmholes! 

Secondly, as there is no restriction about travelling from one point to another, we can imagine all nodes are connected with each other. So nodes_number^2 edges in total. 

Going forward, it is simply dijkstra implementation. 
*/