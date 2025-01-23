#include "CBottomBar.h"
void buttonStyle(QPushButton* btn,QString content) {
	//m_pStopBtn = new QPushButton(this);
	btn->setFixedSize(60, 25);
	btn->setText(content);
	btn->setStyleSheet("QPushButton{background-color:rgb(54,54,112);color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:18px;} QPushButton:hover{border:none;background-color:rgb(105,105,105)}");
}
void buttonStyle(QPushButton* btn) {
	//m_pStopBtn = new QPushButton(this);
	btn->setFixedSize(40, 20);
	btn->setStyleSheet("QPushButton{background-color:rgb(54,54,54);color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:14px;}");
}
CBottomBar::CBottomBar(CvlcPlayKits* clv,QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground);
	m_Pvlc = clv;
	this->setFixedHeight(80);
	this->setStyleSheet("background-color:rgb(54,54,54)");
	initUI();
	initConnect();
}
void CBottomBar::initUI() {
	QVBoxLayout *pBVMlay = new QVBoxLayout(this);
	pBVMlay->setContentsMargins(0, 0, 0, 0);
	
	
	
//	pBVMlay->addLayout(pBProTime);
	m_pRtmpBtn = new QPushButton(this);
	m_pRtmpBtn->setFixedSize(60, 25);
	m_pRtmpBtn->setText(u8"网络视频");
	m_pRtmpBtn->setStyleSheet("QPushButton{color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:10px;}");

	m_pStopBtn = new QPushButton(this);
	buttonStyle(m_pStopBtn,u8"停止");

	m_pUpBtn = new QPushButton(this);
	buttonStyle(m_pUpBtn, u8"上");

	m_pPlayBtn = new QPushButton(this);
	buttonStyle(m_pPlayBtn, u8"播放");

	m_pNextBtn = new QPushButton(this);
	buttonStyle(m_pNextBtn, u8"下");
	
	m_QSlider = new QSlider(this);
	m_QSlider->setFixedSize(150, 10);
	m_QSlider->setOrientation(Qt::Horizontal);

	m_pVolumBtn = new QPushButton(this);
	buttonStyle(m_pVolumBtn);
	m_pVolumBtn->setText("0%");

	QHBoxLayout *pBHMlay = new QHBoxLayout(this);
	QHBoxLayout *pHlay = new QHBoxLayout(this);
	pHlay->addWidget(m_pRtmpBtn);
	pHlay->addStretch();
	pHlay->addWidget(m_pStopBtn);
	pHlay->addWidget(m_pUpBtn);
	pHlay->addWidget(m_pPlayBtn);

	pHlay->addWidget(m_pNextBtn);
	pHlay->addWidget(m_QSlider);
	pHlay->addWidget(m_pVolumBtn);
	pHlay->addStretch();
	pBHMlay->addLayout(pHlay);

	QHBoxLayout *pHRlay = new QHBoxLayout(this);

	m_pSettingBtn = new QPushButton(this);
	buttonStyle(m_pSettingBtn, u8"1.0");

	m_pPlayListBtn = new QPushButton(this);
	buttonStyle(m_pPlayListBtn, u8"列表");

	m_pAllScreenBtn = new QPushButton(this);
	buttonStyle(m_pAllScreenBtn, u8"全屏");

	pHRlay->addWidget(m_pSettingBtn);
	pHRlay->addWidget(m_pPlayListBtn);
	pHRlay->addWidget(m_pAllScreenBtn);
	pHRlay->setContentsMargins(0, 0, 20, 0);
	pBHMlay->addLayout(pHRlay);
	pBVMlay->addLayout(pBHMlay);
	connect(m_pRtmpBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
	connect(m_pStopBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
	connect(m_pUpBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
	connect(m_pPlayBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);

	connect(m_pNextBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
	connect(m_pVolumBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
	connect(m_pSettingBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);

	connect(m_pPlayListBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
	connect(m_pAllScreenBtn, &QPushButton::clicked, this, &CBottomBar::onClicked);
}

void CBottomBar::initConnect() {
	connect(m_Pvlc, &CvlcPlayKits::sign_VolumeSliderPos, this, &CBottomBar::setVolumeSliderPos);
	connect(m_QSlider, &QAbstractSlider::sliderMoved, this, &CBottomBar::VolumeSliderMove);
	connect(m_Pvlc, &CvlcPlayKits::sign_VideoPlayButtonContent, [=](QString total) {
		m_pPlayBtn->setText(total);
	});
}
void CBottomBar::VolumeSliderMove(int value) {
	libvlc_audio_set_volume(m_Pvlc->media_player(), value);
}
void CBottomBar::setVolumeSliderPos(int value) {
	m_QSlider->setValue(value);
	char buf[128] = { 0 };
	sprintf(buf, "%2d", value);

	m_pVolumBtn->setText(QString(buf) + "%");
}
void CBottomBar::onClicked() {
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());
	QWidget* qWindow = this->window();
	if (pButton == m_pStopBtn) {
		if (m_Pvlc)
		{
			m_Pvlc->stop();
		}
	}else if (pButton == m_pUpBtn) {
		emit sign_bottom_click(2);
	}
	else if (pButton == m_pPlayBtn) {
		if (m_Pvlc)
		{
			m_Pvlc->play();
		}
	}
	else if (pButton == m_pNextBtn) {
		emit sign_bottom_click(4);
	}
	else if (pButton == m_pVolumBtn) {
		emit sign_bottom_click(5);
	}
	else if (pButton == m_pSettingBtn) {
		rate += 0.5;
		if (rate>2)
		{
			rate = 1.0;
		}
		libvlc_media_player_set_rate(m_Pvlc->media_player(), rate);
		char buf[128] = { 0 };
		sprintf(buf, "%.1f", rate);
		m_pSettingBtn->setText(QString(buf));
	}
	else if (pButton == m_pPlayListBtn) {
		emit sign_bottom_click(6);
	}
	else if (pButton == m_pAllScreenBtn) {
		emit sign_bottom_click(7);
	}
	else if (pButton == m_pRtmpBtn) {
		emit sign_bottom_click(8);
	}
}
CBottomBar::~CBottomBar()
{
}
void CBottomBar::resizeEvent(QResizeEvent* event) {
	

}
