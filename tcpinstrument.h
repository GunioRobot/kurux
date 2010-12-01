#ifndef TCPINSTRUMENT_H
#define TCPINSTRUMENT_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

class TcpInstrument : public QObject
{
    Q_OBJECT
public:
    explicit TcpInstrument(QObject *parent = 0);
    TcpInstrument(const QHostAddress &address, quint16 port);
    TcpInstrument(const QHostAddress &address);
    void setTimeout(int newTimeout);
    void send(QByteArray data);
    QByteArray sendReceive(QByteArray data);
signals:

public slots:

private:
    QTcpSocket socket;
    int timeout;
};

#endif // TCPINSTRUMENT_H
