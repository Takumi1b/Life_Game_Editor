/*****
      自由制作課題
      life_game_editor.c
      簡易的なライフゲ-ムを生成するエディタ.使い方,プログラムの仕様等はプログラム内の"Help"を参照
      the task 7.12
      2018 7.12 g1853509 Takumi Tanabe
******/
#include <stdio.h>
#include <stdlib.h>
#include <handy.h>
#define WIDTH 1000
#define HEIGHT 700
#define CELL_WIDTH 64
#define CELL_HEIGHT 64
#define celllong 10

typedef struct RGB{
    int R,G,B;
} RGB;
RGB make_color;

int cell[2][CELL_WIDTH][CELL_HEIGHT];//0: 現在のセル 1:次世代のセル
int current;

void draw_status(int wid);//ウィンドウ画面の表示
void draw(int wid);//セルの描画等
int LiveCount(int _x, int _y);//隣接する生きているセルの数を数える
void helpWindow(int wid2);//ヘルプウィンドウの内容

int main(){
    int wid;
    wid = HgOpen (WIDTH, HEIGHT);
    draw_status(wid);
    draw(wid);
    
    return 0;
}

void draw_status(int wid){
    
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 700, 0, 300, 800, 1);
    HgWSetWidth(wid, 2);
    HgWText(wid, 715, 670, "Generaton:");
    HgWLine(wid, 820, 635, 990, 635);
    HgWText(wid, 715, 630, "Selecting Color");
    HgWSetFillColor(wid, HG_BLACK);
    HgWBoxFill(wid, 850, 575, 120, 50, 1);
    HgWText(wid, 715, 560, "Setting Color");
    HgWLine(wid, 810, 565, 990, 565);
    HgWText(wid, 715, 450, "Create Color");
    HgWLine(wid, 800, 455, 990, 455);
    HgWText(wid, 715, 345, "Creating Color");
    HgWText(wid, 715, 175, "Options");
    HgWLine(wid, 775, 180, 990, 180);
    HgWText(wid, 715, 55, "Command");
    HgWLine(wid, 785, 60, 990, 60);
    
    //カラ-パレット
    HgWSetFillColor(wid, HgRGB(0.0, 0.0, 0.0));
    HgWBoxFill(wid, 735, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.3, 0.3, 0.3));
    HgWBoxFill(wid, 765, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.5, 0.0, 0.0));
    HgWBoxFill(wid, 795, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.5, 0.5, 0.0));
    HgWBoxFill(wid, 825, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.0, 0.5, 0.0));
    HgWBoxFill(wid, 855, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.0, 0.5, 0.5));
    HgWBoxFill(wid, 885, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.0, 0.0, 0.5));
    HgWBoxFill(wid, 915, 520, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.5, 0.0, 0.5));
    HgWBoxFill(wid, 945, 520, 20, 20, 1);
    
    HgWSetFillColor(wid, HgRGB(1.0, 1.0, 1.0));
    HgWBoxFill(wid, 735, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.5, 0.5, 0.5));
    HgWBoxFill(wid, 765, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(1.0, 0.0, 0.0));
    HgWBoxFill(wid, 795, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(1.0, 1.0, 0.0));
    HgWBoxFill(wid, 825, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.0, 1.0, 0.0));
    HgWBoxFill(wid, 855, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.0, 1.0, 1.0));
    HgWBoxFill(wid, 885, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(0.0, 0.0, 1.0));
    HgWBoxFill(wid, 915, 490, 20, 20, 1);
    HgWSetFillColor(wid, HgRGB(1.0, 0.0, 1.0));
    HgWBoxFill(wid, 945, 490, 20, 20, 1);;

    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 735, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 765, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 795, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 825, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 855, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 885, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 915, 410, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 945, 410, 20, 20, 1);
    
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 735, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 765, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 795, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 825, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 855, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 885, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 915, 380, 20, 20, 1);
    HgWSetFillColor(wid, HG_LGRAY);
    HgWBoxFill(wid, 945, 380, 20, 20, 1);

    //カラ-ピッカ-
    //赤
    HgWSetWidth(wid, 2);
    HgWBox(wid, 724, 309, 257, 22);
    HgWSetFillColor(wid, HgRGB(1.0, 0.0, 0.0));
    HgWBoxFill(wid, 725, 310, 255, 20, 0);
    HgWSetFillColor(wid, HgRGBA(1.0, 0.0, 0.0, 1.0));
    HgWSetComposite(wid, HG_BLEND_COPY);   
    HgWBoxFill(wid, 725, 310, 235, 20, 0);
    HgWSetFillColor(wid, HgRGBA(1.0, 0.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 310, 215, 20, 0);
    HgWSetFillColor(wid, HgRGBA(1.0, 0.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 310, 205, 20, 0);
    HgWSetFillColor(wid, HgRGBA(1.0, 0.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 310, 195, 20, 0);
    HgWSetFillColor(wid, HgRGBA(1.0, 0.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 310, 175, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.85, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 165, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.75, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 155, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.70, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 145, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.65, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 135, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.60, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 125, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.55, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 115, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.50, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 105, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.45, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 95, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.40, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 85, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.35, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 75, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.30, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 65, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.25, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 55, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.20, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 45, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.17, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 35, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.14, 0.1, 0.1, 1.0));
    HgWBoxFill(wid, 725, 310, 25, 20, 0);
    HgWText(wid, 725, 200, "R:");
    HgWLine(wid, 725, 200, 770, 200);

    //緑
    HgWBox(wid, 724, 279, 257, 22);
    HgWSetFillColor(wid, HgRGB(0.0, 1.0, 0.0));
    HgWBoxFill(wid, 725, 280, 255, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 1.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 280, 235, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 1.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 280, 215, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 1.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 280, 205, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 1.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 280, 195, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 1.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 280, 175, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.85, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 165, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.75, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 155, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.70, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 145, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.65, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 135, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.60, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 125, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.55, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 115, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.50, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 105, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.45, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 95, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.40, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 85, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.35, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 75, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.30, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 65, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.25, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 55, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.20, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 45, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.17, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 35, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.14, 0.1, 1.0));
    HgWBoxFill(wid, 725, 280, 25, 20, 0);
    HgWText(wid, 780, 200, "G:");
    HgWLine(wid, 780, 200, 825, 200);

    //青
    HgWBox(wid, 724, 249, 257, 22);
    HgWSetFillColor(wid, HgRGB(0.0, 0.0, 1.0));
    HgWBoxFill(wid, 725, 250, 255, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 0.0, 1.0, 1.0));
    HgWBoxFill(wid, 725, 250, 235, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 0.0, 1.0, 1.0));
    HgWBoxFill(wid, 725, 250, 215, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 0.0, 1.0, 1.0));
    HgWBoxFill(wid, 725, 250, 205, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 0.0, 1.0, 1.0));
    HgWBoxFill(wid, 725, 250, 195, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.0, 0.0, 1.0, 1.0));
    HgWBoxFill(wid, 725, 250, 175, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.85, 1.0));
    HgWBoxFill(wid, 725, 250, 165, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.75, 1.0));
    HgWBoxFill(wid, 725, 250, 155, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.70, 1.0));
    HgWBoxFill(wid, 725, 250, 145, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.65, 1.0));
    HgWBoxFill(wid, 725, 250, 135, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.60, 1.0));
    HgWBoxFill(wid, 725, 250, 125, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.55, 1.0));
    HgWBoxFill(wid, 725, 250, 115, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.50, 1.0));
    HgWBoxFill(wid, 725, 250, 105, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.45, 1.0));
    HgWBoxFill(wid, 725, 250, 95, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.40, 1.0));
    HgWBoxFill(wid, 725, 250, 85, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.35, 1.0));
    HgWBoxFill(wid, 725, 250, 75, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.30, 1.0));
    HgWBoxFill(wid, 725, 250, 65, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.25, 1.0));
    HgWBoxFill(wid, 725, 250, 55, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.20, 1.0));
    HgWBoxFill(wid, 725, 250, 45, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.17, 1.0));
    HgWBoxFill(wid, 725, 250, 35, 20, 0);
    HgWSetFillColor(wid, HgRGBA(0.1, 0.1, 0.14, 1.0));
    HgWBoxFill(wid, 725, 250, 25, 20, 0);
    HgWText(wid, 835, 200, "B:");
    HgWLine(wid, 835, 200, 880, 200);
    
    
    //コマンドボタン
    HgWBox(wid, 880, 345, 100, 20);
    HgWBox(wid, 905, 195, 60, 30);
    HgWBox(wid, 715, 130, 60, 30);
    HgWBox(wid, 715, 85, 60, 30);
    HgWBox(wid, 785, 130, 60, 30);
    HgWBox(wid, 855, 130, 60, 30);
    HgWBox(wid, 925, 130, 60, 30);
    HgWBox(wid, 785, 85, 60, 30);
    HgWBox(wid, 855, 85, 60, 30);
    HgWBox(wid, 925, 85, 60, 30);
    HgWBox(wid, 715, 20, 60, 30);
    HgWBox(wid, 785, 20, 60, 30);
    HgWBox(wid, 855, 20, 60, 30);
    HgWBox(wid, 925, 20, 60, 30);
    HgWSetFont(wid, HG_HB, 11.0);
    HgWText(wid, 788, 135, "template.1");
    HgWText(wid, 858, 135, "template.2");
    HgWText(wid, 928, 135, "template.3");
    HgWText(wid, 788, 90, "template.4");
    HgWText(wid, 858, 90, "template.5");
    HgWText(wid, 928, 90, "template.6");
    HgWSetFont(wid, HG_HB, 14.0);
    HgWText(wid, 718, 90, "Reverse");
    HgWSetFont(wid, HG_HB, 15.0);
    HgWText(wid, 913, 200, "Create");
    HgWText(wid, 728, 135, "Clear");
    HgWText(wid, 730, 25, "Start");
    HgWText(wid, 800, 25, "Save");
    HgWText(wid, 870, 25, "Help");
    HgWText(wid, 940, 25, "Quit");
}

void draw(int wid){
    int lid1,lid2,lid3,lid4, lidR, lidG, lidB,
        x1, y1,//マウスで取り出した座標
        gen = 1,//世代数
        btn,//警告用
        reverse = 0,//白黒反転用
        colorNum = 0,//色指定用
        mcolor,//色の作成で使用
        i, j;//カウンタ変数
    int color = HgRGB(0.0, 0.0, 0.0);//色(黒で初期化)
    char File_Name[256], mFile_Name[256];//ファイル名関係
    float R, G, B;//RGBカラ-関係
    doubleLayer layers, layers2, layers3, layers4;
    
    lid1 = HgWAddLayer(wid);//ドットの表示に使用
    lid2 = HgWAddLayer(wid);//グリッドの表示に使用
    lid4 = HgWAddLayer(wid);//白黒反転に使用
    layers = HgWAddDoubleLayer(wid);//lid3で使用
    layers2 = HgWAddDoubleLayer(wid);//lidRで使用
    layers3 = HgWAddDoubleLayer(wid);//lidGで使用
    layers4 = HgWAddDoubleLayer(wid);//lidBで使用
    
    HgWSetWidth(wid, 1.5);
    for(i = 0; i <= 64; i++){
        HgWLine(lid2, 30, celllong*i+30, 670, celllong*i+30);
        HgWLine(lid2, celllong*i+30, 30, celllong*i+30, 670);
    }

    //セルの初期化
    for(j=0; j<64; j++){
        for(i=0; i<64; i++){
            cell[current][j][i] = 0;
        }
    }

    HgSetEventMask(HG_MOUSE_DOWN | HG_MOUSE_DRAG);
    for(;;){
        hgevent *event = HgEvent();
        if(event->type == HG_MOUSE_DOWN){
            x1 = event->x;
            y1 = event->y;

            //常設色の指定
            if(735<x1 && x1<755 && 520<y1 && y1<540){
                color = HgRGB(0.0, 0.0, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(765<x1 && x1<785 && 520<y1 && y1<540){
                color = HgRGB(0.3, 0.3, 0.3);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(795<x1 && x1<815 && 520<y1 && y1<540){
                color = HgRGB(0.5, 0.0, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(825<x1 && x1<845 && 520<y1 && y1<540){
                color = HgRGB(0.5, 0.5, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(855<x1 && x1<875 && 520<y1 && y1<540){
                color = HgRGB(0.0, 0.5, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(885<x1 && x1<905 && 520<y1 && y1<540){
                color = HgRGB(0.0, 0.5, 0.5);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(915<x1 && x1<935 && 520<y1 && y1<540){
                color = HgRGB(0.0, 0.0, 0.5);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(945<x1 && x1<965 && 520<y1 && y1<540){
                color = HgRGB(0.5, 0.0, 0.5);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(735<x1 && x1<755 && 490<y1 && y1<510){
                color = HgRGB(1.0, 1.0, 1.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(765<x1 && x1<785 && 490<y1 && y1<510){
                color = HgRGB(0.5, 0.5, 0.5);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(795<x1 && x1<815 && 490<y1 && y1<510){
                color = HgRGB(1.0, 0.0, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(825<x1 && x1<845 && 490<y1 && y1<510){
                color = HgRGB(1.0, 1.0, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(855<x1 && x1<875 && 490<y1 && y1<510){
                color = HgRGB(0.0, 1.0, 0.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(885<x1 && x1<905 && 490<y1 && y1<510){
                color = HgRGB(0.0, 1.0, 1.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(915<x1 && x1<935 && 490<y1 && y1<510){
                color = HgRGB(0.0, 0.0, 1.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(945<x1 && x1<965 && 490<y1 && y1<510){
                color = HgRGB(1.0, 0.0, 1.0);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }

            //作成色の指定
            if(735<x1 && x1<755 && 410<y1 && y1<430){
                FILE *fp;
                fp = fopen("./makeColor/make_color1.txt", "r");
                fscanf(fp, "%d", &make_color.R);
                fscanf(fp, "%d", &make_color.G);
                fscanf(fp, "%d", &make_color.B);
                fclose(fp);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(765<x1 && x1<785 && 410<y1 && y1<430){
                FILE *fp2;
                fp2 = fopen("./makeColor/make_color2.txt", "r");
                fscanf(fp2, "%d", &make_color.R);
                fscanf(fp2, "%d", &make_color.G);
                fscanf(fp2, "%d", &make_color.B);
                fclose(fp2);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(795<x1 && x1<815 && 410<y1 && y1<430){
                FILE *fp3;
                fp3 = fopen("./makeColor/make_color3.txt", "r");
                fscanf(fp3, "%d", &make_color.R);
                fscanf(fp3, "%d", &make_color.G);
                fscanf(fp3, "%d", &make_color.B);
                fclose(fp3);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(825<x1 && x1<845 && 410<y1 && y1<430){
                FILE *fp4;
                fp4 = fopen("./makeColor/make_color4.txt", "r");
                fscanf(fp4, "%d", &make_color.R);
                fscanf(fp4, "%d", &make_color.G);
                fscanf(fp4, "%d", &make_color.B);
                fclose(fp4);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(855<x1 && x1<875 && 410<y1 && y1<430){
                FILE *fp5;
                fp5 = fopen("./makeColor/make_color5.txt", "r");
                fscanf(fp5, "%d", &make_color.R);
                fscanf(fp5, "%d", &make_color.G);
                fscanf(fp5, "%d", &make_color.B);
                fclose(fp5);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(885<x1 && x1<905 && 410<y1 && y1<430){
                FILE *fp6;
                fp6 = fopen("./makeColor/make_color6.txt", "r");
                fscanf(fp6, "%d", &make_color.R);
                fscanf(fp6, "%d", &make_color.G);
                fscanf(fp6, "%d", &make_color.B);
                fclose(fp6);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(915<x1 && x1<935 && 410<y1 && y1<430){
                FILE *fp7;
                fp7 = fopen("./makeColor/make_color7.txt", "r");
                fscanf(fp7, "%d", &make_color.R);
                fscanf(fp7, "%d", &make_color.G);
                fscanf(fp7, "%d", &make_color.B);
                fclose(fp7);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(945<x1 && x1<965 && 410<y1 && y1<430){
                FILE *fp8;
                fp8 = fopen("./makeColor/make_color8.txt", "r");
                fscanf(fp8, "%d", &make_color.R);
                fscanf(fp8, "%d", &make_color.G);
                fscanf(fp8, "%d", &make_color.B);
                fclose(fp8);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(735<x1 && x1<755 && 380<y1 && y1<400){
                FILE *fp9;
                fp9 = fopen("./makeColor/make_color9.txt", "r");
                fscanf(fp9, "%d", &make_color.R);
                fscanf(fp9, "%d", &make_color.G);
                fscanf(fp9, "%d", &make_color.B);
                fclose(fp9);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(765<x1 && x1<785 && 380<y1 && y1<400){
                FILE *fp10;
                fp10 = fopen("./makeColor/make_color10.txt", "r");
                fscanf(fp10, "%d", &make_color.R);
                fscanf(fp10, "%d", &make_color.G);
                fscanf(fp10, "%d", &make_color.B);
                fclose(fp10);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(795<x1 && x1<815 && 380<y1 && y1<400){
                FILE *fp11;
                fp11 = fopen("./makeColor/make_color11.txt", "r");
                fscanf(fp11, "%d", &make_color.R);
                fscanf(fp11, "%d", &make_color.G);
                fscanf(fp11, "%d", &make_color.B);
                fclose(fp11);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(825<x1 && x1<845 && 380<y1 && y1<400){
                FILE *fp12;
                fp12 = fopen("./makeColor/make_color12.txt", "r");
                fscanf(fp12, "%d", &make_color.R);
                fscanf(fp12, "%d", &make_color.G);
                fscanf(fp12, "%d", &make_color.B);
                fclose(fp12);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(855<x1 && x1<875 && 380<y1 && y1<400){
                FILE *fp13;
                fp13 = fopen("./makeColor/make_color13.txt", "r");
                fscanf(fp13, "%d", &make_color.R);
                fscanf(fp13, "%d", &make_color.G);
                fscanf(fp13, "%d", &make_color.B);
                fclose(fp13);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(885<x1 && x1<905 && 380<y1 && y1<400){
                FILE *fp14;
                fp14 = fopen("./makeColor/make_color14.txt", "r");
                fscanf(fp14, "%d", &make_color.R);
                fscanf(fp14, "%d", &make_color.G);
                fscanf(fp14, "%d", &make_color.B);
                fclose(fp14);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(915<x1 && x1<935 && 380<y1 && y1<400){
                FILE *fp15;
                fp15 = fopen("./makeColor/make_color15.txt", "r");
                fscanf(fp15, "%d", &make_color.R);
                fscanf(fp15, "%d", &make_color.G);
                fscanf(fp15, "%d", &make_color.B);
                fclose(fp15);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }
            if(945<x1 && x1<965 && 380<y1 && y1<400){
                FILE *fp16;
                fp16 = fopen("./makeColor/make_color16.txt", "r");
                fscanf(fp16, "%d", &make_color.R);
                fscanf(fp16, "%d", &make_color.G);
                fscanf(fp16, "%d", &make_color.B);
                fclose(fp16);

                color = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                HgWSetFillColor(wid, color);
                HgWBoxFill(wid, 850, 575, 120, 50, 1);
            }

            //ドットの描画
            do{
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if((30+celllong*i)<x1 && x1<(celllong+30+celllong*i) && ((670-celllong)-celllong*j)<y1 && y1<(670-celllong*j)){
                            if(cell[current][j][i] == 0){
                                HgWSetFillColor(lid1, color);
                                HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                            }
                            if(cell[current][j][i] == 1){
                                HgWSetFillColor(lid1, HG_CLEAR);
                                HgWSetComposite(lid1, HG_BLEND_COPY);
                                HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                            }
                            cell[current][j][i] ^= 1;
                        }
                    }
                }
            }while(715>x1 && x1>775 && 20>y1 && y1>50);

                     
            //ライフゲ-ムスタ-ト, 1は生, 0は死
            if(715<x1 && x1<775 && 20<y1 && y1<50){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 715, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 730, 25, "Start");
                btn = HgAlert("描かれている内容が変わりますがよろしいですか?", "OK", "キャンセル", NULL);
                if(btn == 0){
                    for(gen = 0; gen<=100; gen++){
                        lid3 = HgLSwitch(&layers);
                        HgLClear(lid3);
                        HgWText(lid3, 790, 670, "%d", gen+1);
                        HgSleep(0.05);
                        for(j=0; j<64; j++){
                            for(i=0; i<64; i++){
                                int n = LiveCount(i,j);
                                int next = cell[current][j][i];
                                if(cell[current][j][i] == 1){
                                    if((n <= 1) || (n >= 4)){//過疎,過密判定
                                        HgWSetFillColor(lid1, HG_CLEAR);
                                        HgWSetComposite(lid1, HG_BLEND_COPY);
                                        HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                                        next = 0;
                                    }
                                }else{
                                    if(n == 3){//誕生判定
                                        HgWSetFillColor(lid1, color);
                                        HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                                        next = 1;
                                    }
                                }
                                cell[current^1][j][i] = next; //currentが0なら1,1なら0を代入
                            }
                        }
                        current ^= 1;
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 715, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 730, 25, "Start");
            }
        

            //保存
            if(785<x1 && x1<845 && 20<y1 && y1<50){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 785, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 800, 25, "Save");
                
                printf("保存する画像の名前を入力してください(空白,改行,タブ等は使えません): ");
                scanf("%s", mFile_Name);
                sprintf(File_Name, "img/%s", mFile_Name);
                HgLSave(lid1, File_Name);
                
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 785, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 800, 25, "Save");
                HgAlert("内容をimgフォルダに保存しました", NULL, NULL, NULL);
            }
            
            //ヘルプ
            if(855<x1 && x1<915 && 20<y1 && y1<50){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 855, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 870, 25, "Help");
                
                int wid2;
                wid2 = HgWOpen(1000, 300, 500, 700);
                helpWindow(wid2);
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 855, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 870, 25, "Help"); 
            }
            
            //色の作成
            if(905<x1 && x1<965 && 195<y1 && y1<225){
                colorNum++;
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 905, 195, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 913, 200, "Create");
                
                if(colorNum == 1){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp17;
                    fp17 = fopen("./makeColor/make_color1.txt", "w");
                    fprintf(fp17, "%d\n", make_color.R);
                    fprintf(fp17, "%d\n", make_color.G);
                    fprintf(fp17, "%d\n", make_color.B);
                    fclose(fp17);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 735, 410, 20, 20, 1);
                    
                }
                if(colorNum == 2){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp18;
                    fp18 = fopen("./makeColor/make_color2.txt", "w");
                    fprintf(fp18, "%d\n", make_color.R);
                    fprintf(fp18, "%d\n", make_color.G);
                    fprintf(fp18, "%d\n", make_color.B);
                    fclose(fp18);

                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 765, 410, 20, 20, 1);
                }
                if(colorNum == 3){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp19;
                    fp19 = fopen("./makeColor/make_color3.txt", "w");
                    fprintf(fp19, "%d\n", make_color.R);
                    fprintf(fp19, "%d\n", make_color.G);
                    fprintf(fp19, "%d\n", make_color.B);
                    fclose(fp19);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 795, 410, 20, 20, 1);
                }
                if(colorNum == 4){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp20;
                    fp20 = fopen("./makeColor/make_color4.txt", "w");
                    fprintf(fp20, "%d\n", make_color.R);
                    fprintf(fp20, "%d\n", make_color.G);
                    fprintf(fp20, "%d\n", make_color.B);
                    fclose(fp20);
                    
                    mcolor= HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 825, 410, 20, 20, 1);
                }
                if(colorNum == 5){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp21;
                    fp21 = fopen("./makeColor/make_color5.txt", "w");
                    fprintf(fp21, "%d\n", make_color.R);
                    fprintf(fp21, "%d\n", make_color.G);
                    fprintf(fp21, "%d\n", make_color.B);
                    fclose(fp21);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 855, 410, 20, 20, 1);
                }
                if(colorNum == 6){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp22;
                    fp22 = fopen("./makeColor/make_color6.txt", "w");
                    fprintf(fp22, "%d\n", make_color.R);
                    fprintf(fp22, "%d\n", make_color.G);
                    fprintf(fp22, "%d\n", make_color.B);
                    fclose(fp22);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 885, 410, 20, 20, 1);
                }
                if(colorNum == 7){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp23;
                    fp23 = fopen("./makeColor/make_color7.txt", "w");
                    fprintf(fp23, "%d\n", make_color.R);
                    fprintf(fp23, "%d\n", make_color.G);
                    fprintf(fp23, "%d\n", make_color.B);
                    fclose(fp23);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 915, 410, 20, 20, 1);
                }
                if(colorNum == 8){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp24;
                    fp24 = fopen("./makeColor/make_color8.txt", "w");
                    fprintf(fp24, "%d\n", make_color.R);
                    fprintf(fp24, "%d\n", make_color.G);
                    fprintf(fp24, "%d\n", make_color.B);
                    fclose(fp24);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 945, 410, 20, 20, 1);
                }
                if(colorNum == 9){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp25;
                    fp25 = fopen("./makeColor/make_color9.txt", "w");
                    fprintf(fp25, "%d\n", make_color.R);
                    fprintf(fp25, "%d\n", make_color.G);
                    fprintf(fp25, "%d\n", make_color.B);
                    fclose(fp25);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 735, 380, 20, 20, 1);
                }
                if(colorNum == 10){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp26;
                    fp26 = fopen("./makeColor/make_color10.txt", "w");
                    fprintf(fp26, "%d\n", make_color.R);
                    fprintf(fp26, "%d\n", make_color.G);
                    fprintf(fp26, "%d\n", make_color.B);
                    fclose(fp26);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 765, 380, 20, 20, 1);
                }
                if(colorNum == 11){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp27;
                    fp27 = fopen("./makeColor/make_color11.txt", "w");
                    fprintf(fp27, "%d\n", make_color.R);
                    fprintf(fp27, "%d\n", make_color.G);
                    fprintf(fp27, "%d\n", make_color.B);
                    fclose(fp27);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 795, 380, 20, 20, 1);
                }
                if(colorNum == 12){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp28;
                    fp28 = fopen("./makeColor/make_color12.txt", "w");
                    fprintf(fp28, "%d\n", make_color.R);
                    fprintf(fp28, "%d\n", make_color.G);
                    fprintf(fp28, "%d\n", make_color.B);
                    fclose(fp28);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 825, 380, 20, 20, 1);
                }
                if(colorNum == 13){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp29;
                    fp29 = fopen("./makeColor/make_color13.txt", "w");
                    fprintf(fp29, "%d\n", make_color.R);
                    fprintf(fp29, "%d\n", make_color.G);
                    fprintf(fp29, "%d\n", make_color.B);
                    fclose(fp29);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 855, 380, 20, 20, 1);
                }
                if(colorNum == 14){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp30;
                    fp30 = fopen("./makeColor/make_color14.txt", "w");
                    fprintf(fp30, "%d\n", make_color.R);
                    fprintf(fp30, "%d\n", make_color.G);
                    fprintf(fp30, "%d\n", make_color.B);
                    fclose(fp30);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 885, 380, 20, 20, 1);
                }
                if(colorNum == 15){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp31;
                    fp31 = fopen("./makeColor/make_color15.txt", "w");
                    fprintf(fp31, "%d\n", make_color.R);
                    fprintf(fp31, "%d\n", make_color.G);
                    fprintf(fp31, "%d\n", make_color.B);
                    fclose(fp31);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 915, 380, 20, 20, 1);
                }
                if(colorNum == 16){
                    make_color.R = R;
                    make_color.G = G;
                    make_color.B = B;
                    FILE *fp32;
                    fp32 = fopen("./makeColor/make_color16.txt", "w");
                    fprintf(fp32, "%d\n", make_color.R);
                    fprintf(fp32, "%d\n", make_color.G);
                    fprintf(fp32, "%d\n", make_color.B);
                    fclose(fp32);
                    
                    mcolor = HgRGB((float)make_color.R/255, (float)make_color.G/255, (float)make_color.B/255);
                    HgWSetFillColor(wid, mcolor);
                    HgWBoxFill(wid, 945, 380, 20, 20, 1);
                    colorNum = 0;
                    
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 905, 195, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 913, 200, "Create");
            }   

            //全消去
            if(715<x1 && x1<775 && 130<y1 && y1<160){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 715, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 728, 135, "Clear");
                HgLClear(lid1);
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        cell[current][j][i] = 0;
                    }
                }
                
                HgSleep(0.3);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 715, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 728, 135, "Clear");
            }

            //白黒反転
            if(715<x1 && x1<775 && 85<y1 && y1<115){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 715, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 14.0);
                HgWText(wid, 718, 90, "Reverse");
                if(reverse == 0){
                    HgLClear(lid2);
                    HgLClear(lid4);
                    HgWSetFillColor(lid4, HG_BLACK);
                    HgWBoxFill(lid4, 0, 0, 700, 700, 1);
                    HgWSetWidth(wid, 1.5);
                    HgWSetColor(lid2, HG_WHITE);
                    for(i = 0; i <= 64; i++){
                        HgWLine(lid2, 30, celllong*i+30, 670, celllong*i+30);
                        HgWLine(lid2, celllong*i+30, 30, celllong*i+30, 670);
                    }
                    HgLMove(lid4, 0);
                }else if(reverse == 1){
                    HgLClear(lid2);
                    HgLClear(lid4);
                    HgWSetFillColor(lid4, HG_WHITE);
                    HgWBoxFill(lid4, 0, 0, 700, 700, 1);
                    HgWSetWidth(wid, 1.5);
                    HgWSetColor(lid2, HG_BLACK);
                    for(i = 0; i <= 64; i++){
                        HgWLine(lid2, 30, celllong*i+30, 670, celllong*i+30);
                        HgWLine(lid2, celllong*i+30, 30, celllong*i+30, 670);
                    }
                    HgLMove(lid4, 0);
                }
                reverse ^= 1;

                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 715, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 14.0);
                HgWText(wid, 718, 90, "Reverse");
            }

            //template.1
            if(785<x1 && x1<845 && 130<y1 && y1<160){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 785, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 788, 135, "template.1");
                cell[current][31][25] ^= 1;
                cell[current][31][26] ^= 1; 
                cell[current][32][25] ^= 1;
                cell[current][32][26] ^= 1;
                cell[current][33][25] ^= 1; 
                cell[current][33][26] ^= 1;
                cell[current][34][25] ^= 1;
                cell[current][34][26] ^= 1; 
                cell[current][35][25] ^= 1;
                cell[current][35][26] ^= 1;
                cell[current][36][25] ^= 1;  
                cell[current][36][26] ^= 1;
                cell[current][38][25] ^= 1;
                cell[current][38][26] ^= 1;  
                cell[current][38][27] ^= 1;
                cell[current][38][28] ^= 1;
                cell[current][38][29] ^= 1;
                cell[current][38][30] ^= 1; 
                cell[current][39][25] ^= 1;
                cell[current][39][26] ^= 1;
                cell[current][39][27] ^= 1;
                cell[current][39][28] ^= 1;
                cell[current][39][29] ^= 1;
                cell[current][39][30] ^= 1;  
                cell[current][38][32] ^= 1;
                cell[current][38][33] ^= 1;
                cell[current][39][32] ^= 1;
                cell[current][39][33] ^= 1;
                cell[current][37][32] ^= 1;
                cell[current][37][33] ^= 1;
                cell[current][36][32] ^= 1;
                cell[current][36][33] ^= 1;
                cell[current][35][32] ^= 1;
                cell[current][35][33] ^= 1;
                cell[current][34][32] ^= 1;
                cell[current][34][33] ^= 1;
                cell[current][31][28] ^= 1;
                cell[current][31][29] ^= 1; 
                cell[current][31][30] ^= 1;
                cell[current][31][31] ^= 1;
                cell[current][31][32] ^= 1; 
                cell[current][31][33] ^= 1;
                cell[current][32][28] ^= 1;
                cell[current][32][29] ^= 1; 
                cell[current][32][30] ^= 1;
                cell[current][32][31] ^= 1;
                cell[current][32][32] ^= 1;  
                cell[current][32][33] ^= 1; 
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if(cell[current][j][i] == 1){
                            HgWSetFillColor(lid1, color);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                        if(cell[current][j][i] == 0){
                            HgWSetFillColor(lid1, HG_CLEAR);
                            HgWSetComposite(lid1, HG_BLEND_COPY);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 785, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 788, 135, "template.1");
            }

            //template.2
            if(855<x1 && x1<915 && 130<y1 && y1<150){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 855, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 858, 135, "template.2");
                cell[current][30][20] ^= 1;
                cell[current][30][21] ^= 1;
                cell[current][31][20] ^= 1;
                cell[current][31][21] ^= 1; 
                cell[current][30][30] ^= 1;
                cell[current][31][30] ^= 1;
                cell[current][32][30] ^= 1; 
                cell[current][29][31] ^= 1;
                cell[current][28][32] ^= 1;
                cell[current][28][33] ^= 1; 
                cell[current][33][31] ^= 1;
                cell[current][34][32] ^= 1;
                cell[current][34][33] ^= 1;  
                cell[current][31][34] ^= 1;
                cell[current][29][35] ^= 1;
                cell[current][33][35] ^= 1;  
                cell[current][30][36] ^= 1;
                cell[current][31][36] ^= 1;
                cell[current][32][36] ^= 1;
                cell[current][31][37] ^= 1; 
                cell[current][30][40] ^= 1;
                cell[current][30][41] ^= 1;
                cell[current][29][40] ^= 1;
                cell[current][29][41] ^= 1;
                cell[current][28][40] ^= 1;
                cell[current][28][41] ^= 1;  
                cell[current][27][42] ^= 1;
                cell[current][31][42] ^= 1;
                cell[current][31][44] ^= 1;
                cell[current][32][44] ^= 1;
                cell[current][27][44] ^= 1;
                cell[current][26][44] ^= 1;
                cell[current][29][54] ^= 1;
                cell[current][30][54] ^= 1;
                cell[current][29][55] ^= 1;
                cell[current][30][55] ^= 1;
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if(cell[current][j][i] == 1){
                            HgWSetFillColor(lid1, color);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                        if(cell[current][j][i] == 0){
                            HgWSetFillColor(lid1, HG_CLEAR);
                            HgWSetComposite(lid1, HG_BLEND_COPY);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 855, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 858, 135, "template.2");
                
            }

            //template.3
            if(925<x1 && x1<985 && 130<y1 && y1<160){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 925, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 928, 135, "template.3");
                cell[current][30][25] ^= 1;
                cell[current][30][26] ^= 1; 
                cell[current][30][27] ^= 1;
                cell[current][30][28] ^= 1;
                cell[current][30][29] ^= 1; 
                cell[current][30][30] ^= 1;
                cell[current][30][31] ^= 1;
                cell[current][30][32] ^= 1; 
                cell[current][29][32] ^= 1;
                cell[current][28][32] ^= 1;
                cell[current][27][31] ^= 1;  
                cell[current][25][31] ^= 1;
                cell[current][24][32] ^= 1;
                cell[current][23][32] ^= 1;  
                cell[current][22][32] ^= 1;
                cell[current][22][31] ^= 1;
                cell[current][22][30] ^= 1;
                cell[current][22][29] ^= 1; 
                cell[current][22][28] ^= 1;
                cell[current][22][27] ^= 1;
                cell[current][22][26] ^= 1;
                cell[current][22][25] ^= 1;
                cell[current][33][26] ^= 1;
                cell[current][33][27] ^= 1;  
                cell[current][33][28] ^= 1;
                cell[current][34][25] ^= 1;
                cell[current][34][26] ^= 1;
                cell[current][34][27] ^= 1;
                cell[current][34][28] ^= 1;
                cell[current][34][29] ^= 1;
                cell[current][35][25] ^= 1;
                cell[current][35][26] ^= 1;
                cell[current][35][27] ^= 1;
                cell[current][35][29] ^= 1;
                cell[current][35][30] ^= 1;
                cell[current][36][28] ^= 1;
                cell[current][36][29] ^= 1;
                cell[current][19][26] ^= 1;
                cell[current][19][27] ^= 1;  
                cell[current][19][28] ^= 1;
                cell[current][18][25] ^= 1;
                cell[current][18][26] ^= 1;
                cell[current][18][27] ^= 1;
                cell[current][18][28] ^= 1;
                cell[current][18][29] ^= 1;
                cell[current][17][25] ^= 1;
                cell[current][17][26] ^= 1;
                cell[current][17][27] ^= 1;
                cell[current][17][29] ^= 1;
                cell[current][17][30] ^= 1;
                cell[current][16][28] ^= 1;
                cell[current][16][29] ^= 1;
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if(cell[current][j][i] == 1){
                            HgWSetFillColor(lid1, color);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                        if(cell[current][j][i] == 0){
                            HgWSetFillColor(lid1, HG_CLEAR);
                            HgWSetComposite(lid1, HG_BLEND_COPY);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 925, 130, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 928, 135, "template.3");
            }

            //template.4
            if(785<x1 && x1<845 && 85<y1 && y1<115){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 785, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 788, 90, "template.4");
                cell[current][31][28] ^= 1;
                cell[current][31][29] ^= 1; 
                cell[current][31][30] ^= 1;
                cell[current][31][34] ^= 1;
                cell[current][31][35] ^= 1; 
                cell[current][31][36] ^= 1;
                cell[current][33][28] ^= 1;
                cell[current][33][29] ^= 1; 
                cell[current][33][30] ^= 1;
                cell[current][33][34] ^= 1;
                cell[current][33][35] ^= 1;  
                cell[current][33][36] ^= 1;
                cell[current][26][28] ^= 1;
                cell[current][26][29] ^= 1;  
                cell[current][26][30] ^= 1;
                cell[current][26][34] ^= 1;
                cell[current][26][35] ^= 1;
                cell[current][26][36] ^= 1; 
                cell[current][38][28] ^= 1;
                cell[current][38][29] ^= 1;
                cell[current][38][30] ^= 1;
                cell[current][38][34] ^= 1;
                cell[current][38][35] ^= 1;
                cell[current][38][36] ^= 1;
                cell[current][28][31] ^= 1;
                cell[current][29][31] ^= 1;
                cell[current][30][31] ^= 1;
                cell[current][34][31] ^= 1;
                cell[current][35][31] ^= 1;
                cell[current][36][31] ^= 1;
                cell[current][28][33] ^= 1;
                cell[current][29][33] ^= 1;
                cell[current][30][33] ^= 1;
                cell[current][34][33] ^= 1;
                cell[current][35][33] ^= 1;
                cell[current][36][33] ^= 1;
                cell[current][28][26] ^= 1;
                cell[current][29][26] ^= 1;
                cell[current][30][26] ^= 1;  
                cell[current][34][26] ^= 1;
                cell[current][35][26] ^= 1;
                cell[current][36][26] ^= 1;
                cell[current][28][38] ^= 1;
                cell[current][29][38] ^= 1;
                cell[current][30][38] ^= 1;
                cell[current][34][38] ^= 1;
                cell[current][35][38] ^= 1;
                cell[current][36][38] ^= 1;
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if(cell[current][j][i] == 1){
                            HgWSetFillColor(lid1, color);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                        
                        if(cell[current][j][i] == 0){
                            HgWSetFillColor(lid1, HG_CLEAR);
                            HgWSetComposite(lid1, HG_BLEND_COPY);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 785, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 788, 90, "template.4");
            }

            //template.5
            if(855<x1 && x1<915 && 85<y1 && y1<115){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 855, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 858, 90, "template.5");
                cell[current][32][31] ^= 1;
                cell[current][32][32] ^= 1; 
                cell[current][32][33] ^= 1;
                cell[current][32][34] ^= 1;
                cell[current][32][36] ^= 1; 
                cell[current][32][29] ^= 1;
                cell[current][32][37] ^= 1; 
                cell[current][32][28] ^= 1;
                cell[current][31][30] ^= 1;
                cell[current][31][35] ^= 1; 
                cell[current][33][30] ^= 1;
                cell[current][33][35] ^= 1;
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if(cell[current][j][i] == 1){
                            HgWSetFillColor(lid1, color);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                        if(cell[current][j][i] == 0){
                            HgWSetFillColor(lid1, HG_CLEAR);
                            HgWSetComposite(lid1, HG_BLEND_COPY);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 855, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 858, 90, "template.5");
            }

            //template.6
            if(925<x1 && x1<985 && 85<y1 && y1<115){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 925, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 928, 90, "template.6");
                cell[current][32][31] ^= 1;
                cell[current][33][31] ^= 1; 
                cell[current][32][34] ^= 1;
                cell[current][33][34] ^= 1;
                cell[current][31][32] ^= 1; 
                cell[current][31][33] ^= 1;
                cell[current][34][32] ^= 1;
                cell[current][34][33] ^= 1; 
                cell[current][30][31] ^= 1;
                cell[current][30][34] ^= 1;
                cell[current][35][31] ^= 1;  
                cell[current][35][34] ^= 1;
                cell[current][31][30] ^= 1;
                cell[current][31][35] ^= 1;  
                cell[current][34][30] ^= 1;
                cell[current][34][35] ^= 1;
                for(j=0; j<64; j++){
                    for(i=0; i<64; i++){
                        if(cell[current][j][i] == 1){
                            HgWSetFillColor(lid1, color);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                        if(cell[current][j][i] == 0){
                            HgWSetFillColor(lid1, HG_CLEAR);
                            HgWSetComposite(lid1, HG_BLEND_COPY);
                            HgWBoxFill(lid1, 30+celllong*i, (670-celllong)-celllong*j, celllong, celllong, 0);
                        }
                    }
                }
                
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_LGRAY);
                HgWBoxFill(wid, 925, 85, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 11.0);
                HgWText(wid, 928, 90, "template.6");
            }
            
            //終了
            if(925<x1 && x1<985 && 20<y1 && y1<50){
                HgWSetWidth(wid, 2);
                HgWSetFillColor(wid, HG_GRAY);
                HgWBoxFill(wid, 925, 20, 60, 30, 1);
                HgWSetColor(wid, HG_BLACK);
                HgWSetFont(wid, HG_HB, 15.0);
                HgWText(wid, 940, 25, "Quit");
                HgSleep(0.25);
                break;
            }
        }else if(event->type == HG_MOUSE_DRAG){//ドラッグ操作
            x1 = event->x;
            y1 = event->y;

            //R
            if(725<=x1 && x1<=980 && 310<y1 && y1<330){
                R = x1 - 725;
                lidR = HgLSwitch(&layers2);
                HgLClear(lidR);
                HgWLine(lidR, R+725, 308, R+725, 332);
                HgWText(lidR, 745, 200, "%d", (int)R);
                HgWSetFillColor(wid, HgRGB(R/255, G/255, B/255));
                HgWBoxFill(wid, 880, 345, 100, 20, 1);
            }

            //G
            if(725<=x1 && x1<=980 && 280<y1 && y1<300){
                G = x1 - 725;
                lidG = HgLSwitch(&layers3);
                HgLClear(lidG);
                HgWLine(lidG, G+725, 278, G+725, 302);
                HgWText(lidG, 800, 200, "%d", (int)G);
                HgWSetFillColor(wid, HgRGB(R/255, G/255, B/255));
                HgWBoxFill(wid, 880, 345, 100, 20, 1);
            }

            //B
            if(725<=x1 && x1<=980 && 250<y1 && y1<270){
                B = x1 - 725;
                lidB = HgLSwitch(&layers4);
                HgLClear(lidB);
                HgWLine(lidB, B+725, 248, B+725, 272);
                HgWText(lidB, 855, 200, "%d", (int)B);
                HgWSetFillColor(wid, HgRGB(R/255, G/255, B/255));
                HgWBoxFill(wid, 880, 345, 100, 20, 1);
            }
        }
    }

    HgClose();
    
}

int LiveCount(int _x, int _y){
    int count = 0;
    for(int y=-1; y<=1; y++){
        for(int x=-1; x<=1; x++){
            if((x==0) && (y==0)){//中央の座標の時処理を飛ばす
                continue;
            }
            int x2 = (CELL_WIDTH+_x + x)%CELL_WIDTH;
            int y2 = (CELL_HEIGHT+_y + y)%CELL_HEIGHT;
            count += cell[current][y2][x2];
        }
    }
    return count;
}

void helpWindow(int wid2){
    int x2, y2;
    HgWSetWidth(wid2, 2);
    HgWSetFillColor(wid2, HG_LGRAY);
    HgWBoxFill(wid2, 0, 0, 500, 700, 1);
    HgWBoxFill(wid2, 225, 20, 60, 30, 1);
    HgWSetColor(wid2, HG_BLACK);
    HgWSetFont(wid2, HG_HB, 10.5);
    HgWText(wid2, 10, 680, "==Life_Game_Editor==");
    HgWText(wid2, 10, 655, "このプログラムは23/3ライフゲームを実行します。");
    HgWText(wid2, 10, 635, "・23/3ライフゲームとは");
    HgWText(wid2, 20, 620, "周囲のマスの状態によってあるマスの状態を決定する生命の簡易的なシュミレーションゲームである。");
    HgWText(wid2, 20, 605, "周囲に3つの生命が存在していればそのマスに生命が誕生し、2つか3つの生命が存在していればその");
    HgWText(wid2, 20, 590, "マスは生き残り、1つ以下であれば過疎、4つ以上であれば過密によりそのマスの生命が死滅します。");
    HgWText(wid2, 10, 570, "・使い方");
    HgWText(wid2, 20, 555, "マス目にカーソルを合わせてクリックして描画したい内容を描きます。");
    HgWText(wid2, 20, 540, "\"Command\"欄の\"Start\"をクリックするとライフゲームが開始されます。この時、描画内容は変更さ");
    HgWText(wid2, 20, 525, "れます。また、描画されているマスを再びクリックすると透明色が描画されます。");
    HgWText(wid2, 10, 505, "・各種説明");
    HgWText(wid2, 20, 490, "Generation: セルが今第何世代なのかを表示します。世代は100世代単位で表示されます。 ");
    HgWText(wid2, 20, 470, "Selecting Color: 現在選択している色が表示されます。");
    HgWText(wid2, 20, 450, "Setting Color: 常設色の色を指定することができます。常設色は変更することができません。");
    HgWText(wid2, 20, 430, "Create Color: RGBで色を作ることができます。各色のカラーピッカー(赤、緑、青の棒状の部分)を");
    HgWText(wid2, 20, 415, "                        ドラッグ操作し、\"Create\"をクリックすることで、色を作ることができます。色は" );
    HgWText(wid2, 20, 400, "                        カラーパレットの左上から順に格納されます。カラーパレットを選択することで、" );
    HgWText(wid2, 20, 385, "                        作った色を選択することができます。色は16色まで保存でき、17色以降は、左上の");
    HgWText(wid2, 20, 360, "                        カラーパレットから順に上書きされます。");
    HgWText(wid2, 20, 340, "Creating Color: 現在作っている色を表示します。");
    HgWText(wid2, 20, 320, "Options: \"Clear\": 描画している全ての内容を消去します。");
    HgWText(wid2, 20, 305, "                \"Reverse\": 白黒を反転します。描画されている内容は失われません。");
    HgWText(wid2, 20, 290, "                \"template._\": テンプレートをマス目に表示します。詳しくはreadmeを読んでください。");
    HgWText(wid2, 20, 270, "Command: \"Start\": ライフゲームを開始します。描画されている内容が変更されます。");
    HgWText(wid2, 20, 255, "                    \"Save\": 描画されている内容をpng形式で保存します。ターミナル上で保存名を入力する");
    HgWText(wid2, 20, 240, "                                  必要があります。");
    HgWText(wid2, 20, 225, "                    \"Help\": ヘルプを表示します。");
    HgWText(wid2, 20, 210, "                    \"Quit\": このプログラムを終了します。");
    HgWText(wid2, 10, 190, "・このプログラムの仕様");
    HgWText(wid2, 20, 175, "*このプログラムのライフゲームは23/3形式の標準的なライフゲームを実行します。");
    HgWText(wid2, 20, 160, "*マス目の端に描画内容が到達すると、反対側の端に表示され、ループします。");
    HgWText(wid2, 20, 145, "*色を作る際、何も指定せずに\"Create\"をクリックすると黒色が生成されます。");
    HgWText(wid2, 20, 130, "*ライフゲームをスタートすると、描画が入れ替わる部分だけ指定している色に上書きされます。");
    HgWText(wid2, 20, 115, "*\"template._\"をクリックして、描画がかぶる場合、うまくテンプレートが表示されません。");
    HgWText(wid2, 20, 100, " これは描画されている状態とされていない状態で色をのせるかどうかを判別しているためです。");
    HgWText(wid2, 20, 85, "*予期せず動作が終了することがあります。ご了承ください。");
    HgWSetFont(wid2, HG_HB, 15.0);
    HgWText(wid2, 238, 25, "Back");
    HgWSetEventMask(wid2, HG_MOUSE_DOWN);

    for(;;){
        hgevent *event = HgEventNonBlocking();
        if(event!=NULL){
            x2 = event->x;
            y2 = event->y;
            if(225<x2 &&  x2<285 && 20<y2 && y2<50){
                HgWSetFillColor(wid2, HG_GRAY);
                HgWBoxFill(wid2, 225, 20, 60, 30, 1);
                HgWSetColor(wid2, HG_BLACK);
                HgWText(wid2, 238, 25, "Back");
                HgSleep(0.25);
                break;
            }
        }
    }
    HgWClose(wid2);
}
