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

//#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include <tcpinstrument.h>

#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtScript/QScriptEngine>
#include <QtGui/QMessageBox>

void foo(void){
    throw "Error in foo";
}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    QApplication a(argc, argv);
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
        socket.close();
    }catch(const char* errorMessage) {
        cerr << errorMessage << endl;
    }

//    cout << "TcpInstrument test" << endl;
//    try{
//        TcpInstrument *inst = new TcpInstrument(QHostAddress("192.168.0.72"));
//        cout << inst->sendReceive("*IDN?\n").trimmed() << endl;
//    }catch(const char* errorMessage) {
//        cerr << errorMessage << endl;
//    }

    cout << "Script test" << endl;
    QScriptEngine engine;
    QPushButton button;
    QScriptValue scriptButton = engine.newQObject(&button);
    engine.globalObject().setProperty("button", scriptButton);
    QByteArray script="button.text = 'Hello World!';\nbutton.styleSheet = 'font-style: italic';\nbutton.show();";
    QScriptValue result = engine.evaluate(script);
    if (result.isError()) {
        QMessageBox::critical(0, "Hello Script",
                              QString::fromLatin1("%0: %1")
                              .arg(result.property("lineNumber").toInt32())
                              .arg(result.toString()));
        return -1;
    }

    cout << "end." << endl;
    a.exec();
}
