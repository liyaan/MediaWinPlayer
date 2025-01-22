#include "Utils.h"

Utils::Utils(QObject *parent)
	: QObject(parent)
{
}
QString Utils::baseName(QString fileName) {
	QFileInfo fileInfo(fileName);
	QString justFileName = fileInfo.baseName();
	return justFileName;
}
QString Utils::absolutePath(QString fileName) {
	QFileInfo fileInfo(fileName);
	QString justFilePath = fileInfo.absolutePath();
	return justFilePath;
}
Utils::~Utils()
{
}
