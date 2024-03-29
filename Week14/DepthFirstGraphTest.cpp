#include <iostream>
#include "Graphs.h"

using namespace std;
/*
int main(int args, char **argc)
{
   cout << "Graphs - Depth First Search" << endl;
   cout << endl;

   Graph<char> demoGraph(6);

   demoGraph.push('A');
   demoGraph.push('B');
   demoGraph.push('C');
   demoGraph.push('D');
   demoGraph.push('E');
   demoGraph.push('F');

   // Attach A to C and C to A.
   demoGraph.attachEdge(0, 2);

   // Attach A to D and D to A.
   demoGraph.attachEdge(0, 3);

   // Attach B to E and E to B.
   demoGraph.attachEdge(1, 4);

   // Attach C to F and F to C.
   demoGraph.attachEdge(2, 5);

   // Perform depth first search for a path from A to D.
   cout << "DepthFirstSearch Nodes Visited: ";

   int result = demoGraph.DepthFirstSearch(0, 3);
   cout << endl << endl;

   if(result == 1)
      cout << "Path from A to D found!";
   else
      cout << "Path from A to D NOT found!";

   cout << endl << endl;

   return 1;
}

*/