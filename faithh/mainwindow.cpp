#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtMultimedia/QMediaPlayer>
#include <QFileDialog>
#include<QString>
#include<QAudioOutput>
#include <QMediaMetaData>
#include <QPushButton>
#include <QDesktopServices>
#include <QPixmap>
#include<iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    listSongs = new PlayList;
    PabloPlayList= new PlayList;
    ZazaPlayList= new PlayList;
    SherenPlayList= new PlayList;
    FayrouzPlayList= new PlayList;
    AmrPlayList= new PlayList;
    WeekndPlayList= new PlayList;
    player->setAudioOutput(audioOutput);
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->pushButton_prev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::durationChanged);
    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::positionChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::onPositionChanged);
    ui->horizontalSlider_volume->setRange(0,100);
    audioOutput->setVolume(ui->horizontalSlider_volume->value());
    ui->horizontalSlider_seek_bar->setRange(0,player->duration());
    QPixmap photo("C:/Users/youssef/OneDrive/Desktop/qt projects/faithh/faithh/photos/pblo");
    QPixmap photo1("C:/Users/youssef/OneDrive/Desktop/qt projects/faithh/faithh/photos/sherene");
    QPixmap photo2("C:/Users/youssef/OneDrive/Desktop/qt projects/faithh/faithh/photos/amrdiab");
    QPixmap photo3("C:/Users/youssef/OneDrive/Desktop/qt projects/faithh/faithh/photos/wgz2");
    QPixmap photo4("C:/Users/youssef/OneDrive/Desktop/qt projects/faithh/faithh/photos/weeknd");
    QPixmap photo5("C:/Users/youssef/OneDrive/Desktop/qt projects/faithh/faithh/photos/");
    QPushButton pablobutton;
    ui->pablobutton->setIcon(photo);
    ui->pablobutton->setIconSize(QSize(ui->pablobutton->width(), ui->pablobutton->height()));
    QPushButton sherenbutton;
    ui->sherenbutton->setIcon(photo1);
    ui->sherenbutton->setIconSize(QSize(ui->sherenbutton->width(), ui->sherenbutton->height()));
    QPushButton amrbutton;
    ui->amrbutton->setIcon(photo2);
    ui->amrbutton->setIconSize(QSize(ui->amrbutton->width(), ui->amrbutton->height()));
    QPushButton zazabutton;
    ui->zazabutton->setIcon(photo3);
    ui->zazabutton->setIconSize(QSize(ui->zazabutton->width(), ui->zazabutton->height()));
    QPushButton fayrouzbutton;
    ui->fayrouzbutton->setIcon(photo4);
    ui->fayrouzbutton->setIconSize(QSize(ui->fayrouzbutton->width(), ui->fayrouzbutton->height()));
    QPushButton weekndbutton;
    ui->weekndbutton->setIcon(photo5);
    ui->weekndbutton->setIconSize(QSize(ui->weekndbutton->width(), ui->weekndbutton->height()));
    QFileInfo fileinfo1("C:/Users/youssef/OneDrive/Desktop/music/songs/marwan pablo/Elmabda2.mp3");
    PabloPlayList->addSong(fileinfo1);
    QFileInfo fileinfo_1("C:/Users/youssef/OneDrive/Desktop/music/songs/amr diab/Ray'aa.mp3");
    AmrPlayList->addSong(fileinfo_1);
    QFileInfo fileinfo2("C:/Users/youssef/OneDrive/Desktop/music/songs/wegz/Elbakht.mp3");
    ZazaPlayList->addSong(fileinfo2);
    QFileInfo fileinfo3("C:/Users/youssef/OneDrive/Desktop/music/songs/the weeknd/17 Die For You.mp3");
    WeekndPlayList->addSong(fileinfo3);
    QFileInfo fileinfo4("C:/Users/youssef/OneDrive/Desktop/music/songs/sherine/El Kadabeen.mp3");
    SherenPlayList->addSong(fileinfo4);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Next 3 functions is for the seek bar and to control the timer and duartion of the song
void MainWindow::seek(int Mseconds)
{
    player->setPosition(Mseconds);
}



void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;
    ui->horizontalSlider_seek_bar->setMaximum(duration);
}
// to update the timer of the song
void MainWindow::positionChanged(qint64 progress)
{
    if (!ui->horizontalSlider_seek_bar->isSliderDown())
        ui->horizontalSlider_seek_bar->setValue(progress);

    updateduration(progress / 1000);
}
//to display time and duartion of the song
void MainWindow::updateduration(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || Mduration) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60, currentInfo % 60,
                          (currentInfo * 1000) % 1000);
        QTime totalTime((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60,
                        (Mduration * 1000) % 1000);
        QString format = "mm:ss";
        if (Mduration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    ui->label_timer->setText(tStr);
}

//pause and play function (control the pause and play button)
void MainWindow::on_pushButton_pause_play_clicked()
{
    if(IsPlaying==false){
        player->play();
        IsPlaying=true;
        ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }else if(IsPlaying==true){
        player->pause();
        IsPlaying=false;
        ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

//


//set and control the volume function
void MainWindow::on_horizontalSlider_volume_sliderMoved(int position)
{
    audioOutput->setVolume(volume());
}

float MainWindow::volume() const
{
    qreal linearVolume =
        QAudio::convertVolume(ui->horizontalSlider_volume->value() / qreal(100),
                              QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);

    return linearVolume;
}


void MainWindow::setVolume(float volume)
{
    qreal logarithmicVolume = QAudio::convertVolume(volume, QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    ui->horizontalSlider_volume->setValue(qRound(logarithmicVolume * 100));
}


//previous button function that gets the previous song in the selected playlist
void MainWindow::on_pushButton_prev_clicked()
{
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    player->setSource(QUrl(listSongs->getPrevSong().filePath()));
    ui->label_song_name->setText(listSongs->getcurSong().baseName());
    player->play();
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
}

//next button function that gets the next song in the selected playlist

void MainWindow::on_pushButton_next_clicked()
{
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    player->setSource(QUrl(listSongs->getNextSong().filePath()));
    ui->label_song_name->setText(listSongs->getcurSong().baseName());
    player->play();
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
}

//controlling the seek bar
void MainWindow::on_horizontalSlider_seek_bar_sliderMoved(int position){
    if (player->isSeekable()){
        qint64 duration = player->duration();  // Total duration of the media
        qint64 newPosition = position * duration / ui->horizontalSlider_seek_bar->maximum();
        player->setPosition(newPosition);
    }
}

//this function allow us to select a certain song from the playlist in the list widget
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    player->setSource(QUrl(listSongs->searchSong(item->text()).filePath()));
    ui->label_song_name->setText(listSongs->getcurSong().baseName());
    player->play();
    ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
}

//the next 6 functions to open each playlist and add song to it
void MainWindow::on_pablobutton_clicked()
{
    if(curplaylist=="pablo"){
    }else{
        listSongs=PabloPlayList;
        ui->listWidget->clear();
        for(int i=0;i<PabloPlayList->getnumSongs();i++){
            QListWidgetItem *item1 = new QListWidgetItem(PabloPlayList->displayPLayList(i));
            ui->listWidget->addItem(item1);
        }
        curplaylist="pablo";
    }
}


void MainWindow::on_zazabutton_clicked()
{
    if(curplaylist=="zaza"){
    }else{
        listSongs=ZazaPlayList;
        ui->listWidget->clear();
        for(int i=0;i<ZazaPlayList->getnumSongs();i++){
            QListWidgetItem *item1 = new QListWidgetItem(ZazaPlayList->displayPLayList(i));
            ui->listWidget->addItem(item1);
        }
        curplaylist="zaza";
    }
}


void MainWindow::on_sherenbutton_clicked()
{
    if(curplaylist=="sheren"){
    }else{
        listSongs=SherenPlayList;
        ui->listWidget->clear();
        for(int i=0;i<SherenPlayList->getnumSongs();i++){
            QListWidgetItem *item1 = new QListWidgetItem(SherenPlayList->displayPLayList(i));
            ui->listWidget->addItem(item1);
        }
        curplaylist="sheren";
    }
}


void MainWindow::on_fayrouzbutton_clicked()
{
    if(curplaylist=="weeknd"){
    }else{
        listSongs=WeekndPlayList;
        ui->listWidget->clear();
        for(int i=0;i<WeekndPlayList->getnumSongs();i++){
            QListWidgetItem *item1 = new QListWidgetItem(WeekndPlayList->displayPLayList(i));
            ui->listWidget->addItem(item1);
        }
        curplaylist="weeknd";
    }
}


void MainWindow::on_amrbutton_clicked()
{
    if(curplaylist=="amr"){
    }else{
        listSongs=AmrPlayList;
        ui->listWidget->clear();
        for(int i=0;i<AmrPlayList->getnumSongs();i++){
            QListWidgetItem *item1 = new QListWidgetItem(AmrPlayList->displayPLayList(i));
            ui->listWidget->addItem(item1);
        }
        curplaylist="amr";
    }
}


void MainWindow::on_weekndbutton_clicked()
{
    if(curplaylist=="fayrouz"){
    }else{
        listSongs=SherenPlayList;
        ui->listWidget->clear();
        for(int i=0;i<FayrouzPlayList->getnumSongs();i++){
            QListWidgetItem *item1 = new QListWidgetItem(FayrouzPlayList->displayPLayList(i));
            ui->listWidget->addItem(item1);
        }
        curplaylist="fayrouz";
    }
}
//automatically plays the next song when the current song is finished
void MainWindow::onPositionChanged(qint64 position)
{
    if (position >= ui->horizontalSlider_seek_bar->maximum())
    {
        // Automatically play the next song when the end of the seek bar is reached
        ui->pushButton_next->click();
    }
}

void MainWindow::on_actionopen_audio_file_triggered()
{
    if(curplaylist!=""){
    try{
        QString fileName = QFileDialog::getOpenFileName(this,tr("select audio file"),"",tr("mp3 files(*mp3)"));
        QFileInfo fileinfo(fileName);
        if(!listSongs->isSong(fileinfo)){
            listSongs->addSong(fileinfo);
            if(listSongs->getnumSongs()==1){
                ui->label_song_name->setText(listSongs->getcurSong().baseName());
                player->setSource(QUrl(listSongs->getcurSong().filePath()));
            }else{
                ui->label_song_name->setText(listSongs->getcurSong().baseName());
                player->setSource(QUrl(listSongs->getcurSong().filePath()));
            }
            QListWidgetItem *item1 = new QListWidgetItem(listSongs->getcurSong().baseName());
            ui->listWidget->addItem(item1);
            ui->pushButton_pause_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        }
    }
    catch(const string& error){
        cout<<"error opening file"<< error<<endl;
    }
    }
}

