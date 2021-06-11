#pragma once

#include <string>

struct sqlite3;
class MeasureDataBase
{
private:
	sqlite3* m_SqliteDB = nullptr;

public:
	void AddBME280SensorDatas(const uint64_t& vDateTime, const float& vTemperature, const float& vPressure, const float& vHumidity);
	std::string GetJSonDatas(const int& vCountLastHours);

private:
	bool OpenDB();
	void CreateDB();
	void CloseDB();

public: // singleton
	static MeasureDataBase* Instance()
	{
		static MeasureDataBase _instance;
		return &_instance;
	}
	MeasureDataBase() = default;
	MeasureDataBase(const MeasureDataBase&) = delete;
	MeasureDataBase& operator =(const MeasureDataBase&) = delete;
	~MeasureDataBase() = default;
};