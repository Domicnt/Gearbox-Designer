#pragma once
#include "stdafx.h"

class Gearbox
{
public:
	//directly attatched to motor
	Gear a;
	//attatched to gear a by chain Ca
	Gear b;
	//attatches gear a and b
	Chain Ca;
	
	//directly attatched to gear b
	Gear c;
	//attatched to gear c by chain Cb
	Gear d;
	//attatches gear c and d
	Chain Cb;

	double ratio, mismatch;
	double minCenterDist, maxCenterDist;
	double length, width;

	Gearbox() = default;
	Gearbox(const Gear& B, const Gear& D, const Chain& CA, const Chain& CB);

	bool operator < (const Gearbox& gearbox) const
	{
		return ratio < gearbox.ratio;
	}
	
	double findRatio();
	double findMismatch();
	double findLength();
	double findWidth();
	bool checkColliding() const;

	void printToFile(std::ofstream& file) const;
};