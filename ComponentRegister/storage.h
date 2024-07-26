#ifndef _STORAGE_H
#define _STORAGE_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QString>
#include <QDebug>

class Storage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList menuList READ getMenuList WRITE setMenuList NOTIFY menuListChanged)
    Q_PROPERTY(int totalValue READ getTotalValue WRITE setTotalValue NOTIFY totalValueChanged)
    Q_PROPERTY(int clearCountFlag READ getClearCountFlag WRITE setClearCountFlag NOTIFY clearCountFlagChanged)

public:
    Storage(QObject * parent = nullptr);
    ~Storage();

    QStringList getMenuList() const;
    void setMenuList(const QStringList &value);
    Q_INVOKABLE void clearMenuList();

    int getTotalValue() const;
    void setTotalValue(int value);

    Q_INVOKABLE void addTotalValue(QStringList arg);
    Q_INVOKABLE void subtractValue(QStringList arg);

    bool getClearCountFlag() const;
    void setClearCountFlag(bool value);

signals:
    void menuListChanged();
    void totalValueChanged();
    void clearCountFlagChanged();
private:
    QStringList menuList;
    int totalValue;
    bool clearCountFlag;

    QMap<QString,QStringList> store;//牺牲内存空间换执行速度

};

#endif
