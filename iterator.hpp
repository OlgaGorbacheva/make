#ifndef ITERATOR_H
#define ITERATOR_H
#include "graph.h"


#include <list>
template<class DataV, class DataE>
graph<DataV, DataE>::iterator_dfs::iterator_dfs(graph<DataV, DataE> *_G):G(_G)
{
    color.resize(G->Inf.size(), 0);
}

template<class DataV, class DataE>
typename graph<DataV, DataE>::iterator_dfs& graph<DataV, DataE>::iterator_dfs::operator ++()
{
    if (passed.size() == 0){
        vector<char>::iterator itr = color.begin(), end = color.end();
        for (int i = 0; itr != end; itr++, i++)
            if (*itr == 0){
                passed.push(i);
                *itr = 1;
                break;
            }
        if (itr == end){
            elem = G->Inf.end();
            return *this;
        }
    }
    bool flag = true;
    while (flag){
        flag = false;
        typename list<pair<int, DataE> >::iterator itr = G->AdjR[passed.top()].begin(), end = G->AdjR[passed.top()].end();
        for(; itr != end && !flag; itr++){
            if (color[itr -> first] == 0){
                flag = true;
                color[itr -> first] = 1;
                passed.push(itr -> first);
            }
        }
    }
    color[passed.top()] = 2;
    elem = G->Inf.begin() ;
    for (int i = 0; i < + passed.top(); i++)
        elem++;
    passed.pop();
    return *this;
}

template<class DataV, class DataE>
pair<const int, DataV> & graph<DataV, DataE>::iterator_dfs::operator *()
{
    return *elem;
}

template<class DataV, class DataE>
graph<DataV, DataE>::iterator_bfs::iterator_bfs(graph<DataV, DataE> *_G):G(_G)
{
    color.resize(G->Inf.size(), 0);
}

template<class DataV, class DataE>
pair<const int, DataV> & graph<DataV, DataE>::iterator_bfs::operator *()
{
    return *elem;
}

template<class DataV, class DataE>
typename graph<DataV, DataE>::iterator_bfs& graph<DataV, DataE>::iterator_bfs::operator ++()
{
    if (passed.size() == 0){
        vector<char>::iterator itr = color.begin(), end = color.end();
        for (int i = 0; itr != end; itr++, i++)
            if (*itr == 0){
                passed.push(i);
                *itr = 1;
                break;
            }
        if (itr == end){
            elem = G->Inf.end();
            return *this;
        }
    }
    typename list<pair<int, DataE> >::const_iterator itr = G->AdjR[passed.front()].begin(), end = G->AdjR[passed.front()].end();
    for(; itr != end; itr++){
        if (color[itr -> first] == 0){
            color[itr -> first] = 1;
            passed.push(itr -> first);
        }
    }
    color[passed.front()] = 2;
    elem = G->Inf.begin() ;
    for (int i = 0; i < + passed.front(); i++)
        elem++;
    passed.pop();
    return *this;
}

template<class DataV, class DataE>
graph<DataV, DataE>::iterator_dfs::iterator_dfs(graph<DataV, DataE>::iterator_dfs const &itr):color(itr.color),
    elem(itr.elem), passed(itr.passed), G(itr.G)
{}

template<class DataV, class DataE>
graph<DataV, DataE>::iterator_bfs::iterator_bfs(graph<DataV, DataE>::iterator_bfs const &itr):color(itr.color),
    elem(itr.elem), passed(itr.passed), G(itr.G)
{}

template<class DataV, class DataE>
bool graph<DataV, DataE>::iterator_dfs::operator ==(graph<DataV, DataE>::iterator_dfs const itr)
{
    return elem == itr.elem;
}

template<class DataV, class DataE>
bool graph<DataV, DataE>::iterator_dfs::operator !=(graph<DataV, DataE>::iterator_dfs const itr)
{
    return elem != itr.elem;
}

template<class DataV, class DataE>
bool graph<DataV, DataE>::iterator_bfs::operator ==(graph<DataV, DataE>::iterator_bfs const itr)
{
    return elem == itr.elem;
}

template<class DataV, class DataE>
bool graph<DataV, DataE>::iterator_bfs::operator !=(graph<DataV, DataE>::iterator_bfs const itr)
{
    return elem != itr.elem;
}

#endif // ITERATOR_H
