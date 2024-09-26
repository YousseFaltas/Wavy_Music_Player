#ifndef PLAYLIST_H
#define PLAYLIST_H

//#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include<QFileDialog>
#include<QtMultimedia/QMediaPlayer>
#include<QAudioOutput>
#include"LinkedList.h"
class PlayListData;

class PlayList
{
    //Q_OBJECT
    QML_ELEMENT
public:
    PlayList();
    PlayList(const PlayList &);
    PlayList &operator=(const PlayList &);
    ~PlayList();
    void addSong(QFileInfo newSong);
    QFileInfo getcurSong();
    QString displayPLayList(int index);
    int getnumSongs();
    void removeSong();
    /*void setname();
    QString getName();*/
    QFileInfo getNextSong();
    QFileInfo getPrevSong();
    bool getIsFirstSong() const;
    void setIsFirstSong(bool newIsFirstSong);
    QFileInfo searchSong(QString SongName);
    bool isSong(QFileInfo mp3file);
private:
    QSharedDataPointer<PlayListData> data;
    //QFileInfo arr[20];
    int numSongs=0;
    QFileInfo curSong;
    QString name;
    bool isFirstSong=true;
    LinkedList *songList=new LinkedList();
};

#endif // PLAYLIST_H
