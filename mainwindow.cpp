#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //menu widget
    p_menu_widget = new QWidget;
    p_menu_layout = new QGridLayout;
    p_menu_widget->setLayout(p_menu_layout);

    p_stacked_widget = new QStackedWidget;
    p_stacked_widget->addWidget(p_menu_widget);
    p_stacked_widget->setCurrentWidget(p_menu_widget);

    setCentralWidget(p_stacked_widget);

    p_calculation_values_scroll_area = new QScrollArea;
    p_scroll_area_widget = new QWidget;
    p_calculation_values_scroll_area->setWidget(p_scroll_area_widget);
    p_scroll_area_layout = new QVBoxLayout;
    p_scroll_area_layout->setMargin(0);
    p_scroll_area_layout->setSpacing(0);
    p_scroll_area_widget->setLayout(p_scroll_area_layout);

    p_add_value_button = new QPushButton("+");
    p_remove_value_button = new QPushButton("-");
//    p_add_value_button->setFlat(true);
//    p_remove_value_button->setFlat(true);

    p_menu_layout->addWidget(p_add_value_button, 0, 0, 1, 1);
    p_menu_layout->addWidget(p_remove_value_button, 0, 1, 1, 1);
    connect(p_add_value_button, SIGNAL(clicked(bool)), SLOT(addNewElement()));
    connect(p_remove_value_button, SIGNAL(clicked(bool)), SLOT(removeLastElement()));

    p_precision_buttons = new PrecisionGroupBox;
    p_menu_layout->addWidget(p_calculation_values_scroll_area, 1, 0, 4, 2);
    p_menu_layout->addWidget(p_precision_buttons, 1, 2, 4, 2);
    connect(p_precision_buttons, SIGNAL(sendPrecision(QString)), SLOT(setPrecision(QString)));

    p_start_button = new QPushButton("Start calculating");
    p_menu_layout->addWidget(p_start_button, 5, 1, 1, 2);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addNewElement()
{
    qDebug() << "add new element";

    QWidget *p_new_element = new QWidget;
    QHBoxLayout *p_new_element_layout = new QHBoxLayout;

    p_new_element->setFixedHeight(70);

    p_new_element->setLayout(p_new_element_layout);

    QLabel *p_new_element_label = new QLabel("11");
    QLineEdit *p_new_element_line_edit = new QLineEdit;

    p_new_element_layout->addWidget(p_new_element_label);
    p_new_element_layout->addWidget(p_new_element_line_edit);

    p_scroll_area_widget->resize(p_calculation_values_scroll_area->width() - 2, p_scroll_area_widget->height() + p_new_element->height());
    p_scroll_area_layout->addWidget(p_new_element);
}

void MainWindow::removeLastElement()
{
    qDebug() << "remove last element";
}

void MainWindow::setPrecision(QString _precision)
{
    qDebug() << "set precision " << _precision;
}

void MainWindow::startCalculating()
{
    qDebug() << "start calculating";
}
