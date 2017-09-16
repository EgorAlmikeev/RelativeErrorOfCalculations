#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QVector>

#include "valueelement.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);

    double student_coefficient_table [14][8] =
         //0,    1,    2,     3,     4,      5
    {
        { 3.080, 6.31, 12.71, 63.70, 127.30, 637.20 }, //0 - 2
        { 1.886, 2.92, 4.30,  9.92,  14.10,  31.60  }, //1 - 3
        { 1.638, 2.35, 3.188, 5.84,  7.50,   12.94  }, //2 - 4
        { 1.533, 2.13, 2.77,  4.60,  5.60,   8.61   }, //3 - 5
        { 1.476, 2.02, 2.57,  4.03,  4.77,   6.86   }, //4 - 6
        { 1.440, 1.94, 2.45,  3.71,  4.32,   9.96   }, //5 - 7
        { 1.415, 1.90, 2.36,  3.50,  4.03,   5.40   }, //6 - 8
        { 1.397, 1.86, 2.31,  3.36,  3.83,   5.04   }, //7 - 9
        { 1.383, 1.83, 2.26,  3.25,  3.69,   4.78   }, //8 - 10
        { 1.363, 1.80, 2.20,  3.11,  3.50,   4.49   }, //9 - 12
        { 1.350, 1.77, 2.16,  3.01,  3.37,   4.22   }, //10 - 14
        { 1.341, 1.75, 2.13,  2.95,  3.29,   4.07   }, //11 - 16
        { 1.333, 1.74, 2.11,  2.90,  3.22,   3.96   }, //12 - 18
        { 1.328, 1.73, 2.09,  2.86,  3.17,   3.88   }  //13 - 20
    };

signals:

    void sendMiddleValue(QString);
    void sendDispersion(QString);
    void sendStandartDeviation(QString);
    void sendAbsoluteDeviation(QString);
    void sendRelativeDeviation(QString);
    void sendFinalValue(QString);

    void endOfCalculating();

public slots:

    void startCalculating(int n, int precision_number, QVector<ValueElement*>*);
};

#endif // CORE_H
