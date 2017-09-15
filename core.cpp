#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}

void Core::startCalculating(int n, int precision_number)
{
    if(n <= 10)
        n -= 2;

    double student_value = student_value_table[n][precision_number];
}
