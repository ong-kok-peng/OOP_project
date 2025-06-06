#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Cargo.h"
#include "Freight.h"

class Schedule : public Freight, Cargo{
private:
	const static string FREIGHT_MODE; //name macro for freight mode
	const static string CARGO_MODE; //name macro for cargo mode
	string dataMode;
public:
	Schedule();
	void gotoDataMode(int);
	void showDataMenu();

	void openFile() override;
	void dispInfo() override;
	void sortInfo() override;
	void addInfo() override;
	void delInfo() override;
	void editInfo() override;

};

#endif // !SCHEDULE_H

