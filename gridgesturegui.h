#ifndef GRIDGESTUREGUI_H
#define GRIDGESTUREGUI_H

#include <QQuickPaintedItem>
#include <QPainter>

const int GRID_WIDTH = 320;
const int GRID_HEIGHT = 240;

class GridGestureGUI : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit GridGestureGUI(QQuickItem *parent = nullptr);
    ~GridGestureGUI();
    void paint(QPainter *painter);
    void createPatternMap(int width, int height, int margin);
    Q_INVOKABLE void seekPatternMap(int x, int y);
    Q_INVOKABLE void setPattern0000(bool flag);
    int XXfromPattern(unsigned short ptn, int width, int height);
    int YYfromPattern(unsigned short ptn, int width, int height);
    int WWfromPattern(unsigned short ptn, int widht, int height);
    int HHfromPattern(unsigned short ptn, int widht, int height);
    Q_INVOKABLE int getNextXX() {
        return XXfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT); }
    Q_INVOKABLE int getNextYY() {
        return YYfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT); }
    Q_INVOKABLE int getNextWW() {
        return WWfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT); }
    Q_INVOKABLE int getNextHH() {
        return HHfromPattern(nextPattern, GRID_WIDTH, GRID_HEIGHT); }

/*signals:
public slots:*/

private:
    unsigned short **pattern;
    unsigned short currentPattern;
    unsigned short nextPattern;
};

#endif // GRIDGESTUREGUI_H
