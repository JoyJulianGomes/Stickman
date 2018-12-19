#include "iostream"
#include "vector"
using namespace std;

class Point
{
    public:
    int x;
    int y;
};

class Shape
{
    public:
    int noOfEdge;
    vector<Point> vertices;
    bool centerFlag;
    Point center;

    int insertNoOfEdge()
    {
        int temp;
        cout<<"Insert no of edge:";
        cin>>temp;
        cout<<endl;

        return (temp>2)?temp:insertNoOfEdge();
    }
    vector<Point> insertVerticesList(int limit)
    {
        vector<Point> tempList;

        for(int i = 0; i<limit; i++)
        {
            Point tempPoint;
            cin>>tempPoint.x>>tempPoint.y;
            cout<<endl;
            tempList.push_back(tempPoint);
        }
        return tempList;
    }
    Shape()
    {
        centerFlag = false;
        this->noOfEdge = insertNoOfEdge();
        cout<<"Enter the vertices:"<<endl;
        this->vertices = insertVerticesList(this->noOfEdge);
    }
    Shape(int edges)
    {
        centerFlag = false;
        this->noOfEdge = edges;
    }
    Shape(Shape* dice)
    {
        centerFlag = false;
        this->noOfEdge = dice->noOfEdge;
        this->vertices = dice->vertices;
    }
    Shape(string x)
    {
        centerFlag = false;
        this->noOfEdge = 5;
        vector<Point> tempList;
//-20 0 -5 -20 5 -20 20 0 0 20
        Point tempPoint;
        tempPoint.x = -20; tempPoint.y = 0;
        tempList.push_back(tempPoint);
        tempPoint.x = -8; tempPoint.y = -20;
        tempList.push_back(tempPoint);
        tempPoint.x = 8; tempPoint.y = -20;
        tempList.push_back(tempPoint);
        tempPoint.x = 20; tempPoint.y = 0;
        tempList.push_back(tempPoint);
        tempPoint.x = 0; tempPoint.y = 20;
        tempList.push_back(tempPoint);


        this->vertices = tempList;
    }
    void showShape()
    {
        cout<<"No of edge = "<<this->noOfEdge<<endl;
        cout<<"Vertices"<<endl;
        for(int i = 0; i < this->noOfEdge; i++)
        {
            cout<<this->vertices[i].x<<" "<<this->vertices[i].y<<endl;
        }
    }
    void AddVertex(Point p)
    {
        //cout<<p.x<<" "<<p.y;
        if(centerFlag==false){
            center.x=p.x;
            center.y=p.y;
            centerFlag=true;
        }
        else{
            center.x+=p.x;
            center.y+=p.y;
            center.x/=2;
            center.y/=2;
        }
        this->vertices.push_back(p);
    }
    void AddVertex(int x, int y)
    {
        Point p;
        p.x=x;
        p.y=y;
        AddVertex(p);
    }
    void clearVertices()
    {
        vertices.clear();
    }
};
