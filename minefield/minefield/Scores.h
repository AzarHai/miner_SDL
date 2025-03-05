#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Score
{
	string name = "";
	int time = 0;
};

class Scores
{
public:
	static void Add_Record(string name, int time)
	{
		vector<Score> scores = ReadFromFile();
		Score temp;
		temp.name = name;
		temp.time = time;
		scores.push_back(temp);

		sort(scores.begin(), scores.end(), [](Score& a, Score& b) { return a.time < b.time; });
		
		if (scores.size() > 10) scores.pop_back();

		fstream f;
		f.open("Records.bin", fstream::out, fstream::binary);
		for (auto el : scores)
		{
			size_t len = el.name.length();
			f.write((char*)&len, sizeof(size_t));
			f.write(el.name.data(), len);
			f.write((char*)&el.time, sizeof(int));
		}
		f.close();
	}

	static vector<Score> ReadFromFile()
	{
		vector<Score> scores;
		fstream f;
		f.open("Records.bin", fstream::in, fstream::binary);
		size_t len = 0;
		Score temp;
		while (!f.eof())
		{
			f.read((char*)&len, sizeof(size_t));
			if (f.eof()) break;
			char* buf = new char[len + 1];
			f.read(buf, len);
			buf[len] = 0;
			temp.name = buf;
			f.read((char*)&temp.time, sizeof(int));
			scores.push_back(temp);
		}
		f.close();
		return scores;
	}

	static void ClearFile()
	{
		fstream f;
		f.open("Records.bin", fstream::out, fstream::binary);
		f.clear();
		f.close();
	}

	static void ToPrint()
	{
		vector<Score> scores = ReadFromFile();
		fstream f;
		f.open("Records.txt", fstream::out);
		f.clear();
		for (auto el : scores)
		{
			f << el.name << ": " << el.time / 1000 << "." << el.time % 1000 / 10 << "\n";
		}
		f.close();
	}
};