#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include "pitchwindow.h"
#include "SerialPort.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PitchWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    SerialPort _port;

    CustomPlot custom_plot;

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

    void on_btnOpenPitchWindow_clicked();

private:
    //Ui::MainWindow *ui;

    PitchWindow* pitch_window;

    //SerialPort _port;

    void loadPorts();

};
#endif // MAINWINDOW_H
