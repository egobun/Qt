#include "rollwindow.h"
#include "ui_rollwindow.h"

RollWindow::RollWindow(MainWindow *mainWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::RollWindow), mainWin(mainWin) {
    ui->setupUi(this);
    custom_plot.configurePlot(ui->roll_plot, "Крен, [°]", "Время, [с]");
    connect(&(mainWin->_port), &SerialPort::dataReceived,this,&RollWindow::readData);
    this->moveToThread(&_rollthread);
    _rollthread.start();
}

RollWindow::~RollWindow()
{
    delete ui;
}

void RollWindow::plot()
{
    ui->roll_plot->graph(0)->setData(custom_plot.qv_x,custom_plot.qv_y);
    ui->roll_plot->replot();
    ui->roll_plot->update();
}

void RollWindow::readData(QByteArray data)
{

    QString x_data; // Второе значение (число с плавающей точкой)
    QString y_data;
    // Преобразуем QByteArray в QString
    QString stringData = QString::fromUtf8(data);

    // Разделяем строку на части по пробелу
    QStringList dataList = stringData.split(' ', QString::SkipEmptyParts);

    QVector<QStringList> result;

    for (const QString& item : dataList) {
        // Разделяем каждый элемент по двоеточию
        QStringList keyValue = item.split(':', QString::SkipEmptyParts);
        if (keyValue.size() == 2) {
            // Добавляем в результирующий вектор
            QStringList pair;
            pair.append(keyValue[0].trimmed());
            pair.append(keyValue[1].trimmed());
            result.append(pair);
        }
    }

    for (const QStringList& pair : result) {
        if(pair[0] == "time"){
            x_data = pair[1];
        }
        if(pair[0] == "roll"){
            y_data = pair[1];
        }
    }

    if(x_data != "" && y_data != ""){
        ui->roll_plot->xAxis->setRange(x_data.toFloat()-5,x_data.toFloat()+5);
        if(y_data.toFloat() > 0){
            ui->roll_plot->yAxis->setRange(0,y_data.toFloat()+8);
        } else {
            ui->roll_plot->yAxis->setRange(0,y_data.toFloat()-8);
        }

        custom_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot();

}



