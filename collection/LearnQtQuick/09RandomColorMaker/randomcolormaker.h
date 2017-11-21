#ifndef RANDOMCOLORMAKER_H
#define RANDOMCOLORMAKER_H

#include <QObject>
#include <QColor>
#include <QTimerEvent>

class RandomColorMaker : public QObject
{
    Q_OBJECT
public:
    explicit RandomColorMaker(QObject *parent = nullptr);

signals:
    void colorChanged(const QColor& color);
    void currentTimeNotified(const QString& time);

public slots:
    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent* evt);

private:
    QColor color_;
    int color_timer_;
};

#endif // RANDOMCOLORMAKER_H
