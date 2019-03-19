#include "DecodeAnimation.h"

DecodeAnimation::DecodeAnimation() : QObject ()
{

}

void DecodeAnimation::showAnimation_Appear(int StartWidth, int StartHeight, int EndWidth, int EndHeight, QWidget *object)
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

    /*
     *
     *
    */
}

void DecodeAnimation::showAnimation_Fade(QWidget *object,int begin_Opacity, int end_Opacity)
{
    if(animation_Opacity != nullptr )
    {
        delete animation_Opacity;
        animation_Opacity = nullptr;
    }

    animation_Opacity = new QPropertyAnimation(object, "windowOpacity");
    animation_Opacity->setDuration(300);
    animation_Opacity->setStartValue(begin_Opacity);
    animation_Opacity->setEndValue(end_Opacity);
    animation_Opacity->setEasingCurve(QEasingCurve::OutQuint);
    animation_Opacity->start();
}

void DecodeAnimation::showAnimation_Zoom(QWidget *object)
{
    if(animation_Size != nullptr)
    {
        delete animation_Size;
        animation_Size = nullptr;
    }
    /*
     *
     *
    */
}
