#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QQuickWindow>
#include <QDateTime>
#include <QDir>

class ScreenShot : public QObject
{
Q_OBJECT
public:
    /*explicit ScreenShot(QObject *parent = nullptr)
    {
    }*/

    Q_INVOKABLE static void save()
    {
        QDir dir("Screenshots");
        if(!dir.exists())
            dir.mkpath(".");

        QPixmap pixmap = QPixmap::grabWindow((WId)GetForegroundWindow()); // アクティブウィンドウのHWND取得(※windows API)
        // QPixmap pixmap = QPixmap::grabWindow((WId)this->GetSafeHwnd());

        QString dateInterval = QString::number(QDateTime::currentSecsSinceEpoch());
        QFile f("Screenshots/Screenshot-"+dateInterval+".jpg");
         f.open(QIODevice::WriteOnly);
         if(f.isOpen()) pixmap.save(&f, "JPG");
    }
};

#endif // SCREENSHOT_H
