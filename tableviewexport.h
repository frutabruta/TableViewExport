#ifndef TABLEVIEWEXPORT_H
#define TABLEVIEWEXPORT_H

#include <QObject>
#include <QAbstractItemModel>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

enum class ExportFileType
{
    Csv,
    Xml
};

class TableViewExport: QObject
{
    Q_OBJECT
public:
    TableViewExport();
    void exportToCsv(QString cesta, QAbstractItemModel *model);
    void exportToXml(QString cesta, QAbstractItemModel *model);


    void selectExportPath(ExportFileType exportType, QAbstractItemModel *model, QWidget *parent);

    QString zmenPriponu(QString vstup, QString pripona);
    QString otevriSouborDialog(QString cesta, QWidget *parent, QString fileExtension, QString fileTypeDescription);
private:
    void messageBox(QString obsah);

};

#endif // TABLEVIEWEXPORT_H
