#pragma once

#include <string>

struct sqlite3;
class DataBase
{
private:
	sqlite3* m_SqliteDB = nullptr;

public:
	void AddBME280SensorDatas(const int& vDateTime, const float& vTemperature, const float& vPressure, const float& vHumidity);
	std::string GetJSonDatas(const int& vCountLastHours);

private:
	bool OpenDB();
	void CreateDB();
	void CloseDB();

public: // singleton
	static DataBase* Instance()
	{
		static DataBase _instance;
		return &_instance;
	}
	DataBase() = default;
	DataBase(const DataBase&) = delete;
	DataBase& operator =(const DataBase&) = delete;
	~DataBase() = default;
};