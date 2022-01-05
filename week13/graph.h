#ifndef GRAPH_H_
#define GRAPH_H_

#include <cmath>
#include "deque.h"
#include "set.h"
#include "vector.h"
#include "vertex.h"

class Graph
{
public:
   Graph(int numVertices);
   Graph(const Graph& rhs);
   ~Graph();
   Graph& operator=(const Graph& rhs);
   void add(const Vertex& v1, const Vertex& v2);
   void add(const Vertex& v, const custom::set<Vertex>& vertices);
   void clear();
   custom::set<Vertex> findEdges(const Vertex& v) const;
   custom::vector<Vertex> findPath(const Vertex& v1,
                                   const Vertex& v2) const;
   bool isEdge(const Vertex& v1, const Vertex& v2) const;
   int size() const;

private:
   bool* array_;
   int numVertices_;
   int numElements_;

   int matrixIndex(int x, int y) const;
};

#endif // GRAPH_H_
