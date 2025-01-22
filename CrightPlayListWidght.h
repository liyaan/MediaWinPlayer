#pragma once

#include <QWidget>
#include <QPushButton>
#include "CvlcPlayKits.h"
#include "QSqlData.h"
#include <QFileDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QScrollBar>
#include "Utils.h"
class CrightPlayListWidght : public QWidget
{
	Q_OBJECT

public:
	CrightPlayListWidght(CvlcPlayKits* clv, QSqlData* qSqlData, QWidget *parent = nullptr);
	~CrightPlayListWidght();
	void resizeEvent(QResizeEvent *event) override;
	void showEvent(QShowEvent *event) override;
	void hideEvent(QHideEvent *event) override;
	QListWidget* getQListWidget();
	void setSelectedItemText(QString text);
private:
	void initUI();
	void initConnect();
private slots:
	void onClickSelectVideo();
	void onItemClick(QListWidgetItem *item);
signals:
	void onSignItemClick(QString name);
private:
	QPushButton* m_pSelectVideo = nullptr;
	CvlcPlayKits *m_Pvlc = nullptr;
	QSqlData* m_qSqlData;
	QListWidget* m_qListWidget;
	Utils* m_Utils = nullptr;
	QListWidgetItem *selectedItem = nullptr;

	QString selectedItemText = nullptr;

};
