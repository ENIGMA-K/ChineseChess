//
//  ChineseChess.h
//  ChineseChess
//
//  Created by Kevin on 2021/3/27.
//  Upload to Github at 2021/4/1 21:42:56
//这是一个中国象棋的头文件，使用这个文件能够用于设计中国象棋游戏、中国象棋打谱以及象棋 AI 的开发。

#ifndef ChineseChess_h
#define ChineseChess_h
//MARK:声明引用&全局变量
#include <vector>
#include "math.h"
#include <time.h>
using namespace std;
#define ORI_SITU "#@rtbgkgbtr10c5c1p1p1p1p1p18P1P1P1P1P1C5C10RTBGKGBTR@#"
//MARK:基础方法
//延时函数
void sleep(double _duration){
    struct timespec ts, ts1;
    ts.tv_nsec =(_duration-floor(_duration))*1000000000;
    ts.tv_sec = floor(_duration);
    nanosleep(&ts, &ts1);
}
//比大小
int max(int _a,int _b){
    if (_a>=_b){
        return _a;
    }else{
        return _b;
    }
}
int min(int _a,int _b){
    if (_a<=_b){
        return _a;
    }else{
        return _b;
    }
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
//MARK:棋子相关方法
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
//棋子名称序列
char StoneBankEng[32]={
    'K','G','G','B','B','T','T','R','R','C','C','P','P','P','P','P','k','g','g','b','b','t','t','r','r','c','c','p','p','p','p','p'
};
string StoneBankCna[32]={
    "帅","仕","仕","相","相","马","马","车","车","炮","炮","兵","兵","兵","兵","兵","将","士","士","象","象","馬","馬","車","車","砲","砲","卒","卒","卒","卒","卒"
};
//定义棋子集
typedef struct Stone
{
    Pos position={-1,-1};//布局上以黑方1路车为(0,0)，红方1路车为(9,8)
    bool isAlive=false;//是否还在场上存活
}Stone;
//初始局面点集
const Stone StoneSet[32]={
    {{9,4},true},{{9,3},true},{{9,5},true},{{9,2},true},{{9,6},true},{{9,1},true},{{9,7},true},{{9,0},true},{{9,8},true},{{7,1},true},{{7,7},true},{{6,0},true},{{6,2},true},{{6,4},true},{{6,6},true},{{6,8},true},{{0,4},true},{{0,3},true},{{0,5},true},{{0,2},true},{{0,6},true},{{0,1},true},{{0,7},true},{{0,0},true},{{0,8},true},{{2,1},true},{{2,7},true},{{3,0},true},{{3,2},true},{{3,4},true},{{3,6},true},{{3,8},true}
};



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
//MARK:棋盘类 CHESSBOARD
class CHESSBOARD
{
public://参数部分
    Stone chess_board[32];//表现场上32个棋子
    /*棋盘类只有这三十二个棋子，其余的相关内容均不重要，以免影响以后设计 AI 时的运算速度和储存空间*/
public://方法部分
    CHESSBOARD();//空白初始化
    /*涉及的方法有，初始局面布置，棋子的移动，棋子可能移动的点，棋子移动与棋谱的转换，导出局面，导出局面的压缩，将军的判定，叫吃的判定*/
    //根据局面布置棋盘，_type表示局面的类型，true 表示利用压缩型局面，false 表示使用未压缩的格式，初始布局为全局变量ORI_SITU,默认不适用初始局面，若使用初始局面，无论前两项为何值，只要 isOri 为 true,则改变为初始局面
    CHESSBOARD(string _situation,bool _type=true,bool _isOri=false);
    //两个点之间的距离
    int distance(int _id1,Pos _pos);//若重合返回0,若不在同一行则返回-1
    //检验某个坐标存在棋子是哪一方的
    int exist(Pos _pos);//-1为红方，1为黑方，0为不存在
    //两个点之间间隔的棋子数目
    int between(int _id1,Pos _pos);//若重合返回0，若不在同一行返回-1
    //棋子在棋谱中的名称
    string id_to_nickname(int _id1);//注意到，无论哪种形式的棋谱，每一步的四字组的前两位都是用来描述棋子的，故使用此种方法获得棋子在棋谱中的名称
    //用棋子在棋谱中的名称获得 ID
    int nickname_to_id(string _nickname);
    //棋子的移动
    string move(int _id,Pos _pos);//移动合理返回该步棋谱格式，否则返回""
    //棋子能够移动的点
    vector<Pos> movable(int _id);//返回所有能够移动的点的坐标
    //是否将军
    bool is_check(bool _side);//检测的一方，false 为红方，true 为黑方
//    //移动转换为棋谱
//    string move_to_manual(int _id,Pos _pos);//将移动转化为 string 类型的棋谱移动步骤（char[4]）
    //棋谱转换为实际的移动参数(仅限于英文棋谱)
    int* manual_to_move(string _manual);//将 string 类型的棋谱移动步骤（char[4]）转化为移动参数(mtm[0]=_id,mtm[1]=_pos._x,mtm[2]=_pos._y)
    //导出局面
    string get_situ(bool _type=true);//_type表示局面的类型，true 表示利用压缩型局面，false表示使用未压缩的格式
};
//MARK:棋盘类方法
CHESSBOARD::CHESSBOARD()
{
    for (int i=0;i<32;i++){
        chess_board[i].position={-1,-1};
        chess_board[i].isAlive=false;
    }
}
//根据局面布置棋盘，_type表示局面的类型，true 表示利用压缩型局面，false 表示使用未压缩的格式，初始布局为全局变量ORI_SITU,默认不适用初始局面，若使用初始局面，无论前两项为何值，只要 isOri 为 true,则改变为初始局面
CHESSBOARD::CHESSBOARD(string _situation,bool _type,bool _isOri)
{
    for (int i=0;i<32;i++/*全部清空*/){
        chess_board[i].position={-1,-1};
        chess_board[i].isAlive=false;
    }
    if (_isOri){
        for (int i=0;i<32;i++){
            chess_board[i]=StoneSet[i];
        }
    }else{
        //检验是否符合棋谱格式#@@#
        if (!(_situation[0]=='#'&&_situation[1]=='@'&&_situation[_situation.size()-2]=='@'&&_situation[_situation.size()-1]=='#')){
        }else{
            string _set_string="";
            if (_type/*使用压缩型格式描述局面*/){
                for (int i=2;i<_situation.size()-2;i++){
                    if (!isnumber(_situation[i])){
                        _set_string+=_situation[i];
                    }else{
                        string _num_of_empty_in_str="";
                        do {
                            _num_of_empty_in_str+=_situation[i];
                            i++;
                        }while(isnumber(_situation[i]));
                        int _num_of_empty=stoi(_num_of_empty_in_str);
                        for (int j=0;j<_num_of_empty;j++){
                            _set_string+='0';
                        }
                        i-=1;
                    }
                }
            }else/*使用非压缩型格式描述局面*/{
                for (int i=2;i<_situation.size()-2;i++){
                    _set_string+=_situation[i];
                }
            }
            if (_set_string.size()!=90/*棋谱有误*/){
                return;
            }else{
                for (int i=0;i<90;i++){
                    if (_set_string[i]!='0'/*有棋子*/){
                        //查找棋子的 Id
                        for (int j=0;j<32;j++){
                            if ((_set_string[i]==StoneBankEng[j])&&chess_board[j].isAlive==false/*找到对应棋子*/){
                                chess_board[j].position={i/9,i%9};
                                chess_board[j].isAlive=true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
//两个点之间的距离//若重合返回0,若不在同一行则返回-1
int CHESSBOARD::distance(int _id1,Pos _pos){
    int _opt=-1;
    if (chess_board[_id1].position._x==_pos._x){
        return abs(chess_board[_id1].position._y-_pos._y);
    }else if (chess_board[_id1].position._y==_pos._y){
        return abs(chess_board[_id1].position._x-_pos._x);
    }
    return _opt;
}
//检验某个坐标存在棋子
int CHESSBOARD::exist(Pos _pos){
    for (int i=0;i<16;i++){
        if ((chess_board[i].position._x==_pos._x)&&(chess_board[i].position._y==_pos._y)){
            return -1;
        }
    }
    for (int i=16;i<32;i++){
        if ((chess_board[i].position._x==_pos._x)&&(chess_board[i].position._y==_pos._y)){
            return 1;
        }
    }
    return 0;
}
//两个点之间间隔的棋子数目//若重合返回0，若不在同一行返回-1
int CHESSBOARD::between(int _id1,Pos _pos){
    int _opt=0;
    if (chess_board[_id1].position._x==_pos._x){
        for (int i=min(chess_board[_id1].position._y,_pos._y)+1;i<max(chess_board[_id1].position._y,_pos._y);i++){
            if (exist({chess_board[_id1].position._x,i})){
                _opt++;
            }
        }
    }else if (chess_board[_id1].position._y==_pos._y){
        for (int i=min(chess_board[_id1].position._x,_pos._x)+1;i<max(chess_board[_id1].position._x,_pos._x);i++){
            if (exist({i,chess_board[_id1].position._y})){
                _opt++;
            }
        }
    }else{
        return -1;
    }
    return _opt;
}
//棋子在棋谱中的名称//注意到，无论哪种形式的棋谱，每一步的四字组的前两位都是用来描述棋子的，故使用此种方法获得棋子在棋谱中的名称
string CHESSBOARD::id_to_nickname(int _id1){
    if (!chess_board[_id1].isAlive){
        return "";//所查找的棋子不存在
    }
    string _opt="";
    //备忘 KGGBBTTRRCCPPPPP kggbbttrrccppppp
    switch (_id1) {
        case 0:
            //K=红方的帅
            _opt=StoneBankEng[_id1]+to_string(9-chess_board[_id1].position._y);
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
            //红方对称兵（前置位）
            if (chess_board[_id1+1].isAlive&&(chess_board[_id1].position._y==chess_board[_id1+1].position._y)){
                //双存活且共线
                if (chess_board[_id1].position._x>chess_board[_id1+1].position._x){
                    //所得居后
                    _opt=&"Z"[StoneBankEng[_id1]];
                }else{
                    //所得居前
                    _opt=&"A"[StoneBankEng[_id1]];
                }
            }else{
                //单存活或不共线
                _opt=StoneBankEng[_id1]+to_string(9-chess_board[_id1].position._y);
            }
            break;
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
            //红方对称兵（后置位）
            if (chess_board[_id1-1].isAlive&&(chess_board[_id1].position._y==chess_board[_id1-1].position._y)){
                //双存活且共线
                if (chess_board[_id1].position._x>chess_board[_id1-1].position._x){
                    //所得居后
                    _opt=&"Z"[StoneBankEng[_id1]];
                }else{
                    //所得居前
                    _opt=&"A"[StoneBankEng[_id1]];
                }
            }else{
                //单存活或不共线
                _opt=StoneBankEng[_id1]+to_string(9-chess_board[_id1].position._y);
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            //红方兵
            int group[5];//兵的纵列值
            int group_ori[5];//兵的 Id
            for (int i=0;i<5;i++){
                group_ori[i]=i+10;
                group[i]=chess_board[i+10].position._x;
            }
            for (int i=0;i<4;i++){
                for (int j=i;j<4;j++){
                    //swich j j+1
                    //升序排列
                    if (group[i]>=group[i+1]){
                        int inst=group[i];
                        group[i]=group[i+1];
                        group[i+1]=inst;
                        inst=group_ori[i];
                        group_ori[i]=group_ori[i+1];
                        group_ori[i+1]=inst;
                    }
                }
            }
            //检查共列数目
            int same_line[5];
            for (int i=0;i<5;i++){
                same_line[i]=0;
            }
            int _numOfRow;
            _numOfRow=0;
            same_line[0]=1;
            for (int i=1;i<5;i++){
                if (!(group[i]==group[i-1])){
                    _numOfRow++;
                }
                same_line[_numOfRow]++;
            }
            
            break;
        case 16:
        
            break;
        case 17:
        
            break;
        case 18:
        
            break;
        case 19:
        
            break;
        case 20:
        
            break;
        case 21:
        
            break;
        case 22:
        
            break;
        case 23:
        
            break;
        case 24:
        
            break;
        case 25:
        
            break;
        case 26:
        
            break;
        case 27:
        
            break;
        case 28:
        
            break;
        case 29:
        
            break;
        case 30:
        
            break;
        case 31:
        
            break;
        case 32:
        
            break;
        default:
            break;
    }
    return _opt;
}
//用棋子在棋谱中的名称获得 ID
int CHESSBOARD::nickname_to_id(string _nickname){
    return -1;
}
//棋子的移动//移动合理返回该步棋谱格式，否则返回""
string CHESSBOARD::move(int _id,Pos _pos){
    string _opt="";
    
    
    return _opt;
}
//MARK:其他行为

#endif /* ChineseChess_h */
