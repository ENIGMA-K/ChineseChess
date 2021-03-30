# ChineseChess
It's a coding tool for Chinese chess in C++.

#  ChineseChess.h 说明文档

## 结构

1. 引用 & 声明
    + 定义棋子
2. 基础方法
3. 棋盘类 CHESSBOARD
4. 棋盘类方法
5. 棋谱类 CHESSMANUAL
6. 棋谱类方法
7. 其他行为

## 棋谱文档格式

以#为字段分段，各分段如下:

> #对局名称（比赛名称）
>
> #比赛日期
>
> #红方
>
> #红方队伍
>
> #黑方
>
> #黑方队伍
>
> #结果（红先胜）
>
> #棋谱类型（全局谱/残局谱）
>
> #先手（红先/黑先）
>
> ##（以‘##’分隔的部分为正文）
>
> #0（#0后为原谱，默认红先，若黑先则记为#0!）（棋谱以标准记谱法标记）
>
> 当记谱出现分支时，另起一行标记#\d+\*\d+-\d+，意味第 a 变招，起自第 b 变招的第 c 招，最后以@/$结尾记胜负，@R 红胜，@B 黑胜，@P 和棋，$R 红优，$B 黑优，$P 均势
>

#### 例：《橘中秘1.1（顺炮横车破直车弃马局）》

> #0 C2S5 c8s5 T2W3 t8w7 R1W1 r9s8 R1S6 r8w6 R6W7 t2w1 ... @B
>
> #1#0-9 P7W1 r8s7 c2w2 ... @B

> ##（以‘##’分隔的部分为批注）
>
> 以#分隔每一条批注，批注位置标记为#\d+-\d+，意味批注在第 b 变招的第 c 招
>
> #0-7 此步不好...

## 局面记录

> 从左上至右下顺次排列共九十个交叉点，每一个位置上若为棋子则记为简记字母，否则记为0，换行记为/，可以得到一串char[90]，将连续的 n 个0以 n 替代，可以得到一串字符，即为局面简记，以#@开始，以@#结束，例如初始局面记作：
>
> #@rtbgkgbtr10c5c1p1p1p1p1p18P1P1P1P1P1C5C10RTBGKGBTR@#

## 中国象棋记谱法

&emsp象棋棋盘共九路十行，红方自右向左分别记为"一"..."九"路，黑方自左向右分别记为"1"..."9"路，在记谱法中，以一个四字组记录一步棋，四字组共有三类：

    1. 一般类型（例：兵七进一）

       第一个字代表具体的棋子，第二个字代表棋子所在的路数，第三位代表行棋方式，第四位代表移动终点的位置

    2. 共线类型（例：前兵平四）

       第一个字代表棋子在共线的若干子中所处的位置，一般的棋子以"前"、"后"区分，当三兵一线的时候以"前"、"中"、"后"区分，大于三个兵一线时以"一"..."五"区分，第二个字代表具体的棋子，第三位代表行棋方式，第四位代表移动终点的位置

    3. 多兵多线（例：前五进一）

       第一个字代表棋子在共线的若干子中所处的位置，方法同2.，第二个字代表棋子所在的路数，第三位代表行棋方式，第四位代表移动终点的位置

&emsp在棋谱中以英文字符代替中文汉字记谱，以四个字符为一组，红方行棋用大写，黑方用小写。K=帅,G=仕,B=相,T=马,R=车,C=炮,P=兵,k=将,g=士,b=象,t=马,r=车,c=炮,p=卒,A/a=进,H/h=平,R/r=退,数字以1...9表示,在第一位上A/a=前,M/m=中,Z/z=后

## 棋谱文档示例

//压缩方案

```
##
#0#C2H5c8h5T2A3t8a7R1A1r9h8R1H6r8a6R6A7t2a1R9A1c2a7C8H5t7r8C5A4g6a5R9H6k5h6R6A1g5r4R6H4c5h6R4A6k6h5C8H5@R
#1#0-9#P7A1r8h7T8A7c2a2T7A6c2h7T6A4r7h6T3A2r6r1C8A2r6h3C8H9t2a1T2A3r3r1T4A3c7r2C5A4g6a5R6H4r3h7R4A5r1h2C9H7p3a1R9A2c7h6T3A2r7r3R9H3r7a6T2R4k5h6T4A2k6h5R4A3@R
#2#0-10#t2a3R6H7c2a2P7A1t7r5$P
#3#2-11#R6R2p5a1R6H7t3a5C8A4r8h7$P
#4#0-12#r8h8$P
#5#0-20#k6a1R6R1c5h6C8H5k6r1C5H4c6h8R6H5b3a5R6H4c2r7C4A1@R
#6#5-22#c5h7R6H4c7h6C8H5r8r4R6H5k6r1C5H4c6a6C5H4@R
#7#5-21#3RA7c5h71RH5c7r1C8A1k6a1R6H5c7h6C8R1@R
#8#0-14#c2r2C8H3c2h7C5A4g6a5R9H6k5h6R6A1g5r4R6H4c5h6R4A6k6h5R4A1@R
#9#0-14#r8r4R6H3r1h2C8H3b7a9C5A4g4a5R9H6r2a4R6A7r2h5C3H1r5r1C1A2r8r2R3H5@R
#10#9-26#r8r2R3R1r5r1C1H5g5r4C5H8r8a7C8R6r5h6R3A2g4a5C8H5r6r2R3R2r8h7R3H7@R
#11#9-22#p3a1R6A7t1a3C3H1t3r4C1A2r8r2R3H5k5h4R5A1@R
#12#9-20#g6a5C3H1r8r2R9H2r8h6R3H2r8r2R9H2r8h6R3H2r2a4C1A2r6h9R2A1@R
#13#9-15#C5A4t7a5C8H2t5a6B3A5t6a7R9H4r1h2R4A1t7a9C2A2g4a5R4A6c5a5K5A1@R
#14#13-22#t7r5C2A2g4a5R4A7t5r6G4A5t6r7R6H5t7r5R4A1@R
#15#14-30#k5h4R5H6k4h5R4H3r1h2R3R1r2a2R3H4@R
#16#13-20#t6a5G4A5r1h2R6H4r2a4C2R3t5a7K5H4g4a5R9H6c5h6C2H5r2h5R4R1r5a1R4A2g5r6P5A1@R
#17#16-22#t5a7K5H4c5h6R6H8r1h2R8A1t1r2R9H8$R
#18#13-19#G4A5t6a7C2R3r1h2C2H5g6a5R9H6k5h6C5A4g4a5R6H5@R
#19#18-22#t7r5C2H5g6a5R6R5k5h6R9A1k6a1R9H4g5a6R6A5c5r1C5H4t5r6K5H4@R
#20#19-33#K5H4@R
#21#19-26#t5a7R9H6k5h61RH4c5h6R6A5r1h2R6H3b3a5R3A1c2r7R4R1t7r9R4H2p9a1R2A6c2r1R2H4k6a1C5H4@R
#22#21-42#c6a4R3R1c2a1R3A1c2r1@P
#23#0-14#r8h7C8H3r7h6R6H3b7a9C5A4g6a5R9H2r6r6C3H2c2r6C5R2c5a1C2A2r6a2C2H1b3a5R3A1r6r2R2A7b5r7R2H4@R
#24#23-25#C2A2r6a3R3A1r6r3$R
#25#23-29#R3A1r6r2R2H4@R
#26#23-34#c2r2R3H4k5h6R2A1k6a1T3A4@R
#27#0-14#g6a5R9H4r8r4R4A7r1h2C8H3r8h7C5A4r2a4G4A5r2h5R4R2b7a9K5H4r7r2R6R4@R
#28#27-16#r1h2C8H3c2r6R4A7r8r4R4H3b7a9P3A1p1a1T3A4c5a4C5A4c2h5T4A5r2a8C3H1r8a6R3A1g5r6R3H4k5h6R6A1@R
#29#28-32#r8r2T5A3t1a2T3A5t2a3C1H5k5h6R6A1@R
##
```

//可视化方案
```
##
#0 C2H5 c8h5 T2A3 t8a7 R1A1 r9h8 R1H6 r8a6 R6A7 t2a1 R9A1 c2a7 C8H5 t7r8 C5A4 g6a5 R9H6 k5h6 R6A1 g5r4 R6H4 c5h6 R4A6 k6h5 C8H5 @R
#1#0-9 P7A1 r8h7 T8A7 c2a2 T7A6 c2h7 T6A4 r7h6 T3A2 r6r1 C8A2 r6h3 C8H9 t2a1 T2A3 r3r1 T4A3 c7r2 C5A4 g6a5 R6H4 r3h7 R4A5 r1h2 C9H7 p3a1 R9A2 c7h6 T3A2 r7r3 R9H3 r7a6 T2R4 k5h6 T4A2 k6h5 R4A3 @R
#2#0-10 t2a3 R6H7 c2a2 P7A1 t7r5 $P
#3#2-11 R6R2 p5a1 R6H7 t3a5 C8A4 r8h7 $P
#4#0-12 r8h8 $P
#5#0-20 k6a1 R6R1 c5h6 C8H5 k6r1 C5H4 c6h8 R6H5 b3a5 R6H4 c2r7 C4A1 @R
#6#5-22 c5h7 R6H4 c7h6 C8H5 r8r4 R6H5 k6r1 C5H4 c6a6 C5H4 @R
#7#5-21 3RA7 c5h7 1RH5 c7r1 C8A1 k6a1 R6H5 c7h6 C8R1 @R
#8#0-14 c2r2 C8H3 c2h7 C5A4 g6a5 R9H6 k5h6 R6A1 g5r4 R6H4 c5h6 R4A6 k6h5 R4A1 @R
#9#0-14 r8r4 R6H3 r1h2 C8H3 b7a9 C5A4 g4a5 R9H6 r2a4 R6A7 r2h5 C3H1 r5r1 C1A2 r8r2 R3H5 @R
#10#9-26 r8r2 R3R1 r5r1 C1H5 g5r4 C5H8 r8a7 C8R6 r5h6 R3A2 g4a5 C8H5 r6r2 R3R2 r8h7 R3H7 @R
#11#9-22 p3a1 R6A7 t1a3 C3H1 t3r4 C1A2 r8r2 R3H5 k5h4 R5A1 @R
#12#9-20 g6a5 C3H1 r8r2 R9H2 r8h6 R3H2 r8r2 R9H2 r8h6 R3H2 r2a4 C1A2 r6h9 R2A1 @R
#13#9-15 C5A4 t7a5 C8H2 t5a6 B3A5 t6a7 R9H4 r1h2 R4A1 t7a9 C2A2 g4a5 R4A6 c5a5 K5A1 @R
#14#13-22 t7r5 C2A2 g4a5 R4A7 t5r6 G4A5 t6r7 R6H5 t7r5 R4A1 @R
#15#14-30 k5h4 R5H6 k4h5 R4H3 r1h2 R3R1 r2a2 R3H4 @R
#16#13-20 t6a5 G4A5 r1h2 R6H4 r2a4 C2R3 t5a7 K5H4 g4a5 R9H6 c5h6 C2H5 r2h5 R4R1 r5a1 R4A2 g5r6 P5A1 @R
#17#16-22 t5a7 K5H4 c5h6 R6H8 r1h2 R8A1 t1r2 R9H8 $R
#18#13-19 G4A5 t6a7 C2R3 r1h2 C2H5 g6a5 R9H6 k5h6 C5A4 g4a5 R6H5 @R
#19#18-22 t7r5 C2H5 g6a5 R6R5 k5h6 R9A1 k6a1 R9H4 g5a6 R6A5 c5r1 C5H4 t5r6 K5H4 @R
#20#19-33 K5H4 @R
#21#19-26 t5a7 R9H6 k5h6 1RH4 c5h6 R6A5 r1h2 R6H3 b3a5 R3A1 c2r7 R4R1 t7r9 R4H2 p9a1 R2A6 c2r1 R2H4 k6a1 C5H4 @R
#22#21-42 c6a4 R3R1 c2a1 R3A1 c2r1 @P
#23#0-14 r8h7 C8H3 r7h6 R6H3 b7a9 C5A4 g6a5 R9H2 r6r6 C3H2 c2r6 C5R2 c5a1 C2A2 r6a2 C2H1 b3a5 R3A1 r6r2 R2A7 b5r7 R2H4 @R
#24#23-25 C2A2 r6a3 R3A1 r6r3 $R
#25#23-29 R3A1 r6r2 R2H4 @R
#26#23-34 c2r2 R3H4 k5h6 R2A1 k6a1 T3A4 @R
#27#0-14 g6a5 R9H4 r8r4 R4A7 r1h2 C8H3 r8h7 C5A4 r2a4 G4A5 r2h5 R4R2 b7a9 K5H4 r7r2 R6R4 @R
#28#27-16 r1h2 C8H3 c2r6 R4A7 r8r4 R4H3 b7a9 P3A1 p1a1 T3A4 c5a4 C5A4 c2h5 T4A5 r2a8 C3H1 r8a6 R3A1 g5r6 R3H4 k5h6 R6A1 @R
#29#28-32 r8r2 T5A3 t1a2 T3A5 t2a3 C1H5 k5h6 R6A1 @R
##
```
