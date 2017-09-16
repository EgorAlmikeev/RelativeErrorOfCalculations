#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}

void Core::startCalculating(int n, int precision_number)
{
    int row, col;
    col = precision_number;

    if(n <= 10)
        row = n - 2;
    else if(n > 10 && n < 20)
    {
        if(n < 20)
            row = 12;
        if(n < 18)
            row = 11;
        if(n < 16)
            row = 10;
        if(n < 14)
            row = 9;
        if(n < 12)
            row = 8;
    }
    else if(n >= 20)
        row = 13;

    double student_value = student_value_table[row][col];
}
