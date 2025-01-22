#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include <QScreen>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget w;
	// ��ȡ��ǰ��Ļ
	QScreen *screen = QGuiApplication::primaryScreen();
	if (screen) {
		// ��ȡ��Ļ�ĳߴ�
		QRect screenGeometry = screen->geometry();
		int screenWidth = screenGeometry.width();
		int screenHeight = screenGeometry.height();

		// ���㴰�����Ͻǵ����꣬ʹ���ھ���
		int x = (screenWidth - w.width()) / 2;
		int y = (screenHeight - w.height()) / 2;

		// �ƶ����ڵ������������λ��
		w.move(x, y);
	}

	w.show();
	return a.exec();
}
