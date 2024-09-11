#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include "SerialPort.h"
#include "qcustomplot.h"

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

    void addPoint(double x, double y);
    void clearData();
    void plot();

private slots:
    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_btnOpenPorts_clicked();

    void on_btnSend_clicked();

    void readData(QByteArray data);

    void on_checkTransmit_stateChanged(int arg1);

    void on_rbtn1Hz_clicked();

    void on_rbtn10Hz_clicked();

    void on_rbtn20Hz_clicked();

private:
    Ui::MainWindow *ui;

    SerialPort _port;
    void loadPorts();

    QVector<double> qv_x,qv_y;
    QVector<double> qv_xx,qv_yy;
};
#endif // MAINWINDOW_H
