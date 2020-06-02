#pragma once
#include "stdafx.h"

class Chain
{
public:
	double pitch, width;
	//must be even
	int links, maxLinks;

	Chain() = default;
	Chain(const double& Pitch, const double& Width, const unsigned int& Links, const unsigned int& MaxLinks);

	void printToFile(std::ofstream& file) const;
};