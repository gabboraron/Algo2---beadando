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
#include <deque>

using namespace std;

class vertex
{
    public:
        int point;          //ID
        int parrent;        //parrent of point
        int d;              //distance from the point
        int color;          //possible values:
                            //                  1 - white
                            //                  2 - grey
                            //                  3 - black

        vertex(int p)
        {
            point = p;
            parrent = -50000;
            d = -50000;
            color = 1;
        }

        void print()
        {
            cout<<"("<<point<<", p: "<<parrent<<", d: "<<d<<", color:"<<color<<")";
        }

        void reset_with(vertex v)  //reset the current vertex with the given vertex values (copy)
        {
            point = v.point;
            parrent = v.parrent;
            d = v.d;
            color = v.color;
        }
};



class Graph
{
    public:
        vector<vector<int>> edges; //vectors of indexes of the vertexes from the vertexes vector, but the first value is a real vertex value!
        vector<vertex> vertexes;

        //add new edge to the list by vertexpoints ID-s
        void add_edge(int u, int v)
        {
            //find if starter or end vertex exist
            bool found1 = false; bool found2 = false;
            int edx=0;
            while((edx<edges.size()) && (!found1 || !found2))
            {
                if(edges[edx][0] == u)
                {
                    found1 = true;
                    edges[edx].push_back(idx_of_vertex(v));
                }

                if(edges[edx][0] == v)
                {
                    found2 = true;
                    edges[edx].push_back(idx_of_vertex(u));
                }
                ++edx;
            }

            //add a new list if it doesent exists
            if(!found1)
            {
                add_new_vertex_to_edgelist(u,v);
            }

            if(!found2)
            {
                add_new_vertex_to_edgelist(v,u);
            }
        }

        //find an edge by 2 vertexpoint
        bool containsedge(vertex v1, vertex v2)
        {
            for(int i=0; i<edges.size(); ++i)
            {
                if(edges[i][0] == v1.point)
                {
                    for(int vdx=1; vdx<edges[i].size(); ++vdx)
                        if(v2.point == vertexes[edges[i][vdx]].point)
                        {
                            //cout<<"edge found: "<<v1.point<<" to "<<v2.point<<endl; //LOG
                            return true;
                        }
                }
            }
            return false;
        }

        /*
        * add new vertex to the vertex list
        */
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

        void print()
        {
            print_vertexes();
            cout<<endl<<"EDGES: "<<endl;
            for(int i=0; i<edges.size(); ++i)
            {
                cout<<edges[i][0]<<": "<<endl;
                for(int j=1; j<edges[i].size(); ++j)
                    cout<<"\t"<<vertexes[edges[i][j]].point<<endl;
            }
        }

        void reinit() //reinit the d, color and parrent values for the second turn
        {
            for(int idx=0; idx<vertexes.size(); ++idx)
            {
                vertexes[idx].d = -50000;
                vertexes[idx].parrent = -50000;
                vertexes[idx].color = 1;
            }
        }

    private:

        //print the whole vertex list
        void print_vertexes()
        {
            cout<<"VERTEXES:"<<endl;
            for(int idx=0; idx<vertexes.size(); idx++)
            {
                vertexes[idx].print();
                cout<<"; ";
            }
            cout<<endl;
        }

        //create new edgelist into vector of edges
        //the first element is the real id of the vertex
        //the rest of elements are indexes of the vertexes from the 'vertexes' vector
        void add_new_vertex_to_edgelist(int v, int u)
        {
            vector<int> tmp;
            tmp.push_back(v);
            tmp.push_back(idx_of_vertex(u));
            edges.push_back(tmp);
        }

        //return the index of a vertex from the vector of 'vertexes'
        int idx_of_vertex(int v)
        {
            bool found = false;
            int idx = 0;
            while(!found && idx<vertexes.size())
            {
                if(vertexes[idx].point == v)
                {
                    found = true;
                    return idx;
                }
                ++idx;
            }
        }
};

/*
    Forrás:     http://aszt.inf.elte.hu/~asvanyi/ad/ad2jegyzet.pdf#page=38
*/
vertex BFS(Graph g, vertex startingpoint)
{
    g.reinit();
    //g.print();//LOG
    vertex vertex_with_max_d(startingpoint.point);
    vertex_with_max_d.reset_with(startingpoint);
    //vertex_with_max_d.print(); //LOG
    /*g.vertexes[0].d = 0;//s
    g.vertexes[0].color = 2;//s    //grey*/

    startingpoint.d = 0;
    startingpoint.color = 2;
    deque<vertex> bfs_queue;
    //bfs_queue.push_back(g.vertexes[0]);
    bfs_queue.push_back(startingpoint);
    while(!bfs_queue.empty())
    {
        vertex u = bfs_queue.front();
        bfs_queue.pop_front();
        //cout<<"ROUTE FROM ";u.print(); cout<<" TO "    //LOG
        for(int vidx=0; vidx<g.vertexes.size(); ++vidx)
        {
            if(g.containsedge(u, g.vertexes[vidx]))
                if(g.vertexes[vidx].d == -50000)
                {
                    g.vertexes[vidx].d = u.d + 1;
                    g.vertexes[vidx].parrent = u.point;
                    g.vertexes[vidx].color = 2; //grey
                    bfs_queue.push_back(g.vertexes[vidx]);
                    if(vertex_with_max_d.d<g.vertexes[vidx].d)
                        //vertex_with_max_d.print();cout<<"->";g.vertexes[vidx].print();cout<<endl;//LOG
                        vertex_with_max_d.reset_with(g.vertexes[vidx]);
                }
        }
//LOG
//cout<<"for ended"<<endl;
/*for(int i=0;i<bfs_queue.size(); ++i)
  bfs_queue[i].print();
cout<<endl<<"----------"<<endl;*/
//LOG
        u.color = 3; //black
    }
//LOG
/*
cout<<"OUTPUT GRAPH: ";
g.print();
cout<<endl;*/
//LOG
    //cout<<"RETURNED VERTEX: ";vertex_with_max_d.print();//LOG
    return vertex_with_max_d;
}


int main(int argc, char** argv)
{
//cout<<"Opening "<<argv[1]<<endl;                     //LOG
  //open the command lien argument
  string filename = argv[1];
  ifstream myfile;
  myfile.open (filename);

  int nr_of_threes_int;
  myfile>>nr_of_threes_int;
//cout<<"nr of threes "<<nr_of_threes_int<<endl;        //LOG
  //iterate on the graphs
  for(int gidx=0; gidx<nr_of_threes_int; gidx++)
  {
    //read and create the graph
    int nr_of_vertexes; //nr of the vertexes in the current graph (the first value)
    myfile>>nr_of_vertexes;
    Graph g;    //the current graph
    int u,v;    //the first 2 value in the graph, v and u are vertexes, and (v,u) is an edge
    myfile>>u>>v;
	while (!(u==0 && v==0))
	{
        //add vertexes of u and v
        vertex uu(u);
        g.add_vertex(uu);

        vertex vv(v);
        g.add_vertex(vv);
//cout<<"added vertexes: "<<u<<", "<<v<<endl;           //LOG
        //add edge
        g.add_edge(u,v);
//cout<<"added edge"<<endl;                             //LOG
        myfile>>u>>v;
	}
//LOG
/*
cout<<"INPUT GRAPH: ";
g.print();
cout<<endl;
*/
//LOG
	if(nr_of_vertexes != g.vertexes.size())
        cout<<"READING ERROR IN GRAPH "<<gidx<<endl;

    //processing of the current graph
    cout<<gidx+1<<". fa: "<<BFS(g,BFS(g,g.vertexes[0])).d<<endl;
   // cout<<"****************************"<<endl;
  }
  myfile.close();

  return 0;
}

