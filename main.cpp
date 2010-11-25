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

void foo(void){
    throw "Error in foo";
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //a.exec();
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    cout << "hello world" << endl;
    try{
        foo();
    }catch(const char* errorMessage) {
        cerr << errorMessage << endl;
        return 1;
    }    
    cout << "end" << endl;
}
