#include "gridgesturegui.h"

// GridGestureGUI::GridGestureGUI()
GridGestureGUI::GridGestureGUI(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    currentPattern = 0x0000;
    nextPattern = 0x0000;
    createPatternMap(GRID_WIDTH, GRID_HEIGHT, 8);
}

GridGestureGUI::~GridGestureGUI()
{
    for (int i = 0; i <= GRID_HEIGHT-1; i++) {
        delete[] pattern[i];
    }
    delete[] pattern;
}

void GridGestureGUI::paint(QPainter *painter)
{
    int xx, yy, ww, hh;

    if(nextPattern != 0x0000) {
        // 前のアイテムを白色で描画
        if(currentPattern != 0x0000) {
            xx = XXfromPattern(currentPattern, GRID_WIDTH, GRID_HEIGHT);
            yy = YYfromPattern(currentPattern, GRID_WIDTH, GRID_HEIGHT);
            ww = WWfromPattern(currentPattern, GRID_WIDTH, GRID_HEIGHT);
            hh = HHfromPattern(currentPattern, GRID_WIDTH, GRID_HEIGHT);
            // qDebug("currentPattern:%04x xx:%3d yy:%3d ww:%3d: hh:%3d", currentPattern, xx, yy, ww, hh);
            painter->fillRect(xx, yy, ww, hh, Qt::white);
        }

        // 枠(方眼)を描画
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter->drawRect(0, 0, width()-1, height()-1); //四角描写

        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        painter->drawLine(0, height()/2-1, width()-1, height()/2-1); //十字描写
        painter->drawLine(width()/2-1, 0, width()/2-1, height()-1);

        painter->setPen(QPen(Qt::black, 2, Qt::DashLine));
        painter->drawLine(0, height()/4-1, width()-1, height()/4-1); //格子描写
        painter->drawLine(0, height()*3/4-1, width()-1, height()*3/4-1);
        painter->drawLine(width()/4-1, 0, width()/4-1, height()-1);
        painter->drawLine(width()*3/4-1, 0, width()*3/4-1, height()-1);

        // アイテムを灰色で描画
        xx = XXfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT);
        yy = YYfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT);
        ww = WWfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT);
        hh = HHfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT);
        // qDebug("nextPattern:%04x xx:%3d yy:%3d ww:%3d: hh:%3d", nextPattern, xx, yy, ww, hh);
        painter->fillRect(xx, yy, ww, hh, Qt::gray);
    }
    // 範囲外(0x0000)の場合、全て白色で描画
    else painter->fillRect(0, 0, width()-1, height()-1, Qt::white);
}

void GridGestureGUI::createPatternMap(int width, int height, int margin)
{
    int i,j;

    pattern = new unsigned short*[width];
    for(i = 0; i <= width-1; i++) pattern[i] = new unsigned short[height];

    for(i = 0; i <= width/4-margin-1; i++) {
        for(j = 0; j <= height/4-margin-1; j++) pattern[i][j] = 0x0001;
        for(j = height/4-margin; j <= height/4+margin-1; j++) pattern[i][j] = 0x0011;
        for(j = height/4+margin; j <= height/2-margin-1; j++) pattern[i][j] = 0x0010;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0x3333;
        for(j = height/2+margin; j <= height*3/4-margin-1; j++) pattern[i][j] = 0x0100;
        for(j = height*3/4-margin; j <= height*3/4+margin-1; j++) pattern[i][j] = 0x1100;
        for(j = height*3/4+margin; j <= height-1; j++) pattern[i][j] = 0x1000;
    }
    for(i = width/4-margin; i <= width/4+margin-1; i++) {
        for(j = 0; j <= height/4-margin-1; j++) pattern[i][j] = 0x0003;
        for(j = height/4-margin; j <= height/4+margin-1; j++) pattern[i][j] = 0x0033;
        for(j = height/4+margin; j <= height/2-margin-1; j++) pattern[i][j] = 0x0030;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0x3333;
        for(j = height/2+margin; j <= height*3/4-margin-1; j++) pattern[i][j] = 0x0300;
        for(j = height*3/4-margin; j <= height*3/4+margin-1; j++) pattern[i][j] = 0x3300;
        for(j = height*3/4+margin; j <= height-1; j++) pattern[i][j] = 0x3000;
    }
    for(i = width/4+margin; i <= width/2-margin-1; i++) {
        for(j = 0; j <= height/4-margin-1; j++) pattern[i][j] = 0x0002;
        for(j = height/4-margin; j <= height/4+margin-1; j++) pattern[i][j] = 0x0022;
        for(j = height/4+margin; j <= height/2-margin-1; j++) pattern[i][j] = 0x0020;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0x3333;
        for(j = height/2+margin; j <= height*3/4-margin-1; j++) pattern[i][j] = 0x0200;
        for(j = height*3/4-margin; j <= height*3/4+margin-1; j++) pattern[i][j] = 0x2200;
        for(j = height*3/4+margin; j <= height-1; j++) pattern[i][j] = 0x2000;
    }

    for(i = width/2-margin; i <= width/2+margin-1; i++) {
        for(j = 0; j <= height/2-margin-1; j++) pattern[i][j] = 0x00FF;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0xFFFF;
        for(j = height/2+margin; j <= height-1; j++) pattern[i][j] = 0xFF00;
    }

    for(i = width/2+margin; i <= width*3/4-margin-1; i++) {
        for(j = 0; j <= height/4-margin-1; j++) pattern[i][j] = 0x0004;
        for(j = height/4-margin; j <= height/4+margin-1; j++) pattern[i][j] = 0x0044;
        for(j = height/4+margin; j <= height/2-margin-1; j++) pattern[i][j] = 0x0040;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0xCCCC;
        for(j = height/2+margin; j <= height*3/4-margin-1; j++) pattern[i][j] = 0x0400;
        for(j = height*3/4-margin; j <= height*3/4+margin-1; j++) pattern[i][j] = 0x4400;
        for(j = height*3/4+margin; j <= height-1; j++) pattern[i][j] = 0x4000;
    }
    for(i = width*3/4-margin; i <= width*3/4+margin-1; i++) {
        for(j = 0; j <= height/4-margin-1; j++) pattern[i][j] = 0x000C;
        for(j = height/4-margin; j <= height/4+margin-1; j++) pattern[i][j] = 0x00CC;
        for(j = height/4+margin; j <= height/2-margin-1; j++) pattern[i][j] = 0x00C0;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0xCCCC;
        for(j = height/2+margin; j <= height*3/4-margin-1; j++) pattern[i][j] = 0x0C00;
        for(j = height*3/4-margin; j <= height*3/4+margin-1; j++) pattern[i][j] = 0xCC00;
        for(j = height*3/4+margin; j <= height-1; j++) pattern[i][j] = 0xC000;
    }
    for(i = width*3/4+margin; i <= width-1; i++) {
        for(j = 0; j <= height/4-margin-1; j++) pattern[i][j] = 0x0008;
        for(j = height/4-margin; j <= height/4+margin-1; j++) pattern[i][j] = 0x0088;
        for(j = height/4+margin; j <= height/2-margin-1; j++) pattern[i][j] = 0x0080;
        for(j = height/2-margin; j <= height/2+margin-1; j++) pattern[i][j] = 0xCCCC;
        for(j = height/2+margin; j <= height*3/4-margin-1; j++) pattern[i][j] = 0x0800;
        for(j = height*3/4-margin; j <= height*3/4+margin-1; j++) pattern[i][j] = 0x8800;
        for(j = height*3/4+margin; j <= height-1; j++) pattern[i][j] = 0x8000;
    }
}

void /*unsigned short*/ GridGestureGUI::seekPatternMap(int x, int y)
{
    if((x < GRID_WIDTH) && (y < GRID_HEIGHT)) {
        currentPattern = nextPattern;
        nextPattern = pattern[x][y];
        // qDebug("x:%03d y:%03d nextPattern:%04x currentPattern:%04x", x, y, nextPattern, currentPattern);
        update();
    }
    // return pattern[x][y];
}

void GridGestureGUI::setPattern0000(bool flag)
{
    if(!flag) {
        currentPattern = 0x0000;
        nextPattern = 0x0000;
        update();
    }
}

int GridGestureGUI::XXfromPattern(unsigned short ptn, int width, int height)
{
    int xx = 0;

    switch(ptn) {
    case 0x0001:    case 0x0010:    case 0x0100:    case 0x1000:
    case 0x0003:    case 0x0030:    case 0x0300:    case 0x3000:
    case 0x0011:    case 0x1100:
    case 0x0033:    case 0x3300:    case 0x3333:
    case 0x00FF:    case 0xFF00:    case 0xFFFF:
        xx = 0;
        break;
    case 0x0002:    case 0x0020:    case 0x0200:    case 0x2000:
    case 0x0022:    case 0x2200:
        xx = width/4;
        break;
    case 0x0004:    case 0x0040:    case 0x0400:    case 0x4000:
    case 0x000C:    case 0x00C0:    case 0x0C00:    case 0xC000:
    case 0x0044:    case 0x4400:
    case 0x00CC:    case 0xCC00:    case 0xCCCC:
        xx = width/2;
        break;
    case 0x0008:    case 0x0080:    case 0x0800:    case 0x8000:
    case 0x0088:    case 0x8800:
        xx = width*3/4;
        break;
    case 0x0000:    default:
        xx = 0;
        break;
    }
    return xx;
}

int GridGestureGUI::YYfromPattern(unsigned short ptn, int width, int height)
{
    int yy = 0;

    switch(ptn) {
    case 0x0001:    case 0x0002:    case 0x0004:    case 0x0008:
    case 0x0011:    case 0x0022:    case 0x0044:    case 0x0088:
    case 0x0003:    case 0x000C:
    case 0x0033:    case 0x00CC:
    case 0x3333:    case 0xCCCC:
    case 0x00FF:    case 0xFFFF:
        yy = 0;
        break;
    case 0x0010:    case 0x0020:    case 0x0040:    case 0x0080:
    case 0x0030:    case 0x00C0:
        yy = height/4;
        break;
    case 0x0100:    case 0x0200:    case 0x0400:    case 0x0800:
    case 0x1100:    case 0x2200:    case 0x4400:    case 0x8800:
    case 0x0300:    case 0x0C00:
    case 0x3300:    case 0xCC00:
    case 0xFF00:
        yy = height/2;
        break;
    case 0x1000:    case 0x2000:    case 0x4000:    case 0x8000:
    case 0x3000:    case 0xC000:
        yy = height*3/4;
        break;
    case 0x0000:    default:
        yy = 0;
        break;
    }
    return yy;
}

int GridGestureGUI::WWfromPattern(unsigned short ptn, int width, int height)
{
    int ww = 0;

    switch(ptn) {
    case 0x0001:    case 0x0002:    case 0x0004:    case 0x0008:
    case 0x0010:    case 0x0020:    case 0x0040:    case 0x0080:
    case 0x0100:    case 0x0200:    case 0x0400:    case 0x0800:
    case 0x1000:    case 0x2000:    case 0x4000:    case 0x8000:
    case 0x0011:    case 0x0022:    case 0x0044:    case 0x0088:
    case 0x1100:    case 0x2200:    case 0x4400:    case 0x8800:
        ww = width/4;
        break;
    case 0x0003:    case 0x0030:    case 0x0300:    case 0x3000:
    case 0x000C:    case 0x00C0:    case 0x0C00:    case 0xC000:
    case 0x0033:    case 0x00CC:    case 0x3300:    case 0xCC00:
    case 0x3333:    case 0xCCCC:
        ww = width/2;
        break;
    case 0x00FF:    case 0xFF00:    case 0xFFFF:
        ww = width;
        break;
    case 0x0000:    default:
        ww = 0;
        break;
    }
    return ww;
}

int GridGestureGUI::HHfromPattern(unsigned short ptn, int width, int height)
{
    int hh = 0;

    switch(ptn) {
    case 0x0001:    case 0x0002:    case 0x0004:    case 0x0008:
    case 0x0010:    case 0x0020:    case 0x0040:    case 0x0080:
    case 0x0100:    case 0x0200:    case 0x0400:    case 0x0800:
    case 0x1000:    case 0x2000:    case 0x4000:    case 0x8000:
    case 0x0003:    case 0x0030:    case 0x0300:    case 0x3000:
    case 0x000C:    case 0x00C0:    case 0x0C00:    case 0xC000:
        hh = height/4;
        break;
    case 0x0011:    case 0x0022:    case 0x0044:    case 0x0088:
    case 0x1100:    case 0x2200:    case 0x4400:    case 0x8800:
    case 0x0033:    case 0x00CC:    case 0x3300:    case 0xCC00:
    case 0xFF00:    case 0x00FF:
        hh = height/2;
        break;
    case 0x3333:    case 0xCCCC:    case 0xFFFF:
        hh = height;
        break;
    case 0x0000:    default:
        hh = 0;
        break;
    }
    return hh;
}
