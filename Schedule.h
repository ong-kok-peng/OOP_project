#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Cargo.h"
#include "Freight.h"

class Schedule : public Freight, Cargo{
private:
	const static string FREIGHT_MODE; //name macro for freight mode
	const static string CARGO_MODE; //name macro for cargo mode
	string dataMode;

	vector<vector<string>> pairedFlights;
	vector<vector<string>> unpairedCargo;
	vector<vector<string>> unpairedFreight;
	bool isScheduleGenerated;
public:
	Schedule();
	void gotoDataMode(int);
	void showDataMenu();
	void clearTerminal();

	void openFile() override;
	void dispInfo() override;
	void sortInfo() override;
	void addInfo() override;
	void delInfo() override;
	void editInfo() override;

	void generateSchedule();
	void dispSchedule();
	void saveSchedule();
};

#endif // !SCHEDULE_H

