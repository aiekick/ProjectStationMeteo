#ifndef BALISEMER_HPP
#define BALISEMER_HPP
#include "infosClient.hpp"
#include "datasMeteo.hpp"
#include <vector>

class BaliseMer : public InfoClient
{
private:
	DatasMeteo datas;
	DatasMeteo summary;
	vector<DatasMeteo> history;

public:
	BaliseMer(int, int, string, string, string, string, DatasMeteo, DatasMeteo, vector<DatasMeteo>);
	~BaliseMer();
	DatasMeteo getDatas();
	void setDatas(DatasMeteo);
	DatasMeteo getSummary();
	void setSummary(DatasMeteo);
	vector<DatasMeteo> getHistory();
	void setHistory(vector<DatasMeteo>);

	string displayDatas();
	

};

#endif