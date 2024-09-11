#include "pitchwindow.h"
#include "ui_pitchwindow.h"

PitchWindow::PitchWindow(MainWindow *mainWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::PitchWindow), mainWin(mainWin) {
    ui->setupUi(this);
    custom_plot.configurePlot(ui->pitch_plot, "Тангаж, [°]", "Время, [с]");
    connect(&(mainWin->_port), &SerialPort::dataReceived,this,&PitchWindow::readData);
}

PitchWindow::~PitchWindow()
{
    delete ui;
}

void PitchWindow::plot()
{
    ui->pitch_plot->graph(0)->setData(custom_plot.qv_x,custom_plot.qv_y);
    ui->pitch_plot->replot();
    ui->pitch_plot->update();
}

void PitchWindow::readData(QByteArray data)
{

    QString x_data; // Второе значение (число с плавающей точкой)
    QString y_data;
    // Преобразуем QByteArray в QString
    QString stringData = QString::fromUtf8(data);

    // Разделяем строку на части по пробелу
    QStringList dataList = stringData.split(' ', QString::SkipEmptyParts);

    // Проверяем, что получено достаточно данных
    if (dataList.size() >= 5) {
        // Извлекаем второе и пятое значения
        x_data = dataList[1]; // Второе значение (число с плавающей точкой)
        y_data = dataList[4]; // Пятое значение
    }

    if(x_data != "" && y_data != ""){
        ui->pitch_plot->xAxis->setRange(x_data.toFloat()-5,x_data.toFloat()+5);
        if(y_data.toFloat() > 0){
            ui->pitch_plot->yAxis->setRange(0,y_data.toFloat()+8);
        } else {
            ui->pitch_plot->yAxis->setRange(0,y_data.toFloat()-8);
        }

        custom_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot();


}
