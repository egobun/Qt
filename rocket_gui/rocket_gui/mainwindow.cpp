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
        if(pair[0] == "altitude"){
            y_data = pair[1];
        }
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


void MainWindow::on_checkAltitude_stateChanged(int arg1)
{
    if(ui->checkAltitude->isChecked()){
        QString message = "ALTITUDE_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "ALTITUDE_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}


void MainWindow::on_checkPitch_stateChanged(int arg1)
{
    if(ui->checkPitch->isChecked()){
        QString message = "PITCH_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "PITCH_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}

void MainWindow::on_checkRoll_stateChanged(int arg1)
{
    if(ui->checkRoll->isChecked()){
        QString message = "ROLL_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "ROLL_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}

void MainWindow::on_btnOpenRollWindow_clicked()
{
    roll_window = new RollWindow(this);
    roll_window->show();
}
