#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <unistd.h>

std::unordered_map<std::string, int> kmerMap;
std::vector<KmerCouple> mostFrequentKmers;

struct KmerCouple {
	std::string key;
	int count;
};

struct isBigger
{
	inline bool operator() (const KmerCouple& struct1, const KmerCouple& struct2)
	{
		return (struct1.count > struct2.count);
	}
};

bool isAvailable(std::string kmer, int count)
{
	KmerCouple tempKmerCouple = mostFrequentKmers.back();
	bool isAvailableFlag = true;

	for (int i = 0; i < mostFrequentKmers.size(); i++) 
	{
		KmerCouple kmerExists = mostFrequentKmers.at(i);
		if (kmerExists.key == kmer) 
		{
			isAvailableFlag = false;
			break;
		}
	}
	return (count > tempKmerCouple.count) & isAvailableFlag;
}

void insertAndSortVector(int length, std::string kmer, int count)
{
	if (mostFrequentKmers.size() < length || isAvailable(kmer, count)) 
	{
		KmerCouple kmerCouple;
		kmerCouple.key = kmer;
		kmerCouple.count = count;
		mostFrequentKmers.push_back(kmerCouple);
		sort(mostFrequentKmers.begin(), mostFrequentKmers.end(), isBigger());

		// Eliminating extra ones
		// This is for showing only the desired numbered K-mers
		if (mostFrequentKmers.size() > length) 
		{
			mostFrequentKmers.pop_back();
		}
	}
}

void countKmers(std::string line, int k, int length)
{

	std::string kmer;

	for (int i = 0; i < line.length() - k; i++)
	{
		kmer = line.substr(i, k);

		if (kmerMap.count(kmer) > 0)
		{
			kmerMap[kmer]++;
		}
		else 
		{
			kmerMap.insert(std::make_pair<std::string, int>(kmer, 1));
		}

		insertAndSortVector(10, kmer, kmerMap[kmer]);
	}
}

int main(int argc, char **argv)
{
	char* filename;
	int k = 30;
	int top = 25;
	char c;

	opterr = 0;

	while ((c = getopt(argc, argv, "f:k:t:")) != -1)
		switch (c)
		{
		case 'f':
			filename = optarg;
			break;
		case 'k':
			k = atoi(optarg);
			break;
		case 't':
			top = atoi(optarg);
			break;
		}

	std::string data;

	std::ifstream infile;
	infile.open(filename);

	std::cout << "Reading from the file." << std::endl;
	int counter = 3;

	while (infile.good())
	{
		getline(infile, data);

		if (counter % 4 == 0)
		{
			countKmers(data, k, top);
		}
		counter++;
	}

	for (int i = 0; i < mostFrequentKmers.size(); i++) 
	{
		KmerCouple temp = mostFrequentKmers.at(i);
		std::cout << temp.key << ": " << temp.count << std::endl;
	}


	infile.close();

	return 0;
}
