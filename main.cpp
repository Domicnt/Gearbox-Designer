#include "stdafx.h"

int main()
{
	//parameters:
	double maxMismatch = .01;
	double minRatio = 15;
	double maxRatio = 30;
	double maxLength = 7.5;
	double maxWidth = 4.25;

	auto newInputs = false;
	std::string str;
	std::cout << "Do you want to set new parameters?" << std::endl << "Y/N: ";
	std::cin >> str;
	std::cout << std::endl;
	if(str == "y" || str == "Y")
	{
		std::cout << "Maximum mismatch: ";
		std::cin >> maxMismatch;
		std::cout << std::endl << "Minimum ratio: ";
		std::cin >> minRatio;
		std::cout << std::endl << "Maximum ratio: ";
		std::cin >> maxRatio;
		std::cout << std::endl << "Maximum length: " << std::endl;
		std::cin >> maxLength;
		std::cout << std::endl << "Maximum width: " << std::endl;
		std::cin >> maxWidth;
		std::cout << std::endl << "All set." << std::endl;
	}
	
	std::vector<Gear> possibleGearsA = {
		{.966,12,1.083},
		{1.045,13,1.164},
		{1.124,14,1.245},
		{1.203,15,1.326},
		{1.282,16,1.407},
		{1.361,17,1.487},
		{1.440,18,1.568},
		{1.519,19,1.648},
		{1.589,20,1.729},
		{1.678,21,1.809},
		{1.757,22,1.889},
		{1.836,23,1.969},
		{1.915,24,2.049},
		{1.995,25,2.129},
		{2.074,26,2.209},
		{2.154,27,2.289},
		{2.233,28,2.369},
		{2.312,29,2.249},
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
		{1.331,11,1.502},
		{1.449,12,1.625},
		{1.567,13,1.746},
		{1.685,14,1.868},
		{1.804,15,1.989},
		{1.922,16,2.110},
		{2.041,17,2.231},
		{2.160,18,2.352},
		{2.279,19,2.472},
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
	const Chain Ca = { 0.25, 0.238, 28, 70 };
	const Chain Cb = { 0.375, 0.35, 22,  50 };

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
		if (i.mismatch > maxMismatch || i.ratio <= minRatio || i.ratio >= maxRatio || i.length > maxLength || i.width > maxWidth || i.checkColliding())
			continue;
		file << "Mismatch: " << i.mismatch << std::endl << "Ratio: " << i.ratio << std::endl << "Average Center Distance: " << (i.minCenterDist + i.maxCenterDist) / 2 << std::endl;
		i.printToFile(file);
		x++;
	}

	std::cout << x;
	std::cin >> str;

	return 0;
}