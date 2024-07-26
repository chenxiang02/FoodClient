#include "foodconfig.h"


FoodConfig::FoodConfig()
{
    this->defaultConfig = new QSettings("Food.ini",QSettings::IniFormat);

    this->socket = new ClientSocket;

    connectControl = new QTimer(this);
    connectControl->setInterval(1000);
    connect(connectControl,&QTimer::timeout,this,[&]{
        if(!this->socket->IsConnected())
        {
            this->socket->ConnectedServe();
            setLazyLoad(this->socket->IsConnected());
        }
        else
        {
            this->connectControl->stop();
            setLazyLoad(true);
        }
    });

    this->socket->clientSocketInit();//连接

    connectControl->start();

    connect(socket,&ClientSocket::connectSuccess,this,[&]{
          this->socket->SendData("SQL Requsted Find menuList");
    });

    connect(socket,&ClientSocket::returnSQLMenuFind,this,&FoodConfig::unpackMenu);


    qDebug()<<Q_FUNC_INFO<<"FoodConfig类构造";
}

FoodConfig::~FoodConfig()
{
    delete  this->defaultConfig;
    delete  this->socket;
    qDebug()<<Q_FUNC_INFO<<"FoodConfig类构造";
}

QStringList FoodConfig::getFoodType() const
{
    return this->foodType;
}

void FoodConfig::setFoodType(const QStringList value)
{
   this->foodType = value;
   emit foodTypeChanged();
}

QStringList FoodConfig::getFoodName() const
{
    return this->foodName;
}

void FoodConfig::setFoodName(const QStringList value)
{
    this->foodName = value;
    emit foodNameChanged();
}

QString FoodConfig::MenuIntToString(QString date)
{
    if(date == "0")
        return QString("汤类");
    else if(date == "1")
        return QString("肉类");
    else if(date == "2")
        return QString("蔬菜");
    return "null";
}

bool FoodConfig::isSell(QString date)
{
    return date.toInt();
}

void FoodConfig::unpackMenu(QString date)
{
    int length = date.length();

    QStringList foodName;
    QStringList foodType;
    QStringList foodPrice;
    QStringList typeIndex;
    QStringList rangeValue;
    rangeValue<<"0";

    int TypeIndex = 0;

    QString strFood;
    QString strBear;

    for(int i = 0,index = 0;i < length;i++)//遍历返回值 按协议拼接
    {
        if(date[i]=="|")
        {
            if(index==0)//食物名
            {
                strBear = strFood;
                foodName<<strBear;
            }
            else if(index == 2)//食物类型
            {
                strBear = MenuIntToString(strFood);
                if(!foodType.contains(strBear))
                {
                    foodType<<strBear;
                    typeIndex<<QString::number(TypeIndex);
                }
                TypeIndex++;
            }
            else if(index == 3)
            {
                strBear = strFood;
                foodPrice<<strBear;
            }
            strFood.clear();
            index++;
            continue;
        }
        if(date[i]=='/')
        {
            index = 0;
            strFood.clear();
            continue;
        }

        strFood +=date[i];//拼接内容
    }
    typeIndex<<QString::number(TypeIndex);

    for(int i = 1;i<typeIndex.size();i++)
        rangeValue<<QString::number(typeIndex.at(i).toInt() * 60 -10);

    qDebug()<<rangeValue;

    setFoodName(foodName);
    setFoodType(foodType);
    setFoodPrice(foodPrice);
    setRangeBackground(rangeValue);
}

void FoodConfig::sendMenuList(QStringList date,QString value)
{
    int length = date.length();
    QString SendPack;
    SendPack.append("Food List");//添加包头

    int index = 0;
    for(int i = 0;i < length;i++)
    {
        if(index == 2)
        {
            SendPack.append(date.at(i));
            SendPack.append('/');
            index = 0;
            continue;
        }else
        {
            SendPack.append(date.at(i));
            SendPack.append('|');
        }
        index++;
    }

    SendPack.append("+"+value+"+");

    SendPack.append("List End");//添加包尾

    this->socket->SendData(SendPack);//发送包

}

QStringList FoodConfig::getRangeBackground() const
{
    return rangeBackground;
}

void FoodConfig::setRangeBackground(const QStringList &value)
{
    rangeBackground = value;
    emit rangeBackgroundChanged();
}


QStringList FoodConfig::getFoodPrice() const
{
    return foodPrice;
}

void FoodConfig::setFoodPrice(const QStringList &value)
{
    foodPrice = value;
    emit foodPriceChanged();
}

bool FoodConfig::getLazyLoad() const
{
    return LazyLoad;
}

void FoodConfig::setLazyLoad(bool value)
{
    LazyLoad = value;
    emit lazyLoadChanged();
}

