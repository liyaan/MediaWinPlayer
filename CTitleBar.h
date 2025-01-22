#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <qt_windows.h>
class CTitleBar : public QWidget

{
	Q_OBJECT

public:
	CTitleBar(QWidget* p = nullptr);
	~CTitleBar();
private:
	void initUI();
	void mousePressEvent(QMouseEvent* event) override;
private slots:
	void onClicked();
signals:
	void sign_close();
private:
	QLabel* m_pLogo;
	QLabel* m_titleTextLabel;

	QPushButton* m_pSetBtn;
	QPushButton* m_pMinBtn;
	QPushButton* m_pMaxBtn;
	QPushButton* m_pCloseBtn;
};
