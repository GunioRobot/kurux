#include "tcpinstrument.h"

TcpInstrument::TcpInstrument(QObject *parent) :
    QObject(parent)
{
}

TcpInstrument::TcpInstrument(const QHostAddress &address, quint16 port){
    socket.connectToHost(address, port, QTcpSocket::ReadWrite);
}

TcpInstrument::TcpInstrument(const QHostAddress &address){
    socket.connectToHost(address, 5025, QTcpSocket::ReadWrite);
}

void
TcpInstrument::send(QByteArray data){
    if(!socket.waitForConnected(timeout)){
        throw "cannot connect";
    }
    socket.write(data);
    if(!socket.waitForBytesWritten(timeout)){
        throw "cannot write";
    }
}

QByteArray
TcpInstrument::sendReceive(QByteArray data){
    send(data);
    if(!socket.waitForReadyRead(timeout)){
        throw "cannot read";
    }
    return socket.readLine(255);
}

