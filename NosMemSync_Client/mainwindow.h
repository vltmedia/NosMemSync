#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

#include <QFile>
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ReturnData(QString data);
    QString ChoiceTest = "Poo";

public slots:
    void onReadyRead();
    void connectToServer();

private slots:
    void on_ConnectServerpushButton_clicked();

    void on_pushButton_clicked();

    void on_comboBoxTest_currentTextChanged(const QString &arg1);

    void on_pushButton_2Test_clicked();

    void on_RetroArchBrowse_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket  _socket;
};

#endif // MAINWINDOW_H
