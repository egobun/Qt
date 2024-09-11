#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    custom_plot.configurePlot(ui->plot, "Высота, [м]", "Время, [с]");
    loadPorts();
    connect(&_port, &SerialPort::dataReceived,this,&MainWindow::readData);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(custom_plot.qv_x,custom_plot.qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_btn_add_clicked()
{
    custom_plot.addPoint(ui->bx_x->value(),ui->bx_y->value());
    plot();
}


void MainWindow::on_btn_clear_clicked()
{
    custom_plot.clearData();
    plot();
}

void MainWindow::loadPorts()
{
    foreach (auto &port, QSerialPortInfo::availablePorts()) {
        ui->cmbPorts->addItem(port.portName());
    }
}

void MainWindow::on_btnOpenPorts_clicked()
{
    auto isConnected = _port.connect(ui->cmbPorts->currentText());
    if (!isConnected){
        QMessageBox::critical(this,"Error","There is a problem connecting");
    }
}

void MainWindow::on_btnSend_clicked()
{
    auto numBytes = _port.write(ui->lnMessage->text().toUtf8());
    if(numBytes == -1){
        QMessageBox::critical(this,"Error","Something went wrong");
    }
}


void MainWindow::readData(QByteArray data)
{
    ui->lstMessages->addItem(QString(data));
    ui->lstMessages->scrollToBottom(); // Прокрутка вниз
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
        y_data = dataList[3]; // Четвертое значение
    }

    if(x_data != "" && y_data != ""){
        ui->plot->xAxis->setRange(x_data.toFloat()-5,x_data.toFloat()+5);
        if(y_data.toFloat() > 0){
            ui->plot->yAxis->setRange(0,y_data.toFloat()+8);
        } else {
            ui->plot->yAxis->setRange(0,y_data.toFloat()-8);
        }

        custom_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot();


}

void MainWindow::on_checkTransmit_stateChanged(int arg1)
{
    if(ui->checkTransmit->isChecked()){
        QString message = "TRANSMIT_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "TRANSMIT_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}

void MainWindow::on_rbtn1Hz_clicked()
{
    if(ui->rbtn1Hz->isChecked()){
        QString message = "frequency_data_transmission:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}



void MainWindow::on_rbtn10Hz_clicked()
{
    if(ui->rbtn10Hz->isChecked()){
        QString message = "frequency_data_transmission:10;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}


void MainWindow::on_rbtn20Hz_clicked()
{
    if(ui->rbtn20Hz->isChecked()){
        QString message = "frequency_data_transmission:20;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}


void MainWindow::on_btnOpenPitchWindow_clicked()
{
    pitch_window = new PitchWindow(this);
    pitch_window->show();
}

