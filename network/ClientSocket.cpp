#include "ClientSocket.h"

ClientSocket::ClientSocket()
{
    this->IsConnect = false;
    qDebug()<<Q_FUNC_INFO<<"ClientSocket类构造";
}

ClientSocket::~ClientSocket()
{
    this->clientIndex->close();
    qDebug()<<Q_FUNC_INFO<<"ClientSocket类析构";
}

void ClientSocket::clientSocketInit()
{
    this->clientIndex = new QTcpSocket(this);
    this->clientIndex->connectToHost("127.0.0.1",6666);
    connect(clientIndex,&QTcpSocket::connected,this,[&]{
        this->IsConnect = true;
        emit connectSuccess();
    });
    connect(clientIndex,&QTcpSocket::readyRead,this,&ClientSocket::ReiveData);
}

void ClientSocket::SendData(QString data)
{
    if(!this->IsConnect)
    {
        qDebug()<<Q_FUNC_INFO<<"连接未成功,请耐心等待";
        return;
    }

    this->clientIndex->write(data.toUtf8());
    lastSend = data;
}

bool ClientSocket::IsConnected() const
{
    return this->IsConnect;
}

void ClientSocket::ConnectedServe() const
{
    this->clientIndex->connectToHost("127.0.0.1",6666);
}

void ClientSocket::ReiveData()
{
    date = QString::fromUtf8(this->clientIndex->readAll());

    if(!date.contains("10101111")|| !date.contains("01011111"))//如果不包含协议头和协议尾,则要求重传
        this->clientIndex->write(lastSend.toUtf8());

    date.remove(0,8);//删除协议头
    date.remove(date.length() - 8,8);//删除协议尾

    if(date.contains("|10000010|"))
    {
        date.remove(date.length() - 10,10);
        emit returnSQLMenuFind(date);
        date.clear();
    }
}
