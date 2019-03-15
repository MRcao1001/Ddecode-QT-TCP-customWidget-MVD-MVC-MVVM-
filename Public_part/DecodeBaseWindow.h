#ifndef DECODEBASEWINDOW_H
#define DECODEBASEWINDOW_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
namespace Ui {
class DecodeBaseWindow;
}

#define PADDING 10
enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
enum BaseWindowType{ NOTITLEBAR=0, NOSEARCHBOX=1, NOICON, NOTITLE, ONLYBTN, WITHOUTBTN, NOMAXBTN, NOMINBTN, NOCLOSEBTN, NORMAL};
class DecodeBaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DecodeBaseWindow(QWidget *parent = 0);
    ~DecodeBaseWindow();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    /**
     * @brief TargetWindowSize_clicked 最大化/还原槽函数
     */
    void TargetWindowSize_clicked();
    /**
     * @brief InitWindowStyle 初始化窗体样式
     */
    void InitWindowStyle();

    /**
     * @brief TargetWindowSize 设置窗口模式
     */
    void TargetWindowSize();
    /**
     * @brief IsMaxnum 窗口状态标志
     */
    void SetWindowShadowEffect();
    /**
     * @brief getScreenInfo 获取当前窗口大小
     * @param int &, int &
     */
    void getScreenInfo(int &g_nActScreenW, int &g_nActScreenH);

    /**
     * @brief region 判断此时鼠标在窗口的上下左右的方位
     * @param const QPoint &
     */
    void region(const QPoint &cursorGlobalPoint);
    /**
     * @brief on_CloseWindow_clicked 关闭按钮点击事件
     */
    void on_CloseWindow_clicked();
public:
    /**
     * @brief showAnimation 显示动画_出现动画
     */
    void showAnimation_Appear(int StartWidth, int StartHeight,int EndWidth, int EndHeight, QWidget *object);
    /**
     * @brief showAnimation 显示动画_消失动画
     */
    void showAnimation_Disappear(QWidget *object);
    /**
     * @brief showAnimation 显示动画_缩放动画
     */
    void showAnimation_Zoom(QWidget *object);


private:
    Ui::DecodeBaseWindow *ui;
    /**
     * @brief IsMaxnum 窗口状态标志
     */
    bool m_isMaxnum = false;
    /**
     * @brief IsMaxnum 窗口是否处于按下状态标志
     */
    bool m_isPressed = false;
    /**
     * @brief History_Pos 最大化之前的坐标
     */
    QRect m_historyPos;
    /**
     * @brief m_startMovePos 窗口开始移动的坐标
     */
    QPoint m_startMovePos;
    /**
     * @brief History_Size 最大化之前的尺寸
     */
    QGraphicsDropShadowEffect *WindowShadowEffect;
    /**
     * @brief isLeftPressDown  判断左键是否按下,默认未按下
     */
    bool isLeftPressDown=false;
    /**
     * @brief dragPosition 窗口移动拖动时需要记住的点
     */
    QPoint dragPosition;
    /**
     * @brief dir 窗口大小改变时，记录改变方向
     */
    Direction dir = NONE;
    /**
     * @brief animation_Opacity 透明度动画对象
     */
    QPropertyAnimation *animation_Opacity = nullptr;
    /**
     * @brief animation_Opacity 尺寸动画对象
     */
    QPropertyAnimation *animation_Size = nullptr;
    /**
     * @brief animation_Opacity 位置动画对象
     */
    QPropertyAnimation *animation_Position = nullptr;
    /**
     * @brief animation_Opacity 并行动画对象组
     */
    QParallelAnimationGroup *animation_Group = nullptr;
public Q_SLOTS:
    /**
     * @brief showMaximized 最大化窗口
     */
    void showMaximized();
    /**
     * @brief showNormal 还原窗口
     */
    void showNormal();
    /**
     * @brief addWidgetToMainArea 将空间添加到主区域
     */
    void addWidgetToMainArea(QWidget *widget);
    /**
     * @brief TargetWindowSize 用于初始化窗体标自定义的题栏样式
     */
    void SetCustomTitleBarStyle(int type);

};

#endif // DECODEBASEWINDOW_H
