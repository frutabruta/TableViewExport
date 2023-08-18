#include "tableviewexport.h"

TableViewExport::TableViewExport()
{

}

void TableViewExport::exportToCsv(QString cesta, QAbstractItemModel *model)
{
    qDebug()<<Q_FUNC_INFO;
    if(model==NULL)
    {
        qDebug()<<"pointer je prazdny";
    }


    QFile data(cesta);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug()<<"soubor se povedlo otevrit";
        QTextStream out(&data);
        out.setEncoding(QStringConverter::System);

        QStringList hlavicka;
        for(int i=0;i<model->columnCount();i++)
        {

            hlavicka<<QString("\""+model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString().replace("\n"," ")+"\"");

        }
        out<<hlavicka.join(";")<<"\r\n";

        for (int i = 0; i < model->rowCount(); i++)
        {
            QStringList radek;
            for (int j = 0; j < model->columnCount(); j++)
            {
                //qDebug()<<i<<" "<<j<<" "
                radek<<QString("\""+model->index(i,j).data(Qt::DisplayRole).toString()+"\"");

            }
            out<<radek.join(";")<<"\r\n";
            qDebug()<<radek;
            //   textData += QLatin1Char('\n');
        }

    }
    else
    {
        qDebug()<<"soubor se nepovedlo otevrit";
    }

}

void TableViewExport::exportToXml(QString cesta, QAbstractItemModel *model)
{
    qDebug()<<Q_FUNC_INFO;


}

void TableViewExport::selectExportPath(ExportFileType exportType, QAbstractItemModel *model, QWidget* parent)
{
    qDebug()<<Q_FUNC_INFO;


    QString fileExtension="";
    QString fileTypeDescription="";


    switch(exportType)
    {
    case ExportFileType::Csv:
        fileExtension="csv";
        fileTypeDescription="CSV soubor ";
        break;
    case ExportFileType::Xml:
        fileExtension="xml";
        fileTypeDescription="XML soubor ";
        break;
    default:
        break;

    }

    //ui->tableView_vysledkyDetail->model()
    if(model==NULL)
    {
        qDebug()<<"pointer je prazdny";
        messageBox("nejdřív vyber test!");
        return;
    }
    qDebug()<<model->rowCount();

    QString cestaSouboru="";



    QString cestaCsv=otevriSouborDialog(zmenPriponu( cestaSouboru,"csv"),parent,fileExtension,fileTypeDescription);
    qDebug()<<"cesta csv "<<cestaCsv;
    if(cestaCsv!="")
    {
        if(model->rowCount()>0)
        {
            switch(exportType)
            {
            case ExportFileType::Csv:
                exportToCsv(cestaCsv,model);
                break;
            case ExportFileType::Xml:
                exportToXml(cestaCsv,model);
                break;
            default:
                break;

            }


        }
    }
    else
    {
        return;
    }
}


QString TableViewExport::zmenPriponu(QString vstup,QString pripona)
{
    qDebug()<<Q_FUNC_INFO;

    if (vstup.isEmpty())
    {
        return "";
    }

    QString zbytek=vstup.split(".").first();
    QString staraPripona=vstup.split(".").last();

    qDebug()<<"zbytek: "<<zbytek<<" pripona: "<<staraPripona;

    QString vystup=zbytek+"."+pripona;

    return vystup;
}





QString TableViewExport::otevriSouborDialog(QString cesta, QWidget* parent, QString fileExtension, QString fileTypeDescription)
{
    qDebug() <<  Q_FUNC_INFO;

    QString fileName = QFileDialog::getSaveFileName(parent,
                                                    tr("Otevři soubor"), cesta,
                                                    fileTypeDescription+" (*."+fileExtension+");;All Files (*)");
    return fileName;
}


void TableViewExport::messageBox(QString obsah)
{
    QMessageBox msgBox;
    msgBox.setText(obsah);
    msgBox.exec();
}
