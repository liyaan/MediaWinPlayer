#pragma once

#include <QObject>
#include <QFileInfo>
class Utils : public QObject
{
	Q_OBJECT

public:
	Utils(QObject *parent = nullptr);
	~Utils();
	QString baseName(QString fileName);
	QString absolutePath(QString fileName);
	QString getSelectPath();
private:
	QString selectPath = nullptr;
};
