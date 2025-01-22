#include "QSqlData.h"

QSqlData::QSqlData(QObject *parent)
	: QObject(parent)
{
	m_Utils = new Utils();
	initSql();
}
void QSqlData::initSql() {
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("vlcLyaSql.db");

	if (!db.open()) {
		qDebug() << "Error: connection with database failed";
		return;
	}

	QSqlQuery query;
	query.exec("CREATE TABLE IF NOT EXISTS vlcLya (id INTEGER PRIMARY KEY, name VARCHAR(512) NOT NULL, filename VARCHAR(1024) NOT NULL, filepath VARCHAR(1024) NOT NULL)");
}
void QSqlData::insertData(QString fileName) {
	QString justFileName = m_Utils->baseName(fileName);
	QString justFilePath = m_Utils->absolutePath(fileName);
	qDebug() << "justFileName" << justFileName;

	if (!db.open()) {
		qDebug() << "Could not open database";
		return;
	}
	if (readDataFile(justFilePath,justFileName))
	{
		qDebug() << "file is have";
		return;
	}
	QSqlQuery query;
	query.prepare("INSERT INTO vlcLya (name, filename,filepath) VALUES (:name, :filename,:filepath)");
	query.bindValue(":name", justFileName);
	query.bindValue(":filename", fileName);
	query.bindValue(":filepath", justFilePath);
	query.exec();
}
QString QSqlData::readData(QString name) {
	QString fileName;
	if (!db.open()) {
		qDebug() << "Could not open database";
		return fileName;
	}
	QSqlQuery query(db);
	query.prepare("SELECT * FROM vlcLya WHERE  name = :name");
	query.bindValue(":name", name);
	if (!query.exec()) {
		qDebug()<< "readData" << "Error: " << query.lastError().text();
		qDebug() << "Query:" << query.lastQuery();
		qDebug() << "Values:" << query.boundValues();
	}
	if (query.next()) {
		int id = query.value(0).toInt();
		fileName = query.value(2).toString();
		qDebug() << "readData" << id << name << fileName;
	}
	return fileName;
}

bool QSqlData::readDataFile(QString filePath, QString fileName){
	bool isNotData = false;
	if (!db.open()) {
		qDebug() << "Could not open database";
		return isNotData;
	}
	QSqlQuery query(db);
	query.prepare("SELECT * FROM vlcLya WHERE  filepath = :filepath AND name = :name");
	query.bindValue(":filepath", filePath);
	query.bindValue(":name", fileName);
	if (!query.exec()) {
		qDebug() << "readData readDataFile" << "Error: " << query.lastError().text();
		qDebug() << "Query:" << query.lastQuery();
		qDebug() << "Values:" << query.boundValues();
		return true;
	}
	//isNotData = query.next();
	if (query.next()) {
		int id = query.value(0).toInt();
		fileName = query.value(2).toString();
		qDebug() << "readData readDataFile" << id  << fileName;
		isNotData = true;
	}
	qDebug() << "readData readDataFile " << filePath << fileName << isNotData;
	return isNotData;
}
QStringList QSqlData::readDataList() {
	QStringList list;
	if (!db.open()) {
		qDebug() << "Could not open database";
		return list;
	}
	QSqlQuery query("SELECT id, name, filename FROM vlcLya");
	
	while (query.next()) {
		int id = query.value(0).toInt();
		QString name = query.value(1).toString();
		QString filename = query.value(2).toString();
		qDebug()<< "readDataList" << id << name << filename;
		list.append(name);
	}
	return list;
}
QSqlData::~QSqlData()
{
}
void QSqlData::close() {
	db.close();
}
