#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *digitButtons[] = {
        ui->btn0,
        ui->btn1,
        ui->btn2,
        ui->btn3,
        ui->btn4,
        ui->btn5,
        ui->btn6,
        ui->btn7,
        ui->btn8,
        ui->btn9
    };

    for (QPushButton *button : digitButtons)
    {
        connect(button, &QPushButton::clicked,
                this, [this, button]() {
                    inputDigit(button->text());
                });
    }

    connect(ui->btnDecimal, &QPushButton::clicked,
            this, &MainWindow::inputDecimal);

    connect(ui->btnBackspace, &QPushButton::clicked,
            this, &MainWindow::backspace);

    connect(ui->btnClear, &QPushButton::clicked,
            this, &MainWindow::clearDisplay);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::inputDigit(const QString &digit)
{
    QString text = ui->display->text();

    if (text == "0")
    {
        ui->display->setText(digit);
    }
    else
    {
        ui->display->setText(text + digit);
    }
}
void MainWindow::inputDecimal()
{
    QString text = ui->display->text();

    if (!text.contains('.'))
    {
        ui->display->setText(text + ".");
    }
}
void MainWindow::backspace()
{
    QString text = ui->display->text();

    if (text.length() > 1)
    {
        text.chop(1);
        ui->display->setText(text);
    }
    else
    {
        ui->display->setText("0");
    }
}
void MainWindow::clearDisplay()
{
    ui->display->setText("0");
}