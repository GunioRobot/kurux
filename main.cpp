#include <QtCore/QCoreApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << "hello" << endl;
    return a.exec();
}
