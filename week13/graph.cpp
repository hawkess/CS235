#include "graph.h"

namespace detail
{

Vertex constructVertex(int index)
{
   auto vert = Vertex{};
   vert.set(index);
   return vert;
}

} // namespace detail

Graph::Graph(int numVertices) :
   numElements_(numVertices * numVertices),
   numVertices_(numVertices)

{
   array_ = new bool[numElements_];
   for (auto i = 0; i < numElements_; ++i)
      array_[i] = false;
}

Graph::Graph(const Graph& rhs)
{
   numElements_ = rhs.numElements_;
   numVertices_ = rhs.numVertices_;
   array_ = new bool[numElements_];
   for (auto i = 0; i < numElements_; ++i)
      array_[i] = rhs.array_[i];
}

Graph::~Graph()
{
   delete [] array_;
}

Graph& Graph::operator=(const Graph& rhs)
{
   numElements_ = rhs.numElements_;
   numVertices_ = rhs.numVertices_;
   for (auto i = 0; i < numElements_; ++i)
      array_[i] = rhs.array_[i];
   return *this;
}

void Graph::add(const Vertex& v1, const Vertex& v2)
{
   array_[matrixIndex(v1.index(), v2.index())] = true;
}

void Graph::add(const Vertex& v1, const custom::set<Vertex>& vertices)
{
   for (auto vert_it = vertices.cbegin(); vert_it != vertices.cend(); vert_it++)
      add(v1, *vert_it);
}

void Graph::clear()
{
   delete [] array_;
   numElements_ = 0;
   numVertices_ = 0;
   array_ = new bool[0];
}

custom::set<Vertex> Graph::findEdges(const Vertex& v) const
{
   auto edges = custom::set<Vertex>{};
   for (auto v2_i = 0; v2_i < numElements_; ++v2_i)
   {
      auto v2 = detail::constructVertex(v2_i);
      if (isEdge(v, v2))
         edges.insert(v2);
   }
   return edges;
}

custom::vector<Vertex> Graph::findPath(const Vertex& v1,
                                        const Vertex& v2) const
{
   auto distance = 0;

   auto toVisit = deque::custom::deque<Vertex>{};
   toVisit.push_back(v1);

   auto distances = custom::vector<int>{numVertices_, -1};
   auto predecessor = custom::vector<Vertex>{numVertices_};

   while (!toVisit.empty() && (distances[v2.index()] == -1))
   {
      auto v = toVisit.front();
      toVisit.pop_front();

      if (distances[v.index()] > distance)
         ++distance;

      auto edges = findEdges(v);
      for (auto it = edges.cbegin(); it != edges.cend(); ++it)
      {
         if (distances[(*it).index()] == -1)
         {
            distances[(*it).index()] = distance + 1;
            predecessor[(*it).index()] = v;
            toVisit.push_back(*it);
         }
         ++distance;
      }
   }

   if (distances[v2.index()] == -1)
      return custom::vector<Vertex>{};
   auto path = custom::vector<Vertex>{};
   path.push_back(v2);
   for (auto i = 1; i < distance; ++i)
      path.push_back(predecessor[path[i - 1].index()]);
   return path;
}

int Graph::matrixIndex(int x, int y) const
{
   return (x + numVertices_ * y);
}

bool Graph::isEdge(const Vertex& v1, const Vertex& v2) const
{
   return array_[matrixIndex(v1.index(), v2.index())];
}

int Graph::size() const
{
   return numVertices_;
}
