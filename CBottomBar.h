#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include "CvlcPlayKits.h"
#include <QMoveEvent>
#include <windows.h>
class CBottomBar : public QWidget
{
	Q_OBJECT

public:
	CBottomBar(CvlcPlayKits* clv, QWidget *parent= nullptr);
	~CBottomBar();
	void resizeEvent(QResizeEvent *event) override;
	void setVolumeSliderPos(int value);
	
private:
	void initUI();
	void initConnect();
private slots :
	void onClicked();
	void VolumeSliderMove(int);
signals :
	void sign_bottom_click(int value);
private:
	QPushButton* m_pRtmpBtn;
	QPushButton* m_pStopBtn;
	QPushButton* m_pUpBtn;
	QPushButton* m_pPlayBtn;
	QPushButton* m_pNextBtn;
	QPushButton* m_pVolumBtn;
	QPushButton* m_pSettingBtn;
	QPushButton* m_pPlayListBtn;
	QPushButton* m_pAllScreenBtn;
	QSlider* m_QSlider;
	CvlcPlayKits *m_Pvlc;
	float rate = 1.0;
};
