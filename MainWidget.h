#pragma once

#include <QtWidgets/QWidget>
#include "CTitleBar.h"
#include "CBottomBar.h"
#include "VideoWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CFrameLessWidgetBase.h"
#include "CrightPlayListWidght.h"
#include <memory>
using namespace std;
class MainWidget : public CFrameLessWidgetBase
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = Q_NULLPTR);
	~MainWidget();
private:
	void initUI();
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
private slots:
	void onCloseSlot();
	void onClickSlot(int value);
private:
	CTitleBar *m_pTitleBar = nullptr;
	CrightPlayListWidght* m_pRightPlayListWidght = nullptr;
	VideoWidget* m_pVideoWidget = nullptr;
	CBottomBar* m_pBottomBar = nullptr;
	std::unique_ptr<CvlcPlayKits> m_Pvlc;
	QSqlData* m_QSqlData = nullptr;
	
};
