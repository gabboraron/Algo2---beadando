/*
*   Név:        Burian Sándor
*   Neptun:     AWXYHE
*
*   Feladat:    Adjunk hatékony algoritmust egy fa átmérőjének kiszámítására.
*   Forrás:     http://aszt.inf.elte.hu/~asvanyi/ad/ad2jegyzet.pdf#page=38
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>

using namespace std;

class edge
{
    public:
        int u;              //the begining of the edge
        int v;              //the end of the edge

        edge(int uu, int vv)
        {
            u = uu;
            v = vv;
        }

        void print()
        {
            std::cout<<"("<<u<<","<<v<<")";
        }
};

class vertex
{
    public:
        int point;          //ID
        int parrent;        //parrent of point
        int d;              //distance from the point

        vertex(int p)
        {
            point = p;
            parrent = 50000;
            d = 50000;
        }
        void print()
        {
            cout<<"("<<point<<", p: "<<parrent<<", d: "<<")";
        }
};

class Graph
{
    public:
        vector<edge> edges;
        vector<vertex> vertexes;

        //add new edge to the list by vertexpoints ID-s
        void add_edge(int u, int v)
        {
            edge e(u,v);
            edges.push_back(e);
        }

        //find an edge by 2 vertexpoint
        bool containsedge(vertex v1, vertex v2)
        {
            edge e(v1.point,v2.point);
            for(int i=0; i<edges.size(); ++i)
            {
                //find vice-versa in the possible edges (because of undirected graph
                if(((e.u == edges[i].u) && (e.v == edges[i].v)) || ((e.u == edges[i].v) && (e.v == edges[i].u)))
                    return true;
            }
            return false;
        }

        //new vertex
        void add_vertex(vertex v)
        {
            bool available = false;
            for(int i=0; i<vertexes.size(); i++)
            {
                if(vertexes[i].point == v.point)
                    available = true;
            }

            if(!available)
                vertexes.push_back(v);
        }

        //print the whole list
        void print_edges()
        {
            for(int idx=0; idx<edges.size(); idx++)
            {
                edges[idx].print();
                cout<<"; ";
            }
            cout<<endl;
        }

        //print the whole list
        void print_vertexes()
        {
            for(int idx=0; idx<vertexes.size(); idx++)
            {
                vertexes[idx].print();
                cout<<"; ";
            }
            cout<<endl;
        }
};


//create graphs db from the input file
vector<Graph> readData(string filename){
  ifstream myfile;
  myfile.open (filename);
  //cout << "Opening...";

  string nr_of_threes_st;
  getline (myfile,nr_of_threes_st);
  int nr_of_threes_int = std::stoi(nr_of_threes_st);

  vector<Graph> graphs;
  for(int gidx=0; gidx<=nr_of_threes_int; gidx++)
  {
    //read and convert the current line into a vector of int
    string tmpline;
    getline(myfile,tmpline);
	vector<int>line;
	for (int i = 0; i < tmpline.length()-4; i++)
	{
        if(!isspace(tmpline[i]))
        {
            line.push_back((int)tmpline[i]);
        }
	}

    //processing of a line
    Graph g;
    for(int edgeidx=1; edgeidx<=line[0]; edgeidx+=2)
    {
        g.add_edge(line[edgeidx], line[edgeidx+1]);
        g.add_vertex(line[edgeidx]);
        g.add_vertex(line[edgeidx+1]);
    }
    graphs.push_back(g);
  }
  myfile.close();


  return graphs;
}

/*
    Forrás:     http://aszt.inf.elte.hu/~asvanyi/ad/ad2jegyzet.pdf#page=38
*/
int BFS(Graph g)
{
    int maxd = 0;

    g.vertexes[0].d = 0;
    vector<vertex> bfs_queue;
    bfs_queue.push_back(g.vertexes[0]);
    while(!bfs_queue.empty())
    {
        vertex u = bfs_queue.back();
        int vidx = 0;
        for(int vidx=0; vidx<g.vertexes.size(); ++vidx)
        {
            if(g.containsedge(u, g.vertexes[vidx]))
                if(g.vertexes[vidx].d == 50000)
                {
                    g.vertexes[vidx].d = u.d + 1;
                    g.vertexes[vidx].parrent = u.point;
                    bfs_queue.push_back(g.vertexes[vidx]);
                    if(maxd<g.vertexes[vidx].d)
                        maxd = g.vertexes[vidx].d;
                }
        }
    }

    return maxd;
}


int main(int argc, char** argv)
{
    vector<Graph> graphs = readData(argv[0]); //read data into a vector of graphs from the command line entered parameter

    for(int i=0; i<graphs.size(); ++i)
    {
        cout<<i<<". fa: "<<BFS(graphs[i])<<endl;
    }
    return 0;
}

