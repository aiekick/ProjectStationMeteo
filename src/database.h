#pragma once

#include <string>

struct sqlite3;
class DataBase
{
private:
	sqlite3* m_SqliteDB = nullptr;

public:
	DataBase();
	~DataBase();

public:
	void AddSensorDatas(const int& vDateTime, const float& vTemperature, const float& vPressure, const float& vHumidity);
	std::string GetJSonDatas(const int& vCountLastHours);

private:
	bool OpenDB();
	void CreateDB();
	void CloseDB();

};