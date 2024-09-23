#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QByteArray>


class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void dataProcessed(QByteArray data, const QString x_data, const QString y_data);

    void data_pitch_Processed(QByteArray data, const QString x_data, const QString y_data);

    void data_roll_Processed(QByteArray data, const QString x_data, const QString y_data);

    void data_d_pitch_Processed(QByteArray data, const QString x_data, const QString y_data);

    void data_d_roll_Processed(QByteArray data, const QString x_data, const QString y_data);

    void data_d_yaw_Processed(QByteArray data, const QString x_data, const QString y_data);

    void data_temperature_Processed(QByteArray data, const QString x_data, const QString y_data);

    void data_battery_voltage_Processed(QByteArray data, const QString x_data, const QString y_data);

public slots:
    void processData(const QByteArray &data);

    void process_pitch_Data(const QByteArray &data);

    void process_roll_Data(const QByteArray &data);

    void process_d_pitch_Data(const QByteArray &data);

    void process_d_roll_Data(const QByteArray &data);

    void process_d_yaw_Data(const QByteArray &data);

    void process_temperature_Data(const QByteArray &data);

    void process_battery_voltage_Data(const QByteArray &data);
};

#endif // DATAPROCESSOR_H
