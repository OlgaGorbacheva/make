#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>

using namespace std;

template<class DataV, class DataE>
class graph
{
private:
    vector<list<pair<int, DataE> > > AdjR;
    vector<list<pair<int, DataE> > > AdjT;
    map<int, DataV> Inf;
public:
    graph();

    graph<DataV, DataE> transpose();
    list<pair<int, DataE> > getInEdge(unsigned v);
    list<pair<int, DataV> > getInVertex(unsigned v);
    list<pair<int, DataE> > getOutEdge(unsigned v);
    list<pair<int, DataV> > getOutVertex(unsigned v);
    map<int, DataV> getVertex();
    void InsertV(DataV _data);
    void InsertE(unsigned int v1, unsigned int v2, DataE _data);

    class iterator_dfs;
    class iterator_bfs;

    template <class T, class U>
    friend istream& operator >> (istream &cin, graph<T, U>& _graph);

    template <class T, class U>
    friend ostream& operator << (ostream &cout, graph<T, U>& _graph);

    iterator_dfs begin_dfs();
    iterator_dfs end_dfs();
    iterator_bfs begin_bfs();
    iterator_bfs end_bfs();

    bool is_cycle();
};

template<class DataV, class DataE>
class graph<DataV, DataE>::iterator_dfs
{
private:
    vector<char> color;
    typename map<int, DataV>::iterator elem;
    stack<int> passed;
    graph *G;
public:
    iterator_dfs(graph<DataV, DataE> *_G);
    iterator_dfs(iterator_dfs const &itr);

    friend class graph;

    iterator_dfs& operator ++();
    pair<const int, DataV>& operator *();
    bool operator ==(iterator_dfs const itr);
    bool operator !=(iterator_dfs const itr);
};

template<class DataV, class DataE>
class graph<DataV, DataE>::iterator_bfs
{
private:
    vector<char> color;
    typename map<int, DataV>::iterator elem;
    queue<int> passed;
    graph *G;
public:
    iterator_bfs(graph<DataV, DataE> *_G);
    iterator_bfs(iterator_bfs const &itr);

    friend class graph;

    iterator_bfs& operator ++();
    pair<const int, DataV>& operator *();
    bool operator ==(iterator_bfs const itr);
    bool operator !=(iterator_bfs const itr);
};

#include "graph.hpp"
#include "iterator.hpp"
#endif // GRAPH_H
