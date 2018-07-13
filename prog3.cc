/**Brian Lee
 * 3620101
 * CMPSC 130B Prog3
 * Implementation file for
 * Prog3 Helper Functions
 **/
 
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <float.h>

#include "prog3.h"

using namespace std;

double getDist(Point p1, Point p2)
{
    double xVal = p2.x -p1.x;
    double yVal = p2.y - p1.y;
    double zVal = p2.z - p1.z;
    double x = xVal * xVal;
    double y = yVal * yVal;
    double z = zVal * zVal;
    double d = x + y +z;
    d = sqrt(d);
    return d;
}

double getArea(Point p1, Point p2, Point p3)
{
    double a, b, c, s;
    a = getDist(p1, p2);
    b = getDist(p2, p3);
    c = getDist(p3, p1);
    s = (a + b + c) / 2;
    
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

vector<vector<Node> > minCost(vector<vector<Node> > graph)
{
    vector<vector<Node> > minCostGraph = graph;
    
    //Initialize first column
    for(int i = 1; i < minCostGraph.size(); ++i)
    {
        minCostGraph.at(i).at(0).weight = getArea(minCostGraph.at(i).at(0).q, minCostGraph.at(i).at(0).p, minCostGraph.at(i - 1).at(0).p);
        minCostGraph.at(i).at(0).pathCost = minCostGraph.at(i).at(0).weight + minCostGraph.at(i - 1).at(0).pathCost;
    }
    
    //Initialize first row
    for(int j = 1; j < minCostGraph.at(0).size(); ++j)
    {
        minCostGraph.at(0).at(j).weight = getArea(minCostGraph.at(0).at(j).p, minCostGraph.at(0).at(j).q, minCostGraph.at(0).at(j - 1).q);
        minCostGraph.at(0).at(j).pathCost = minCostGraph.at(0).at(j).weight + minCostGraph.at(0).at(j - 1).pathCost;
    }
    
    //Figure out the cost of the rest of the graph
    for(int i = 1; i < minCostGraph.size(); ++i)
    {
        for(int j = 1; j < minCostGraph.at(i).size(); ++j)
        {
            //Compare costs between top and left graphs
            double topWeight = getArea(minCostGraph.at(i).at(j).q, minCostGraph.at(i).at(j).p, minCostGraph.at(i - 1).at(j).p);
            double topCost = topWeight + minCostGraph.at(i - 1).at(j).pathCost;
            double leftWeight = getArea(minCostGraph.at(i).at(j).p, minCostGraph.at(i).at(j).q, minCostGraph.at(i).at(j - 1).q);
            double leftCost = leftWeight + minCostGraph.at(i).at(j - 1).pathCost;
            
            //Recurrence relation
            if(topCost < leftCost)
            {
                minCostGraph.at(i).at(j).weight = topWeight;
                minCostGraph.at(i).at(j).pathCost = topCost;
                minCostGraph.at(i).at(j).fromTop = true;
            }
            else
            {
                minCostGraph.at(i).at(j).weight = leftWeight;
                minCostGraph.at(i).at(j).pathCost = leftCost;
                minCostGraph.at(i).at(j).fromTop = false;
            }
        }
    }
    
    return minCostGraph;
}

vector<vector<int> > minPath(vector<vector<Node> > graph) //FIXIT!
{
    int x = graph.size() - 1;
    int y = graph.at(x).size() - 1;
    vector<vector<int> > pathFound;
    
    while(x != 0 && y != 0)
    {
        vector<int> triangle;
        int first, second, third;
        if(graph.at(x).at(y).fromTop)
        {
            first = graph.at(x).at(y).q.pointNum;
            second = graph.at(x).at(y).p.pointNum;
            third = graph.at(x - 1).at(y).p.pointNum;
            x--;
        }
        else
        {
            first = graph.at(x).at(y).p.pointNum;
            second = graph.at(x).at(y).q.pointNum;
            third = graph.at(x).at(y - 1).q.pointNum;
            y--;
        }
        
        triangle.push_back(first);
        triangle.push_back(second);
        triangle.push_back(third);
        
        pathFound.push_back(triangle);
    }
    
    if(x == 0 && y != 0)
    {
        while(y != 0)
        {
            vector<int> triangle;
            int first, second, third;
            first = graph.at(x).at(y).p.pointNum;
            second = graph.at(x).at(y).q.pointNum;
            third = graph.at(x).at(y - 1).q.pointNum;
            y--;
            
            triangle.push_back(first);
            triangle.push_back(second);
            triangle.push_back(third);
            
            pathFound.push_back(triangle);
        }
    }
    else if(y == 0 && x != 0)
    {
        while(x != 0)
        {
            vector<int> triangle;
            int first, second, third;
            first = graph.at(x).at(y).q.pointNum;
            second = graph.at(x).at(y).p.pointNum;
            third = graph.at(x - 1).at(y).p.pointNum;
            x--;
            
            triangle.push_back(first);
            triangle.push_back(second);
            triangle.push_back(third);
            
            pathFound.push_back(triangle);
        }
    }
    
    return pathFound;
}

void printPath(vector<vector<int> > path)
{
    for(int i = 0; i < path.size(); ++i)
    {
        for(int j = 0; j < path.at(i).size(); ++j)
        {
            cout << path.at(i).at(j);
            
            if(j == path.at(i).size() - 1)
            {
                cout << endl;
            }
            else
            {
                cout << " ";
            }
        }
    }
}

void printGraph(vector< vector<Node> > graph)
{
    for(int i = 0; i < graph.size(); ++i)
    {
        for(int j = 0; j < graph.at(i).size(); ++j)
        {
            cout << "(" << graph.at(i).at(j).p.pointNum << ", " << graph.at(i).at(j).q.pointNum << "), ";
            cout << graph.at(i).at(j).weight << ", " << graph.at(i).at(j).pathCost << ", " << graph.at(i).at(j).fromTop;
            if(j == graph.at(i).size() - 1)
            {
                cout << endl;
            }
            else
            {
                cout << "; ";
            }
        }
    }
}