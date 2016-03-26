#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDialog>
#include <QDebug>

#include <QFile>
#include <QFileInfo>

#include <QAudioFormat>
#include <QAudioOutput>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

	videoWidget = new VideoWidget();
	videoWidget->resize(400, 300);
	videoWidget->setWindowTitle("VideoView");
	videoWidget->setAttribute(Qt::WA_QuitOnClose, false);

    player = new QMediaPlayer;
    player->setVolume(ui->volumeHorizontalSlider->value());
	player->setVideoOutput(videoWidget);

    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(updateTimeElapsedSlider(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(setDuration(qint64)));

	connect(videoWidget, SIGNAL(closed()), this, SLOT(onVideoWidgetClosed()));
	connect(videoWidget, SIGNAL(shown()), this, SLOT(onVideoWidgetShown()));

    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
    setWindowTitle("MediaPlayer");
}

MainWindow::~MainWindow() {
	delete videoWidget;
    delete player;
    delete ui;
}

void MainWindow::on_openPushButton_clicked() {
    mediaFilename = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr(""));
	updateMediaInfo();
}

void MainWindow::on_listenPushButton_clicked() {
	if (!isMediaAvailable()) {
		return;
	}
	if (player->isVideoAvailable()) {
		videoWidget->show();
	}
	
    player->play();
}

void MainWindow::on_stopPushButton_clicked() {
    if (!isMediaAvailable()) {
        return;
    }

    player->stop();
}

void MainWindow::on_volumeHorizontalSlider_valueChanged(int value) {
    if (!isMediaAvailable()) {
        return;
    }

    player->setVolume(value);
}

void MainWindow::on_pausePushButton_clicked() {
    if (!isMediaAvailable()) {
        return;
    }

    player->pause();
}

void MainWindow::on_rewindPushButton_clicked() {
    if (!isMediaAvailable()) {
        return;
    }

    player->setPosition(0);
    ui->positionHorizontalSlider->setValue(0);
    player->play();
}

void MainWindow::on_positionHorizontalSlider_sliderMoved(int position) {
    player->setPosition(position);
}

void MainWindow::updateTimeElapsedSlider(qint64 percent) {
    ui->positionHorizontalSlider->setValue(percent);
}

void MainWindow::setDuration(qint64 duration) {
    ui->positionHorizontalSlider->setMaximum(duration);
}

void MainWindow::setMediaFromFile(const QString& filename) {
	mediaFilename = filename;
	updateMediaInfo();
}

std::string MainWindow::getMediaFilename() {
	return mediaFilename.toStdString();
}

bool MainWindow::isMediaAvailable() {
	return player->isVideoAvailable() || player->isAudioAvailable();
}

void MainWindow::updateMediaInfo() {
	if (mediaFilename.isEmpty()) {
		return;
	}
	if (isMediaAvailable()) {
		player->stop();
		videoWidget->close();
	}
	ui->filePathLineEdit->setText(mediaFilename);
	player->setMedia(QUrl::fromLocalFile(mediaFilename));
}

void MainWindow::onVideoWidgetClosed() {
	player->stop();
	videoViewShown = false;
}

void MainWindow::onVideoWidgetShown() {
	videoViewShown = true;
}

bool MainWindow::canPlayAudio() {
	return player->isAudioAvailable();
}

bool MainWindow::canPlayVideo() {
	return player->isVideoAvailable();
}

QMediaPlayer::MediaStatus MainWindow::getMediaStatus() {
	return player->mediaStatus();
}

QMediaPlayer::State MainWindow::getPlayerState() {
	return player->state();
}

void MainWindow::clickPlay() {
	on_listenPushButton_clicked();
}

void MainWindow::clickPause() {
	on_pausePushButton_clicked();
}

void MainWindow::clickStop() {
	on_stopPushButton_clicked();
}

void MainWindow::clickRewind() {
	on_rewindPushButton_clicked();
}

void MainWindow::changeVolume(int value) {
	on_volumeHorizontalSlider_valueChanged(value);
}

int MainWindow::getVolumeValue() {
	return player->volume();
}

qint64 MainWindow::getPositionValue() {
	return player->position();
}

void MainWindow::changePosition(int position) {
	player->setPosition(position);
}

bool MainWindow::isVideoViewShown() {
	return videoViewShown;
}

void MainWindow::closeVideoView() {
	videoWidget->close();
}
