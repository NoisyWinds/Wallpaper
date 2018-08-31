#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QMainWindow>
#include <QtWebEngineWidgets>
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
    QWebEngineView *view;

private slots:
    void on_path_button_clicked();
    void on_hoverButton_clicked();
    void on_fillButton_clicked();
    void on_secondButton_clicked();
    void on_firstButton_clicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showMainAction();
    void on_exitAppAction();
    void on_filePath_textChanged(const QString &arg1);

private:
    bool isHover;
    HHOOK hook;
    Ui::Wallpaper *ui;
    QJsonObject obj;
    void closeEvent(QCloseEvent *event);
    void init();
    HWND workerW;
};

#endif // WALLPAPER_H
