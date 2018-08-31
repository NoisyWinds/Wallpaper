/*
update at 2018/8/31
增加 hover 交互的实现
注意：
此种方法实现的交互仅仅是初级手段，会造成window消息堵塞，并且效果有一定的延迟。
如果你有更好的实现方法，欢迎提供至 github/Thomashuai/Wallpaper
另外，就桌面整理程序的兼容，有一定的问题没有解决，目前没有很好的思路，如果你能提供更好的方法，
也欢迎一起交流学习
*/

#include "wallpaper.h"
#include "ui_wallpaper.h"
#include "utils.h"
#include <QCloseEvent>
#include <QWebEngineProfile>
#include <QSystemTrayIcon>
#include <QFile>
#include <QDebug>

using namespace std;

WId viewId;
LRESULT CALLBACK HookShoot(_In_ int nCode, _In_ WPARAM wParam,LPARAM lParam){
    if(wParam == WM_MOUSEMOVE || wParam == WM_NCMOUSEMOVE){
         MOUSEHOOKSTRUCT * mshook = (MOUSEHOOKSTRUCT *)lParam;
         PostMessage((HWND)viewId,WM_MOUSEMOVE,0,MAKELPARAM(mshook->pt.x,mshook->pt.y));
    };
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

Wallpaper::Wallpaper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Wallpaper)
{
    ui->setupUi(this);
    isHover = true;
    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/images/icon.png");
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->setToolTip("Wallpaper");
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    createActions();
    createMenu();
    mSysTrayIcon->show();
    QWebEngineProfile::NoCache;
    view = new QWebEngineView();
    viewId = view->winId();
    // 返回workerW窗口句柄
    HWND workerW =  Utils::GetWorkerW();
    //设置窗口样式
    GetWindowLongA((HWND)viewId, GWL_STYLE);
     //设置壁纸窗体的父窗体
    SetParent((HWND)viewId,workerW);
    SetWindowPos((HWND)viewId,HWND_TOP,0,0,0,0,WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR|WS_EX_NOACTIVATE);
    // 设置全局鼠标事件钩子
    hook = SetWindowsHookEx(WH_MOUSE_LL,HookShoot,GetModuleHandle(NULL),0);
    this->init();
    view->show();
    this->show();
}
void Wallpaper::init()
{
    QFile file("config.json");
    if(file.open(QIODevice::ReadWrite))
    {
        QByteArray byte_array;
        if(file.exists())
        {
            QString app_path = QCoreApplication::applicationDirPath();
            app_path += "/html/example/bubbles/index.html";
            obj.insert("path",app_path);
            obj.insert("layout",2);
            QJsonDocument document;
            document.setObject(obj);
            byte_array = document.toJson(QJsonDocument::Compact);
            file.write(byte_array);
        }
        else
        {
           byte_array = file.readAll();
        }
        QJsonParseError e;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(byte_array,&e);
        if(e.error == QJsonParseError::NoError && !jsonDoc.isNull())
        {
            obj = jsonDoc.object();
            ui->filePath->setText(QString(obj["path"].toString()));
            view->setUrl(QUrl(QString(obj["path"].toString())));
            view->showFullScreen();
            switch (obj["layout"].toInt()) {
            case 1:
                ui->firstButton->setChecked(true);
                this->on_firstButton_clicked();
                break;
            case 2:
                ui->fillButton->setChecked(true);
                this->on_fillButton_clicked();
                break;
            case 3:
                ui->secondButton->setChecked(true);
                this->on_secondButton_clicked();
                break;
            default:
                break;
            }
        }
    }
    file.close();
}

void Wallpaper::closeEvent(QCloseEvent *event)
{
    this->hide();
}


void Wallpaper::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        this->show();
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}

void Wallpaper::createActions()
{
    mShowWindow = new QAction(QObject::trUtf8("显示程序"),this);
    connect(mShowWindow,SIGNAL(triggered()),SLOT(on_showMainAction()));
    mExitAppAction = new QAction(QObject::trUtf8("退出程序"),this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
}


void Wallpaper::on_showMainAction()
{
    this->show();
}

void Wallpaper::on_exitAppAction()
{
    QFile file("config.json");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "write json file failed";
    }
    else
    {
        QJsonDocument document;
        document.setObject(obj);
        QByteArray byte_array = document.toJson(QJsonDocument::Compact);
        file.write(byte_array);
    }
    file.close();
    exit(0);
}


void Wallpaper::createMenu()
{
    mMenu = new QMenu(this);
    mMenu->addAction(mShowWindow);
    mMenu->addAction(mExitAppAction);
    mMenu->setStyleSheet("QMenu{color:black;border-bottom:1px solid #ccc;}");
    mSysTrayIcon->setContextMenu(mMenu);
}


Wallpaper::~Wallpaper()
{
    delete ui;
    delete view;
    delete mMenu;
}

void Wallpaper::on_path_button_clicked()
{
   QString path = QFileDialog::getOpenFileName(this);
   ui->filePath->setText(path);
}

void Wallpaper::on_hoverButton_clicked()
{
    if(!isHover)
    {
        // 设置全局钩子
        hook = SetWindowsHookEx(WH_MOUSE_LL,HookShoot,GetModuleHandle(NULL),0);
        ui->hoverButton->setText("关闭");
        ui->hoverButton->setStyleSheet("background-color:rgb(255, 170, 0);color:white;border-radius:5px;border:none;font-size:14px;");
        isHover = true;
    }else{
        // 销毁全局钩子
        UnhookWindowsHookEx(hook);
        ui->hoverButton->setText("开启");
        ui->hoverButton->setStyleSheet("background-color:rgb(60,60,60);color:white;border-radius:5px;border:none;font-size:14px;");
        isHover = false;
    }
}



void Wallpaper::on_fillButton_clicked()
{
    QDesktopWidget *desktop = QApplication::desktop();
    view->move(QPoint(0,0));
    int height = desktop->height();
    int width = desktop->width();
    view->resize(QSize(width,height));
    obj["layout"] = 2;
}

void Wallpaper::on_secondButton_clicked()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect size_first = desktop->screenGeometry(0);
    int width_first = size_first.width();
    view->move(QPoint(width_first,0));
    QRect size = desktop->screenGeometry(1);
    int height = size.height();
    int width = size.width();
    view->resize(QSize(width,height));
    obj["layout"] = 3;
}

void Wallpaper::on_firstButton_clicked()
{
    QDesktopWidget *desktop = QApplication::desktop();
    view->move(QPoint(0,0));
    QRect size = desktop->screenGeometry(0);
    int height = size.height();
    int width = size.width();
    view->resize(QSize(width,height));
    obj["layout"] = 1;
}

void Wallpaper::on_filePath_textChanged(const QString &arg1)
{
    QString path = ui->filePath->text();
    obj["path"] = path;
    view->setUrl(QUrl(path));
}
