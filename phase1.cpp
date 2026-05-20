#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MOS
{
private:
	char M[100][4];
	char IR[4];
	char R[4];
	int IC;
	bool C;
	int SI;
	ifstream input;
	ofstream output;

public:
	MOS()
	{
		input.open("input.txt");
		output.open("output.txt");
	}

	void init()
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				M[i][j] = ' ';
			}
		}

		for (int i = 0; i < 4; i++)
		{
			IR[i] = ' ';
			R[i] = ' ';
		}

		IC = 0;
		SI = 0;
		C = false;
	}

	void load()
	{
		string line;
		int memPtr = 0;

		while (getline(input, line))
		{
			if (line.substr(0, 4) == "$AMJ")
			{
				init();
				memPtr = 0;
			}
			else if (line.substr(0, 4) == "$DTA")
			{
				execute();
			}
			else if (line.substr(0, 4) == "$END")
			{
				continue;
			}
			else
			{
				int k = 0;
				for (int i = 0; i < line.length(); i++)
				{
					M[memPtr][k++] = line[i];
					if (k == 4)
					{
						memPtr++;
						k = 0;
					}
				}
			}
		}

		printmemory();
	}

	void printmemory()
	{
		cout << " | 0 | 1 | 2 | 3 | " << endl;
		for (int i = 0; i < 100; i++)
		{
			cout << i << " | ";
			for (int j = 0; j < 4; j++)
			{
				cout << M[i][j] << " | ";
			}
			cout << endl;
		}
	}

	void execute()
	{
		IC = 0;
		while (true)
		{
			for (int i = 0; i < 4; i++)
			{
				IR[i] = M[IC][i];
			}
			IC++;

			int addr = (IR[2] - '0') * 10 + (IR[3] - '0');

			if (IR[0] == 'L' && IR[1] == 'R')
			{
				for (int i = 0; i < 4; i++)
				{
					R[i] = M[addr][i];
				}
			}
			else if (IR[0] == 'S' && IR[1] == 'R')
			{
				for (int i = 0; i < 4; i++)
				{
					M[addr][i] = R[i];
				}
			}
			else if (IR[0] == 'C' && IR[1] == 'R')
			{
				C = true;
				for (int i = 0; i < 4; i++)
				{
					if (R[i] != M[addr][i])
					{
						C = false;
						break;
					}
				}
			}
			else if (IR[0] == 'B' && IR[1] == 'T')
			{
				if (C == true)
				{
					IC = addr;
				}
			}
			else if (IR[0] == 'G' && IR[1] == 'D')
			{
				SI = 1;
				MOS_Interrupt();
			}
			else if (IR[0] == 'P' && IR[1] == 'D')
			{
				SI = 2;
				MOS_Interrupt();
			}
			else if (IR[0] == 'H')
			{
				SI = 3;
				MOS_Interrupt();
				break;
			}
		}
	}

	void MOS_Interrupt()
	{
		if (SI == 1)
		{
			read();
		}
		else if (SI == 2)
		{
			write();
		}
		else if (SI == 3)
		{
			terminate();
		}
	}

	void read()
	{
		string data;
		getline(input, data);

		if (data.substr(0, 4) == "$END")
		{
			output << "No inputs found" ;
			terminate();
			return;
		}

		int addr = (IR[2] - '0') * 10;
		int k = 0;
		for (int i = 0; i < data.length(); i++)
		{
			M[addr][k++] = data[i];
			if (k == 4)
			{
				addr++;
				k = 0;
			}
		}
	}

	void write()
	{
		int addr = (IR[2] - '0') * 10;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				output << M[addr + i][j];
			}
		}
		output << endl;
	}

	void terminate()
	{
		output << endl << endl;
	}
};

int main()
{
	MOS os;
	os.load();
	return 0;
}
