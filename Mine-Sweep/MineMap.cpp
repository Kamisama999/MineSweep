#include "MineMap.h"
#include <stdlib.h>
#include <time.h>

MineMap::MineMap():MineNumber(0),winflag(0),RemainMine(0)
{
    Row=10;
    Column=8;
    MineNumber=15;
    Map=NULL;
}

MineMap::~MineMap()
{
}

//生成雷和数字
void MineMap::Restart()
{
    int i,j;
    //初始化
    for(i=0;i<Row;i++)
        for(j=0;j<Column;j++)
            Map[i][j] = 100;            //100为空白

    //随机布雷
    srand(time(NULL));
    for(i=0;i<MineNumber;i++)
    {
        int x=rand()%Row;
        int y=rand()%Column;
        if(Map[x][y]!=99)
            Map[x][y]=99;            //99为雷
        else
            i--;            //如果已经布雷就重新来一次
    }

    //生成雷周围的数字
    for(i=0;i<Row;i++)
    {
        for(j=0;j<Column;j++)
        {
            if(Map[i][j]==99)
            {
                int x,y;
                for(x=-1;x<2;x++)
                {
                    for(y=-1;y<2;y++)
                    {
                        // 越界或是雷就跳过
                        if(i+x>=Row||j+y>=Column||i+x<0||j+y<0||Map[i+x][j+y]==99)
                        {
                            continue;
                        }
                        Map[i+x][j+y]++;        //101到109为数字
                    }
                }
            }
        }
    }
    winflag=1;
    RemainMine=MineNumber;
    first=true;
    timer=0;
}

//创造Map空间
void MineMap::Create()
{
    int i;
    if(Map!=NULL)         //删除原本地图
    {
        for(i=0;i<Row;i++)
        {
            delete Map[i];
        }
        delete Map;
        Map=NULL;
    }
    Map=new int*[Row];
    for(i=0;i<Row;i++)
    {
        Map[i]=new int[Column];
    }
    Restart();     //生成雷和数字
}

//自定义创造Map空间大小
void MineMap::Create(int row,int column,int number)
{
    int i;
    if(Map!=NULL)         //删除原本地图
    {
        for(i=0;i<Row;i++)
        {
            delete Map[i];
        }
        delete Map;
        Map=NULL;
    }
    Row=row;                     //自定义行列数和炸弹数
    Column=column;
    MineNumber=number;
    Map=new int*[Row];
    for(i=0;i<Row;i++)
    {
        Map[i]=new int[Column];
    }
    Restart();     //生成雷和数字
}

//左键点击格子
bool MineMap::LClick(int x,int y)
{
    if(winflag==0||winflag==2)
        return false;

    //越界或已打开
    if(x>=Row||y>=Column||x<0||y<0||Map[x][y]<=90)
        return false;

    //有数字
    if(Map[x][y]>=101&&Map[x][y]<=108)
    {
        Map[x][y]-=100;    //打开数字为1到8
        first=false;
        Win();                       //判断是否胜利
        return true;
    }

    //没有数字，递归打开周围的格子
    if(Map[x][y]==100)
    {
        Map[x][y]-=100;       //打开为0
        LClick(x-1,y);
        LClick(x+1,y);
        LClick(x,y+1);
        LClick(x,y-1);
        LClick(x-1,y-1);
        LClick(x+1,y-1);
        LClick(x-1,y+1);
        LClick(x+1,y+1);
    }

    //踩雷
    if(Map[x][y]==99)
    {
        int i,j;
        if(first)       //第一步就踩雷
        {
            RemainMine--;       //消除当前位置的雷
            int t=0;
            //改变周围的数字
            for(i=-1;i<2;i++)
            {
                for(j=-1;j<2;j++)
                {
                    if((i+x<Row)&&(j+y)<Column&&(i+x>=0)&&(j+y>=0)&&(x||y))
                    {
                        if(Map[i+x][j+y]>99)
                            Map[i+x][j+y]--;
                        if(Map[i+x][j+y]==99)
                            t++;
                    }
                }
            }
            first=false;
            Map[x][y]=100+t;
            LClick(x,y);           //消除雷后点开
            return true;
        }

        //显示出雷和插错的旗子
        for(i=0;i<Row;i++)
        {
            for(j=0;j<Column;j++)
            {
                if(Map[i][j]==99)
                Map[i][j]=-1;                   //-1为雷
                if(Map[i][j]>49&&Map[i][j]<60)
                Map[i][j]=-2;                   //-2为插错的旗子
            }
        }
        winflag=0;
    }
    return true;
}

//右键插旗
bool MineMap::RClick(int x,int y)
{
    if(winflag==0||winflag==2)
        return false;
    if(x>=Row||x<0||y>=Column||y<0||Map[x][y]<40)
        return false;
    if(Map[x][y]>90)       //未打开
    {
        Map[x][y]-=50;
        RemainMine--;
    }
    else if(Map[x][y]>40&&Map[x][y]<60)    //已插旗
    {
        RemainMine++;
        Map[x][y]+=50;
    }
    return true;
}

//计算周围的旗子数
int MineMap::NearFlag(int x,int y)
{
    if(x>=Row||x<0||y>=Column||y<0)     //越界
    {
        return -1;
    }
    int n=0;
    int i,j;
    for(i=-1;i<2;i++)
    {
        for(j=-1;j<2;j++)
        {
            //越界或不是旗子就跳过
            if(x+i>=Row||y+j>=Column||x+i<0||y+j<0||Map[x+i][y+j]>60||Map[x+i][y+j]<40)
                continue;
            n++;
        }
    }
    return n;
}

//左右键同时按
bool MineMap::LRClick(int x,int y)
{
    if(x>=Row||x<0||y>=Column||y<0||Map[x][y]>40)   //越界或未打开
        return false;
    if(Map[x][y]==NearFlag(x,y))     //数字刚好和周围的旗子相等
    {                                                    //打开周围的格子
        LClick(x-1,y);
        LClick(x+1,y);
        LClick(x,y+1);
        LClick(x,y-1);
        LClick(x-1,y-1);
        LClick(x+1,y-1);
        LClick(x-1,y+1);
        LClick(x+1,y+1);
    }
    return true;
}

//判断是否获胜
bool MineMap::Win()
{
    int i,j;
    for(i=0;i<Row;i++)
    {
        for(j=0;j<Column;j++)
        {
            //有未打开或旗子插错就未获胜
            if(Map[i][j]>99||(Map[i][j]>49&&Map[i][j]<59))
                return false;
        }
    }
    winflag=2;
    return true;
}
