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
	selectPath = fileInfo.filePath();
	return justFilePath;
}
QString Utils::getSelectPath() {
	if (selectPath.isEmpty())
	{
		selectPath = 'C:';
	}
	return selectPath;
}

Utils::~Utils()
{
}
