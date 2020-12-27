#ifndef TCP_CLIENT_A_H
#define TCP_CLIENT_A_H

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

        QByteArray Inblock;
        QString FileName;
        qint64 totalsize;
        qint64 bytereceived;
        void loadSettings();
          void saveSettings();
          struct SPreferences
          {
              QString retroarchMemLocation;
                QString pcsx2MemLocation;
          };
          SPreferences m_prefs;

    private slots:
        void Acceptconnection ();
        void ReadClient ();


        void on_pushButton_clicked();
        void on_pushButton_LoadSettings_clicked();
        void on_pushButton_SaveSettings_clicked();
        void on_pushButton_NextChoice_clicked();
};

#endif // TCP_CLIENT_A_H
