#include "stdafx.h"

Gear::Gear(const double& PitchDiameter, const int& Teeth, const double& diameter)
{
	pitchDiameter = PitchDiameter;
	radius = diameter/2;
	teeth = Teeth;
}

double Gear::findTotalDiameter(const Chain& chain) const
{
	return pitchDiameter + chain.width;
}

double Gear::findCenterDistance(const Gear& gear, const Chain& chain) const
{
	const auto a = chain.pitch / 8;
	const auto b = 2 * double(chain.links) - double(teeth) - double(gear.teeth);
	const auto c = 8 / (3.14159 * 3.14159);
	const auto d = double(teeth) - double(gear.teeth);
	const auto e = b * b - (c * (d * d));
	const auto f = e<0?-1:1*sqrt(abs(e));

	const auto x = a * (b + f);
	
	return x;
}

void Gear::printToFile(std::ofstream& file) const
{
	file << "Teeth: " << teeth << std::endl;
}
