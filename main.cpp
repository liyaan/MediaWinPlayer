#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include <QScreen>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget w;
	// 获取当前屏幕
	QScreen *screen = QGuiApplication::primaryScreen();
	if (screen) {
		// 获取屏幕的尺寸
		QRect screenGeometry = screen->geometry();
		int screenWidth = screenGeometry.width();
		int screenHeight = screenGeometry.height();

		// 计算窗口左上角的坐标，使窗口居中
		int x = (screenWidth - w.width()) / 2;
		int y = (screenHeight - w.height()) / 2;

		// 移动窗口到计算出的坐标位置
		w.move(x, y);
	}

	w.show();
	return a.exec();
}
