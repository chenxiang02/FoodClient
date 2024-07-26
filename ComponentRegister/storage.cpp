#include "storage.h"

Storage::Storage(QObject *parent):QObject(parent)
{
    this->totalValue = 0;
    this->clearCountFlag = false;
    qDebug()<<Q_FUNC_INFO<<"Storage类构造";
}

Storage::~Storage()
{
    qDebug()<<Q_FUNC_INFO<<"Storage类构造";
}

QStringList Storage::getMenuList() const
{
    return menuList;
}

void Storage::setMenuList(const QStringList &value)
{
    menuList = value;
    emit menuListChanged();
}

void Storage::clearMenuList()
{
    menuList.clear();
    store.clear();
    emit menuListChanged();
}

int Storage::getTotalValue() const
{
    return totalValue;
}

void Storage::setTotalValue(int value)
{
    totalValue = value;
    emit totalValueChanged();
}

void Storage::addTotalValue(QStringList arg)
{
    QString foodname = arg.at(0),count= arg.at(1),price= arg.at(2);
    QString oldCount;
    QStringList vessel;
    int total = getTotalValue();
    QStringList menulist = getMenuList();

    if(store.contains(foodname))
    {
        oldCount = store[foodname].at(0);
        total -=oldCount.toInt() * price.toInt();//减去原本价格
        total +=count.toInt() * price.toInt();//加上新价格

        store[foodname].replace(0,count);//更新store

        int index = menulist.indexOf(foodname);
        menulist.replace(index+1,count);//更新menulist

    }
    else
    {
        vessel<<count<<price;
        store.insert(foodname,vessel);
        menulist<<foodname<<count<<price;
        vessel.clear();
        total += count.toInt() * price.toInt();
    }

    setTotalValue(total);
    setMenuList(menulist);
}

void Storage::subtractValue(QStringList arg)
{
    QString foodname = arg.at(0),count= arg.at(1),price= arg.at(2);
    QString oldCount;
    QStringList vessel;
    int total = getTotalValue();
    QStringList menulist = getMenuList();

    if(store.contains(foodname))//值保护
    {
        if(count.toInt() == 0)
        {
            oldCount = store[foodname].at(0);

            total -= oldCount.toInt() * price.toInt();//更新为最新总价

            store.remove(foodname);//删除原有存储

            //删除原有三个值
            int index = menulist.indexOf(foodname);
            menulist.removeAt(index);
            menulist.removeAt(index);
            menulist.removeAt(index);

        }
        else
        {
            oldCount = store[foodname].at(0);

            total -= oldCount.toInt() * price.toInt();//减去原有价格
            total +=count.toInt() * price.toInt();//更新为最新总价

            store[foodname].replace(0,count);//更新原有存储

            int index = menulist.indexOf(foodname);
            menulist.replace(index+1,count);//更新为最新数量
        }

    }

    setTotalValue(total);
    setMenuList(menulist);
}

bool Storage::getClearCountFlag() const
{
    return clearCountFlag;
}

void Storage::setClearCountFlag(bool value)
{
    clearCountFlag = value;
    emit clearCountFlagChanged();
}
