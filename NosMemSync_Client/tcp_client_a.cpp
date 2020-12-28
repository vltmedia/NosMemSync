#include "tcp_client_a.h"
#include "nms_types.h"
#include "ui_tcp_client_a.h"
#include <QTextCodec>
#include <QSettings>
#include <QStringListModel>
TCP_Client_A::TCP_Client_A(QWidget *parent) : QMainWindow(parent),
    ui (new Ui::TCP_Client_A)
{
    ui-> setupUi (this);
    loadSettings();

      nmstype.nmsCommand =NMSCommand::GetFiles;
        nmstype.nmsApp =NMSApp::RetroArch;
          nmstype.nmsFolders =NMSFolders::MemoryCards;
    nmstype.getNMSTCPCommand();
    ui->CommandLabel->setText( nmstype.nmsTCPCommand);
      //ui-> progressLabel-> hide ();

     // QTextCodec :: setCodecForTr (QTextCodec :: codecForName ("GBK"));

}

//void TCP_Client_A::filepathAvailablesChanged(){


//}

void TCP_Client_A :: Acceptconnection ()
{
    qDebug("Connection!");
    ui->statusbar->showMessage("Connected, preparing to receive files!");
    ui-> receivedStatusLabel-> setText (tr ("Connected, preparing to receive files!"));

    receivedsocket = server->nextPendingConnection ();
    connect (receivedsocket, SIGNAL (readyRead ()), this, SLOT (ReadClient ()));
}

void TCP_Client_A :: ReadClient ()
{
    ui-> receivedStatusLabel-> setText (tr ("Receiving file ..."));

    if (bytereceived == 0) // just started to receive data, this data is file information
    {
        ui-> receivedProgressBar-> setValue (0);

        QDataStream in (receivedsocket);
        in >> totalsize >> bytereceived >> FileName;
        FileName = "C:/Users/Justin Jaro/Documents/Temp/TestFiles/" + FileName;
        newfile = new QFile (FileName);
        newfile-> open (QFile :: WriteOnly);
    }
    else // Officially read the file content
    {
        Inblock = receivedsocket-> readAll ();

        bytereceived += Inblock.size ();
        newfile-> write (Inblock);
        newfile-> flush ();
    }

    ui-> progressLabel-> show ();
    ui-> receivedProgressBar-> setMaximum (totalsize);
    ui-> receivedProgressBar-> setValue (bytereceived);

    if (bytereceived == totalsize)
    {
        ui-> receivedStatusLabel-> setText (tr ("% 1receive completed"). arg (FileName));

        Inblock.clear ();
        bytereceived = 0;
        totalsize = 0;
    }
}

TCP_Client_A :: ~TCP_Client_A ()
{
    delete ui;
}


void TCP_Client_A::on_pushButton_clicked()
{
    totalsize = 0;
    bytereceived = 0;

    server = new QTcpServer (this);
   server->listen (QHostAddress::Any, 4242);
    //server.listen(QHostAddress::Any, 4242);

    connect(server, SIGNAL (newConnection ()), this, SLOT (Acceptconnection()));

    ui-> receivedProgressBar-> setValue (0);
    ui-> receivedStatusLabel-> setText (tr ("Start listening ..."));
}



void TCP_Client_A::loadSettings()
{
  QSettings settings;
  settings.value("Retroarch", "Poo");
  m_prefs.retroarchMemLocation = settings.value("retroarchMemLocation", "Poop").toString();
  m_prefs.pcsx2MemLocation = settings.value("pcsx2MemLocation", "Poop").toString();
  ui->RetroArchLoc->setText(m_prefs.retroarchMemLocation);
  ui->PCSXLoc->setText(m_prefs.pcsx2MemLocation);

}

void TCP_Client_A::saveSettings()
{
    QSettings settings;
    settings.setValue("retroarchMemLocation", m_prefs.retroarchMemLocation);
    settings.setValue("pcsx2MemLocation", m_prefs.pcsx2MemLocation);

}
void TCP_Client_A::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event;
}

void TCP_Client_A::on_pushButton_LoadSettings_clicked()
{
    loadSettings();

}

void TCP_Client_A::on_pushButton_SaveSettings_clicked()
{
     m_prefs.retroarchMemLocation = ui->RetroArchLoc->toPlainText();
     m_prefs.pcsx2MemLocation = ui->PCSXLoc->toPlainText();
    saveSettings();
}

void TCP_Client_A::on_pushButton_NextChoice_clicked()
{

    filepathAvailables = {"Poo", "Summoner", "Ryu"};
    QStringListModel *model = new QStringListModel(filepathAvailables);
ui->listViewChoices->setModel(model);
//nmstype.nmsCommand =NMSCommand::Download;
//nmstype.nmsFolders =  NMSFolders::MemoryCards;
//nmstype.nmsApp =  NMSApp::PCSX2;
//int index = metaObject()->indexOfEnumerator("NMSApp");
//QMetaEnum metaEnum = metaObject()->enumerator(index);

//QString hing = metaEnum.valueToKey(static_cast<int>(*nmstype.nmsApp));
//qDebug() << nmstype.nmsApp;

///nmstype.nmsApp = new NMSApp(NMSApp::PCSX2);
//qDebug() <<  QVariant::fromValue(*nmstype.nmsApp).toString();
//nmstype.nmsTCPCommandClass.nmsCommand << NMSCommand::Download;

//nmstype.getNMSTCPCommand();


//qDebug() << nmstype.nmsTCPCommand;


}

void TCP_Client_A::on_pushButton_RemoveNext_clicked()
{
  //  qDebug() << filepathAvailables;
   filepathsRemoveLast();
   QStringListModel *model = new QStringListModel(filepathAvailables);
ui->listViewChoices->setModel(model);
  //  qDebug() << filepathAvailables;
}

void TCP_Client_A::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Download"){
        nmstype.nmsCommand =NMSCommand::Download;
    }

    if(arg1 == "Update"){
        nmstype.nmsCommand =NMSCommand::Update;
    }

    if(arg1 == "Get Files"){
        nmstype.nmsCommand =NMSCommand::GetFiles;
    }
    nmstype.getNMSTCPCommand();
    ui->CommandLabel->setText( nmstype.nmsTCPCommand);
}

void TCP_Client_A::on_pushButton_SaveSettings_2_clicked()
{
    nmstype.getNMSTCPCommand();

    nmstype.getNMSTCPCommand();
    ui->CommandLabel->setText( nmstype.nmsTCPCommand);
    qDebug() << nmstype.nmsTCPCommand;
}

void TCP_Client_A::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "RetroArch"){
        nmstype.nmsApp = NMSApp::RetroArch;
    }

    if(arg1 == "PCSX2"){
        nmstype.nmsApp =NMSApp::PCSX2;
    }

    if(arg1 == "Project64"){
        nmstype.nmsApp =NMSApp::Project64;
    }
    nmstype.getNMSTCPCommand();
    ui->CommandLabel->setText( nmstype.nmsTCPCommand);
}

void TCP_Client_A::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Memory Cards"){
        nmstype.nmsFolders = NMSFolders::MemoryCards;
    }

    if(arg1 == "Configs"){
        nmstype.nmsFolders =NMSFolders::Configs;
    }

    if(arg1 == "Cheats"){
        nmstype.nmsFolders =NMSFolders::Cheats;
    }

    nmstype.getNMSTCPCommand();
    ui->CommandLabel->setText( nmstype.nmsTCPCommand);
}
