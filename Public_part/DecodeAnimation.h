#ifndef DECODEANIMATION_H
#define DECODEANIMATION_H

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
class DecodeAnimation : public QObject
{
    Q_OBJECT
public:
    DecodeAnimation();
public:
    /**
     * @brief showAnimation 显示动画_出现动画
     */
    void showAnimation_Appear(int StartWidth, int StartHeight,int EndWidth, int EndHeight, QWidget *object);
    /**
     * @brief showAnimation 显示动画_消失动画
     */
    void showAnimation_Fade(QWidget *object, int begin_Opacity, int end_Opacity);
    /**
     * @brief showAnimation 显示动画_缩放动画
     */
    void showAnimation_Zoom(QWidget *object);
private:
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
};

#endif // DECODEANIMATION_H
