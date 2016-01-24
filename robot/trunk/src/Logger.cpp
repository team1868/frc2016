/*
 * Logger.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: chloe
 */

#include "Logger.h"

std::string Logger::dataFilePath = GetTimeStamp((std::string("/home/lvuser/%H_%M_datalog.txt")).c_str());
std::string Logger::actionFilePath = GetTimeStamp((std::string("/home/lvuser/%H_%M_actionlog.txt")).c_str());
std::ofstream Logger::logData;
std::ofstream Logger::logAction;

void Logger::LogState(RobotModel* myRobot, RemoteControl *myHumanControl) {
	// std::string fileName = dataFilePath + std::to_string(myRobot->GetTime());
	if (!logData.is_open()) {
		logData.open(dataFilePath, std::ofstream::out);
		//<< "# Time   LeftWheelSpeed   RightWheelSpeed   IsLowGear   Voltage ";
	}
	logData << myRobot->GetTime() <<", " <<
			myRobot->GetWheelSpeed(RobotModel::kLeftWheels) << ", " <<
			myRobot->GetWheelSpeed(RobotModel::kRightWheels) << ", " <<
			myRobot->IsLowGear() << ", " << myRobot->GetVoltage() << ", " <<
			myHumanControl->GetJoystickValue(RemoteControl::kLeftJoy, RemoteControl::kX) << ", " <<
			myHumanControl->GetJoystickValue(RemoteControl::kLeftJoy, RemoteControl::kY) << ", " <<
			myHumanControl->GetJoystickValue(RemoteControl::kRightJoy, RemoteControl::kX) << ", " <<
			myHumanControl->GetJoystickValue(RemoteControl::kRightJoy, RemoteControl::kY) << ", " <<
			myHumanControl->GetReverseDriveDesired() << ", " <<
			myHumanControl->GetLowGearDesired() << "\r\n";
}
/* format:
 * robotmodel state / controlboard state
 *
 * ie:
 *
 * timer / left motor / right motor / gear shift / pdp voltage / leftjoy x / leftjoy y
 * 			/ rightjoy x / rightjoy y / reverse desired / gearshift desired /
 */

void Logger::LogAction(RobotModel* myRobot, const std::string& fileName, int line,
		const std::string& stateName, bool state) {
	if (!logAction.is_open()) {
		logAction.open(actionFilePath, std::ofstream::out);
	}
	logAction << myRobot->GetTime() << ", " << fileName << ", " << line << ", " << stateName
			<< ", " << state << "\r\n";
}

std::string Logger::GetTimeStamp(const char* fileName) {
	time_t rawtime = time(0);
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime (buffer, 80, fileName, timeinfo); // fileName contains %F_%H_%M
	return buffer;
}