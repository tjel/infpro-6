#include <sys/stat.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>

class Database
{
public:
	Database(QString &path)
	{
		this->dbPath = path;
				
		struct stat buffer;
		
		if (stat(path.c_str(), buffer) == 0)
			return this->open();
		else
			return this->create();
	}

	~Database()
	{
		this->db->close();
	}


private:
	QString dbPath;

	bool create (QString &path)
	{
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");		
		db.setDatabaseName(path);

		return db.isValid();
	}

	bool open ()
	{
		
	}


};
