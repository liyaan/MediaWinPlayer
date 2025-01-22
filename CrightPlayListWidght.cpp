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
	m_pSelectVideo->setText(u8"添加视频");
	m_pSelectVideo->setStyleSheet("QPushButton{color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:18px;border-radius: 20px;} QPushButton:hover{border-radius: 20px;}");
	m_qListWidget = new QListWidget(this);
	m_qListWidget->setFixedWidth(300);

	QString styleSheet = R"(
        QListWidget {
            background-color: #202020; /* 背景色 */
            border: 1px solid #ccc; /* 边框 */
            border-radius: 5px; /* 边框圆角 */
            padding: 5px; /* 内边距 */
        }
        QListWidget::item {
            height: 40px; /* 列表项高度 */
			color: white; /* 选中项文字颜色 */
        }
        QListWidget::item:selected {
            background-color: #3399ff; /* 选中项背景色 */
            color: white; /* 选中项文字颜色 */
        }
    )";
	m_qListWidget->setStyleSheet(styleSheet);
	QScrollBar* horizontalScrollBar = m_qListWidget->horizontalScrollBar();
	QScrollBar* verticalScrollBar = m_qListWidget->verticalScrollBar();
	horizontalScrollBar->setFixedHeight(10);
	verticalScrollBar->setFixedWidth(10);
	QString styleScrollHSheet = R"(
		QScrollBar {
			background-color: #f0f0f0; /* 滚动条背景颜色 */
			width: 12px; /* 滚动条宽度 */
			border: none; /* 滚动条边框取消 */
		}
		QScrollBar::handle {
			background-color: #c0c0c0; /* 滚动条滑块颜色 */
			border-radius: 4px; /* 滑块圆角 */
		}
		QScrollBar::add-line {
			background: none; /* 向下按钮背景色 */
			height: 10px; /* 向下按钮高度 */
			subcontrol-position: bottom; /* 位置 */
			subcontrol-origin: margin; /* 原点 */
		}
		QScrollBar::sub-line {
			background: none; /* 向上按钮背景色 */
			height: 10px; /* 向上按钮高度 */
			subcontrol-position: top; /* 位置 */
			subcontrol-origin: margin; /* 原点 */
		}
 
		QScrollBar::add-page, QScrollBar::sub-page {
			background: none; /* 滚动页背景色 */
		}
 
		QScrollBar:horizontal {
			height: 12px; /* 水平滚动条高度 */
		}
 
		QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
			width: 10px; /* 水平滚动条按钮宽度 */
		}
 
		QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
			background: none; /* 水平滚动页背景色 */
		}
		QScrollBar:vertical {
			width: 12px; /* 水平滚动条高度 */
		}
 
		QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
			height: 10px; /* 水平滚动条按钮宽度 */
		}
 
		QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
			background: none; /* 水平滚动页背景色 */
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
	QString filename = QFileDialog::getOpenFileName(this, "选择打开的文件", "D:/", tr("*.*"));
	std::replace(filename.begin(), filename.end(), QChar('/'), QChar('\\'));
	qDebug() << "播放的媒体:" << filename;
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
