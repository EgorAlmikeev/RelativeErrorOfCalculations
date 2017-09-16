#include "core.h"
#include <math.h>

Core::Core(QObject *parent) : QObject(parent)
{

}

void Core::startCalculating(int n, int precision_number, QVector<ValueElement*>* p_values_vector)
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
    else row = 13;

    double student_coefficient = student_coefficient_table[row][col];

    double x_0 = p_values_vector->first()->p_line_edit->text().toDouble();

    for(QVector<ValueElement*>::iterator iter = p_values_vector->begin(); iter != p_values_vector->end(); ++iter)
        x_0 = ((*iter)->p_line_edit->text().toDouble() < x_0) ? (*iter)->p_line_edit->text().toDouble() : x_0;

    double sum;

    //middle value calc
    sum = 0.0;
    for(QVector<ValueElement*>::iterator iter = p_values_vector->begin(); iter != p_values_vector->end(); ++iter)
        sum += (*iter)->p_line_edit->text().toDouble() - x_0;

    double middle_value = x_0 + sum / (double)n;
    emit sendMiddleValue(QString::number(middle_value));

    //dispersion calc
    sum = 0.0;
    for(QVector<ValueElement*>::iterator iter = p_values_vector->begin(); iter != p_values_vector->end(); ++iter)
        sum += ((*iter)->p_line_edit->text().toDouble() - x_0) * ((*iter)->p_line_edit->text().toDouble() - x_0);

    double dispersion = (sum - n * (middle_value - x_0) * (middle_value - x_0)) / (n * (n - 1));
    emit sendDispersion(QString::number(dispersion));

    //standart deviation calc
    double standart_deviation = sqrt(dispersion);
    emit sendStandartDeviation(QString::number(standart_deviation));

    //absolute deviation calc
    double absolute_deviation = student_coefficient * standart_deviation;
    emit sendAbsoluteDeviation(QString::number(absolute_deviation));

    //relative calc
    double relative = absolute_deviation / middle_value * 100.0;
    emit sendRelativeDeviation(QString::number(relative) + "%");

    emit sendFinalValue(QString::number(middle_value) + " +- " + QString::number(absolute_deviation));

    emit endOfCalculating();
}
