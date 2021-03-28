# ChineseChess
It's a coding tool for Chinese chess in C++.

#  ChineseChess.h 说明文档

## 结构

1. 引用声明
2. 基础方法
+ 延时函数 void sleep(double _duration)
+ 随机数 int rnd(int uper)
+ 生成随机序列 bool* select(int m,int n,int non)
+ 安全释放指针
    inline void SafeDelete(T*& pVal)
    inline void SafeDeleteArray(T*& pVal)
3. 棋子类 STONE & 棋子行为
    三种初始化方法+棋子的移动+棋子的移除
4. 棋盘类 CHESSBOARD & 棋盘类方法
5. 棋谱类 CHESSMANUAL & 棋谱类方法
6. 其他行为

## 棋谱文档格式
以#为字段分段，各分段如下
# 对局名称（比赛名称）
# 比赛日期
# 红方
# 红方队伍
# 黑方
# 黑方队伍
# 结果（红先胜）
# 棋谱类型（全局谱/残局谱）
# 先手（红先/黑先）
##（以‘##’分隔的部分为正文）

#0（#0后为原谱，默认红先，若黑先则记为#0!）
（棋谱以标准记谱法标记）
K=帅,G=仕,B=相,T=马,R=车,C=炮,P=兵
k=将,g=士,b=象,t=马,r=车,c=炮,p=卒
V=前,M=中,D=后,W=进,X=退,S=平,（此六者大小写随红黑方改变）,数字对应表示，每四个字符为一组
当记谱出现分支时，另起一行标记#\d+*\d+-\d+，意味第 a 变招，起自第 b 变招的第 c 招，最后以@结尾记胜负，@R 红胜，@B 黑胜，@P 平局
例：《橘中秘1.1（顺炮横车破直车弃马局）》

#0 C2S5 c8s5 T2W3 t8w7 R1W1 r9s8 R1S6 r8w6 #1# R6W7 t2w1 ... @B
#1#0-9 P7W1 r8s7 c2w2 ... @B

##（以‘##’分隔的部分为批注）

以#分隔每一条批注，批注位置标记为#\d+-\d+，意味批注在第 b 变招的第 c 招

#0-7 此步不好...
//进度回溯，若查找的变招早于该变的第一招，则回溯的变招的起源

/*局面记录*/
从左上至右下顺次排列共九十个交叉点，每一个位置上若为棋子则记为简记字母，否则记为0，换行记为/，可以得到一串char[90]，将连续的 n 个0以 n 替代，可以得到一串字符，即为局面简记，以#@开始，以@#结束，例如初始局面记作：
#@rtbgkgbtr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RTBGKGBTR@#




