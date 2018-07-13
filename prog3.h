/**Brian Lee
 * 3620101
 * CMPSC 130B Prog3
 * Header file for
 * Prog3 Helper Functions
 **/

#ifndef PROG3_H_
#define PROG3_H_

#include <vector>
#include <float.h>
using namespace std;

struct Point
{
    double x;
    double y;
    int z;
    int pointNum;
    
    Point(): x(0.0), y(0.0), z(0), pointNum(0){}
    Point(double x, double y, int z, int num): x(x), y(y), z(z), pointNum(num){}
};

struct Node
{
    Point p;
    Point q;
    double weight;
    double pathCost;
    bool fromTop;
    
    Node(): p(Point()), q(Point()), weight(DBL_MAX), pathCost(DBL_MAX), fromTop(false){}
    Node(Point a, Point b): p(a), q(b), weight(DBL_MAX), pathCost(DBL_MAX), fromTop(false){}
    Node(Point a, Point b, double area, double cost): p(a), q(b), weight(area), pathCost(cost), fromTop(false){}
};

double getDist(Point p1, Point p2);

double getArea(Point p1, Point p2, Point p3);

vector<vector<Node> > minCost(vector<vector<Node> > graph);

vector<vector<int> > minPath(vector<vector<Node> > graph);

void printPath(vector<vector<int> > path);

void printGraph(vector< vector<Node> > graph);

#endif