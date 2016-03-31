// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ArmStop.h"
#define LEFT_Y_AXIS 1

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ArmStop::ArmStop(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::arm.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ArmStop::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ArmStop::Execute() {
	// when limit switch is FALSE, it is enabled!!
	// if switch not enabled (aka TRUE), let it move
	if (Robot::arm->armLimit->Get())
	{
		// trimming joystick
		if (fabs(Robot::oi->getcoDriver()->GetRawAxis(LEFT_Y_AXIS)) > .1)
			Robot::arm->armLeft->Set(Robot::oi->getcoDriver()->GetRawAxis(LEFT_Y_AXIS));
			Robot::arm->armRight->Set(Robot::oi->getcoDriver()->GetRawAxis(LEFT_Y_AXIS));
	}

	else
	{
		// trimming joystick; can only move arm up (negative float value)
		if(Robot::oi->getcoDriver()->GetRawAxis(LEFT_Y_AXIS) < -.1)
		{
			Robot::arm->armLeft->Set(Robot::oi->getcoDriver()->GetRawAxis(LEFT_Y_AXIS));
			Robot::arm->armRight->Set(Robot::oi->getcoDriver()->GetRawAxis(LEFT_Y_AXIS));
		}
		else
		{
			Robot::arm->armLeft->Set(0.0);
			Robot::arm->armRight->Set(0.0);
		}
	}

	ChangeArmGoal();
	SmartDashboard::PutNumber("armAngle", Robot::arm->CurrentArmAngle());
    SmartDashboard::PutNumber("armEncoder", Robot::arm->armEncoder->Get());
    SmartDashboard::PutBoolean("armLimit", Robot::arm->armLimit->Get());
    SmartDashboard::PutNumber("m_armGoal", Robot::m_armGoal);
}

// Make this return true when this Command no longer needs to run execute()
bool ArmStop::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ArmStop::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmStop::Interrupted() {

}

// Smart button for changing arm angle
void ArmStop::ChangeArmGoal() {
	switch(Robot::oi->getcoDriver()->GetPOV(0)) {

	case 90: Robot::m_armGoal = 48; break;

	case 180: Robot::m_armGoal = 2; break;

	case 360 || 0: Robot::m_armGoal = 95; break;

	}
}
