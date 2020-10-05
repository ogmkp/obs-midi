#pragma once

#include "obs-midi.h"
#include <QObject>
#include <QtSql>

class Config :public QObject {
	Q_OBJECT
public:
	Config();
	~Config();
	void init_db();
private:
	QSqlDatabase db;
};
