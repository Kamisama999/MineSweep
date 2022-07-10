#ifndef MINEMAP_H
#define MINEMAP_H

class MineMap
{
public:
    MineMap();
    ~MineMap();
    void Create();              //布雷
    void Create(int row, int column, int number);
    void Restart();             //重新布雷
    int NearFlag(int m, int n);    //计算周围的旗子数
    int** Map;                   //地图
    int MineNumber;       //雷数
    int Row;                       //行
    int Column;                 //列
    bool RClick(int x, int y);      //右击
    bool LRClick(int x, int y);    //左右同时按
    bool LClick(int x, int y);       //左击
    bool Win();             //判断是否获胜
    int winflag;             //判断胜利 0为失败 2为胜利
    int RemainMine;   //剩余雷数
    bool first;             //判断是否为第一次，防止直接踩雷
    int timer;              //记录时间
};

#endif // MINEMAP_H
