#include "CrightPlayListWidght.h"

CrightPlayListWidght::CrightPlayListWidght(CvlcPlayKits* clv, QSqlData* qSqlData, QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground);
	m_Pvlc = clv;
	m_qSqlData = qSqlData;
	m_Utils = new Utils();
	this->setFixedWidth(300);
	this->setStyleSheet("background-color:rgb(30,30,50)");
	initUI();
	initConnect();
}
void CrightPlayListWidght::initUI() {
	QVBoxLayout* pVlay = new  QVBoxLayout(this);
	pVlay->setContentsMargins(0, 0, 0, 0);
	m_pSelectVideo = new QPushButton(this);
	m_pSelectVideo->setFixedHeight(40);
	m_pSelectVideo->setText(u8"�����Ƶ");
	m_pSelectVideo->setStyleSheet("QPushButton{color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:18px;border-radius: 20px;} QPushButton:hover{border-radius: 20px;}");
	m_qListWidget = new QListWidget(this);
	m_qListWidget->setFixedWidth(300);

	QString styleSheet = R"(
        QListWidget {
            background-color: #202020; /* ����ɫ */
            border: 1px solid #ccc; /* �߿� */
            border-radius: 5px; /* �߿�Բ�� */
            padding: 5px; /* �ڱ߾� */
        }
        QListWidget::item {
            height: 40px; /* �б���߶� */
			color: white; /* ѡ����������ɫ */
        }
        QListWidget::item:selected {
            background-color: #3399ff; /* ѡ�����ɫ */
            color: white; /* ѡ����������ɫ */
        }
    )";
	m_qListWidget->setStyleSheet(styleSheet);
	QScrollBar* horizontalScrollBar = m_qListWidget->horizontalScrollBar();
	QScrollBar* verticalScrollBar = m_qListWidget->verticalScrollBar();
	horizontalScrollBar->setFixedHeight(10);
	verticalScrollBar->setFixedWidth(10);
	QString styleScrollHSheet = R"(
		QScrollBar {
			background-color: #f0f0f0; /* ������������ɫ */
			width: 12px; /* ��������� */
			border: none; /* �������߿�ȡ�� */
		}
		QScrollBar::handle {
			background-color: #c0c0c0; /* ������������ɫ */
			border-radius: 4px; /* ����Բ�� */
		}
		QScrollBar::add-line {
			background: none; /* ���°�ť����ɫ */
			height: 10px; /* ���°�ť�߶� */
			subcontrol-position: bottom; /* λ�� */
			subcontrol-origin: margin; /* ԭ�� */
		}
		QScrollBar::sub-line {
			background: none; /* ���ϰ�ť����ɫ */
			height: 10px; /* ���ϰ�ť�߶� */
			subcontrol-position: top; /* λ�� */
			subcontrol-origin: margin; /* ԭ�� */
		}
 
		QScrollBar::add-page, QScrollBar::sub-page {
			background: none; /* ����ҳ����ɫ */
		}
 
		QScrollBar:horizontal {
			height: 12px; /* ˮƽ�������߶� */
		}
 
		QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
			width: 10px; /* ˮƽ��������ť��� */
		}
 
		QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
			background: none; /* ˮƽ����ҳ����ɫ */
		}
		QScrollBar:vertical {
			width: 12px; /* ˮƽ�������߶� */
		}
 
		QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
			height: 10px; /* ˮƽ��������ť��� */
		}
 
		QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
			background: none; /* ˮƽ����ҳ����ɫ */
		}
		)";
	horizontalScrollBar->setStyleSheet(styleScrollHSheet);
	verticalScrollBar->setStyleSheet(styleScrollHSheet);
	pVlay->addWidget(m_pSelectVideo);
	pVlay->addWidget(m_qListWidget);
	
}
void CrightPlayListWidght::initConnect() {
	connect(m_pSelectVideo, &QPushButton::clicked, this, &CrightPlayListWidght::onClickSelectVideo);
	connect(m_qListWidget, &QListWidget::itemClicked,this, &CrightPlayListWidght::onItemClick);
}
void CrightPlayListWidght::onClickSelectVideo() {
	QString filename = QFileDialog::getOpenFileName(this, "ѡ��򿪵��ļ�", "D:/", tr("*.*"));
	std::replace(filename.begin(), filename.end(), QChar('/'), QChar('\\'));
	qDebug() << "���ŵ�ý��:" << filename;
	m_qSqlData->insertData(filename);

	
	QString justFileName = m_Utils->baseName(filename).arg(m_qListWidget->count() + 1);
	QListWidgetItem *item = new QListWidgetItem(justFileName);
	m_qListWidget->addItem(item);
	//item->setSelected(true);

	//m_qListWidget->clear();
	//QStringList list = m_qSqlData->readDataList();
	//for (int i = 0; i < list.size(); i++)
	//{
		//m_qListWidget->addItem(list[i]);
	//}
}
void CrightPlayListWidght::onItemClick(QListWidgetItem *item) {
	qDebug() << "Clicked item: " << item->text();
	
	emit onSignItemClick(item->text());
	qDebug() << "Clicked item: " << item->text();
}
void CrightPlayListWidght::resizeEvent(QResizeEvent* event) {
	if (m_qListWidget && m_pSelectVideo) {
		m_qListWidget->resize(this->width()-5, this->height()-40);
		m_pSelectVideo->resize(this->width(),0);
	}

}
void CrightPlayListWidght::showEvent(QShowEvent *event) {
	if (m_qListWidget) {
		
		m_qListWidget->clear();
		QStringList list = m_qSqlData->readDataList();
		m_qListWidget->addItems(list);
		if (!selectedItemText.isEmpty())
		{
			int index = list.indexOf(selectedItemText);
			m_qListWidget->item(index)->setSelected(true);
		}
	}
}
void CrightPlayListWidght::hideEvent(QHideEvent *event) {
	qDebug() << "selectedItem " << "hideEvent";
}
QListWidget* CrightPlayListWidght::getQListWidget() {
	return m_qListWidget;
}
void CrightPlayListWidght::setSelectedItemText(QString text) {
	selectedItemText = text;
}
CrightPlayListWidght::~CrightPlayListWidght()
{
}
