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

      int* getR(){
          return R ;
      };

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
void Map::initindex(){
          indexmap = new int*[row];
          for(int i=0 ; i<row ; i++ ){
            indexmap[i] = new int[col];
           for(int j=0 ; j<col ; j++ )
             indexmap[i][j] = -1 ;
          }
 };

void Map::create_array(){
    bit = new Bit[vertex];
    bit[0].row = R[0];
    bit[0].col = R[1];
    initindex();
    indexmap[R[0]][R[1]] = 0 ;

    int tmp = 1 ;
    for(int i=0 ; i<row ; i++){
       for(int j=0 ; j<col ; j++){
           if(met[i][j] == 0){
             bit[tmp].row = i;
             bit[tmp].col = j;
             setindex(i , j , tmp);
             tmp++ ;
           }
       }
    }

};

void Map::creatList(){
     adjList = new int*[vertex];
    for(int i = 0 ; i<row ; i++){
        for(int j = 0 ; j<col ; j++){
            int tmp =0 ;
            if(indexmap[i][j] != -1){
                adjList[indexmap[i][j]] = new int[4];
                for(int k=0 ; k<4 ; k++)
                 adjList[indexmap[i][j]][k] = -1 ;
             if(j+1<col&&indexmap[i][j+1] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i][j+1];
                tmp++ ;
             }
             if(j-1>0&&indexmap[i][j-1] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i][j-1];
                tmp++ ;
             }
             if(i+1<row&&indexmap[i+1][j] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i+1][j];
                tmp++ ;
             }
             if(i-1>0&&indexmap[i-1][j] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i-1][j];
                tmp++ ;
             }
            }

        }

    }

    delete(indexmap);
}

void Robot::BFS_startpoint(Map &map , int startpoint){
    find1 = new int[map.vertex+1];
    predecessor1 = new int[map.vertex+1];
    distance1 = new int[map.vertex+1];
    int findarr[map.vertex+1] ,tmp=0; 

    int i = startpoint ;
    for(int j=0 ; j<=map.vertex ; j++) {
        find1[j] = 0 ;
        predecessor1[j] = -1 ;
        distance1[j] =(map.vertex)+1;
        findarr[j]=-1;
    }

    find1[i] =1 ;
    distance1[i] = 0 ;
    predecessor1[i] = -1 ;
    findarr[tmp] = i;
    tmp++ ;
    while(findarr[0]!=-1){
                int u  = findarr[0];
                for(int k =0 ; k<4 && map.adjList[u][k] != -1 ; k++){
                    if(find1[map.adjList[u][k]]==0){
                        find1[map.adjList[u][k]] = 1;
                        distance1[map.adjList[u][k]] = distance1[u]+1;
                        predecessor1[map.adjList[u][k]] = u ;
                        findarr[tmp]=map.adjList[u][k] ;
                        tmp++ ;
                    }
                }
                for(int m=0 ; m<=map.vertex && findarr[m]!=-1;m++){
                    findarr[m] = findarr[m+1];
                }
                tmp--;
    }
};

int Robot:: topoint(Map &map){
    int max = 0 ;
    int topoint ;
    for(int i =0 ; i<=map.vertex ; i++){
        if(distance1[i]>=max && vertexfind[i]==0){
            topoint = i;
            max = distance1[i];
        }
    }
    //cout<<"we are going to" <<map.bit[topoint].row<<" "<<map.bit[topoint].col<<endl;
    add_path(map , 1, topoint);
    return topoint ;
};
void Robot::BFS_interpoint(Map &map , int interpoint){
    find2 = new int[map.vertex+1];
    predecessor2 = new int[map.vertex+1];
    distance2 = new int[map.vertex+1];
    int* findarr =new int[map.vertex+1] , tmp=0 ;
    int i = interpoint ;

    for(int i=0 ; i<=map.vertex ; i++) {
        find2[i] = 0 ;
        predecessor2[i] = -1 ;
        distance2[i] =(map.vertex)+1;
        findarr[i]=-1;
    }

    find2[i] =1 ;
    distance2[i] = 0 ;
    predecessor2[i] = -1 ;
    findarr[tmp] = i;
    tmp++ ;
    while(findarr[0]!=-1){
                int u  = findarr[0];
                for(int k =0 ; k<4 && map.adjList[u][k] != -1 ; k++){
                    if(find2[map.adjList[u][k]]==0){
                        find2[map.adjList[u][k]] = 1;
                        distance2[map.adjList[u][k]] = distance2[u]+1;
                        predecessor2[map.adjList[u][k]] = u ;
                        findarr[tmp]=map.adjList[u][k] ;
                        tmp++ ;
                    }
                }
                for(int m=0 ; m<=map.vertex && findarr[m]!=-1;m++){
                    findarr[m] = findarr[m+1];
                }
                tmp -- ;
    }

};

int Robot::updatefind(Map &map , int x , int remain , int type ){
         int tmp = x ;

         if(type == 1 || type ==3){

            for(int i =0 ; i<=distance1[x] ; i++){
                if(vertexfind[tmp]== 0){
                  remain -- ;
                  vertexfind[tmp] = 1;
                }
                 tmp = predecessor1[tmp];

            }
         }else {
             for(int k =0 ; k<distance2[x] ; k++){
                  if(vertexfind[tmp]== 0){
                    remain -- ;
                    vertexfind[tmp] = 1;
                  }
                 tmp = predecessor2[tmp];
            }

         }
         return remain ;

};



int Robot::nextpoint(Map &map , int x , int y){
    int max = 0 ;
    int nextpoint ;
    int find = 0 ;
   // cout<<"remain B is "<<y<<endl;
    for(int i =0 ; i<=map.vertex ; i++){
        if(distance2[i]!=(map.vertex)+1 && distance2[i]+distance1[i]<=y && distance2[i]+distance1[i]>=max && vertexfind[i]==0){
            nextpoint = i;
            max = distance2[i]+distance1[i];
            find = 1 ;
            //cout<<"find a point"<<map.bit[i].row<<" "<<map.bit[i].col<<endl;
            //cout<<"max is"<<distance2[i]<<" + "<<distance1[i]<<"="<<distance2[i]+distance1[i]<<endl;
        }
    }
    if(find==1){
        //cout<<"nextpoint is :"<<map.bit[nextpoint].row<<" "<<map.bit[nextpoint].col<<endl;
            add_path(map , 2 , nextpoint);

    }else{
        nextpoint=x;
        //cout<<"go back"<<"nextpoint is :"<<map.bit[x].row<<" "<<map.bit[x].col<<endl;
        add_path(map , 3 ,nextpoint);
    }
    return nextpoint ;
};

void Robot:: add_path(Map &map ,int type , int x){
  if(type == 1){
        if(head == NULL){

           head  = new Path[1];
           head->row = map.bit[0].row ;
           head->col = map.bit[0].col ;
           tail  = new Path[1] ;
           tail->row = map.bit[x].row ;
           tail->col = map.bit[x].col ;
           head->next = tail ;
           tail->next = NULL;
           step = step+1 ;
           Path *tmp = tail;
           int i = predecessor1[x];
           for( ; i!=0 ; ){
               Path *np = new Path[1];
               np->row = map.bit[i].row ;
               np->col = map.bit[i].col ;
               np->next = tmp ;
               tmp = np ;
               head->next = np ;
               i = predecessor1[i];
               step++ ;

           }
        } else {
             Path *ntail = new Path[1];
             ntail->row = map.bit[x].row ;
             ntail->col = map.bit[x].col ;
             tail->next = ntail ;
             Path* tmp = ntail ;
             int i = predecessor1[x];
             step++ ;

             for( ; i!=0 ; ){
               Path *np = new Path[1];
               np->row = map.bit[i].row ;
               np->col = map.bit[i].col ;
               np->next = tmp ;
               tmp = np ;
               tail->next = np ;
               i = predecessor1[i];
               step++;
            }
            tail = ntail ;
        }

  } else if (type == 2){
             Path *ntail = new Path[1];
             ntail->row = map.bit[x].row ;
             ntail->col = map.bit[x].col ;
             tail->next = ntail ;
             Path* tmp = ntail ;
             int i = predecessor2[x];
             step++;
             for(int k =1 ; k<distance2[x] ; k++ ){
               Path *np = new Path[1];
               np->row = map.bit[i].row ;
               np->col = map.bit[i].col ;
               np->next = tmp ;
               tmp = np ;
               tail->next = np ;
               i = predecessor2[i];
               step ++ ;
            }
            tail = ntail ;

   } else if(type == 3){
       int i = predecessor1[x] ;
       Path* tmp = tail;
        for( ; i!=-1 ; ){
               Path *np = new Path[1];
               np->row = map.bit[i].row ;
               np->col = map.bit[i].col ;
               np->next = NULL ;
               tmp ->next = np ;
               tmp = np ;
               i = predecessor1[i];
               step ++ ;
            }
            tail = tmp ;
   }

 };

void Robot::findpath(Map &map){
     initvertexfind(map);
     static int cleanblock = map.vertex ;
     step = 0;
     vertexfind[0]=1;
     BFS_startpoint(map , 0);
     int remainB = B;
     int next , back ;
      while(cleanblock>0){
          back=0 ;
          next = topoint(map);
          cleanblock = updatefind(map ,next , cleanblock , 1);
          remainB = remainB-distance1[next];
          while(back == 0){
               BFS_interpoint(map ,next);
               int tmp =nextpoint(map ,next,  remainB);
               cleanblock = updatefind(map ,tmp  , cleanblock , 2);
               if(next != tmp) {
                  remainB = remainB-distance2[tmp];
                  next =tmp;
               } else back = 1 ;
          }
          cleanblock = updatefind(map , next  , cleanblock , 3);
          //cout<<" cleanblock is: "<<cleanblock<<endl;
          remainB = B;
          /*file2<<"we have clean this blocks :"<<endl;
          for(int i =0 ; i<=map.vertex ; i++){
            if(vertexfind[i]==1)
                file2<<i<<": "<<map.bit[i].row<<" "<<map.bit[i].col<<endl;
          }
          file2<<"================"<<endl;
          */

     }
};

void Robot::printpath(){
     Path* tmp = head ;
     file2<<step<<endl;
     while(tmp!=NULL){
        file2<<tmp->row<<" "<<tmp->col<<" "<<endl;
        tmp=tmp->next;
     }

}


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
    if(cleanblock==0){
        file2<<"0"<<endl;
        file2<<map.getR()[0]<<" "<<map.getR()[1]<<endl;
        return 0 ;
    }
    map.setvertex(cleanblock);
    map.create_array();
    map.creatList ();
    robot.findpath(map);
    robot.printpath();


return 0 ;

}
