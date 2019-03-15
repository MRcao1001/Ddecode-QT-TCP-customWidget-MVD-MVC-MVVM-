#include "DecodeBaseWindow.h"
#include "ui_DecodeBaseWindow.h"

DecodeBaseWindow::DecodeBaseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DecodeBaseWindow)
{
    ui->setupUi(this);
    InitWindowStyle();
}

DecodeBaseWindow::~DecodeBaseWindow()
{
    delete ui;
}

/*!
  Override event function
  重写的窗口双击事件
*/
void DecodeBaseWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}

/*!
  Override event function
  重写的窗口被按下事件
*/
void DecodeBaseWindow::mousePressEvent(QMouseEvent *event)
{
    if(m_isMaxnum)
    {
        return;
    }
    else{
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }
    update();
}

/*!
  Override event function
  重写的窗口拖动事件
*/
void DecodeBaseWindow::mouseMoveEvent(QMouseEvent *event)
{

    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->pos();
        m_startMovePos = event->globalPos();
        this->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
    update();
    event->ignore();
}

/*!
  Override event function
  重写的窗口被释放事件
*/
void DecodeBaseWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    this->setCursor(Qt::ArrowCursor);
}

/*!
  Ordinary function
  用于初始化窗体样式为无边框，为自定义边框做基础
*/
void DecodeBaseWindow::InitWindowStyle()
{
    m_isMaxnum = false;
    connect(ui->TargetWindowSize, SIGNAL(clicked()),this, SLOT(TargetWindowSize_clicked()),Qt::UniqueConnection);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    SetWindowShadowEffect();
    this->setMouseTracking(true);
    return;
}

/*!
  Ordinary function
  用于初始化窗体样式为无边框，为自定义边框做基础
*/
void DecodeBaseWindow::SetWindowShadowEffect()
{
    WindowShadowEffect = new QGraphicsDropShadowEffect;
    WindowShadowEffect->setBlurRadius(20);
    WindowShadowEffect->setXOffset(0);
    WindowShadowEffect->setYOffset(0);
    WindowShadowEffect->setColor(QColor(50,50,50,150));
    this->ui->BackgroundFrame->setGraphicsEffect(WindowShadowEffect);
}

/*!
  Ordinary function
  获取当前窗口大小
*/
void DecodeBaseWindow::getScreenInfo(int &g_nActScreenW, int &g_nActScreenH)
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    g_nActScreenW = screenRect.width();
    g_nActScreenH = screenRect.height();
}



/*!
  Ordinary function
  将指定widget添加到主显示区域
*/
void DecodeBaseWindow::addWidgetToMainArea(QWidget *widget)
{
    this->ui->MainArea->addWidget(widget);
}

/*!
  Ordinary function
  最大化窗口
*/
void DecodeBaseWindow::showMaximized()
{
    m_historyPos = this->geometry();
    int window_width, window_height;
    getScreenInfo(window_width, window_height);
    this->move(QPoint(-20,-20));
    this->resize(window_width+40,window_height+10);
}

/*!
  Ordinary function
  还原窗口
*/
void DecodeBaseWindow::showNormal()
{
    this->move(m_historyPos.x(), m_historyPos.y());
    this->resize(m_historyPos.width(), m_historyPos.height());
}

/*!
  Ordinary function
  设置窗口模式：最大化或还原
*/
void DecodeBaseWindow::TargetWindowSize()
{
    if(!m_isMaxnum)
    {
        this->showMaximized();
        WindowShadowEffect->setBlurRadius(0);
        m_isMaxnum = true;
        return;
    }
    this->showNormal();
    WindowShadowEffect->setBlurRadius(20);
    m_isMaxnum = false;
    return;
}



/*!
  Ordinary function
  最大化还原按钮事件
*/
void DecodeBaseWindow::TargetWindowSize_clicked()
{
    TargetWindowSize();
}


void DecodeBaseWindow::on_ResizeBtn_pressed()
{
    ResizeBtn_pressed = true;
    OldWindowSize = this->geometry();

}

void DecodeBaseWindow::on_ResizeBtn_released()
{
    ResizeBtn_pressed = false;
}
