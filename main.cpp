#include <QtCore/QCoreApplication>
#include <QTextStream>

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
        a.exit(1);
    }
    return a.exec();
}
