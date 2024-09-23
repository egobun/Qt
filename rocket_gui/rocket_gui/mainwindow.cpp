#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

#define width_data_field 20

#define width_currencydata_field 5

#define width_time_field 5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    custom_plot.configurePlot(ui->plot, "Высота, [м]", "Время, [с]");
    custom_pitch_plot.configurePlot(ui->pitch_plot, "Тангаж, [°]", "Время, [с]");
    custom_roll_plot.configurePlot(ui->roll_plot, "Крен, [°]", "Время, [с]");
    custom_yaw_plot.configurePlot(ui->yaw_plot, "Рысканье, [°]", "Время, [с]");
    custom_d_pitch_plot.configurePlot(ui->d_pitch_plot, "Скорость изм. тангажа, [°/с]", "Время, [с]");
    custom_d_roll_plot.configurePlot(ui->d_roll_plot, "Скорость изм. крена, [°/с]", "Время, [с]");
    custom_d_yaw_plot.configurePlot(ui->d_yaw_plot, "Скорость изм. рысканья, [°/с]", "Время, [с]");
    custom_temperature_plot.configurePlot(ui->temperature_plot, "Температура, [°]", "Время, [с]");
    custom_battery_voltage_plot.configurePlot(ui->battery_voltage_plot, "Напяжение, [В]", "Время, [с]");
    loadPorts();

    // Создаем поток и процессор данных
    DataProcessor* dataProcessor = new DataProcessor();
    QThread* dataThread = new QThread();

    // Перемещаем процессор данных в новый поток
    dataProcessor->moveToThread(dataThread);

    // Подключаем сигнал от SerialPort к слоту processData в DataProcessor
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::processData);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::dataProcessed, this, &MainWindow::readData);

    //Подключаем сигналы для pitch
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_pitch_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_pitch_Processed, this, &MainWindow::readData_pitch);

    //Подключаем сигналы для roll
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_roll_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_roll_Processed, this, &MainWindow::readData_roll);

    //Подключаем сигналы для d_pitch
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_d_pitch_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_d_pitch_Processed, this, &MainWindow::readData_d_pitch);

    //Подключаем сигналы для d_roll
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_d_roll_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_d_roll_Processed, this, &MainWindow::readData_d_roll);

    //Подключаем сигналы для d_yaw
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_d_yaw_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_d_yaw_Processed, this, &MainWindow::readData_d_yaw);

    //Подключаем сигналы для temperature
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_temperature_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_temperature_Processed, this, &MainWindow::readData_temperature);

    //Подключаем сигналы для battery_voltage
    connect(&_port, &SerialPort::dataReceived, dataProcessor, &DataProcessor::process_battery_voltage_Data);

    // Подключаем сигнал от DataProcessor к слоту readData в MainWindow
    connect(dataProcessor, &DataProcessor::data_battery_voltage_Processed, this, &MainWindow::readData_battery_voltage);



    // Запускаем поток
    dataThread->start();

    //connect(&_port, &SerialPort::dataReceived,this,&MainWindow::readData);
    //connect(&_port, &SerialPort::dataReceived,this,&MainWindow::readData_pitch);
    //connect(&_port, &SerialPort::dataReceived,this,&MainWindow::readData_roll);
    connect(&_port, &SerialPort::dataReceived,this,&MainWindow::readData_yaw);

}

MainWindow::~MainWindow()
{
    // Останавливаем поток и удаляем объекты
    //dataThread->quit();
    //dataThread->wait();
    //delete dataProcessor;
    //delete dataThread;
    delete ui;
}

void MainWindow::plot(QCustomPlot *plot, CustomPlot custom_plot)
{
    plot->graph()->setData(custom_plot.qv_x,custom_plot.qv_y);
    plot->replot();
    plot->update();
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


void MainWindow::readData(QByteArray data, const QString x_data, const QString y_data)
{
    ui->lstMessages->addItem(QString(data));
    ui->lstMessages->scrollToBottom(); // Прокрутка вниз

    if(x_data != "" && y_data != ""){
        ui->plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        if(y_data.toFloat() > 0){
            ui->plot->yAxis->setRange(0,y_data.toFloat()+8);
        } else {
            ui->plot->yAxis->setRange(0,y_data.toFloat()-8);
        }

        custom_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->plot, custom_plot);
    //ui->plot->graph()->setData(custom_plot.qv_x,custom_plot.qv_y);
    //ui->plot->replot();
    //ui->plot->update();

}

void MainWindow::readData_pitch(QByteArray data, QString x_data, QString y_data)
{

    if(x_data != "" && y_data != ""){
        ui->pitch_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);

        ui->pitch_plot->yAxis->setRange(y_data.toFloat()-width_data_field,y_data.toFloat()+width_data_field);


        custom_pitch_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }

    plot(ui->pitch_plot, custom_pitch_plot);
}

void MainWindow::readData_roll(QByteArray data, QString x_data, QString y_data)
{
    if(x_data != "" && y_data != ""){
        ui->roll_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->roll_plot->yAxis->setRange(y_data.toFloat()-width_data_field,y_data.toFloat()+width_data_field);

        custom_roll_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->roll_plot,custom_roll_plot);
}

void MainWindow::readData_yaw(QByteArray data)
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
        if(pair[0] == "yaw"){
            y_data = pair[1];
        }
    }

    if(x_data != "" && y_data != ""){
        ui->yaw_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->yaw_plot->yAxis->setRange(y_data.toFloat()-width_data_field,y_data.toFloat()+width_data_field);

        custom_yaw_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->yaw_plot, custom_yaw_plot);
}

void MainWindow::readData_d_pitch(QByteArray data, QString x_data, QString y_data)
{
    if(x_data != "" && y_data != ""){
        ui->d_pitch_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->d_pitch_plot->yAxis->setRange(y_data.toFloat()-width_data_field,y_data.toFloat()+width_data_field);

        custom_d_pitch_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->d_pitch_plot,custom_d_pitch_plot);
}

void MainWindow::readData_d_roll(QByteArray data, QString x_data, QString y_data)
{
    if(x_data != "" && y_data != ""){
        ui->d_roll_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->d_roll_plot->yAxis->setRange(y_data.toFloat()-width_data_field,y_data.toFloat()+width_data_field);

        custom_d_roll_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->d_roll_plot,custom_d_roll_plot);
}

void MainWindow::readData_d_yaw(QByteArray data, QString x_data, QString y_data)
{
    if(x_data != "" && y_data != ""){
        ui->d_yaw_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->d_yaw_plot->yAxis->setRange(y_data.toFloat()-width_data_field,y_data.toFloat()+width_data_field);

        custom_d_yaw_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->d_yaw_plot,custom_d_yaw_plot);
}

void MainWindow::readData_temperature(QByteArray data, QString x_data, QString y_data)
{
    if(x_data != "" && y_data != ""){
        ui->temperature_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->temperature_plot->yAxis->setRange(y_data.toFloat()-width_currencydata_field,y_data.toFloat()+width_currencydata_field);

        custom_temperature_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->temperature_plot,custom_temperature_plot);
}

void MainWindow::readData_battery_voltage(QByteArray data, QString x_data, QString y_data)
{
    if(x_data != "" && y_data != ""){
        ui->battery_voltage_plot->xAxis->setRange(x_data.toFloat()-width_time_field,x_data.toFloat()+width_time_field);
        ui->battery_voltage_plot->yAxis->setRange(y_data.toFloat()-width_currencydata_field,y_data.toFloat()+width_currencydata_field);

        custom_battery_voltage_plot.addPoint(x_data.toFloat(),y_data.toFloat());
    }
    plot(ui->battery_voltage_plot,custom_battery_voltage_plot);
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

void MainWindow::on_rbtn15Hz_clicked()
{
    if(ui->rbtn15Hz->isChecked()){
        QString message = "frequency_data_transmission:15;";
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

void MainWindow::on_checkYaw_stateChanged(int arg1)
{
    if(ui->checkYaw->isChecked()){
        QString message = "YAW_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "YAW_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}

void MainWindow::on_checkD_Pitch_stateChanged(int arg1)
{
    if(ui->checkD_Pitch->isChecked()){
        QString message = "D_PITCH_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "D_PITCH_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}


void MainWindow::on_checkD_Roll_stateChanged(int arg1)
{
    if(ui->checkD_Roll->isChecked()){
        QString message = "D_ROLL_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "D_ROLL_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}


void MainWindow::on_checkD_Yaw_stateChanged(int arg1)
{
    if(ui->checkD_Yaw->isChecked()){
        QString message = "D_YAW_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "D_YAW_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}

void MainWindow::on_checkTemperature_stateChanged(int arg1)
{
    if(ui->checkTemperature->isChecked()){
        QString message = "TEMPERATURE_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "TEMPERATURE_IS_OK:0;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    }
}

void MainWindow::on_checkBattery_voltage_stateChanged(int arg1)
{
    if(ui->checkBattery_voltage->isChecked()){
        QString message = "BATTERY_VOLTAGE_IS_OK:1;";
        auto numBytes = _port.write(message.toUtf8());
        if(numBytes == -1){
            QMessageBox::critical(this,"Error","Something went wrong");
        }
    } else {
        QString message = "BATTERY_VOLTAGE_IS_OK:0;";
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

void MainWindow::on_tabWidget_currentChanged(int index)
{
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        QWidget *tab = ui->tabWidget->widget(i);
        if (i == index) {
            tab->show(); // Показываем активную вкладку

        } else {
            tab->hide(); // Скрываем неактивные вкладки

        }
    }
}







