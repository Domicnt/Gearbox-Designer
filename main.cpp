#include "stdafx.h"

int main()
{
	//parameters:
	auto minMismatch = .01;
	auto minRatio = 15;
	auto maxLength = 7.5;
	auto maxWidth = 4.25;

	auto newInputs = false;
	std::string str;
	std::cout << "Do you want to set new parameters?" << std::endl << "Y/N: ";
	std::cin >> str;
	std::cout << std::endl;
	if(str == "y" || str == "Y")
	{
		std::cout << "Minimum mismatch: ";
		std::cin >> minMismatch;
		std::cout << std::endl << "Minimum ratio: ";
		std::cin >> minRatio;
		std::cout << std::endl << "Maximum length: " << std::endl;
		std::cin >> maxLength;
		std::cout << std::endl << "Maximum width: " << std::endl;
		std::cin >> maxWidth;
		std::cout << std::endl << "All set." << std::endl;
	}
	
	std::vector<Gear> possibleGearsA = {
		{2.392,30,2.529},
		{2.471,31,2.609},
		{2.551,32,2.688},
		{2.630,33,2.768},
		{2.710,34,2.848},
		{2.789,35,2.928},
		{2.869,36,3.008},
		{2.948,37,3.087},
		{3.028,38,3.167},
		{3.197,39,3.324},
		{3.187,40,3.327},
		{3.266,41,3.406},
		{3.346,42,3.486},
		{3.425,43,3.566},
		{3.505,44,3.646},
		{3.584,45,3.725},
		{3.664,46,3.805},
		{3.743,47,3.885},
	};
	std::vector<Gear> possibleGearsB = {
		{2.397,20,2.593},
		{2.516,21,2.713},
		{2.635,22,2.833},
		{2.754,23,2.953},
		{2.873,24,3.073},
		{2.992,25,3.193},
		{3.111,26,3.313},
		{3.230,27,3.433},
		{3.349,28,3.553},
		{3.468,29,3.673},
		{3.588,30,3.793}
	};
	const Chain Ca = { 0.25, 0.238, 40, 60 };
	const Chain Cb = { 0.375, 0.35, 30,  40 };

	std::vector<Gearbox> possibleGearBoxes;
	for (auto i : possibleGearsA)
	{
		for (auto j : possibleGearsB)
		{
			for (auto k = Ca.links; k <= Ca.maxLinks; k += 2)
			{
				for (auto l = Cb.links; l <= Cb.maxLinks; l += 2)
				{
					auto a = Ca;
					a.links = k;
					auto b = Cb;
					b.links = l;
					possibleGearBoxes.emplace_back(i, j, a, b);
				}
			}
		}
	}

	std::ofstream file("output.txt", std::ofstream::out | std::ofstream::trunc);

	for (auto& i : possibleGearBoxes)
	{
		i.findRatio();
		i.findMismatch();
		i.findLength();
		i.findWidth();
	}

	std::sort(possibleGearBoxes.begin(), possibleGearBoxes.end());

	auto x = 0;

	for (const auto& i : possibleGearBoxes)
	{
		if (i.mismatch > minMismatch || i.ratio <= minRatio || i.length > maxLength || i.width > maxWidth || i.checkColliding())
			continue;
		file << "Mismatch: " << i.mismatch << std::endl << "Ratio: " << i.ratio << std::endl << "Average Center Distance: " << (i.minCenterDist + i.maxCenterDist) / 2 << std::endl;
		i.printToFile(file);
		x++;
	}

	std::cout << x;
	std::cin >> str;

	return 0;
}