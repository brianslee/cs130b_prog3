/**Brian Lee
 * 3620101
 * CMPSC 130B Prog3
 * Minimum Cost Path
 * for Toroidal Graph
 **/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <float.h>

#include "prog3.h"

using namespace std;

int main()
{
    int m, n;
    cout << "Number of points: ";
    cin >> m >> n;
    
    int counter = 1;
    vector<Point> firstPlane;
    vector<Point> secPlane;
    
    //cout << m << n << endl;
    //Get Points
    double x, y, z;
    for(int i = 0; i < m; ++i)
    {
        cout << "First Plane Point Coordinates: ";
        cin >> x >> y >> z;
        Point temp(x, y, z, counter);
        firstPlane.push_back(temp);
        counter++;
    }
    
    for(int j = 0; j < n; ++j)
    {
        cout << "Second Plane Point Coordinates: ";
        cin >> x >> y >> z;
        Point temp(x, y, z, counter);
        secPlane.push_back(temp);
        counter++;
    }
    
    //Rotate Second plane
    int minNum = secPlane.at(0).pointNum;
    double minArea = DBL_MAX;
    for(int i = 0; i < n; ++i)
    {
        //Check area
        double area = getArea(firstPlane.at(0), secPlane.at(0), secPlane.at(1));
        //If area is smaller, update checker
        if(area < minArea)
        {
            minArea = area;
            minNum = secPlane.at(0).pointNum;
        }
        //Rotate
        Point temp = secPlane.at(0);
        secPlane.erase(secPlane.begin());
        secPlane.push_back(temp);
    }
    
    //While the point aligned with the first point on the first plane is not
    //The first point in the vector
    while(minNum != secPlane.at(0).pointNum)
    {
        //Rotate
        Point temp = secPlane.at(0);
        secPlane.erase(secPlane.begin());
        secPlane.push_back(temp);
    }
    
    //Make Graph
    vector<vector<Node> > torGraph;
    
    //Graph is of size m+1 x n+1
    for(int i = 0; i <= m; ++i)
    {
        vector<Node> row;
        for(int j = 0; j <= n; ++j)
        {
            //For the first point
            Node newNode;
            if(i == 0 && j == 0)
            {
                newNode = Node(firstPlane.at(i), secPlane.at(j), 0.0, 0.0);
            }
            else
            {
                int x = i;
                int y = j;
                if(i == m)
                {
                    x = 0;
                }
                if(j == n)
                {
                    y = 0;
                }
                
                newNode = Node(firstPlane.at(x), secPlane.at(y));
            }
            
            row.push_back(newNode);
        }
        
        torGraph.push_back(row);
    }
    
    //Make Path
    //printGraph(torGraph);
    torGraph = minCost(torGraph);
    //printGraph(torGraph);
    
    vector< vector<int> > graphPath = minPath(torGraph);
    
    //Print Path
    printPath(graphPath);
    
    return 0;
}