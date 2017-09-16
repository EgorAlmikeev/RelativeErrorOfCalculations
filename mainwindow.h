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

#include "valueelement.h"
#include "core.h"

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

    PrecisionGroupBox()
    {
        setTitle("Precision");

        p_layout = new QVBoxLayout;
        setLayout(p_layout);

        p_precision_button_1 = new QRadioButton("0.80");
        p_precision_button_2 = new QRadioButton("0.90");
        p_precision_button_3 = new QRadioButton("0.95");
        p_precision_button_4 = new QRadioButton("0.99");
        p_precision_button_5 = new QRadioButton("0.995");
        p_precision_button_6 = new QRadioButton("0.999");

        p_layout->addWidget(p_precision_button_1);
        p_layout->addWidget(p_precision_button_2);
        p_layout->addWidget(p_precision_button_3);
        p_layout->addWidget(p_precision_button_4);
        p_layout->addWidget(p_precision_button_5);
        p_layout->addWidget(p_precision_button_6);

        p_mapper = new QSignalMapper();

        p_mapper->setMapping(p_precision_button_1, 0);
        p_mapper->setMapping(p_precision_button_2, 1);
        p_mapper->setMapping(p_precision_button_3, 2);
        p_mapper->setMapping(p_precision_button_4, 3);
        p_mapper->setMapping(p_precision_button_5, 4);
        p_mapper->setMapping(p_precision_button_6, 5);

        connect(p_precision_button_1, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_2, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_3, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_4, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_5, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));
        connect(p_precision_button_6, SIGNAL(clicked(bool)), p_mapper, SLOT(map()));

        connect(p_mapper, SIGNAL(mapped(int)), this, SIGNAL(sendPrecision(int)));
    }

signals:

    void sendPrecision(int);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStackedWidget *p_stacked_widget;

    Core *p_core;

    int precision_number;

    //menu widgets

    QWidget *p_menu_window;
    QGridLayout *p_menu_layout;

    QScrollArea *p_calculation_values_scroll_area;
    QWidget *p_scroll_area_widget;
    QVBoxLayout *p_scroll_area_layout;

    QPushButton *p_add_value_button;
    QPushButton *p_remove_value_button;
    QPushButton *p_start_button;

    PrecisionGroupBox *p_precision_buttons;

    QVector<ValueElement*> *p_values_vector;

    //result window widgets
    QWidget *p_result_window;
    QVBoxLayout *p_result_window_layout;

    QLineEdit *p_middle_value_line;
    QLineEdit *p_dispersion_line;
    QLineEdit *p_standart_deviation_line;
    QLineEdit *p_absolute_deviation_line;
    QLineEdit *p_relative_deviation_line;
    QLineEdit *p_final_value_line;

    QLabel *p_middle_value_label;
    QLabel *p_dispersion_label;
    QLabel *p_standart_deviation_label;
    QLabel *p_absolute_deviation_label;
    QLabel *p_relative_deviation_label;
    QLabel *p_final_value_label;

    QPushButton *p_close_button;


public slots:

    void addNewElement();
    void removeLastElement();
    void setPrecision(int);
    void startCalculating();
    void showResultWindow();
    void showMenuWindow();
};

#endif // MAINWINDOW_H
