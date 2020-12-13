#include <bits/stdc++.h>
#include <iostream>

using namespace std;
  
// a structure to represent a weighted edge in graph
class Edge
{
public:
int src, dest, weight;
};
  
// a structure to represent a connected, undirected and weighted graph
class Graph
{
public:
// V-> Number of vertices, E-> Number of edges
int V, E;
  
// graph is represented as an array of edges.
Edge* edge;
};
  
// function to create a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
Graph* graph = new Graph;
graph->V = V;
graph->E = E;
  
// array of 100 elements as specified
graph->edge = new Edge[100];
  
return graph;
}
  
// A structure to represent a subset for union-find
class subset
{
public:
int parent;
int rank;
};
  
// recursive function to find set of an element i
int find(subset subsets[], int i)
{
// find root and make root as parent of i
// (path compression)
if (subsets[i].parent != i)
subsets[i].parent = find(subsets, subsets[i].parent);
  
return subsets[i].parent;
}
  
// function that joins to sets and assigns the parent of larger subset
// to the smaller one
void Union(subset subsets[], int x, int y)
{
int xroot = find(subsets, x);
int yroot = find(subsets, y);
  
// Attach smaller rank tree under root of high
// rank tree (Union by Rank)
if (subsets[xroot].rank < subsets[yroot].rank)
subsets[xroot].parent = yroot;
else if (subsets[xroot].rank > subsets[yroot].rank)
subsets[yroot].parent = xroot;
  
// If ranks are same, then make one as root and
// increment its rank by one
else
{
subsets[yroot].parent = xroot;
subsets[xroot].rank++;
}
}
  
// comparator for two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
Edge* a1 = (Edge*)a;
Edge* b1 = (Edge*)b;
return a1->weight > b1->weight;
}
  
// required function
void KruskalMST(Graph* graph)
{
int V = graph->V;
Edge result[V]; // Tnis will store the resultant MST
int e = 0; // An index variable, used for result[]
int i = 0; // An index variable, used for sorted edges
  
// Step 1: Sort all the edges in non-decreasing
// order of their weight.
qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
  
// Allocate memory for creating V ssubsets
subset *subsets = new subset[( V * sizeof(subset) )];
  
// Create V subsets with single elements
for (int v = 0; v < V; ++v)
{
subsets[v].parent = v;
subsets[v].rank = 0;
}
  
// Number of edges to be taken is equal to V-1
while (e < V - 1 && i < graph->E)
{
// Step 2: Pick the smallest edge.
Edge next_edge = graph->edge[i++];
  
int x = find(subsets, next_edge.src);
int y = find(subsets, next_edge.dest);
  
// If including this edge does't cause cycle,
// include it in result and increment the index
// of result for next edge
if (x != y)
{
result[e++] = next_edge;
Union(subsets, x, y);
}
// Else discard the next_edge
}
  
// print the contents of result[] to display the
// built MST
// for total cost
int cost = 0;
cout<<"\nMinimum spanning tree:\n";
for (i = 0; i < e; ++i)
{
cout<<result[i].src<<" "<<result[i].dest<<" "<<result[i].weight<<endl;
cost+= result[i].weight;
}
cout << "Edge weight total: " << cost << endl;
return;
}
  
// Driver code
int main()
{
// now take input transactions
string line;
// store all lines in a vector
vector<string> inputs;
int E = 0; // Number of edges in graph
  
// loop till not end of line
while(true)
{
getline(cin, line);
  
// end of input
if(line == "end-of-file")
{
break;
}
  
  
inputs.push_back(line);
// increase number of edges
E++;
}
  
Graph* graph = createGraph(100, E);
  
// traverse the vector to extract the edges
for(int i=0; i<E; i++)
{
line = inputs[i];
string word = "";
int flag = 0;
  
// extract characters from line
for(int j=0; line[j]!='\0'; j++)
{
if(line[j]==' ')
{
if(flag == 0) // src
{
graph->edge[i].src = stoi(word);
flag = 1;
}
else // dest
{
graph->edge[i].dest = stoi(word);
}
word = "";
}
else
{
word = word + line[j];
}
}
// last word -> weight
graph->edge[i].weight = stoi(word);
}
  
// call the MST evaluation function
KruskalMST(graph);
  
return 0;
}

