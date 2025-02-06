#pragma once

#include <QWidget>
#include "CvlcPlayKits.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
class CLiftRtmpListWidght : public QWidget
{
	Q_OBJECT

public:
	CLiftRtmpListWidght(CvlcPlayKits* clv, QWidget *parent = nullptr);
	~CLiftRtmpListWidght();
private:
	void initUI();
	void onClickPlayVideo();
	void resizeEvent(QResizeEvent *event) override;
private slots:
	void getTextChanged();
signals:
	void onSignItemClick(QString name);
private:
	CvlcPlayKits *m_Pvlc = nullptr;
	QPushButton* m_pSelectVideo = nullptr;
	QTextEdit* m_pQTextEdit = nullptr;
	QLabel* m_pQLabel = nullptr;
	QString m_pContent;
};
