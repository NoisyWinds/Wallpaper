#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QMainWindow>
#include <QtWebEngineWidgets>

class background : public QWebEngineView
{
    Q_OBJECT
    public:
        explicit background(QWidget *parent = 0);
};

#endif // BACKGROUND_H
