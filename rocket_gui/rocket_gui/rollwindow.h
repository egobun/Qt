#ifndef ROLLWINDOW_H
#define ROLLWINDOW_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include <QThread>
#include "SerialPort.h"
#include "qcustomplot.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class RollWindow;
}

class RollWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RollWindow(MainWindow *mainWin, QWidget *parent = nullptr);
    ~RollWindow();

    CustomPlot custom_plot;

    void plot();

private slots:
    void readData(QByteArray data);

private:
    Ui::RollWindow *ui;
    MainWindow *mainWin; // Указатель на MainWindow
    QThread _rollthread;
};

#endif // ROLLWINDOW_H


