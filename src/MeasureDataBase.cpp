#include "MeasureDataBase.h"
#include "SensorBME280.h"
#include <sqlite3.h>
#include <sstream>
#include <vector>
#include <string.h>  

template <typename T>
static inline std::string toStr(T t)
{
	::std::ostringstream os;
	os << t;
	return os.str();
}

void MeasureDataBase::AddBME280SensorDatas(const uint64_t& vDateTime, const float& vTemperature, const float& vPressure, const float& vHumidity)
{
	if (OpenDB())
	{
		// we must create the table
		std::string create_query = "insert into tbl_bme280_sensor_history (epoc_time, temperature, pressure, humidity) values(" + toStr(vDateTime) + ", " + toStr(vTemperature) + ", " + toStr(vPressure) + ", " + toStr(vHumidity) + ");";
		if (sqlite3_exec(m_SqliteDB, create_query.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
		{
			printf("Fail to insert a sensor record in database\n");
		}

		CloseDB();
	}
}

std::string MeasureDataBase::GetHistoryToJson(const int& vCountLasts)
{
	std::string jsonResult;

	// retrieving of last N record from Db, and format them in json format
	if (OpenDB())
	{
		// we must create the table
		std::string select_query = "select * from tbl_bme280_sensor_history order by epoc_time desc limit " + toStr(vCountLasts) + ";";
		std::vector<std::string> jsonLines;	jsonLines.resize(vCountLasts);
		sqlite3_stmt* statement = nullptr;
		if (sqlite3_prepare_v2(m_SqliteDB, select_query.c_str(), -1, &statement, NULL) != SQLITE_OK)
		{
			printf("Fail to select last sensor records in database : %s\n", sqlite3_errmsg(m_SqliteDB));
		}
		else
		{
			int rowID = 0;
			try
			{
				std::string lastLine;
				while (sqlite3_step(statement) == SQLITE_ROW)
				{
					auto epoc = (char*)sqlite3_column_text(statement, 0); // can raise an exception for out of memory
					auto temp = (char*)sqlite3_column_text(statement, 1); // can raise an exception for out of memory
					auto pres = (char*)sqlite3_column_text(statement, 2); // can raise an exception for out of memory
					auto humi = (char*)sqlite3_column_text(statement, 3); // can raise an exception for out of memory

					if (strlen(epoc) && strlen(temp) && strlen(pres) && strlen(humi))
					{
						if (!jsonResult.empty())
							jsonResult += ",";

						lastLine = SensorBME280::ConvertSensorBME280DatasToJSON(epoc, temp, pres, humi);
						if (!lastLine.empty())
						{
							if (jsonResult.size() + lastLine.size() > jsonResult.max_size())
							{
								printf("sonResult.max_size() was reached. stop json extraction\n");
								break;
							}
							jsonResult += lastLine;
							rowID++;
						}
					}
				}
			}
			catch (std::exception& ex)
			{
				printf("Err : %s", ex.what());
			}

			std::ostringstream os; os << rowID;
			jsonResult = "\"count\":" + os.str() + ",\"history\":[\n" + jsonResult + "\n]";

			
			//printf("result : %s, length : %llu\n", jsonResult.c_str(), jsonResult.size());
			
			sqlite3_finalize(statement);
		}

		CloseDB();
	}

	return jsonResult;
}

std::string MeasureDataBase::GetDatabaseInfos()
{
	std::string jsonResult;

	// retrieving of last N record from Db, and format them in json format
	if (OpenDB())
	{
		sqlite3_stmt* statement;

		// get count records
		statement = nullptr;
		std::string countRecords;
		std::string count_query = "select count(*) from tbl_bme280_sensor_history;";
		if (sqlite3_prepare_v2(m_SqliteDB, count_query.c_str(), -1, &statement, NULL) != SQLITE_OK)
		{
			printf("Fail to get count records in table tbl_bme280_sensor_history from database : %s\n", sqlite3_errmsg(m_SqliteDB));
		}
		else
		{
			try
			{
				std::string lastLine;
				while (sqlite3_step(statement) == SQLITE_ROW)
				{
					auto count = (char*)sqlite3_column_text(statement, 0); // can raise an exception for out of memory
					
					if (strlen(count))
					{
						countRecords = std::string(count);
					}
				}
			}
			catch (std::exception& ex)
			{
				printf("Err : %s", ex.what());
			}

			sqlite3_finalize(statement);
		}

		// get database version
		statement = nullptr;
		std::string databaseVersion;
		std::string version_query = "select sqlite_version();";
		if (sqlite3_prepare_v2(m_SqliteDB, version_query.c_str(), -1, &statement, NULL) != SQLITE_OK)
		{
			printf("Fail to get version of database file : %s\n", sqlite3_errmsg(m_SqliteDB));
		}
		else
		{
			try
			{
				std::string lastLine;
				while (sqlite3_step(statement) == SQLITE_ROW)
				{
					auto version = (char*)sqlite3_column_text(statement, 0); // can raise an exception for out of memory

					if (strlen(version))
					{
						databaseVersion = std::string(version);
					}
				}
			}
			catch (std::exception& ex)
			{
				printf("Err : %s", ex.what());
			}

			sqlite3_finalize(statement);
		}

		jsonResult += "\"database_records\":" + countRecords;
		jsonResult += ",\"database_version\":\"" + databaseVersion + "\"";
		jsonResult += ",\"database_path\":\"" + m_DataBaseFilePathName + "\"";
		
		CloseDB();
	}

	return jsonResult;
}	
	
////////////////////////////////////////////////////////////
///// PRIVATE //////////////////////////////////////////////
////////////////////////////////////////////////////////////

bool MeasureDataBase::OpenDB()
{
	m_SqliteDB = nullptr;

	if (sqlite3_open_v2(m_DataBaseFilePathName.c_str(), &m_SqliteDB, SQLITE_OPEN_READWRITE, nullptr) != SQLITE_OK) // db possibily not exist
	{
		CreateDB();
	}

	return (m_SqliteDB != nullptr);
}

void MeasureDataBase::CreateDB()
{
	m_SqliteDB = nullptr;

	if (sqlite3_open_v2(m_DataBaseFilePathName.c_str(), &m_SqliteDB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr) == SQLITE_OK)
	{
		if (m_SqliteDB) // in the doubt
		{
			// we must create the table
			const char* create_query = "create table tbl_bme280_sensor_history (epoc_time integer PRIMARY KEY NOT NULL, temperature double NOT NULL, pressure double NOT NULL, humidity double NOT NULL);";
			if (sqlite3_exec(m_SqliteDB, create_query, nullptr, nullptr, nullptr) != SQLITE_OK)
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

void MeasureDataBase::CloseDB()
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