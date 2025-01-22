#pragma once

#include <QWidget>
#include <Windows.h>
#include <windowsx.h>
#include <qt_windows.h>
class CFrameLessWidgetBase : public QWidget
{
	Q_OBJECT

public:
	CFrameLessWidgetBase(QWidget *parent = nullptr);
	~CFrameLessWidgetBase();
private:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
private:
	const int& BORDER_WIDTH = 5;
};
