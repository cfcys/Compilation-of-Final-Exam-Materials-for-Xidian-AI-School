//本质就是求最短的路径的算法
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>                                 //有INT_MAX可以直接调用整形之中最大的数
#include <iostream>                                 
#include <string>
struct Graph               
{
    int n;                                         //本程序中，程序的标号是从一开始，而不是从0开始
    int m;
    int Matrix[233][233] = {0};
};

void Great(Graph *G){
    printf("请输入顶点的数量：");
    scanf("%d",&(G->n));
    printf("请输入边的数量: ");
    scanf("%d", &(G->m));

    for(int i = 1;i<=233;i++){
        for(int j = 1;j<=233;j++){
           G->Matrix[i][j] = 10000;               //该矩阵默认全部是最大的值
        }
    }
    printf("请输入该网络的邻接矩阵的形式：");
    for(int i = 0;i<G->m;i++){                    //将边给输入好
        int j,k;                                  //j代表横坐标，k代表纵坐标
        int Temp;                               //Temp代表权值的大小
        scanf("%d %d %d",&j,&k,&Temp);
        G->Matrix[j][k] = Temp;
        G->Matrix[k][j] = Temp;
    }     
}

void Dijkstra(Graph *G){                          //从一个城市出发到其他城市的最短的路径  
    printf("请输入你选择的城市的序号（从1开始）：");
    int D[233];                                
    int p[233];                                   //记录最短的路径中顶点i的前驱顶点
    int s[233];                                   //用于标识最短的路径的生成的情况,为1表示从原点到i的最短的路径已经找到 
    int v;
    int k;                                        //这个k具体是干啥用得呢
    scanf("%d",&v);
    int min,max = 10000,pre;
    for(int i = 1;i<=G->n;i++){
        D[i] = G->Matrix[v][i];
        if(D[i] != INT_MAX)                      //如果这里不是空的
            p[i] = v + 1;
        else
            p[i] = 0;
        s[i] = 0;
    }
    s[v] = 1;                                    //将原点送到U
    for(int i = 1;i<G->n;i++){
        min = 10001;                             //min > max 让最大值得那个也能加入U
        for(int j = 1;j<=G->n;j++){
            if((!s[j]) && (D[j] < min)){
                min = D[j];
                k = j;
            }
        }
        s[k] = 1;                                //将找到得顶点k送入U
        for(int j = 1;j<=G->n;j++){
            if((!s[j]) && (D[j] > D[k] + G->Matrix[k][j]))
            {
                D[j] = D[k] + G->Matrix[k][j];
                p[j] = k+1;                      //k是j的前驱
            }
        }                                        //所有的顶点已经扩充到了U中
        }
        for(int k = 1;k<=G->n;k++){
            if(k == v && k <  10){
                printf(" 0 %10d",k);
            }else if(k == v && k >= 10){
                printf(" 0 %11d",k);
            }else if(D[k] == 10000 && k < 10){
                printf(" ∞ %10d",k);
            }else if(D[k] == 10000 && k >= 10){
                printf(" ∞ %11d",k);
            }else{
                printf(" %-10d %d",D[k],k);
            }
            pre= p[k];
            if(k != v){
            while((pre != 0) && (pre != v+1)){
                printf("<_%d",pre-1);
                pre = p[pre-1];
            }
            printf("<_%d",v);}
            printf("\n");
    }
}

void Floyd(Graph *G){
    printf("接下来输出每一对顶点之间的最短路径：\n");
    int Path[233][233];                             //路径矩阵
    int D[233][233];
    int i,j,k,pre;
    int w,max = 10000;
    for(i = 0;i<=G->n;i++){
        for(j = 0;j<=G->n;j++){
            if(G->Matrix[i][j] != max){
                Path[i][j] = i+1;                   //i是j得前驱
            }else{
                Path[i][j] = 0;
            }
            D[i][j] = G->Matrix[i][j];
        }
    }
    for(k = 1;k<=G->n;k++){
        for(i = 1;i<=G->n;i++){
            for(j = 1;j<=G->n;j++){
                if(D[i][j] > (D[i][k] + D[k][j])){
                    D[i][j] = D[i][k] + D[k][j];    //修改路径的长度
                    Path[i][j] = Path[k][j];        //修改路径
                }
            }
        }
    }
    for(i = 1;i<=G->n;i++){
        printf("第%d组：\n",i);
        for(j = 1;j<=G->n;j++){
            if(i == j && j < 10){
                printf(" 0 %10d",j);
            }else if(i == j && j >= 10){
                printf(" 0 %11d",j);
            }else if(D[i][j] == 10000 && j < 10){
                printf(" ∞ %10d",j);
            }else if(D[i][j] == 10000 && j >= 10){
                printf(" ∞ %11d",j);
            }else{
            printf(" %-10d %d",D[i][j],j);
            }
            pre = Path[i][j];
            if(i!=j){
            while((pre != 0) && (pre != i+1)){
                printf("<_%d",pre-1);
                pre = Path[i][pre-1];
            }
            }
            printf("<_%d\n",i);
        }
    }
}

int main(void){
    Graph G;
    Great(&G);
    Dijkstra(&G);
    Floyd(&G);
    return 0;
}
