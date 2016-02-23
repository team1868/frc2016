#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "WPILib.h"
#include "RobotPorts2016.h"
#include "ini.h"
#include "Debugging.h"
#include <iostream>
#include <fstream>
#include "navx/AHRS.h"
#include "TableReader.h"
#include "nivision.h"

class RobotModel {
public:
	enum Wheels {kLeftWheels, kRightWheels, kAllWheels};

	RobotModel();
	~RobotModel() {}

	void SetWheelSpeed(Wheels w, double speed);
	float GetWheelSpeed(Wheels w);

	double GetNavXYaw();
	double GetNavXRoll();
	double GetNavXPitch();
	void ZeroNavXYaw();

	void Reset();

	double GetVoltage();

	double GetLeftEncoderVal();
	double GetRightEncoderVal();
	void ResetDriveEncoders();

	double GetPressureSensorVal();

	void RefreshIni();
	void ResetTimer();

	bool IsLowGear();
	void ShiftToLowGear();
	void ShiftToHighGear();

	double GetTime();

	//Superstructure accessor and mutator methods for RobotModel
	bool IsIntakeArmDown();
	void MoveIntakeArmUp();
	void MoveIntakeArmDown();
	void ChangeIntakeArmState();

	double GetIntakeMotorSpeed();
	void SetIntakeMotorSpeed(double speed);

	bool IsDefenseManipDown();
	void MoveDefenseManipUp();
	void MoveDefenseManipDown();
	void ChangeDefenseManipState();

	double GetOuttakeMotorSpeed();
	void SetOuttakeMotorSpeed(double speed);

	double GetOuttakeEncoderVal();
	void ResetOuttakeEncoders();

	Image* GetCameraImage();

	Ini* pini;
	TableReader* gripLines;
private:
	bool isLowGear;
	Compressor *compressor;

	PowerDistributionPanel* pdp;

	Timer *timer;

	//Actuators
	Victor *leftDriveMotorA, *leftDriveMotorB, *rightDriveMotorA, *rightDriveMotorB;

	// Solenoids
	Solenoid *gearShiftSolenoid;

	//Sensors
	Encoder *leftEncoder, *rightEncoder;
	AnalogInput *pressureSensor;
#if USE_CAMERA
	AxisCamera *camera;
	Image *frame;
#endif

#if USE_NAVX
	//Port the NavX plugs into
	AHRS *navx;
#endif
};

#endif
