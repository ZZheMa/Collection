#ifndef RANDOMCOLORMAKER_H
#define RANDOMCOLORMAKER_H

#include <QObject>
#include <QColor>
#include <QTimerEvent>

class RandomColorMaker : public QObject
{
    Q_OBJECT
    Q_ENUMS(RandomColorAlgorithm)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor)

public:
    enum RandomColorAlgorithm {
        RandomColorRed,
        RandomColorGreen,
        RandomColorBlue,
        RandomColorRgb,
        RandomColorLinearIncrease,
        RandomColorCount
    };

public:
    explicit RandomColorMaker(QObject *parent = nullptr);

    QColor color() const;
    void setColor(const QColor& color);

    Q_INVOKABLE RandomColorAlgorithm colorAlgorithm() const;
    Q_INVOKABLE void setColorAlgorithm(RandomColorAlgorithm color_algorithm);

    QColor timeColor() const;

signals:
    void colorChanged(const QColor& color);
    void currentTimeNotified(const QString& time);

public slots:
    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent* evt);
private:
    void UpdateColor();

private:
    RandomColorAlgorithm color_algorithm_;
    QColor color_;
    int color_timer_;
};

#endif // RANDOMCOLORMAKER_H
