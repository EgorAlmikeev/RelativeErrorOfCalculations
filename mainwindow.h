#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QRadioButton>
#include <QVector>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

#include <QDebug>

class PrecisionGroupBox : public QGroupBox
{
    Q_OBJECT

public:

    QSignalMapper *p_mapper;

    QVBoxLayout *p_layout;

    QRadioButton *p_precision_button_1;
    QRadioButton *p_precision_button_2;
    QRadioButton *p_precision_button_3;
    QRadioButton *p_precision_button_4;
    QRadioButton *p_precision_button_5;
    QRadioButton *p_precision_button_6;
    QRadioButton *p_precision_button_7;
    QRadioButton *p_precision_button_8;

    PrecisionGroupBox()
    {
        setTitle("Precision");

        p_layout = new QVBoxLayout;
        setLayout(p_layout);

        p_precision_button_1 = new QRadioButton("0.80");
        p_precision_button_2 = new QRadioButton("0.90");
        p_precision_button_3 = new QRadioButton("0.95");
        p_precision_button_4 = new QRadioButton("0.98");
        p_precision_button_5 = new QRadioButton("0.99");
        p_precision_button_6 = new QRadioButton("0.995");
        p_precision_button_7 = new QRadioButton("0.998");
        p_precision_button_8 = new QRadioButton("0.999");

        p_layout->addWidget(p_precision_button_1);
        p_layout->addWidget(p_precision_button_2);
        p_layout->addWidget(p_precision_button_3);
        p_layout->addWidget(p_precision_button_4);
        p_layout->addWidget(p_precision_button_5);
        p_layout->addWidget(p_precision_button_6);
        p_layout->addWidget(p_precision_button_7);
        p_layout->addWidget(p_precision_button_8);

        p_mapper = new QSignalMapper();

        p_mapper->setMapping(p_precision_button_1, "0.80");
        p_mapper->setMapping(p_precision_button_2, "0.90");
        p_mapper->setMapping(p_precision_button_3, "0.95");
        p_mapper->setMapping(p_precision_button_4, "0.98");
        p_mapper->setMapping(p_precision_button_5, "0.99");
        p_mapper->setMapping(p_precision_button_6, "0.995");
        p_mapper->setMapping(p_precision_button_7, "0.998");
        p_mapper->setMapping(p_precision_button_8, "0.999");

        connect(p_precision_button_1, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_2, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_3, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_4, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_5, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_6, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_7, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_8, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));

        connect(p_mapper, SIGNAL(mapped(QString)), this, SIGNAL(sendPrecision(QString)));
    }

signals:

    void sendPrecision(QString);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //menu widgets
    QStackedWidget *p_stacked_widget;

    QWidget *p_menu_widget;
    QGridLayout *p_menu_layout;

    QScrollArea *p_calculation_values_scroll_area;
    QWidget *p_scroll_area_widget;
    QVBoxLayout *p_scroll_area_layout;

    QPushButton *p_add_value_button;
    QPushButton *p_remove_value_button;
    QPushButton *p_start_button;

    PrecisionGroupBox *p_precision_buttons;

    //result window widgets

public slots:

    void addNewElement();
    void removeLastElement();
    void setPrecision(QString);
    void startCalculating();
};

#endif // MAINWINDOW_H
