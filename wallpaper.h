#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QMainWindow>
#include <QtWebEngineWidgets>
#include "background.h"
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
    class Wallpaper;
}

class Wallpaper : public QMainWindow
{
    Q_OBJECT
public:
    explicit Wallpaper(QWidget *parent = 0);
    ~Wallpaper();
public:
    void createActions();
    void createMenu();
public:
    QSystemTrayIcon *mSysTrayIcon;
    QMenu *mMenu;
    QAction *mShowWindow;
    QAction *mExitAppAction;

private slots:
    void on_path_button_clicked();
    void on_startButton_clicked();
    void on_fillButton_clicked();
    void on_secondButton_clicked();
    void on_firstButton_clicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showMainAction();
    void on_exitAppAction();
private:
    Ui::Wallpaper *ui;
    QWebEngineView *view;
    QJsonObject obj;
    void closeEvent(QCloseEvent *event);
    void init();
};

#endif // WALLPAPER_H
