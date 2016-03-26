#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QCloseEvent>
#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
	Q_OBJECT

signals:
	void closed();
	void shown();

protected:
	void closeEvent(QCloseEvent* event) {
		emit closed();
		event->accept();
	}

	void showEvent(QShowEvent* event) {
		emit shown();
		event->accept();
	}
};

#endif
