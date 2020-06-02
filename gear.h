#pragma once
#include "stdafx.h"

class Gear
{
public:
	double pitchDiameter;
	double radius;
	int teeth;

	Gear() = default;
	Gear(const double& PitchDiameter, const int& Teeth, const double& diameter);
	
	double findTotalDiameter(const Chain& chain) const;
	double findCenterDistance(const Gear& gear, const Chain& chain) const;

	void printToFile(std::ofstream& file) const;
};