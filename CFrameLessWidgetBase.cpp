#include "CFrameLessWidgetBase.h"

CFrameLessWidgetBase::CFrameLessWidgetBase(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	setAttribute(Qt::WA_Hover);
}

CFrameLessWidgetBase::~CFrameLessWidgetBase()
{
}
bool CFrameLessWidgetBase::nativeEvent(const QByteArray& eventType, void* message, long* result) {
	MSG* param = static_cast<MSG*>(message);
	switch (param->message)
	{
	case WM_NCHITTEST:
		int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
		int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

		/*if (childAt(nX, nY) != nullptr)
		return QWidget::nativeEvent(eventType, message, result);*/
		if (nX > BORDER_WIDTH && nX<this->width() - BORDER_WIDTH && nY>BORDER_WIDTH && nY < this->height() - BORDER_WIDTH) {
			if (childAt(nX, nY) != nullptr)
				return QWidget::nativeEvent(eventType, message, result);
		}
		if ((nX > 0) && (nX < BORDER_WIDTH))
			*result = HTLEFT;

		if ((nX > this->width() - BORDER_WIDTH) && (nX < this->width()))
			*result = HTRIGHT;

		if ((nY > 0) && (nY < BORDER_WIDTH))
			*result = HTTOP;

		if ((nY > this->height() - BORDER_WIDTH) && (nY < this->height()))
			*result = HTBOTTOM;

		if ((nX > 0) && (nX < BORDER_WIDTH) && (nY > 0) && (nY < BORDER_WIDTH))
			*result = HTTOPLEFT;

		if ((nX > this->width() - BORDER_WIDTH) && (nX < this->width()) &&
			(nY > 0) && (nY < BORDER_WIDTH))
			*result = HTTOPRIGHT;

		if ((nX > 0) && (nX < BORDER_WIDTH) && (nY > this->height() - BORDER_WIDTH)
			&& (nY < this->height()))
			*result = HTBOTTOMLEFT;

		if ((nX > this->width() - BORDER_WIDTH) && (nX < this->width())
			&& (nY > this->height() - BORDER_WIDTH) && (nY < this->height()))
			*result = HTBOTTOMRIGHT;

		return true;
	}
	return false;
}