#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ios>
#include <map>
#include <list>

using namespace std;

graph<string, int>  read_file(istream &in, vector<string> &command)
{
    graph<string, int> result;
    char c;
    unsigned int i = 0, j = 0; // используются при добавлении комманды.
    map<string, int> vertex; // храним уже прочитанные цели
    string str;
    c = in.get(); // читаем главную цель
    while(c != ':' && in.good()){
        str.push_back(c);
        c = in.get();
    }
    result.InsertV(str);
    vertex.insert(make_pair(str, i));
    j = i++;
    str.clear();
    if (in.good())
        c = in.get();
    while (in.good()){ //читаем файл
        while(in.good() && (c == '\n' || c == ' ')){
            c = in.get();
        }
        while(in.good() && c != '\n' && c != '\t'){
            while(in.good() && c != ' ' && c != '\n'){
                str.push_back(c);
                c = in.get();
            }
            if (!str.empty()){
                unsigned int k;;
                map<string, int>::iterator itr;
                if ((itr = vertex.find(str)) != vertex.end())
                    k = itr->second;
                else {
                    result.InsertV(str);
                    vertex.insert(make_pair(str, i));
                    k = i++;
                }
                str.clear();
                result.InsertE(j, k, command.size());
            }
            if (in.good() && c != '\n')
                c = in.get();
        }
        while(in.good() && (c == '\n' || c == ' ')){
            c = in.get();
        }
        str.clear();
        if (c == '\t'){
            getline(in, str);
            c = in.get();
            command.push_back(str);
            str.clear();
        }else throw "have not command";
        while(in.good() && (c == '\n' || c == ' ')){
            c = in.get();
        }
        while(c != ':' && in.good()){
            str.push_back(c);
            c = in.get();
        }
        if (!str.empty()){
            if (in.good())
                c = in.get();
            map<string, int>::iterator itr;
            if ((itr = vertex.find(str)) != vertex.end())
                j = itr->second;
            else {
                result.InsertV(str);
                vertex.insert(make_pair(str, i));
                j = i++;
            }
            str.clear();
        }
    }
    return result;
}

int main()
{
    string name;
    ifstream cin("in.txt");
    getline(cin, name);
    ifstream fin(name.c_str());
    ofstream fout("out.txt");
    if (!fin.is_open()){
        cerr << "file for sort not found" << endl;
    }
    vector<string> command;
    graph<string, int> aim = read_file(fin, command);
    fout << aim;
    if (aim.is_cycle()){
        cerr << "incorrect file" << endl;
        return 0;
    }
    graph<string, int>::iterator_dfs itr = aim.begin_dfs(), end = aim.end_dfs();
    for (; itr != end; ++itr){
        if (!aim.getOutVertex((*itr).first).empty()){
            list<pair<int, int> > l = aim.getOutEdge((*itr).first);
            system(command[l.front().second].c_str());
        }
    }
    return 0;
}
