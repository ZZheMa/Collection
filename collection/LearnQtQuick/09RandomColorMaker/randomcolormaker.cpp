#include "randomcolormaker.h"
#include <QDateTime>

RandomColorMaker::RandomColorMaker(QObject *parent)
    : QObject(parent)
    , color_(Qt::black)
    , color_timer_(0) {
    qsrand(QDateTime::currentDateTime().toTime_t());
}

void RandomColorMaker::start() {
    if (color_timer_ != 0) {
        return;
    }

    color_timer_ = startTimer(1000);
}

void RandomColorMaker::stop() {
    if (color_timer_ <= 0) {
        return;
    }

    killTimer(color_timer_);
    color_timer_ = 0;
}

void RandomColorMaker::timerEvent(QTimerEvent* evt) {
    if (evt->timerId() != color_timer_) {
        QObject::timerEvent(evt);
        return;
    }

    color_.setRgb(qrand() % 255, qrand() % 255, qrand() % 255);

    emit colorChanged(color_);
    emit currentTimeNotified(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}













