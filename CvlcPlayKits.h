#pragma once

#include <QObject>
#include "vlc\vlc.h"
#include <QDir>
#include <vector>
#include <QDebug>
using namespace std;
class CvlcPlayKits : public QObject
{
	Q_OBJECT

public:
	CvlcPlayKits();
	~CvlcPlayKits();
	libvlc_media_player_t* media_player();
	libvlc_time_t getDuration();
	void setDuration(libvlc_time_t totalTime);
	int initVLC();

	void setTimeSliderPos(const int& value);
	void setVolumeSliderPos(const int& value);
	void setVideoTimeContent(const QString& total, const QString& current);
	void setVideoPlayButtonContent(QString total);
	void setVecIndex();
	int getVecIndex();
	int play(QString fileName, void *drawable);
	int play(QStringList fileList, void *drawable);
	void play();
	void stop();
	void pauseMethod();
	bool getPasus();

	vector<libvlc_time_t> getVecDuration();
signals:
	void sign_TimeSliderPos(const int& value);
	void sign_VolumeSliderPos(const int& value);
	void sign_VideoTimeContent(const QString& total, const QString& current);
	void sign_VideoPlayButtonContent(QString total);
	
	void sign_VideoTimeProgress(const float& value);

private:
	libvlc_instance_t *vlc_base = nullptr;
	libvlc_media_t *vlc_media = nullptr;
	libvlc_media_player_t *vlc_mediaPlayer = nullptr;
	bool pause = true;
	libvlc_time_t m_totalSecs = -1;
	libvlc_event_manager_t *m_pEvent_manager = nullptr;

	libvlc_media_list_player_t* m_pMediaPlayerList = nullptr;
	libvlc_media_list_t* m_medialist = nullptr;

	vector<libvlc_time_t> m_vecDurations;
	int m_vecIndex = 0;
};
