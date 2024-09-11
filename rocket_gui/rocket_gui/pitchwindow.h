#ifndef PITCHWINDOW_H
#define PITCHWINDOW_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include "pitchwindow.h"
#include "SerialPort.h"
#include "qcustomplot.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class PitchWindow;
}

class PitchWindow : public QDialog
{
    Q_OBJECT

public:
    //explicit PitchWindow(QWidget *parent = nullptr);

    explicit PitchWindow(MainWindow *mainWin, QWidget *parent = nullptr);
    ~PitchWindow();


    CustomPlot custom_plot;

    void plot();

private slots:
    void readData(QByteArray data);

private:
    Ui::PitchWindow *ui;
    MainWindow *mainWin; // Указатель на MainWindow
};

#endif // PITCHWINDOW_H
