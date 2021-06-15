#ifndef BALISEMER_HPP
#define BALISEMER_HPP
#include "balise.h"
#include "datasMeteo.h"
#include <vector>

class BaliseMer : public Balise
{
private:
	DatasMeteo datas;
	DatasMeteo summary;
	vector<DatasMeteo> history;

public:
	BaliseMer();
	BaliseMer(int, int, string, string, string, string, DatasMeteo, DatasMeteo, vector<DatasMeteo>);
	~BaliseMer();

	DatasMeteo getDatas();


	void requestData(); // Send request to server and retrieve infos

};

#endif