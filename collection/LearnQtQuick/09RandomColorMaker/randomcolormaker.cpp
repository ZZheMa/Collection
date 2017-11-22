#include "randomcolormaker.h"
#include <QDateTime>

RandomColorMaker::RandomColorMaker(QObject *parent)
    : QObject(parent)
    , color_(Qt::black)
    , color_timer_(0)
    , color_algorithm_(RandomColorRed) {
    qsrand(QDateTime::currentDateTime().toTime_t());
}

QColor RandomColorMaker::color() const {
    return color_;
}

void RandomColorMaker::setColor(const QColor& color) {
    color_ = color;
    emit colorChanged(color);
}

RandomColorMaker::RandomColorAlgorithm RandomColorMaker::colorAlgorithm() const {
    return color_algorithm_;
}

void RandomColorMaker::setColorAlgorithm(RandomColorMaker::RandomColorAlgorithm color_algorithm) {
    color_algorithm_ = color_algorithm;
}

QColor RandomColorMaker::timeColor() const {
    QTime time = QTime::currentTime();
    int red = time.hour();
    int green = time.minute() * 2;
    int blue = time.second() * 4;
    return QColor::fromRgb(red, green, blue);
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

    UpdateColor();

    emit colorChanged(color_);
    emit currentTimeNotified(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void RandomColorMaker::UpdateColor() {
    if (color_algorithm_ == RandomColorRed) {
        color_.setRed(qrand() % 255);
        color_.setGreen(0);
        color_.setBlue(0);
    } else if (color_algorithm_ == RandomColorGreen) {
        color_.setRed(0);
        color_.setGreen(qrand() % 255);
        color_.setBlue(0);
    } else if (color_algorithm_ == RandomColorBlue) {
        color_.setRed(0);
        color_.setGreen(0);
        color_.setBlue(qrand() % 255);
    } else if (color_algorithm_ == RandomColorRgb) {
        color_.setRgb(qrand() % 255, qrand() % 255, qrand() % 255);
    } else if (color_algorithm_ == RandomColorLinearIncrease) {
        int red = color_.red() + 10;
        int green = color_.green() + 10;
        int blue = color_.blue() + 10;
        color_.setRgb(red % 255, green % 255, blue % 255);
    }
}













