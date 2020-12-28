#ifndef TCP_CLIENT_A_H
#define TCP_CLIENT_A_H
#include "nms_types.h"
#include <QMainWindow>
#include <QtNetwork/QTcpServer>

# include <QtNetwork/QTcpSocket>
#include <QFile>
#include <QString>
namespace Ui {
class TCP_Client_A;
}
class TCP_Client_A : public QMainWindow
{
    Q_OBJECT
public:
    QStringList m_strings;
    ~TCP_Client_A();
explicit TCP_Client_A(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

    private:
        Ui::TCP_Client_A *ui;

        QTcpServer *server;
        QTcpSocket *receivedsocket;
        QFile *newfile;
        QList<QString> filepathAvailables;
        void  filepathsRemoveLast(){


            if(filepathAvailables.length() >0){
           filepathAvailables.removeAt(0);
           DownloadFinished = false;
            }else{

                DownloadFinished = true;
            }


        }
        QByteArray Inblock;
        QString FileName;
        QString ParseType;
        bool DownloadFinished;
        qint64 totalsize;
        qint64 bytereceived;
        NMS_Types nmstype;
        void loadSettings();
          void saveSettings();
          struct SPreferences
          {
              QString retroarchMemLocation;
                QString pcsx2MemLocation;
          };
          SPreferences m_prefs;
 public slots:
          void on_pushButton_clicked();
          void on_pushButton_LoadSettings_clicked();
          void on_pushButton_SaveSettings_clicked();
          void on_pushButton_NextChoice_clicked();
          void on_pushButton_RemoveNext_clicked();
    private slots:
        void Acceptconnection ();
        void ReadClient ();



        void on_comboBox_currentIndexChanged(const QString &arg1);
        void on_pushButton_SaveSettings_2_clicked();
        void on_comboBox_2_currentIndexChanged(const QString &arg1);
        void on_comboBox_3_currentIndexChanged(const QString &arg1);
        void on_ReadDirectoryButton_clicked();
};

#endif // TCP_CLIENT_A_H
