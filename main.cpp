#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

namespace cpu1 {
    extern "C"{
        #include "c_module.h"
    }
}
namespace cpu2 {
    extern "C"{
        #include "c_module.h"
    }
}
int foo1(int somevalue){
   cpu1::set_a(somevalue);
   cpu1::inc_a();
   return cpu1::get_a();
}
int foo2(int somevalue){
   cpu2::set_a(somevalue);
   cpu2::inc_a();
   return cpu2::get_a();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"testprogramm started";

    /* starting test */
    int myinput1 = 1,myoutput1;
    int myinput2 = 8,myoutput2;
    QFuture<int> future1 = QtConcurrent::run(foo1,myinput1);
    QFuture<int> future2 = QtConcurrent::run(foo2,myinput2);
    future1.waitForFinished();
    future2.waitForFinished();
    myoutput1 = future1.result();
    myoutput2 = future2.result();
    qDebug()<<"input 1 was:"<<myinput1<<"\toutput 1 was:"<<myoutput1;
    qDebug()<<"input 2 was:"<<myinput2<<"\toutput 2 was:"<<myoutput2;

    qDebug()<<"testprogramm ended";
    return a.exec();
}
