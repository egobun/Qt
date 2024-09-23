#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include <QThread>
#include "pitchwindow.h"
#include "rollwindow.h"
#include "SerialPort.h"
#include "qcustomplot.h"
#include "dataprocessor.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PitchWindow;

class RollWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    SerialPort _port;

    CustomPlot custom_plot;

    CustomPlot custom_pitch_plot;

    CustomPlot custom_roll_plot;

    CustomPlot custom_yaw_plot;

    CustomPlot custom_d_pitch_plot;

    CustomPlot custom_d_roll_plot;

    CustomPlot custom_d_yaw_plot;

    CustomPlot custom_temperature_plot;

    CustomPlot custom_battery_voltage_plot;

    void plot(QCustomPlot *plot, CustomPlot custom_plot);

private slots:


    void on_btnOpenPorts_clicked();

    void on_btnSend_clicked();

    void readData(QByteArray data, const QString x_data, const QString y_data);

    void readData_pitch(QByteArray data, QString x_data, QString y_data);

    void readData_roll(QByteArray data, QString x_data, QString y_data);

    void readData_yaw(QByteArray data);

    void readData_d_pitch(QByteArray data, QString x_data, QString y_data);

    void readData_d_roll(QByteArray data, QString x_data, QString y_data);

    void readData_d_yaw(QByteArray data, QString x_data, QString y_data);

    void readData_temperature(QByteArray data, QString x_data, QString y_data);

    void readData_battery_voltage(QByteArray data, QString x_data, QString y_data);


    void on_checkTransmit_stateChanged(int arg1);

    void on_rbtn1Hz_clicked();

    void on_rbtn10Hz_clicked();

    void on_rbtn20Hz_clicked();

    void on_btnOpenPitchWindow_clicked();

    void on_checkAltitude_stateChanged(int arg1);

    void on_checkPitch_stateChanged(int arg1);

    void on_btnOpenRollWindow_clicked();

    void on_checkRoll_stateChanged(int arg1);

    void on_tabWidget_currentChanged(int index);

    void on_rbtn15Hz_clicked();

    void on_checkYaw_stateChanged(int arg1);

    void on_checkD_Pitch_stateChanged(int arg1);

    void on_checkD_Roll_stateChanged(int arg1);

    void on_checkD_Yaw_stateChanged(int arg1);

    void on_checkTemperature_stateChanged(int arg1);

    void on_checkBattery_voltage_stateChanged(int arg1);

private:
    //Ui::MainWindow *ui;

    PitchWindow* pitch_window;

    RollWindow* roll_window;

    //SerialPort _port;

    void loadPorts();

};
#endif // MAINWINDOW_H
