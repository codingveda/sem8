#include<iostream>
#include<bits/stdc++.h>
// #include<omp.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfsTraversal(int b)
{
    stack<int> s; //Declare a stack to store all the nodes connected to b
    s.push(b); //Insert b to stack
    visited[b]=true; //mark b as visited
    // double start=omp_get_wtime();
    while(!s.empty())
    {
        int current = s.top();
        s.pop(); //delete the top element form stack
        cout<<current<<" ";
        // #pragma omp parallel
        for(auto neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    // double end=omp_get_wtime();
    // double time=end-start;
    // cout<<"\n\nTime taken => "<<time<<endl;
}

void makeEdge(int a, int b)
{
    graph[a].push_back(b); //an edge from a to b (directed graph)
}

int main()
{
    // omp_set_num_threads(4);
    int numVertices,numEdges;
    cout<<"Consider first vertex => 0"<<endl;
    cout<<"\nEnter the number of vertices: ";
    cin >> numVertices;
    cout<<"\nEnter the number of edges: ";
    cin>>numEdges;
    
    visited.assign(numVertices, false);
    graph.assign(numVertices, vector<int>());

    int a, b, i;
    cout << "\nEnter the edges with source and target vertex: "<<endl;
    for(i=0;i<numEdges;i++)
    {
        cin>>a>>b;
        makeEdge(a, b);
    }

    cout<<"\nThe DFS Traversal is: ";

    for (i=0;i<numVertices;i++)
    {
        if (!visited[i]) // if node i is unvisited
        {
            dfsTraversal(i);
        }
    }
    return 0;
}
