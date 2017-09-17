#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    p_core = new Core;
    precision_number = 2;
    validate_reg = QRegExp("^[+-]?[\\d]+($|[\\.][\\d]+|([\\.][\\d]+[Ee]|[Ee])[+-]?\\d+)$");

    //menu window
    p_menu_window = new QWidget;
    p_menu_layout = new QGridLayout;
    p_menu_window->setLayout(p_menu_layout);

    p_stacked_widget = new QStackedWidget;
    p_stacked_widget->addWidget(p_menu_window);
    p_stacked_widget->setCurrentWidget(p_menu_window);

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

    p_menu_layout->addWidget(p_add_value_button, 0, 0, 1, 1);
    p_menu_layout->addWidget(p_remove_value_button, 0, 1, 1, 1);
    connect(p_add_value_button, SIGNAL(clicked(bool)), SLOT(addNewElement()));
    connect(p_remove_value_button, SIGNAL(clicked(bool)), SLOT(removeLastElement()));

    p_precision_buttons = new PrecisionGroupBox;
    p_menu_layout->addWidget(p_calculation_values_scroll_area, 1, 0, 4, 2);
    p_menu_layout->addWidget(p_precision_buttons, 1, 2, 4, 2);
    connect(p_precision_buttons, SIGNAL(sendPrecision(int)), SLOT(setPrecision(int)));

    p_start_button = new QPushButton("Start calculating");
    p_menu_layout->addWidget(p_start_button, 5, 1, 1, 2);
    connect(p_start_button, SIGNAL(clicked(bool)), SLOT(startCalculating()));

    p_values_vector = new QVector<ValueElement*>;
    p_values_vector->reserve(10);

    //result window
    p_result_window = new QWidget;
    p_result_window_layout = new QVBoxLayout;
    p_result_window->setLayout(p_result_window_layout);

    p_stacked_widget->addWidget(p_result_window);

    p_middle_value_line = new QLineEdit;
    p_dispersion_line = new QLineEdit;
    p_standart_deviation_line = new QLineEdit;
    p_absolute_deviation_line = new QLineEdit;
    p_relative_deviation_line = new QLineEdit;
    p_final_value_line = new QLineEdit;

    p_middle_value_line->setReadOnly(true);
    p_dispersion_line->setReadOnly(true);
    p_standart_deviation_line->setReadOnly(true);
    p_absolute_deviation_line->setReadOnly(true);
    p_relative_deviation_line->setReadOnly(true);
    p_final_value_line->setReadOnly(true);

    p_middle_value_label = new QLabel("Middle value");
    p_dispersion_label = new QLabel("Dispersion");
    p_standart_deviation_label = new QLabel("Standart deviation");
    p_absolute_deviation_label = new QLabel("Absolute deviation");
    p_relative_deviation_label = new QLabel("Relative");
    p_final_value_label = new QLabel("Final");

    p_close_button = new QPushButton("close");

    p_result_window_layout->addWidget(p_middle_value_label);
    p_result_window_layout->addWidget(p_middle_value_line);

    p_result_window_layout->addWidget(p_dispersion_label);
    p_result_window_layout->addWidget(p_dispersion_line);

    p_result_window_layout->addWidget(p_standart_deviation_label);
    p_result_window_layout->addWidget(p_standart_deviation_line);

    p_result_window_layout->addWidget(p_absolute_deviation_label);
    p_result_window_layout->addWidget(p_absolute_deviation_line);

    p_result_window_layout->addWidget(p_relative_deviation_label);
    p_result_window_layout->addWidget(p_relative_deviation_line);

    p_result_window_layout->addWidget(p_final_value_label);
    p_result_window_layout->addWidget(p_final_value_line);

    p_result_window_layout->addWidget(p_close_button);

    connect(p_core, SIGNAL(sendMiddleValue(QString)), p_middle_value_line, SLOT(setText(QString)));
    connect(p_core, SIGNAL(sendDispersion(QString)), p_dispersion_line, SLOT(setText(QString)));
    connect(p_core, SIGNAL(sendStandartDeviation(QString)), p_standart_deviation_line, SLOT(setText(QString)));
    connect(p_core, SIGNAL(sendAbsoluteDeviation(QString)), p_absolute_deviation_line, SLOT(setText(QString)));
    connect(p_core, SIGNAL(sendRelativeDeviation(QString)), p_relative_deviation_line, SLOT(setText(QString)));
    connect(p_core, SIGNAL(sendFinalValue(QString)), p_final_value_line, SLOT(setText(QString)));
    connect(p_core, SIGNAL(endOfCalculating()), SLOT(showResultWindow()));

    connect(p_close_button, SIGNAL(clicked(bool)), SLOT(showMenuWindow()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::addNewElement()
{
    qDebug() << "add new element";

    ValueElement *p_new_element = new ValueElement(p_values_vector->size() + 1);
    p_values_vector->append(p_new_element);

    p_scroll_area_widget->resize(p_calculation_values_scroll_area->width() - 2, p_scroll_area_widget->height() + p_new_element->height());
    p_scroll_area_layout->addWidget(p_new_element);
}

void MainWindow::removeLastElement()
{
    qDebug() << "remove last element";

    if(!p_values_vector->isEmpty())
    {
        ValueElement *p_element_to_delete = p_values_vector->last();
        p_scroll_area_widget->resize(p_calculation_values_scroll_area->width() - 2, p_scroll_area_widget->height() - p_element_to_delete->height());

        delete p_element_to_delete;
        p_values_vector->pop_back();
    }
}

void MainWindow::setPrecision(int _precision_number)
{
    qDebug() << "set precision " << _precision_number;
    precision_number = _precision_number;
}

void MainWindow::startCalculating()
{
    qDebug() << "start calculating";

    if(p_values_vector->size() == 0 || p_values_vector->size() == 1)
    {
        QMessageBox msg;
        msg.setText("error : nothing to calculate");
        msg.setInformativeText("Add two values or more");
        msg.setStandardButtons(QMessageBox::Ok);

        short result = msg.exec();

        if(result == QMessageBox::Ok)
            return;
    }

    int counter = 1;
    for(QVector<ValueElement*>::iterator iter = p_values_vector->begin(); iter != p_values_vector->end(); ++iter, ++counter)
        if(!(*iter)->p_line_edit->text().contains(validate_reg) > 0)
        {
            QMessageBox msg;
            msg.setText("error : value of line " + QString::number(counter) + " : \"" + (*iter)->p_line_edit->text() + "\" is not correct...");
            msg.setInformativeText("Try to edit it");
            msg.setStandardButtons(QMessageBox::Ok);

            short result = msg.exec();

            if(result == QMessageBox::Ok)
            {
                (*iter)->p_line_edit->setFocus();
                return;
            }
        }

    p_core->startCalculating(p_values_vector->size(), precision_number, p_values_vector);
}

void MainWindow::showResultWindow()
{
    p_stacked_widget->setCurrentWidget(p_result_window);
}

void MainWindow::showMenuWindow()
{
    p_stacked_widget->setCurrentWidget(p_menu_window);
}
