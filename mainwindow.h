#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

#include "VideoWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
	std::string getMediaFilename();
	void setMediaFromFile(const QString& filename);

	bool canPlayAudio();
	bool canPlayVideo();
	QMediaPlayer::MediaStatus getMediaStatus();
	QMediaPlayer::State getPlayerState();
	qint64 getPositionValue();
	int getVolumeValue();
	bool isVideoViewShown();

	void clickPlay();
	void clickPause();
	void clickStop();
	void clickRewind();
	void changeVolume(int value);
	void changePosition(int position);
	void closeVideoView();

private slots:
    void on_openPushButton_clicked();
    void on_listenPushButton_clicked();
    void on_stopPushButton_clicked();
    void on_volumeHorizontalSlider_valueChanged(int value);
    void on_pausePushButton_clicked();
    void on_rewindPushButton_clicked();
    void on_positionHorizontalSlider_sliderMoved(int position);

    void updateTimeElapsedSlider(qint64 percent);
    void setDuration(qint64 duration);

	void onVideoWidgetClosed();
	void onVideoWidgetShown();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *player;
    QString mediaFilename;
	VideoWidget *videoWidget;

	void updateMediaInfo();
	bool isMediaAvailable();
	bool videoViewShown = false;
};

#endif // MAINWINDOW_H
