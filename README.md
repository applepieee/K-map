# K-map
 1. Kmap();    //設定初始值 

2.void setStr(string);//把字串分解，並輸入陣列裡 

3. void exminterm();    //把字串讀進，並轉換成陣列的index 

4. void check(int);//abcd字母要每一個都出現，沒有出現的要處理 
5.void setGraph();//設定kmap 

6.char getGraph(int,int);//kmap 

7.int logic();//找prime implicants 

8.void find(int,int,int[][4]);//尋找essential prime implicant 

9.  string getS();//回傳答案 

data member

vector<string> str;//紀錄分解字串 

 int nWeight[5];//數字權重  

   int cnt_graph[16][2];//計算被抓幾次 

    int cnt_1;//find裡會用到的變數 

    bool map[16];//看哪個index有出現 有的話為true 

    bool dont_care[16],exist[4];  //判斷dontcare 與是否要展開abcd4個字母有無出現   

    char graph[4][4]; // 紀錄4*4的畫面 1,0,X
    

    string s[100]; //紀錄prime implicant用
