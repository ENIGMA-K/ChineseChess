//
//  ChineseChess.h
//  ChineseChess
//
//  Created by Kevin on 2021/3/27.
//
//这是一个中国象棋的头文件，使用这个文件能够用于设计中国象棋游戏、中国象棋打谱以及象棋 AI 的开发。

#ifndef ChineseChess_h
#define ChineseChess_h
//MARK:声明引用&全局变量
#include <vector>
#include "math.h"
#include <time.h>
using namespace std;
#define ORI_SITU "RTBGKGBTR10C5C1P1P1P1P1P18p1p1p1p1p1c5c10rtbgkgbtr"
//MARK:基础方法
//延时函数
void sleep(double _duration){
    struct timespec ts, ts1;
    ts.tv_nsec =(_duration-floor(_duration))*1000000000;
    ts.tv_sec = floor(_duration);
    nanosleep(&ts, &ts1);
}
//随机数
int rnd(int uper)
{
    srand((int)time(NULL)*rand());
    return (rand()%uper);
};
//生成随机序列
bool* select(int m,int n,int non/*n个里面取m个，其中第 non 个不取*/)
{
    bool *_opt=new bool[n];
    for (int _i=0;_i<n;_i++){
        *(_opt+_i)=false;
    }
    int sel[m];
    for (int _i=0;_i<m;_i++){
        sel[_i]=rnd(n-m+_i);
    }
    for (int _i=0;_i<m;_i++){
        for (int _j=0;_j<_i;_j++){
            if (sel[_j]>=sel[_i]){
                sel[_j]++;
            }
        }
    }
    for (int _i=0;_i<m;_i++){
        if (sel[_i]>=non&&non>=0){
            sel[_i]++;
        }
    }
    for (int _i=0;_i<m;_i++){
        *(_opt+sel[_i])=true;
    }
    return _opt;
}
//某数据在数组中存在性检验
template <class T>
int isIn(T finditem,T* itembank,int banksize){
    for (int i=0;i<banksize;i++){
        if (finditem==*(itembank+i)){
            return i;
        }
    }
    return -1;
}
//安全释放指针
template <class T>
inline void SafeDelete(T*& pVal)
{
    if (pVal != NULL)
    {
        delete pVal;
        pVal = NULL;
    }
}
template <class T>
inline void SafeDeleteArray(T*& pVal)
{
    if (pVal != NULL)
    {
        delete[] pVal;
        pVal = NULL;
    }
}
//MARK:棋子类 CHESSSTONE
//棋子名称数据集
char StoneNameBank[14]={
    'K','G','B','T','R','C','P','k','g','b','t','r','c','p'
};
//定义坐标数据类型
typedef struct Pos/*九路十行*/
{
    int _x=0;//[0,9]行
    int _y=0;//[0,8]路
}Pos;
class CHESSSTONE
{
public://参数部分
    int name_id=-1;//表示棋子名称的顺序
    int chess_id=-1;//只有在一局棋中的初始化，才会带有 chess_id
    char stone_name=' ';
    //注意：在棋谱中以缩写表达棋子类型，分别为K/G/B/T/R/C/P/k/g/b/t/r/c/p，大写为红方棋子，小写为黑方棋子。' '作为空值
    bool side=false;//false 为红方
    Pos position={-1,-1};//布局上以黑方1路车为(0,0)，红方1路车为(8,9)
    bool isAlive=false;//是否还在场上存活
public://方法部分
    CHESSSTONE();//空白初始化
    CHESSSTONE(char _name,int pos_x,int pos_y);//定位和名称初始化
    CHESSSTONE(int _id);//id 初始化
    //移动
    bool move(int pos_x,int pos_y);//移动到交叉点，true 为移动成功，false 为坐标错误移动失败
    //吃子
    bool remove();//将棋子移除棋局,true为成功，false为失败，如棋子已经死亡
};
//MARK:棋子行为
CHESSSTONE::CHESSSTONE()
{
    name_id=-1;
    chess_id=-1;
    stone_name=' ';
    side=false;
    position={-1,-1};
    isAlive=false;
}
CHESSSTONE::CHESSSTONE(char _name,int pos_x,int pos_y)
{
    chess_id=-1;
    name_id=isIn(_name, StoneNameBank, 14);
    if (name_id==-1||(pos_x<0)||(pos_x>=10)||(pos_y<0)||(pos_y>=9)){
        CHESSSTONE();
        return;
    }
    stone_name=StoneNameBank[name_id];
    position={pos_x,pos_y};
    isAlive=true;
    if (name_id<=6){
        side=false;
    }else{
        side=true;
    }
}
//定义棋子库
const CHESSSTONE StoneBank[32]={
    CHESSSTONE('K', 9, 4),
    CHESSSTONE('G', 9, 3),
    CHESSSTONE('G', 9, 5),
    CHESSSTONE('B', 9, 2),
    CHESSSTONE('B', 9, 6),
    CHESSSTONE('T', 9, 1),
    CHESSSTONE('T', 9, 7),
    CHESSSTONE('R', 9, 0),
    CHESSSTONE('R', 9, 8),
    CHESSSTONE('C', 7, 1),
    CHESSSTONE('C', 7, 7),
    CHESSSTONE('P', 6, 0),
    CHESSSTONE('P', 6, 2),
    CHESSSTONE('P', 6, 4),
    CHESSSTONE('P', 6, 6),
    CHESSSTONE('P', 6, 8),
    CHESSSTONE('k', 0, 4),
    CHESSSTONE('g', 0, 3),
    CHESSSTONE('g', 0, 5),
    CHESSSTONE('b', 0, 2),
    CHESSSTONE('b', 0, 6),
    CHESSSTONE('t', 0, 1),
    CHESSSTONE('t', 0, 7),
    CHESSSTONE('r', 0, 0),
    CHESSSTONE('r', 0, 8),
    CHESSSTONE('c', 2, 1),
    CHESSSTONE('c', 2, 7),
    CHESSSTONE('p', 3, 0),
    CHESSSTONE('p', 3, 2),
    CHESSSTONE('p', 3, 4),
    CHESSSTONE('p', 3, 6),
    CHESSSTONE('p', 3, 8)
};
CHESSSTONE::CHESSSTONE(int _id)
{
    if (_id<0||_id>=32){
        CHESSSTONE();
        return;
    }
    CHESSSTONE _self=StoneBank[_id];
    name_id=_self.name_id;
    chess_id=_self.chess_id;
    stone_name=_self.stone_name;
    side=_self.side;
    position=_self.position;
    isAlive=_self.isAlive;
}
bool CHESSSTONE::move(int pos_x, int pos_y)
{
    if ((pos_x<0)||(pos_x>=10)||(pos_y<0)||(pos_y>=9)){
        return false;
    }else{
        position={pos_x,pos_y};
        return true;
    }
}
bool CHESSSTONE::remove()
{
    if (!isAlive){
        return false;
    }else{
        isAlive=false;
        return true;
    }
}
//MARK:棋盘类 CHESSBOARD
class CHESSBOARD
{
public://参数部分
    CHESSSTONE chess_board[32];//表现场上32个棋子
    /*棋盘类只有这三十二个棋子，其余的相关内容均不重要，以免影响以后设计 AI 时的运算速度和储存空间*/
public://方法部分
    CHESSBOARD();//空白初始化
    /*涉及的方法有，初始局面布置，棋子的移动，棋子可能移动的点，棋子移动与棋谱的转换，导出局面，导出局面的压缩，将军的判定，叫吃的判定*/
    //根据局面布置棋盘，_type表示局面的类型，true 表示利用压缩型局面，false 表示使用未压缩的格式，初始布局为全局变量ORI_SITU,默认不适用初始局面，若使用初始局面，无论前两项为何值，只要 isOri 为 true,则改变为初始局面
    CHESSBOARD(string _situation,bool _type=true,bool _isOri=false);
    
};
//MARK:棋盘类方法
CHESSBOARD::CHESSBOARD()
{
    
}
//MARK:棋谱类 CHESSMANUAL
/*这里的棋谱指的是具体的下棋步骤，不包括棋局信息等情况*/
class CHESSMANUAL
{
public://参数部分
public://方法部分
    CHESSMANUAL();//空白初始化
};
//MARK:棋谱类方法
CHESSMANUAL::CHESSMANUAL()
{
    
}
//MARK:棋谱类 CHESSMANUALMAIN
//定义棋谱信息类型
typedef struct Inform{
    string Name="";//对局或比赛名称
    string Date="";//对局或比赛时间
    string PlayerRed="";//红方姓名
    string TeamRed="";//红方队伍
    string PlayerBlack="";//黑方姓名
    string TeamBlack="";//黑方队伍
    //原本计划有胜负情况一项，但由于涉及到变招的结果，故在此省略，等同于本手的胜负情况，即#0的胜负结果。(-1为结果未定，0为和棋/均势，1为红胜/红优，2为黑胜/黑优)
    bool ManualType=false;//false 为全局谱，true 为残局谱
    bool Init=false;//false 为红先，true 为黑先
    
}Inform;
/*这里的棋谱包括棋局信息等情况*/
class CHESSMANUALMAIN
{
public://参数部分
    Inform GameInformation;
public://方法部分
    CHESSMANUALMAIN();//空白初始化
};
//MARK:棋谱类方法
CHESSMANUALMAIN::CHESSMANUALMAIN()
{
    
}
//MARK:其他行为

#endif /* ChineseChess_h */
