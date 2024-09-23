#include "dataprocessor.h"
#include <QDebug>

void DataProcessor::processData(const QByteArray &data) {
    // Здесь добавьте ваш код для обработки данных
    // Например, вы можете просто вывести данные в консоль
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
    // После обработки данных можно отправить сигнал о завершении
    emit dataProcessed(data, x_data, y_data);  // Отправляем сигнал с обработанными данными
}

void DataProcessor::process_pitch_Data(const QByteArray &data) {
    // Здесь добавьте ваш код для обработки данных
    // Например, вы можете просто вывести данные в консоль
    //qDebug() << "Processing data:" << data;
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
        if(pair[0] == "pitch"){
            y_data = pair[1];
        }
    }
    // После обработки данных можно отправить сигнал о завершении
    emit data_pitch_Processed(data, x_data, y_data);  // Отправляем сигнал с обработанными данными
}

void DataProcessor::process_roll_Data(const QByteArray &data) {
    // Здесь добавьте ваш код для обработки данных
    // Например, вы можете просто вывести данные в консоль
    //qDebug() << "Processing data:" << data;
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
    // После обработки данных можно отправить сигнал о завершении
    emit data_roll_Processed(data, x_data, y_data);  // Отправляем сигнал с обработанными данными
}

void DataProcessor::process_d_pitch_Data(const QByteArray &data) {
    // Здесь добавьте ваш код для обработки данных
    // Например, вы можете просто вывести данные в консоль
    //qDebug() << "Processing data:" << data;
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
        if(pair[0] == "d_pitch"){
            y_data = pair[1];
        }
    }
    // После обработки данных можно отправить сигнал о завершении
    emit data_d_pitch_Processed(data, x_data, y_data);  // Отправляем сигнал с обработанными данными
}

void DataProcessor::process_d_roll_Data(const QByteArray &data) {
    // Здесь добавьте ваш код для обработки данных
    // Например, вы можете просто вывести данные в консоль
    //qDebug() << "Processing data:" << data;
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
        if(pair[0] == "d_roll"){
            y_data = pair[1];
        }
    }
    // После обработки данных можно отправить сигнал о завершении
    emit data_d_roll_Processed(data, x_data, y_data);  // Отправляем сигнал с обработанными данными
}

void DataProcessor::process_d_yaw_Data(const QByteArray &data) {
    // Здесь добавьте ваш код для обработки данных
    // Например, вы можете просто вывести данные в консоль
    //qDebug() << "Processing data:" << data;
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
        if(pair[0] == "d_yaw"){
            y_data = pair[1];
        }
    }
    // После обработки данных можно отправить сигнал о завершении
    emit data_d_yaw_Processed(data, x_data, y_data);  // Отправляем сигнал с обработанными данными
}
