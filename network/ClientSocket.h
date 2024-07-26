 #ifndef _CLIENT_SOCKET_H
#define _CLIENT_SOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    ClientSocket();
    ~ClientSocket();
    Q_INVOKABLE void clientSocketInit();
    void SendData(QString data);

    //连接判断
    bool IsConnected() const;

    void ConnectedServe() const;

public slots:
    void ReiveData();

signals:
    void connectSuccess();
    void returnSQLMenuFind(QString date);

private:
    QTcpSocket * clientIndex;
    bool IsConnect;
    QString date;//相当于读取数据缓存区
    QString lastSend;//保存上次发送信息 如果不对则要求重传
};

#endif
