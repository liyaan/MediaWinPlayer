#include "CvlcPlayKits.h"
#include <iostream>

#include <algorithm>
using namespace std;

QString setDateTime(qint64 value) {
	int _hour = value / 3600;
	int _min = (value - _hour * 3600) / 60;
	int _sec = value - _hour * 3600 - _min * 60;
	char buf[256] = { 0 };
	sprintf(buf, "%02d:%02d:%02d", _hour, _min, _sec);
	QString str(buf);
	return str;
}
void remove_vector(vector<libvlc_time_t> vec, int value) {
	vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
}
void vlc_callback(const struct libvlc_event_t *p_event, void *p_data) {
	CvlcPlayKits * pThis = static_cast<CvlcPlayKits *>(p_data);
	if (pThis)
	{
		if (p_event->type == libvlc_MediaPlayerPositionChanged)
		{
			float pos = libvlc_media_player_get_position(pThis->media_player());
			pThis->setTimeSliderPos(pos * 100);
			qint64 curSecs = libvlc_media_player_get_time(pThis->media_player()) / 1000;
			pThis->setVideoTimeContent(setDateTime(pThis->getDuration()), setDateTime(curSecs));

		}
		else if (p_event->type == libvlc_MediaPlayerAudioVolume)
		{
			int value = libvlc_audio_get_volume(pThis->media_player());
			pThis->setVolumeSliderPos(value);
		}
		else if (p_event->type == libvlc_MediaPlayerMediaChanged)
		{
			if (pThis->getVecDuration().size()>0)
			{
				libvlc_time_t totalSecs = pThis->getVecDuration()[pThis->getVecIndex()];
				pThis->setDuration(totalSecs / 1000);
				cout << "totalSecs = " << totalSecs << endl;
				pThis->setVecIndex();
			}
			
		}else if (p_event->type == libvlc_MediaPlayerTimeChanged)
		{
			libvlc_time_t current = libvlc_media_player_get_time(pThis->media_player());
			libvlc_time_t length = libvlc_media_player_get_length(pThis->media_player());
			float progress = (current * 100.0f) / length;
			pThis->sign_VideoTimeProgress(progress);
		}

	}
}

CvlcPlayKits::CvlcPlayKits()
	: QObject()
{
}



int CvlcPlayKits::initVLC() {
	vlc_base = libvlc_new(0, nullptr);
	if (vlc_base) {
		vlc_mediaPlayer = libvlc_media_player_new(vlc_base);
		if (vlc_mediaPlayer)
		{
			m_pEvent_manager = libvlc_media_player_event_manager(vlc_mediaPlayer);
			if (m_pEvent_manager)
			{
				libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);

				libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
				//libvlc_MediaParsedChanged
				libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerMediaChanged, vlc_callback, this);
				
				libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerTimeChanged, vlc_callback, this);
			}

		}
		else {
			libvlc_release(vlc_base);
			return -2;
		}
	}
	else {
		return -1;
	}
	return 0;
}
int CvlcPlayKits::play(QString filename, void *drawable) {
	vlc_media = libvlc_media_new_path(vlc_base, filename.toUtf8());
	if (!vlc_media)
	{
		return -1;
	}
	libvlc_media_parse(vlc_media);
	//libvlc_media_player_stop(vlc_mediaPlayer);
	libvlc_media_player_set_media(vlc_mediaPlayer, vlc_media);
	libvlc_media_player_set_hwnd(vlc_mediaPlayer, drawable);
	libvlc_media_player_set_rate(vlc_mediaPlayer, 1.0);
	m_totalSecs = libvlc_media_get_duration(vlc_media) / 1000;

	libvlc_media_release(vlc_media);
	vlc_media = nullptr;
	
	if (vlc_mediaPlayer)libvlc_media_player_play(vlc_mediaPlayer);
	setVideoPlayButtonContent(QStringLiteral("ÔÝÍ£"));
	pause = false;
	return 0;
}
int CvlcPlayKits::playRtmp(QString filename, void *drawable) {
	vlc_media = libvlc_media_new_location(vlc_base, filename.toUtf8());
	if (!vlc_media)
	{
		return -1;
	}
	libvlc_media_parse(vlc_media);
	//libvlc_media_player_stop(vlc_mediaPlayer);
	libvlc_media_player_set_media(vlc_mediaPlayer, vlc_media);
	libvlc_media_player_set_hwnd(vlc_mediaPlayer, drawable);
	libvlc_media_player_set_rate(vlc_mediaPlayer, 1.0);
	m_totalSecs = libvlc_media_get_duration(vlc_media) / 1000;

	libvlc_media_release(vlc_media);
	vlc_media = nullptr;

	if (vlc_mediaPlayer)libvlc_media_player_play(vlc_mediaPlayer);
	setVideoPlayButtonContent(QStringLiteral("ÔÝÍ£"));
	pause = false;
	return 0;
}
int CvlcPlayKits::play(QStringList fileList, void *drawable) {
	 m_pMediaPlayerList = libvlc_media_list_player_new(vlc_base);
	 m_medialist = libvlc_media_list_new(vlc_base);
	 int size = fileList.size();
	 for (int i = 0; i < size; i++)
	 {
		 QString fileName = fileList[i];
		 fileName = QDir::toNativeSeparators(fileName);
		 libvlc_media_t* _pMedia = libvlc_media_new_path(vlc_base, fileName.toStdString().c_str());
		 if (!_pMedia) {
			 return -1;
		 }
		 libvlc_media_list_add_media(m_medialist, _pMedia);
		 libvlc_media_parse(_pMedia);
		 libvlc_time_t _duration = libvlc_media_get_duration(_pMedia);
		if (_duration<-1)
		 {
			 return -2;
		}
		m_vecDurations.push_back(_duration);
		 libvlc_media_release(_pMedia);
	 }
	 libvlc_media_list_player_set_media_list(m_pMediaPlayerList, m_medialist);
	 libvlc_media_list_player_set_media_player(m_pMediaPlayerList, vlc_mediaPlayer);
	 libvlc_media_player_set_hwnd(vlc_mediaPlayer, drawable);
	 libvlc_media_list_player_play(m_pMediaPlayerList);
	 setVideoPlayButtonContent(QStringLiteral("ÔÝÍ£"));
	 pause = false;
	 return 0;
}
void CvlcPlayKits::play() {
	if (!pause) {
		if (libvlc_media_player_get_state(vlc_mediaPlayer) == libvlc_state_t::libvlc_Paused ||
			libvlc_media_player_get_state(vlc_mediaPlayer) == libvlc_state_t::libvlc_Stopped) {

			setVideoPlayButtonContent(QStringLiteral("ÔÝÍ£"));
			libvlc_media_player_play(vlc_mediaPlayer);
		}
		else {
			if (libvlc_media_player_get_state(vlc_mediaPlayer) == libvlc_state_t::libvlc_Playing) {
				setVideoPlayButtonContent(QStringLiteral("¼ÌÐø"));
				libvlc_media_player_pause(vlc_mediaPlayer);
			}
		}
	}
	
}
void CvlcPlayKits::stop() {
	if (!pause) {

		if (libvlc_media_player_get_state(vlc_mediaPlayer) == libvlc_state_t::libvlc_Playing) {

			libvlc_media_player_stop(vlc_mediaPlayer);
		}
	}
}
void CvlcPlayKits::pauseMethod() {
	if (libvlc_media_player_get_state(vlc_mediaPlayer) == libvlc_state_t::libvlc_Playing) {
		libvlc_media_player_pause(vlc_mediaPlayer);
	}
}
bool CvlcPlayKits::getPasus() {
	return pause;
}
libvlc_media_player_t* CvlcPlayKits::media_player() {
	return vlc_mediaPlayer;
}

libvlc_time_t CvlcPlayKits::getDuration() {
	return m_totalSecs;
}
void CvlcPlayKits::setDuration(libvlc_time_t totalTime) {
	m_totalSecs = totalTime;
}
vector<libvlc_time_t> CvlcPlayKits::getVecDuration() {
	return m_vecDurations;
}

void CvlcPlayKits::setVecIndex() {
	m_vecIndex++;
}
int CvlcPlayKits::getVecIndex() {
	return m_vecIndex;
}

void CvlcPlayKits::setTimeSliderPos(const int& value) {
	emit sign_TimeSliderPos(value);
}
void CvlcPlayKits::setVolumeSliderPos(const int& value) {
	cout << "setVolumeSliderPos value = " << value << endl;
	emit sign_VolumeSliderPos(value);
}
void CvlcPlayKits::setVideoTimeContent(const QString& total, const QString& current) {
	emit sign_VideoTimeContent(total, current);
}
void CvlcPlayKits::setVideoPlayButtonContent(QString total) {
	emit sign_VideoPlayButtonContent(total);
}

CvlcPlayKits::~CvlcPlayKits()
{
	if (m_pEvent_manager)
	{
		m_pEvent_manager = nullptr;
	}
	if (vlc_mediaPlayer)
	{
		if (libvlc_media_player_is_playing(vlc_mediaPlayer))
		{
			libvlc_media_player_stop(vlc_mediaPlayer);
		}
		libvlc_media_player_release(vlc_mediaPlayer);
		vlc_mediaPlayer = nullptr;
	}
	if (vlc_media)
	{
		libvlc_media_release(vlc_media);
	}
	if (vlc_base)
	{
		libvlc_release(vlc_base);
	}
	vlc_base = nullptr;
}