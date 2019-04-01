#include "DecodeBaseWindow.h"
#include "ui_DecodeBaseWindow.h"

DecodeBaseWindow::DecodeBaseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DecodeBaseWindow)
{
    ui->setupUi(this);
    //InitWindowStyle();
    //showAnimation_Appear(250,150,1280,768,this);
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
    switch(event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        if(dir != NONE) {
            this->mouseGrabber();
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    case Qt::RightButton:
        this->close();
        break;
    default:
        break;
        //QDialog::mousePressEvent(event);
    }
}

/*!
  Override event function
  重写的窗口拖动事件
*/
void DecodeBaseWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown) {
        this->region(gloPoint);
    } else {

        if(dir != NONE) {
            QRect rMove(tl, rb);

            switch(dir) {
            case LEFT:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:
                break;
            }
            this->setGeometry(rMove);
        } else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
    //QDialog::mouseMoveEvent(event);
}

/*!
  Override event function
  重写的窗口被释放事件
*/
void DecodeBaseWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
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
  用于初始化窗体标自定义的题栏样式
*/
void DecodeBaseWindow::SetCustomTitleBarStyle(int type)
{
    switch (type) {
    case NOTITLEBAR:
        this->ui->TitleBar->hide();
        break;
    case NOSEARCHBOX:
        this->ui->Title_SearchBtn->hide();
        this->ui->Title_SerachBox->hide();
        break;
    case NOICON:
        this->ui->IconBtn->hide();
        break;
    case NOTITLE:

        break;
    case ONLYBTN:
        this->ui->Title_SearchBtn->hide();
        this->ui->Title_SerachBox->hide();
        this->ui->IconBtn->hide();
        break;
    case WITHOUTBTN:
        this->ui->ShowMin->hide();
        this->ui->TargetWindowSize->hide();
        this->ui->CloseWindow->hide();
        break;
    case NOMAXBTN:
        this->ui->TargetWindowSize->setEnabled(false);
        break;
    case NOMINBTN:
        this->ui->ShowMin->setEnabled(false);
        break;
    case NOCLOSEBTN:
        this->ui->CloseWindow->setEnabled(false);
        break;
    case NORMAL:
        break;
    default:
        break;
    }
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
    showAnimation_Zoom(this);
}



/*!
  Ordinary function
  最大化还原按钮事件
*/
void DecodeBaseWindow::TargetWindowSize_clicked()
{
    TargetWindowSize();
}

/*!
  Ordinary function
  判断鼠标所在窗口的位置
*/
void DecodeBaseWindow::region(const QPoint &cursorGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

/*!
  Ordinary function
  窗口出现动画
*/
void DecodeBaseWindow::showAnimation_Appear(int StartWidth, int StartHeight, int EndWidth, int EndHeight, QWidget *object)
{
    if(animation_Opacity != nullptr || animation_Size!= nullptr || animation_Group !=nullptr)
    {
        delete animation_Opacity;
        delete animation_Size;
        delete animation_Group;
        animation_Opacity = nullptr;
        animation_Size =nullptr;
        animation_Group = nullptr;
    }

    animation_Group = new QParallelAnimationGroup(object);

    animation_Opacity = new QPropertyAnimation(object, "windowOpacity");
    animation_Opacity->setDuration(200);
    animation_Opacity->setStartValue(0);
    animation_Opacity->setEndValue(1);
    animation_Group->addAnimation(animation_Opacity);

    int width, height;
    getScreenInfo(width, height);
    animation_Size = new QPropertyAnimation(object, "geometry");
    animation_Size->setDuration(200);
    animation_Size->setStartValue(QRect(width/2-(StartWidth/2), height/2-(StartHeight/2), StartWidth, StartHeight));
    animation_Size->setEndValue(QRect(width/2-EndWidth/2, height/2-EndHeight/2, EndWidth, EndHeight));
    animation_Size->setEasingCurve(QEasingCurve::InOutQuad);
    animation_Group->addAnimation(animation_Size);

    animation_Group->start();


}

/*!
  Ordinary function
  窗口消失动画
*/
void DecodeBaseWindow::showAnimation_Disappear(QWidget *object)
{
    if(animation_Opacity != nullptr )
    {
        delete animation_Opacity;
        animation_Opacity = nullptr;
    }

    animation_Group = new QParallelAnimationGroup(object);
    animation_Opacity = new QPropertyAnimation(object, "windowOpacity");
    animation_Opacity->setDuration(300);
    animation_Opacity->setStartValue(1);
    animation_Opacity->setEndValue(0);
    animation_Opacity->setEasingCurve(QEasingCurve::OutQuint);
    animation_Opacity->start();
    connect(animation_Opacity, SIGNAL(finished()), this,SLOT(close()));

}

/*!
  Ordinary function
  窗口缩放动画
*/
void DecodeBaseWindow::showAnimation_Zoom(QWidget *object)
{
    if(animation_Size != nullptr)
    {
        delete animation_Size;
        animation_Size = nullptr;
    }
    if(m_isMaxnum)
    {
        m_isMaxnum = false;
        animation_Size = new QPropertyAnimation(object, "geometry");
        animation_Size->setDuration(200);
        animation_Size->setStartValue(object->geometry());
        animation_Size->setEndValue(m_historyPos);
        animation_Size->setEasingCurve(QEasingCurve::InOutQuad);
        animation_Size->start();
    }
    else {
        m_isMaxnum = true;
        int width, height;
        m_historyPos = object->geometry();
        getScreenInfo(width, height);
        animation_Size = new QPropertyAnimation(object, "geometry");
        animation_Size->setDuration(200);
        animation_Size->setStartValue(m_historyPos);
        animation_Size->setEndValue(QRect(-20, -20, width+40, height));
        animation_Size->setEasingCurve(QEasingCurve::InOutQuad);
        animation_Size->start();
    }
}


void DecodeBaseWindow::on_CloseWindow_clicked()
{
    showAnimation_Disappear(this);
}
