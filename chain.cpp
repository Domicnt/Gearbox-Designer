#include "stdafx.h"

Chain::Chain(const double& Pitch, const double& Width, const unsigned int& Links, const unsigned int& MaxLinks)
{
	pitch = Pitch;
	width = Width;
	links = Links;
	maxLinks = MaxLinks;
}

void Chain::printToFile(std::ofstream& file) const
{
	file << "Links: " << links<< std::endl;
}
