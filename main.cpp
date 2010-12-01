/*
Copyright (c) 2010 Albert Kurucz.

This file, main.c is part of Kurux.

Kurux is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kurux is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Kurux.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include <tcpinstrument.h>

void foo(void){
    throw "Error in foo";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    cout << "hello world" << endl;
    try{
        foo();
    }catch(const char* errorMessage) {
        cerr << errorMessage << endl;
    }
    cout << "network test" << endl;
    try{
        QTcpSocket socket;
        socket.connectToHost("192.168.0.73", 5025, QTcpSocket::ReadWrite);
        if(!socket.waitForConnected(2000)){
            throw "cannot connect";
        }
        cout << "connected." << endl;
        socket.write("*IDN?\n");
        cout << "waiting to write." << endl;
        if(!socket.waitForBytesWritten(1000)){
            throw "cannot write";
        }
        cout << "writing done." << endl;
        cout << "waiting to read" << endl;
        if(!socket.waitForReadyRead(2000)){
            throw "cannot read";
        }
        int a=socket.bytesAvailable();
        cout << "available: " << a << endl;
        cout << "reading..." << endl;
        QByteArray r=socket.readLine(255);
        cout << "reading done. Length: " << r.length() << endl;
        QByteArray rt=r.trimmed();
        cout << "Trimmed length: " << rt.length() << endl;
        if(rt.length() > 0){
            cout << rt << endl;
        }
    }catch(const char* errorMessage) {
        cerr << errorMessage << endl;
        //return 1;
    }

    cout << "TcpInstrument test" << endl;
    TcpInstrument inst;

    cout << inst.sendReceive("*IDN?\n").trimmed() << endl;
    cout << "end." << endl;
    a.exec();
}
