#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
	: CFrameLessWidgetBase(parent)
{
	this->setWindowTitle("vlclyamain");
	m_Pvlc.reset(new CvlcPlayKits());
	m_QSqlData = new QSqlData();
	int ret = m_Pvlc->initVLC();
	switch (ret)
	{
	case -1:
	case -2:
		exit(EXIT_FAILURE);
	}
	initUI();

}
void MainWidget::onCloseSlot() {
	close();
}
void MainWidget::initUI() {
	m_pTitleBar = new CTitleBar(this);
	m_pRightPlayListWidght = new CrightPlayListWidght(m_Pvlc.get(), m_QSqlData, this);
	m_pCLiftRtmpListWidght = new CLiftRtmpListWidght(m_Pvlc.get(), this);
	m_pBottomBar = new CBottomBar(m_Pvlc.get(), this);
	m_pVideoWidget = new VideoWidget(m_Pvlc.get(), m_QSqlData, m_pRightPlayListWidght, m_pBottomBar, m_pCLiftRtmpListWidght, this);
	QVBoxLayout* pVlay = new  QVBoxLayout(this);
	
	m_pCLiftRtmpListWidght->hide();
	m_pRightPlayListWidght->hide();
	pVlay->addWidget(m_pTitleBar);
	pVlay->setSpacing(0);
	QHBoxLayout *pHlay = new QHBoxLayout(this);
	pHlay->addWidget(m_pCLiftRtmpListWidght);
	pHlay->addWidget(m_pVideoWidget);
	pHlay->addWidget(m_pRightPlayListWidght);
	pHlay->setContentsMargins(0, 0, 0, 0);

	pVlay->addLayout (pHlay);
	pVlay->addWidget(m_pBottomBar);
	pVlay->setContentsMargins(0, 0, 0, 0);
	connect(m_pTitleBar, &CTitleBar::sign_close, this, &MainWidget::onCloseSlot);

	connect(m_pBottomBar, &CBottomBar::sign_bottom_click, this, &MainWidget::onClickSlot);
}
void MainWidget::onClickSlot(int value) {
	if (value==7)
	{
		if (this->isFullScreen())
		{
			this->showNormal();
		}
		else {
			this->showFullScreen();
		}
	}
	else if (value == 6) {
		if (m_pRightPlayListWidght->isHidden())
		{
			m_pRightPlayListWidght->show();
		}
		else {
			m_pRightPlayListWidght->hide();
		}
		
	}
	else if (value == 8) {
		if (m_pCLiftRtmpListWidght->isHidden())
		{
			m_pCLiftRtmpListWidght->show();
		}
		else {
			m_pCLiftRtmpListWidght->hide();
		}

	}
}
void MainWidget::mouseDoubleClickEvent(QMouseEvent* event) {
	if (this->isFullScreen())
	{
		this->showNormal();
	}
	else {
		this->showFullScreen();
	}

}
void MainWidget::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape)
	{
		if (this->isFullScreen()) {
			this->showNormal();
		}
	}
}
MainWidget::~MainWidget() {
	m_QSqlData->close();
}

