#include "stdafx.h"

Gearbox::Gearbox(const Gear& B, const Gear& D, const Chain& CA, const Chain& CB)
{
	a = { B.pitchDiameter,12,1.083 };
	b = B;
	c = { D.pitchDiameter,11,1.502 };
	d = D;
	Ca = CA;
	Cb = CB;
}

double Gearbox::findRatio()
{
	ratio = (double(b.teeth) / double(a.teeth)) * (double(d.teeth) / double(c.teeth)) * (double(d.teeth) / double(c.teeth));
	return ratio;
}

double Gearbox::findMismatch()
{
	minCenterDist = c.findCenterDistance(d, Cb);
	maxCenterDist = a.findCenterDistance(b, Ca);
	if (minCenterDist > maxCenterDist)
	{
		const auto temp = maxCenterDist;
		maxCenterDist = minCenterDist;
		minCenterDist = temp;
	}
	mismatch = maxCenterDist - minCenterDist;
	return mismatch;
}

double Gearbox::findLength()
{
	const auto bRad = b.findTotalDiameter(Ca) / 2;
	const auto dRad = d.findTotalDiameter(Cb) / 2;
	length = (maxCenterDist + (bRad >= dRad ? bRad : dRad) * 2) + .207;
	return length;
}

double Gearbox::findWidth()
{
	const auto bDiameter = b.findTotalDiameter(Ca);
	const auto dDiameter = d.findTotalDiameter(Cb);
	width = (bDiameter >= dDiameter ? bDiameter : dDiameter) + .253;
	return width;
}

bool Gearbox::checkColliding() const
{
	if (a.radius + b.radius + 0.03 >= b.findCenterDistance(a, Ca) || c.radius + d.radius + 0.03 >= d.findCenterDistance(c, Cb))
		return true;
	return false;
}

void Gearbox::printToFile(std::ofstream& file) const
{
	file << "Length: " << length << std::endl;
	file << "Width: " << width << std::endl;
	b.printToFile(file);
	Ca.printToFile(file);
	d.printToFile(file);
	Cb.printToFile(file);
	file << std::endl;
}