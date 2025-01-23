#pragma once

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QMessageBox>
#include <windows.h>
#include <QFileDialog>
#include <QDebug>
#include <memory>
#include "CvlcPlayKits.h"
#include <QSlider>
#include <QLabel>
#include <QtWidgets/QWidget>
#include <QAbstractSlider>
#include <QStyleFactory>
#include "QSqlData.h"
#include "CrightPlayListWidght.h"
#include "CBottomBar.h"
#include "CLiftRtmpListWidght.h"
#include "Utils.h"
class VideoWidget : public QWidget
{
	Q_OBJECT

public:
	VideoWidget(CvlcPlayKits* clv, QSqlData* qSqlData, CrightPlayListWidght* crightPlayListWidght, CBottomBar* cBottomBar, CLiftRtmpListWidght* cLiftRtmpListWidght,QWidget *parent = nullptr);
	~VideoWidget();
	void resizeEvent(QResizeEvent *event) override;
	void setTimeSliderPos(int value);
	void setVideoTimeContent(QString total, QString current);
private:
	void initUI();
	void initConnect();
private slots:
	void onClicked();
	void ProgressSliderMove(int);
	void VideoTimeProgress(float);
	void onRightItemClick(QString path);
	void onLeftItemClick(QString path);
	void signBottomClick(int);
private:
	QWidget* m_pVideoWidget = nullptr;
	QPushButton* m_pSelectVideo = nullptr;
	QSlider* m_QProgressBar;
	QLabel* m_QLabel;
	QHBoxLayout *pBProTime;
	CvlcPlayKits *m_Pvlc;
	QSqlData* m_qSqlData;
	CrightPlayListWidght* m_CrightPlayListWidght;
	CBottomBar* m_CBottomBar;
	QString selectName = nullptr;
	Utils* m_Utils = nullptr;
	QListWidget* listWidght = nullptr;
	CLiftRtmpListWidght* m_pCLiftRtmpListWidght = nullptr;
private slots:
	
signals:

};
