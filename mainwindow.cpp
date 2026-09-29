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

    connect(ui->btnAdd, &QPushButton::clicked,
            this, [this]() {
                inputOperator("+");
            });

    connect(ui->btnSubtract, &QPushButton::clicked,
            this, [this]() {
                inputOperator("-");
            });

    connect(ui->btnMultiply, &QPushButton::clicked,
            this, [this]() {
                inputOperator("*");
            });

    connect(ui->btnDivide, &QPushButton::clicked,
            this, [this]() {
                inputOperator("/");
            });

    connect(ui->btnEqual, &QPushButton::clicked,
            this, &MainWindow::calculateResult);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::inputDigit(const QString &digit)
{
    if (resultDisplayed && currentOperator.isEmpty())
    {
        currentInput = digit;
        resultDisplayed = false;
        ui->display->setText(currentInput);
        return;
    }

    if (waitingForSecondOperand)
    {
        currentInput = digit;
        waitingForSecondOperand = false;
    }
    else
    {
        if (currentInput == "0")
            currentInput = digit;
        else
            currentInput += digit;
    }

    if (currentOperator.isEmpty())
    {
        ui->display->setText(currentInput);
    }
    else
    {
        ui->display->setText(
            QString::number(firstOperand) + " " +
            currentOperator + " " +
            currentInput
            );
    }
}
void MainWindow::inputDecimal()
{
    if (resultDisplayed && currentOperator.isEmpty())
    {
        currentInput = "0.";
        resultDisplayed = false;
        ui->display->setText(currentInput);
        return;
    }

    if (waitingForSecondOperand)
    {
        currentInput = "0.";
        waitingForSecondOperand = false;
    }
    else if (!currentInput.contains('.'))
    {
        currentInput += ".";
    }

    if (currentOperator.isEmpty())
    {
        ui->display->setText(currentInput);
    }
    else
    {
        ui->display->setText(
            QString::number(firstOperand) + " " +
            currentOperator + " " +
            currentInput
            );
    }
}
void MainWindow::backspace()
{
    if (resultDisplayed)
    {
        clearDisplay();
        return;
    }

    if (currentInput.length() > 1)
    {
        currentInput.chop(1);
    }
    else
    {
        currentInput = "0";
    }

    ui->display->setText(currentInput);
}
void MainWindow::clearDisplay()
{
    currentInput = "0";
    firstOperand = 0.0;
    currentOperator.clear();
    waitingForSecondOperand = false;
    resultDisplayed = false;

    ui->display->setText("0");
}
void MainWindow::inputOperator(const QString &op)
{
    if (currentOperator.isEmpty())
    {
        firstOperand = currentInput.toDouble();
    }
    else if (waitingForSecondOperand)
    {

        currentOperator = op;

        ui->display->setText(
            QString::number(firstOperand) + " " +
            currentOperator
            );

        return;
    }
    else
    {
        double secondOperand = currentInput.toDouble();
        double result = 0.0;

        if (!compute(secondOperand, result))
        {
            ui->display->setText("Error");

            currentInput = "0";
            firstOperand = 0.0;
            currentOperator.clear();
            waitingForSecondOperand = false;
            resultDisplayed = true;
            return;
        }

        firstOperand = result;
        currentInput = QString::number(result);
    }

    currentOperator = op;
    waitingForSecondOperand = true;
    resultDisplayed = false;

    ui->display->setText(
        QString::number(firstOperand) + " " +
        currentOperator
        );
}
void MainWindow::calculateResult()
{
    if (currentOperator.isEmpty() || waitingForSecondOperand)
        return;

    double secondOperand = currentInput.toDouble();
    double result = 0.0;

    if (!compute(secondOperand, result))
    {
        ui->display->setText("Error");

        currentInput = "0";
        firstOperand = 0.0;
        currentOperator.clear();
        waitingForSecondOperand = false;
        resultDisplayed = true;

        return;
    }

    currentInput = QString::number(result);

    ui->display->setText(currentInput);

    firstOperand = result;
    currentOperator.clear();
    waitingForSecondOperand = false;
    resultDisplayed = true;
}
bool MainWindow::compute(double secondOperand, double &result)
{
    if (currentOperator == "+")
    {
        result = firstOperand + secondOperand;
    }
    else if (currentOperator == "-")
    {
        result = firstOperand - secondOperand;
    }
    else if (currentOperator == "*")
    {
        result = firstOperand * secondOperand;
    }
    else if (currentOperator == "/")
    {
        if (secondOperand == 0.0)
        {
            return false;
        }

        result = firstOperand / secondOperand;
    }
    else
    {
        return false;
    }

    return true;
}