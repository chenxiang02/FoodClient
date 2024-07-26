#ifndef _FOOD_CONFIG_H
#define _FOOD_CONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QTimer>
#include "ClientSocket.h"

class FoodConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList foodType READ getFoodType WRITE setFoodType NOTIFY foodTypeChanged)
    Q_PROPERTY(QStringList foodName READ getFoodName WRITE setFoodName NOTIFY foodNameChanged)
    Q_PROPERTY(QStringList foodPrice READ getFoodPrice WRITE setFoodPrice NOTIFY foodPriceChanged)
    Q_PROPERTY(QStringList rangeBackground READ getRangeBackground WRITE setRangeBackground NOTIFY rangeBackgroundChanged)

    Q_PROPERTY(bool LazyLoad READ getLazyLoad WRITE setLazyLoad NOTIFY lazyLoadChanged)

public:
    FoodConfig();
    ~FoodConfig();

    QStringList getFoodType() const;
    void setFoodType(const QStringList value);

    QStringList getFoodName() const;
    void setFoodName(const QStringList value);

    QString MenuIntToString(QString date);//食物种类int转为字符串显示

    bool isSell(QString date);

    //懒加载
    bool getLazyLoad() const;
    void setLazyLoad(bool value);

    //价格
    QStringList getFoodPrice() const;
    void setFoodPrice(const QStringList &value);

    QStringList getRangeBackground() const;
    void setRangeBackground(const QStringList &value);

public slots:
    void unpackMenu(QString date);
    void sendMenuList(QStringList date,QString value);

signals:
    void foodTypeChanged();
    void foodNameChanged();
    void foodPriceChanged();
    void rangeBackgroundChanged();

    void lazyLoadChanged();

public slots:
private:
    QStringList foodType;
    QStringList foodName;
    QStringList foodPrice;
    QStringList rangeBackground;

    QSettings * defaultConfig;
    ClientSocket * socket;
    QTimer * connectControl;
    bool LazyLoad;

};

#endif
