#include "playlist.h"
#include<QtMultimedia/QMediaPlayer>
#include<QAudioOutput>
class PlayListData : public QSharedData
{
public:
};

PlayList::PlayList()
    : data(new PlayListData)
{}

PlayList::PlayList(const PlayList &rhs)
    : data{rhs.data}
{}

PlayList &PlayList::operator=(const PlayList &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

PlayList::~PlayList() {}
//adding songs
void PlayList::addSong(QFileInfo newSong)
{
    songList->addiTem(newSong);
    curSong=newSong;
    numSongs++;
}
//getting the current song
QFileInfo PlayList::getcurSong()
{
    return curSong;
}
//display the playlist
QString PlayList::displayPLayList(int index)
{
    return songList->searchByIndex(index).baseName();
}
//get the number of songs
int PlayList::getnumSongs()
{
    return numSongs;
}

//getting the next song
QFileInfo PlayList::getNextSong()
{
    QFileInfo song;
    song=songList->getNextItem(curSong);
    curSong=song;
    return curSong;
}
// getting the previous song
QFileInfo PlayList::getPrevSong()
{
    QFileInfo song;
    song=songList->getPrevItem(curSong);
    curSong=song;
    return curSong;
}

bool PlayList::getIsFirstSong() const
{
    return isFirstSong;
}

void PlayList::setIsFirstSong(bool newIsFirstSong)
{
    isFirstSong = newIsFirstSong;
}
//search for the song by name
QFileInfo PlayList::searchSong(QString SongName)
{
    curSong=songList->searchByName(SongName);
    return curSong;
}
//check if the song is in this playlist or not
bool PlayList::isSong(QFileInfo mp3file)
{
    return songList->isSongThere(mp3file);
}
