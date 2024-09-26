#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include<QtCore>
#include<QtWidgets>
#include<QAudioOutput>
#include"playlist.h"
#include<iostream>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    float volume() const;

public slots:
        void setVolume(float volume);

private slots:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pablobutton_clicked();
    void on_pushButton_pause_play_clicked();
    void on_horizontalSlider_volume_sliderMoved(int position);
    void seek(int Mseconds);

    void on_pushButton_prev_clicked();

    void on_pushButton_next_clicked();

    void on_horizontalSlider_seek_bar_sliderMoved(int position);

    void on_zazabutton_clicked();

    void on_sherenbutton_clicked();

    void on_fayrouzbutton_clicked();

    void on_amrbutton_clicked();

    void on_weekndbutton_clicked();
    void onPositionChanged(qint64 position);

    void on_actionopen_audio_file_triggered();

private:
    void updateduration(qint64 duration);
    Ui::MainWindow *ui;
    bool IsPlaying=false;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    qint64  Mduration;
    PlayList *listSongs;
    PlayList *PabloPlayList;
    PlayList *ZazaPlayList;
    PlayList *SherenPlayList;
    PlayList *FayrouzPlayList;
    PlayList *AmrPlayList;
    PlayList *WeekndPlayList;
    QString curplaylist="";

};
#endif // MAINWINDOW_H
