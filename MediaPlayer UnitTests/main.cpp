#include <QtCore/QCoreApplication>
#include <QApplication>

#include <gtest\gtest.h>

#include "mainwindow.h"

class MainWindowTest : public testing::Test {
public:
	MainWindowTest(int argc = 0, char** argv = NULL) : app(argc, argv), mainWindow() {}

	QApplication app;
	MainWindow mainWindow;
};

TEST_F(MainWindowTest, noFilenameIsSetByDefault) {
	EXPECT_EQ("", mainWindow.getMediaFilename());
}

TEST_F(MainWindowTest, canSetMediaFilename) {
	mainWindow.setMediaFromFile("Hello");

	EXPECT_EQ("Hello", mainWindow.getMediaFilename());
}

TEST_F(MainWindowTest, cantPlayAudioByDefault) {
	EXPECT_FALSE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, cantPlayAudioWhenIncorrectFilename) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/hh.mp3");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_FALSE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, canPlayAudioFrom_Mp3_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song1.mp3");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, canPlayAudioFrom_Wav_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, noMediaByDefault) {
	EXPECT_EQ(QMediaPlayer::MediaStatus::NoMedia, mainWindow.getMediaStatus());
}

TEST_F(MainWindowTest, playerIsInStoppedStateByDefault) {
	EXPECT_EQ(QMediaPlayer::State::StoppedState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, canLoadMediaFromFile) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song1.mp3");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_EQ(QMediaPlayer::MediaStatus::LoadingMedia, mainWindow.getMediaStatus());
}

TEST_F(MainWindowTest, playerIsInStoppedStateAfterLoadingMedia) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_EQ(QMediaPlayer::State::StoppedState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInPlayingStateAfterPressingPlay) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();

	EXPECT_EQ(QMediaPlayer::State::PlayingState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInPausedStateAfterPressingPauseWhilePlaying) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.clickPause();

	EXPECT_EQ(QMediaPlayer::State::PausedState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInPlayingStateAfterPressingPlayWhilePaused) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.clickPause();
	mainWindow.clickPlay();

	EXPECT_EQ(QMediaPlayer::State::PlayingState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInStoppedStateAfterPressingStopWhilePlaying) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.clickStop();

	EXPECT_EQ(QMediaPlayer::State::StoppedState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInStoppedStateAfterPressingStopWhilePaused) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.clickPause();
	mainWindow.clickStop();

	EXPECT_EQ(QMediaPlayer::State::StoppedState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInPlayingStateAfterPressingRewindWhilePlaying) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.clickRewind();

	EXPECT_EQ(QMediaPlayer::State::PlayingState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, playerIsInPlayingStateAfterPressingRewindWhilePaused) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.clickPause();
	mainWindow.clickRewind();

	EXPECT_EQ(QMediaPlayer::State::PlayingState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, canSetVolume) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.changeVolume(70);

	EXPECT_EQ(70, mainWindow.getVolumeValue());
}

TEST_F(MainWindowTest, canChangePositionValue) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.changePosition(1000);

	EXPECT_EQ(1000, mainWindow.getPositionValue());
}

TEST_F(MainWindowTest, positionIsZeroAfterLoadingMedia) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_EQ(0, mainWindow.getPositionValue());
}

TEST_F(MainWindowTest, positionIsZeroAfterPressingStopWhilePlaying) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.changePosition(40);
	mainWindow.clickPlay();
	QCoreApplication::processEvents();
	mainWindow.clickStop();

	EXPECT_EQ(0, mainWindow.getPositionValue());
}

TEST_F(MainWindowTest, cantPlayVideoByDefault) {
	EXPECT_FALSE(mainWindow.canPlayVideo());
}

TEST_F(MainWindowTest, cantPlayVideoWhenIncorrectFileName) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/hh.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_FALSE(mainWindow.canPlayVideo());
}

TEST_F(MainWindowTest, canPlayVideoFrom_Mp4_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video1.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayVideo());
}

TEST_F(MainWindowTest, canPlayAudioFrom_Mp4_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video1.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, canPlayVideoFrom_Wmv_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video3.wmv");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayVideo());
}

TEST_F(MainWindowTest, canPlayAudioFrom_Wmv_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video3.wmv");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, canPlayVideoFrom_Mov_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video5.mov");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayVideo());
}

TEST_F(MainWindowTest, canPlayAudioFrom_Mov_File) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video5.mov");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_TRUE(mainWindow.canPlayAudio());
}

TEST_F(MainWindowTest, videoViewIsHideByDefault) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video1.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();

	EXPECT_FALSE(mainWindow.isVideoViewShown());
}

TEST_F(MainWindowTest, videoViewIsShowAfterPressingPlay) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video1.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();

	EXPECT_TRUE(mainWindow.isVideoViewShown());
}

TEST_F(MainWindowTest, videoViewIsNotShownWhenFileNotContainVideo) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Music/Song4.wav");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();

	EXPECT_FALSE(mainWindow.isVideoViewShown());
}

TEST_F(MainWindowTest, playerIsInStoppedStateAfterClosingVideoView) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video1.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.closeVideoView();

	EXPECT_EQ(QMediaPlayer::State::StoppedState, mainWindow.getPlayerState());
}

TEST_F(MainWindowTest, positionIsZeroAfterClosingVideoView) {
	mainWindow.setMediaFromFile("C:/Users/nikolaev.k/Videos/Video1.mp4");

	mainWindow.show();
	QCoreApplication::processEvents();
	mainWindow.clickPlay();
	mainWindow.changePosition(1000);
	QCoreApplication::processEvents();
	mainWindow.closeVideoView();

	EXPECT_EQ(0, mainWindow.getPositionValue());
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
