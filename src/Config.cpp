#include "config.hpp"

Config::Config() {
	
	db.addDatabase("QSQLITE");
	QString dbpath = QString(os_get_config_path_ptr("obs-studio/plugin_config/obs-midi/obs-midi-db.sqlite"));
	db.setDatabaseName(dbpath);
	if (!db.open()) {
		
		qDebug() << "[obs-midi] Database open error at path " << dbpath;
	}
	
};

Config::~Config(){
	db.close();
}
void Config::init_db() {
	QString c_device_table =
		"ID INTEGER,"
		"name VARCHAR,"
		"enabled BOOL,"
		"feedback_name VARCHAR,"
		"feedback_enabled BOOL;";
	QSqlQuery tmpqry(db);
	if (!tmpqry.exec(c_device_table)) {
		qDebug() << "[obs-midi] Create Device Table Error";
	}


}