#include "CTitleBar.h"

CTitleBar::CTitleBar(QWidget* p)
{
	initUI();
}
void CTitleBar::initUI() {
	/*
	QLabel* m_pLogo;
	QLabel* m_titleTextLabel;

	QPushButton* m_pSetBtn;
	QPushButton* m_pMinBtn;
	QPushButton* m_pMaxBtn;
	QPushButton* m_pCloseBtn;*/
	setAttribute(Qt::WA_StyledBackground);
	this->setFixedHeight(42);
	this->setStyleSheet("background-color:rgb(30,30,30)");
	m_pLogo = new QLabel(this);
	m_pLogo->setFixedSize(32, 32);
	m_pLogo->setStyleSheet("QLabel{background-image: url(:/MainWidget/Release/title/icon.png);border:none;}");

	m_titleTextLabel = new QLabel(this);
	m_titleTextLabel->setText(u8"播放器");
	m_titleTextLabel->setFixedWidth(120);
	m_titleTextLabel->setStyleSheet("QLabel{font-size:18px;color:#ffffff;}");


	m_pSetBtn = new QPushButton(this);
	m_pSetBtn->setFixedSize(32, 32);
	m_pSetBtn->setStyleSheet("QPushButton{background-image:url(:/MainWidget/Resources/title/max.svg);border:none;} QPushButton:hover{background-image:url(:/MainWidget/Resources/title/max_hover.svg);border:none;background-color:rgb(54,54,99)}");

	m_pMinBtn = new QPushButton(this);
	m_pMinBtn->setFixedSize(32, 32);
	m_pMinBtn->setText(u8"小");
	m_pSetBtn->setStyleSheet("QPushButton{background-image:url(:/MainWidget/Resources/title/min.svg);border:none;font-size:12px;} QPushButton:hover{background-image:url(:/MainWidget/Resources/title/min_hover.svg);border:none;background-color:rgb(54,54,77)}");

	m_pMaxBtn = new QPushButton(this);
	m_pMaxBtn->setFixedSize(32, 32);
	m_pMaxBtn->setText(u8"大");
	m_pSetBtn->setStyleSheet("QPushButton{background-image:url(:/MainWidget/Resources/title/max.svg);border:none;font-size:12px;} QPushButton:hover{background-image:url(:/MainWidget/Resources/title/max_hover.svg);border:none;background-color:rgb(54,54,100)}");

	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setFixedSize(32, 32);
	m_pCloseBtn->setText(u8"关");
	m_pSetBtn->setStyleSheet("QPushButton{background-image:url(:/MainWidget/Resources/title/close.svg);border:none;font-size:12px;} QPushButton:hover{background-image:url(:/MainWidget/Resources/title/close_hover.svg);border:none;background-color:rgb(54,54,150)}");

	QHBoxLayout *pHlay = new QHBoxLayout(this);
	pHlay->addWidget(m_pLogo);
	pHlay->addWidget(m_titleTextLabel);
	pHlay->addStretch();
	pHlay->addWidget(m_pSetBtn);
	QSpacerItem* pIteml = new QSpacerItem(20, 20, QSizePolicy::Fixed,
			QSizePolicy::Fixed);
	pHlay->addSpacerItem(pIteml);

	pHlay->addWidget(m_pMinBtn);
	QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed,
		QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem2);
	pHlay->addWidget(m_pMaxBtn);

	QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed,
		QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem3);
	pHlay->addWidget(m_pCloseBtn);
	
	pHlay->setContentsMargins(5, 5, 5, 5);

	connect(m_pMinBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pMaxBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pCloseBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
}

void CTitleBar::mousePressEvent(QMouseEvent* event) {
	if (ReleaseCapture())
	{
		QWidget* qWindow = this->window();
		if (qWindow->isTopLevel())
		{
			SendMessage(HWND(qWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
}
void CTitleBar::onClicked() {
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());
	QWidget* qWindow = this->window();
	if (pButton==m_pMinBtn)
	{
		qWindow->showMinimized();
	}else if (pButton == m_pMaxBtn) {
		
		if (qWindow->isMaximized())
		{
			qWindow->showNormal();
		}
		else {
			qWindow->showMaximized();
		}
	}
	else if (pButton == m_pCloseBtn) {
		emit sign_close();
	}
}
CTitleBar::~CTitleBar()
{
}
