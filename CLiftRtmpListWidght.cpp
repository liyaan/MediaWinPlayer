#include "CLiftRtmpListWidght.h"

CLiftRtmpListWidght::CLiftRtmpListWidght(CvlcPlayKits* clv, QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground);
	m_Pvlc = clv;
	this->setFixedWidth(200);
	this->setStyleSheet("background-color:rgb(30,30,50)");
	initUI();
}
void CLiftRtmpListWidght::initUI() {
	QVBoxLayout* pVlay = new  QVBoxLayout(this);
	
	m_pSelectVideo = new QPushButton(this);
	m_pSelectVideo->setFixedHeight(40);
	m_pSelectVideo->setText(u8"播放");
	m_pSelectVideo->setStyleSheet("QPushButton{color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:18px;border-radius: 20px;} QPushButton:hover{border-radius: 20px;}");
	m_pQTextEdit = new QTextEdit();
	m_pQTextEdit->setFixedWidth(200);
	m_pQTextEdit->setPlaceholderText(u8"请输入播放地址");
	m_pQTextEdit->setStyleSheet("QTextEdit{background-color:rgb(30,30,50);border-color: #483d8b;font-size:18px;border-radius: 20px; color:#ffffff;padding:5px;}");
	m_pQTextEdit->setContentsMargins(10, 10, 10, 10);
	m_pQLabel = new QLabel(u8"支持http rtmp rtsp视频播放");
	m_pQLabel->setFixedWidth(200);
	m_pQLabel->setWordWrap(true);
	m_pQLabel->setStyleSheet("QLabel{font-size:14px;color:#ffffff;padding:5px;}");
	m_pQLabel->setContentsMargins(10, 10, 10, 10);
	pVlay->addWidget(m_pQTextEdit);
	pVlay->addWidget(m_pQLabel);
	pVlay->addWidget(m_pSelectVideo);
	pVlay->setContentsMargins(0, 0, 0, 0);
	connect(m_pSelectVideo, &QPushButton::clicked, this, &CLiftRtmpListWidght::onClickPlayVideo);
	connect(m_pQTextEdit, &QTextEdit::textChanged, this, &CLiftRtmpListWidght::getTextChanged);
}
void CLiftRtmpListWidght::getTextChanged() {
	m_pContent = m_pQTextEdit->toPlainText();
}
void CLiftRtmpListWidght::onClickPlayVideo() {
	if (!m_pContent.isEmpty())
	{
		emit onSignItemClick(m_pContent);
		m_pQTextEdit->setText("");
	}
	
}
void CLiftRtmpListWidght::resizeEvent(QResizeEvent *event) {
	if (m_pQTextEdit && m_pQLabel)
	{
		m_pQTextEdit->resize(this->width(), this->height()-260);
		m_pQLabel->resize(200, 60);
	}
}
CLiftRtmpListWidght::~CLiftRtmpListWidght()
{
}
