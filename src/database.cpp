#include "database.h"
#include <sstream>
#include <sqlite3.h>

#define DATABASE_FILENAME "database.db3"

template <typename T>
static inline std::string toStr(T t)
{
	::std::ostringstream os;
	os << t;
	return os.str();
}

void DataBase::AddBME280SensorDatas(const uint64_t& vDateTime, const float& vTemperature, const float& vPressure, const float& vHumidity)
{
	if (OpenDB())
	{
		// we must create the table
		std::string create_query = "insert into tbl_bme280_sensor_history (epoc_time, temperature, pressure, humidity) values(" + toStr(vDateTime) + ", " + toStr(vTemperature) + ", " + toStr(vPressure) + ", " + toStr(vHumidity) + ");";
		if (sqlite3_exec(m_SqliteDB, create_query.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
		{
			printf("Fail to insert a sensor record in database\n");
			m_SqliteDB = nullptr;
		}

		CloseDB();
	}
}

std::string DataBase::GetJSonDatas(const int& vCountLastHours)
{
	// recuperation de seulement les vCountLastHours derniers depuis la table tbl_sensor_history avec tri descendant (le dernier d'abord)
	return "";
}

////////////////////////////////////////////////////////////
///// PRIVATE //////////////////////////////////////////////
////////////////////////////////////////////////////////////

bool DataBase::OpenDB()
{
	m_SqliteDB = nullptr;

	if (sqlite3_open_v2(DATABASE_FILENAME, &m_SqliteDB, SQLITE_OPEN_READWRITE, nullptr) != SQLITE_OK) // db possibily not exist
	{
		CreateDB();
	}

	return (m_SqliteDB != nullptr);
}

void DataBase::CreateDB()
{
	m_SqliteDB = nullptr;

	if (sqlite3_open_v2(DATABASE_FILENAME, &m_SqliteDB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr) == SQLITE_OK)
	{
		if (m_SqliteDB) // in the doubt
		{
			// we must create the table
			std::string create_query = "create table tbl_bme280_sensor_history (epoc_time integer PRIMARY KEY NOT NULL, temperature double NOT NULL, pressure double NOT NULL, humidity double NOT NULL);";
			if (sqlite3_exec(m_SqliteDB, create_query.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
			{
				printf("Fail to create database. cant manage sensors history\n");
				m_SqliteDB = nullptr;
			}
		}
	}
	else
	{
		printf("Fail to open or create database. cant manage sensors history\n");
		m_SqliteDB = nullptr;
	}
}

void DataBase::CloseDB()
{
	if (m_SqliteDB)
	{
		if (sqlite3_close(m_SqliteDB) == SQLITE_BUSY)
		{
			// try to force closing
			sqlite3_close_v2(m_SqliteDB);
		}
	}
}