DS_term_project2
可以做兩種BFS
int BFS_starpoint
--> 這個BFS 創造出來的distance1 array  和 predecessor會一直保存


int BFS_interpoint(i-->j) ;
-->這個BFS每走到一次目標點 就會創造一個新的distance2 和predecessor2


兩種BFS都可以順便return point 告訴我們下一次往哪裡去。
add_path 直接改成創造一個
Node{
    int row ;
    int col ;
    Node* next 
}

Add_path(int type ; int )
利用程設lowerbond的觀念 找到一個 distance2[j]+distance[j]<=剩下的電量
如果沒有的話 就直接走原路回去!

如果第一個到的點剩下的B>　從這個點到下一個還沒有掃過點的distance(從最遠的檢查回來) + 那點回來原點的距離

BFS放robot比較好 還可以順便回傳topoint 和 backpoint 可以用friend

path 還是用link list 而且一開始就存 會比較好
=====================================================================================
更新 map robot 的功能

map
{
create adjancency list ; 
create bitarray -->為了BFS 沒一個要清掃的點都被編號了 bit 的index就是編號 裡面存放的row 和 col 就是為了記錄該編號對應原本的map 的哪裡
indexmap --> 存放的元素為-1 表示該點就是 1 存放元素不會-1 就是該點的編號(其實後面不會用到了啦 只是為了做adjacency list 才會用到)

}

Robot{
 做BFS
 找到path 
 print 出path
}