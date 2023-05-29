#include<iostream>
#include<bits/stdc++.h>
//#include<omp.h>
using namespace std;

vector<bool> visited; // tracks visited nodes
vector<vector<int>> graph; // adjacency list to represent graph

void bfsTraversal(int start)
{
    queue<int> queue; // queue to store all nodes connected to start
    queue.push(start); // insert start node into queue
    visited[start] = true; // mark start node as visited
    
    //double startTime = omp_get_wtime(); // track start time

    while(!queue.empty())
    {
        int current = queue.front();
        queue.pop(); // remove first element from queue
        #pragma omp parallel for
        for(auto neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
        cout << current << " ";
    }

    //double endTime = omp_get_wtime(); // track end time
    //double timeTaken = endTime - startTime;
    //cout << "\n\nTime taken => " << timeTaken << endl;
}

void addEdge(int from, int to)
{
    graph[from].push_back(to); // add directed edge from 'from' to 'to'
}

int main()
{
    //omp_set_num_threads(4); // set number of OpenMP threads to 4
    int numVertices, numEdges;
    cout << "Consider first vertex => 0\n";
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;
    visited.assign(numVertices, false);
    graph.assign(numVertices, vector<int>());

    int from, to, i;
    cout << "\nEnter the edges with source and target vertex: \n";
    for(i=0;i<numEdges;i++)
    {
        cin >> from >> to;
        addEdge(from, to);
    }

    cout << "The BFS Traversal is: ";
    for (i=0;i<numVertices;i++)
    {
        if (!visited[i]) // if node i is unvisited
        {
            bfsTraversal(i);
        }
    }
    return 0;
}

/*
graph - 
0 ---> 1 ---> 2
^      |      |
|      |      |
|      v      v
3 ---> 4 ---> 5

op - 
0 1 2 4 5 3

*/