#include <iostream>
#include <QCoreApplication>
#include "CRootComponent.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CRootComponent root;

    root.requestBoot();

    return a.exec();
}
