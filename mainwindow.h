#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void inputDigit(const QString &digit);
    void inputDecimal();
    void backspace();
    void clearDisplay();

    void inputOperator(const QString &op);
    void calculateResult();

    double firstOperand = 0.0;
    QString currentOperator;
    bool waitingForSecondOperand = false;
    QString currentInput = "0";
    bool resultDisplayed = false;
};

#endif // MAINWINDOW_H