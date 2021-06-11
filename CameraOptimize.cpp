#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <set>

#define MAX_LENGTH 300
#define MAX_SIZE 1000

using namespace std;

//random ra dãy nhị phân rồi lưu vào file input.txt
void init(string filename)
{
	srand(time(NULL));
	fstream f;
	f.open(filename);
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_LENGTH; ++j)
		{
			f << rand() % 2;
		}
		f << endl;
	}
	f.close();
}

void process(string input_file, string output_file, int limit)
{
	fstream input;
	input.open(input_file);
	vector<vector<int>> coordinate;
	int sum[MAX_LENGTH];
	for (int i = 0; i < MAX_LENGTH; ++i)
	{
		sum[i] = 0;
	}

	string text;
	while (getline(input, text))
	{
		vector<int> tmp;
		for (int i = 0; i < text.length(); ++i)
		{
			tmp.push_back(text[i] - '0');
			sum[i] += text[i] - '0';
		}
		coordinate.push_back(tmp);
	}
	input.close();

	remove(output_file.c_str());
	ofstream output(output_file);
	set<int> checked;				//set lưu index của coordinate đã check
	int group = 0;					//số lượng nhóm tạo được
	while (checked.size() != coordinate.size() && group != limit)
	{
		int position_of_max = 0;
		for (int i = 0; i < coordinate[i].size(); ++i)
			if (sum[i] > sum[position_of_max])
				position_of_max = i;

		if (sum[position_of_max] == 0)
			break;

		++group;
		for (int i = 0; i < coordinate.size(); ++i)
		{
			if (coordinate[i][position_of_max] == 1 && checked.count(i) == 0)
			{
				for (int j = 0; j < coordinate[i].size(); ++j)
				{
					if (coordinate[i][j] == 1)
					{
						--sum[j];
					}
				}
				checked.insert(i);

				//in kết quả vào output_file
				for (auto x : coordinate[i])
				{
					output << x;
				}
				output << endl;
			}
		}
		output << "Chon camera thu: " << position_of_max + 1 << endl << endl;
	}
	output.close();
	cout << "Co the dat it nhat " << group << " camera de cho tam nhin toi uu" << endl;
}

int main(int argc, char const *argv[]) //file_input file_output limit
{
	if(argc == 4)
	{
		init(argv[1]);
		process(argv[1], argv[2], stoi(argv[3]));
	}else{
		cout << "Khong du tham so" << endl;
	}
}