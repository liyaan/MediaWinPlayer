#pragma once

#include <QObject>
#include <QtSql/QSqlDatabase>

#include <QtSql/QSqlQuery>  
#include <QtSql/QSqlError> 
#include <QFileInfo>
#include "Utils.h"
#include <QDebug>
class QSqlData : public QObject
{
	Q_OBJECT

public:
	QSqlData(QObject *parent = nullptr);
	~QSqlData();
	void insertData(QString fileName);
	QString readData(QString name);
	bool readDataFile(QString filePath, QString fileName);
	QStringList readDataList();
	bool clearDataList();
	void close();
private:
	void initSql();
	
private:
	QSqlDatabase db;
	Utils* m_Utils;
};
