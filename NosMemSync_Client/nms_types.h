#ifndef NMS_TYPES_H
#define NMS_TYPES_H

#include <QWidget>
#include <QVariant>
#include <QMetaEnum>

enum class NMSCommand
  {
     Download,
     GetFiles,
     Update
  };

enum class NMSApp
  {
     RetroArch,
     PCSX2,
    Project64
  };

enum class NMSFolders
  {
     MemoryCards,
     Configs,
    Cheats
  };
class NMS_Types : public QWidget
{





    Q_OBJECT
public:
    Q_ENUM(NMSCommand)
    Q_ENUM(NMSApp)
    Q_ENUM(NMSFolders)

    struct NMSTCPCommand{
        NMSCommand nmsCommand = NMSCommand::Download;
        NMSApp nmsApp = NMSApp::RetroArch;
        NMSFolders nmsFolders = NMSFolders::MemoryCards;

    };

    explicit NMS_Types(QWidget *parent = nullptr);

    NMSTCPCommand *nmsTCPCommandClass;
    NMSCommand nmsCommand ;
    NMSApp nmsApp ;
    NMSApp nmsApple ;
    NMSFolders nmsFolders ;
    QString nmsTCPCommand;

    QString GetNMSAppString(){
        if (nmsApp ==  NMSApp::RetroArch){
           return("RetroArch");
        }
        if (nmsApp ==  NMSApp::PCSX2){
           return( "PCSX2");
        }
        if (nmsApp ==  NMSApp::Project64){
           return( "Project64");
        }

        return("-");
    }
    QString GetNMSCommandString(){

        if (nmsCommand ==  NMSCommand::Download){
           return( "Download");
        }
        if (nmsCommand ==  NMSCommand::Update){
           return( "Update");
        }
        if (nmsCommand ==  NMSCommand::GetFiles){
           return( "GetFiles");
        }
  return("-");
    }
    QString GetNMSFolderString(){

        if (nmsFolders ==  NMSFolders::MemoryCards){
            return("MemoryCards");
        }
        if (nmsFolders ==  NMSFolders::Configs){
           return("Configs");
        }
        if (nmsFolders ==  NMSFolders::Cheats){
            return("Cheats");
        }
  return("-");
    }
    void getNMSTCPCommand(){

        QString nmsapp = ""  ;
        QString nmscommand = ""  ;
        QString nmsfolders = ""  ;


       nmsTCPCommand  =   GetNMSCommandString() + "~" +GetNMSAppString() + "~" + GetNMSFolderString() ;

      // nmsTCPCommand  = nmscommand + "~" +nmsapp + "~" +nmsfolders  ;

    }
    

signals:

};

#endif // NMS_TYPES_H
