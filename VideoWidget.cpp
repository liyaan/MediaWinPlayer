#include "VideoWidget.h"

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam) {
	TCHAR szTitle[1024];
	int nLen = GetWindowText(hwnd, szTitle, 1024);
	if (nLen>0)
	{
		EnableWindow(hwnd, FALSE);
		KillTimer(NULL, 1);
	}
	return TRUE;
}

void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time) {
	HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"vlclyamain");
	if (vlcHwnd)
	{
		EnumChildWindows(vlcHwnd, lpEnumFunc, NULL);
	}
}

VideoWidget::VideoWidget(CvlcPlayKits* clv, QSqlData* qSqlData, CrightPlayListWidght* crightPlayListWidght, CBottomBar* cBottomBar, CLiftRtmpListWidght* cLiftRtmpListWidght, QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground);
	m_Pvlc = clv;
	m_CrightPlayListWidght = crightPlayListWidght;
	m_CBottomBar = cBottomBar;
	m_qSqlData = qSqlData;
	m_pCLiftRtmpListWidght = cLiftRtmpListWidght;
	m_Utils = new Utils();
	initUI();
	initConnect();
	
}
void VideoWidget::initUI() {
	this->setMinimumSize(800, 600);
	this->setStyleSheet("background-color:rgb(17,17,17)");
	

	m_pVideoWidget = new QWidget(this);
	m_pVideoWidget->resize(width(), height());
	
	m_pSelectVideo = new QPushButton(this);
	m_pSelectVideo->setFixedSize(100, 40);
	m_pSelectVideo->setText(u8"选择视频");
	m_pSelectVideo->setStyleSheet("QPushButton{background-color:rgb(54,54,112);color:#ffffff;padding-top:2px;padding-bottom:2px;font-size:18px;border-radius: 20px;} QPushButton:hover{border:none;border-radius: 20px;}");
	
	pBProTime = new QHBoxLayout(this);
	m_QProgressBar = new QSlider(this);
	m_QProgressBar->setOrientation(Qt::Horizontal);
	m_QProgressBar->setFixedHeight(10);
	m_QProgressBar->setStyleSheet(R"(
        QSlider::groove:horizontal {
            border: 1px solid #999999;
            height: 8px;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                        stop:0 #B9B9B9, stop:1 #c4c4c4);
            margin: 2px 0;
        }
        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                        stop:0 #b4b4b4, stop:1 #8f8f8f);
            border: 1px solid #5c5c5c;
            width: 18px;
            margin: -2px 0;
        }
        QSlider {
            width: 200px;  
        }
		QSlider::add-page:horizontal {
                  background: #aaaaaa;
             }
		QSlider::sub-page:Horizontal
		{
		background-color:rgb(54,54,112);
		}
    )");
	m_QLabel = new QLabel(this);
	m_QLabel->setText("00:00:00/00:00:00");
	m_QLabel->setStyleSheet("QLabel{font-size:18px;color:#ffffff;}");

	pBProTime->addWidget(m_QProgressBar);
	pBProTime->addWidget(m_QLabel);
	//m_pSelectVideo->setGeometry(150, 150, 100, 40);
	
	
}
VideoWidget::~VideoWidget()
{
}
void VideoWidget::resizeEvent(QResizeEvent* event){
	if (m_pSelectVideo && m_pVideoWidget) {
		int x1 = this->width() / 2 -  m_pSelectVideo->width() / 2;
		int y1 = this->height() / 2 - m_pSelectVideo->height() / 2;
		m_pSelectVideo->move(x1, y1);
		m_pVideoWidget->resize(this->width(), this->height());
	}

	if (pBProTime && m_QProgressBar) {
		pBProTime->setContentsMargins(10, this->height()-28, 10, 0);
		m_QProgressBar->setFixedWidth(this->width() - 180);
	}

}
void VideoWidget::initConnect() {
	connect(m_pSelectVideo, &QPushButton::clicked, this, &VideoWidget::onClicked);

	connect(m_QProgressBar, &QAbstractSlider::sliderMoved, this, &VideoWidget::ProgressSliderMove);

	connect(m_Pvlc, &CvlcPlayKits::sign_VideoTimeContent, this, &VideoWidget::setVideoTimeContent);

	connect(m_Pvlc, &CvlcPlayKits::sign_TimeSliderPos, this, &VideoWidget::setTimeSliderPos);

	//connect(m_QProgressBar, &QSlider::valueChanged, this, &VideoWidget::ProgressSliderMove);

	connect(m_Pvlc, &CvlcPlayKits::sign_VideoTimeProgress, this, &VideoWidget::VideoTimeProgress);
	connect(m_CrightPlayListWidght, &CrightPlayListWidght::onSignItemClick, this, &VideoWidget::onRightItemClick);
	connect(m_pCLiftRtmpListWidght, &CLiftRtmpListWidght::onSignItemClick, this, &VideoWidget::onLeftItemClick);
	connect(m_CBottomBar, &CBottomBar::sign_bottom_click, this, &VideoWidget::signBottomClick);

	connect(m_Pvlc, &CvlcPlayKits::sign_YsQPixmap, this, &VideoWidget::signYsQPixmap);
	connect(m_Pvlc, &CvlcPlayKits::sign_ClYsQPixmap, this, &VideoWidget::signClYsQPixmap);
}
void VideoWidget::onRightItemClick(QString name) {
	QString path = m_qSqlData->readData(name);
	if (m_Pvlc && !path.isEmpty())
	{
		int type = m_Pvlc->play(path, (void*)m_pVideoWidget->winId());
		if (type != 0)
		{
			QMessageBox::information(this, u8"提示", u8"播放失败");
			return;
		}
		else if (type == 0) {
			m_pSelectVideo->hide();
			selectName = name;
			m_CrightPlayListWidght->setSelectedItemText(selectName);
		}
		
	}
	SetTimer(NULL, 1, 300, TimeProc);
}
void VideoWidget::onLeftItemClick(QString path) {
	if (m_Pvlc && !path.isEmpty())
	{
		m_pSelectVideo->hide();
		int type = m_Pvlc->playRtmp(path, (void*)m_pVideoWidget->winId());
		if (type != 0)
		{
			QMessageBox::information(this, u8"提示", u8"播放失败");
			return;
		}
		else if (type == 0) {
			
		}

	}
	SetTimer(NULL, 1, 300, TimeProc);
}
void VideoWidget::setTimeSliderPos(int value) {
	m_QProgressBar->setValue(value);
}

void VideoWidget::setVideoTimeContent(QString total, QString current) {
	m_QLabel->setText(current+"/"+ total);
}
void VideoWidget::ProgressSliderMove(int value) {
	libvlc_media_player_set_position(m_Pvlc->media_player(), value / 100.0);
}
void VideoWidget::VideoTimeProgress(float value) {
	if (value > 99) {
		m_pSelectVideo->show();
	}
}
void VideoWidget::signBottomClick(int value) {
	QStringList list = m_qSqlData->readDataList();
	int selectIndex = -1;
	int index = -1;
	listWidght = m_CrightPlayListWidght->getQListWidget();
	if (list.size()>0 && listWidght->count()>0)
	{
		if (!selectName.isEmpty())
		{
			index = list.indexOf(selectName);
		}
		selectIndex = index;
		if (value == 2)
		{
			if (index>0)
			{
				index--;
			}

		}
		else if (value == 4)
		{
			if (list.size()-1>index)
			{
				index++;
			}

		}
		if (selectIndex!=index)
		{
			
			listWidght->item(index)->setSelected(true);
			onRightItemClick(list[index]);
		}
	}
	
}
void VideoWidget::onClicked() {
	QStringList filenames = QFileDialog::getOpenFileNames(this, u8"选择打开的文件", ":", tr("*.*"));
	if (filenames.size() == 1) {
		QString filename = filenames[0];
		std::replace(filename.begin(), filename.end(), QChar('/'), QChar('\\'));
		qDebug() << "播放的媒体:" << filename;
		if (m_Pvlc)
		{
			int type = m_Pvlc->play(filename, (void*)m_pVideoWidget->winId());
			if (type != 0)
			{
				QMessageBox::information(this, u8"提示", u8"播放失败");
				return;
			}
			else if (type == 0) {
				m_pSelectVideo->hide();
				m_qSqlData->insertData(filename);
				listWidght = m_CrightPlayListWidght->getQListWidget();
				QString justFileName = m_Utils->baseName(filename).arg(listWidght->count() + 1);
				QListWidgetItem *item = new QListWidgetItem(justFileName);
				listWidght->addItem(item);
				item->setSelected(true);
				m_CrightPlayListWidght->setSelectedItemText(justFileName);
			}
			
			//m_qSqlData->readDataList();
			//m_qSqlData->readData("0962fe185a92ab2bcc7ba0007034a31c");
		}

	}
	else {
		if (m_Pvlc)
		{
			if (m_Pvlc->play(filenames, (void*)m_pVideoWidget->winId()) != 0)
			{
				QMessageBox::information(this, u8"提示", u8"播放失败");
				return;
			}
			if (filenames.size()>1)
			{
				m_pSelectVideo->hide();
			}
			
		}
	}
	
	SetTimer(NULL, 1, 300, TimeProc);
}
void VideoWidget::signYsQPixmap(QPixmap value) {
	m_QYImage->setPixmap(value);
}
void VideoWidget::signClYsQPixmap(QPixmap value) {
	m_QYcImage->setPixmap(value);
}
