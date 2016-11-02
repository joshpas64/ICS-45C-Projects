#include <iostream>
void prtspaces(int space);
void prtfrstln(int wdth);
void prtscndln(int width);

int main()
{
	int prompt;
	std::cin >> prompt;
	int level;
	int temp1;
	int length;
	level = 1;
	int height;
	do
	{
		height = 0; //column
		temp1 = prompt - level;
		length = (3 * level)-(level-1);
		while(height < 2)
		{
			prtspaces(temp1);
			if((height%2)==0)
			{
				prtfrstln(length);
			}
			else
			{
				prtscndln(length);
			}
			height++;
		}
		level++;
	}
	while(level <= prompt);
	prtfrstln(length);
    return 0;
}

void prtspaces(int space)
{
	for(int i = 0; i < space; i++)
	{
		std::cout << " ";
	}
}

void prtfrstln(int wdth)
{
	for(int a = 0; a < wdth; a++)
	{
		std::cout << "*";
	}
	std::cout << std::endl;
}

void prtscndln(int width)
{
	for(int b = 0; b < width; b++)
	{
		if((b % 2) == 0)
		{
			std::cout << "*";
		}	
		else
		{
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}
