#include "background.h"
#include "utils.h"

using namespace std;

background::background(QWidget *parent) :
    QWebEngineView(parent)
{
    this->setObjectName("background");
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::CoverWindow|Qt::WindowStaysOnBottomHint);
    this->setWindowState(Qt::WindowNoState);
    this->setFocusPolicy(Qt::NoFocus);
    this->setUrl(QUrl("http://10.21.40.155/worldSkillCountDown/"));
    SetParent((HWND)this->winId(),Utils::GetWorkerW());
    this->showFullScreen();
}

