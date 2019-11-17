#include<iostream>
#include<fstream>
using namespace std;

ifstream file("floor.data");
ofstream file2("final.path");
class Bit{
 public:
  int row ;
  int col ;
};
class Robot;
class Map ;

class Path{
 public:
    int row ;
    int col ;
    Path* next ;
};
class Map{
    private:
      int vertex  , row , col , R[2];
      int**  met ;
      int** indexmap;
      int** adjList ;
      Bit* bit ;

    public:
      void setrow (int x) { row = x;};

      void setcol (int x) { col = x ;};

      void setR(int x , int y){
         R[0] = x ;
         R[1] = y ;
      };

      void initmet(){
          met = new int*[row];
          for(int i=0 ; i<row ; i++)
           met[i]=new int [col];
      };

      void setmap(int i , int j , int x) {met[i][j] = x ;};

      int* getadj(int x){return adjList[x];};

      Bit* getbit(){return bit ;};

      int getvertex(){return vertex;};

      void initindex();

      void setindex(int i , int j , int x){
          indexmap[i][j] = x ;
      };

      void setvertex(int x) {vertex = x;};

      void create_array();

      void creatList();

      friend class Robot ;
};

class Robot{
 private :
  int B ;
  Path*  head =NULL ;
  Path*  tail =NULL ;
  int* vertexfind ;
  int *find1 , *distance1 , *predecessor1  ;
  int *find2 , *distance2 , *predecessor2 ;
  int step ;
 public:

     void setB(int x) { B = x;};

     void initvertexfind(Map &map){
         vertexfind = new int [map.vertex+1] ;
         for(int i =0 ; i<=map.vertex ; i++)
           vertexfind[i] = 0 ;
     }


     void findpath(Map &map);

     void BFS_startpoint(Map &map , int x);

     void BFS_interpoint(Map &map , int x);

     int topoint (Map &map);

     int nextpoint(Map &map , int x , int y);

     void add_path(Map &map , int type , int x);

     int  updatefind(Map &map , int x , int remain , int type);

     void printpath();

};

int main (){
    int x , y , z , cleanblock=0 ;
    char bit ;
    file>>x>>y>>z ;
    Robot robot ;
    Map map ;
    map.setrow(x);
    map.setcol(y);
    map.initmet();
    robot.setB(z) ;
    for(int i=0 ; i<x ; i++){
        for(int j=0 ; j<y ; j++){
            file>>bit ;
            if(bit == '0') {
                map.setmap(i , j , 0);
                cleanblock++ ;

            }
            else if(bit == '1')  map.setmap(i , j , 1);
            else{
                map.setR(i , j);
                map.setmap(i , j , 2);
             }
        }
    }
    map.setvertex(cleanblock);
    map.create_array();
    map.creatList ();
    robot.findpath(map);
    robot.printpath();


return 0 ;

}
