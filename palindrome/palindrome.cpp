#include <iostream>

using namespace std;

int main()
{
	int size, // размерность главного массива
		a, // переменная поиска наибольшей последовательности без цифр
		b, // переменная поиска наибольшей последовательности без цифр
		longest, // наибольшая последовательность символов без цифр
		m,// позиция в массиве первого элемента требуемой последовательности
		M,// позиция в массиве последнего элемента требуемой последовательности
		length; //длина самой большой последовательности
	int repid = 0; //число максимальных последовательностей одинаковой длины
	length = -1;
	float center; //параметр центровки вторичного массива
	bool exit, palindr; //палиндромность (нет:0; да:1)
	palindr = exit = 0;
	char swap = 0; //переменная для перестановки элементов в массиве
	m = M = a = b = longest = center = 0;

	cout << "Set size of array = " << endl;
	cin >> size;

	char* string = new char[size]; // первоначальный массив
	int* Arr_longest = new int[size]; // массив наиб числа символов без цифр в подстроке
	int* Arr_Mm = new int[size]; // массив верх и нижн граней подстрок

	cout << "Fill in array" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> string[i];
	}

	//иниц-ция массивов Arr_longest и Arr_Mm ??
	for (int i = 0; i < size; i++)
	{
		Arr_longest[i] = Arr_Mm[i] = 0;
	}

	//поиск наибольшего кол-ва последующих символов без цифр
	for (int k = 0; k < 2 * size;) //
	{
		for (int i = 0; i < size; i++)
		{
			if (!isdigit(string[i]))
			{
				a++;
				if ((a > 0) && ((k == 0) || ((k > 0) && (a >= Arr_longest[k / 2 - 1]))))
				{
					Arr_longest[k / 2] = a;
					if (Arr_longest[k / 2] > 1)
					{
						Arr_Mm[k + 1] = i;
						Arr_Mm[k] = i - (Arr_longest[k / 2] - 1);
					}
					else//для одного элемента в подстроке
					{
						Arr_Mm[k + 1] = i;
						Arr_Mm[k] = i;
					}
				}
				if ((i == size - 1) && (a < Arr_longest[k / 2 - 1]))
				{
					k = k - 2;
					break;
				}
				continue;
			}
			if (isdigit(string[i]))
			{
				if ((a > 0) && ((k == 0) || ((k > 0) && (a >= Arr_longest[k / 2 - 1]))))
				{
					k = k + 2;
				}
				a = 0;
			}
			for (int j = i + 1; j < size; j++)
			{
				if (!isdigit(string[j]))
				{
					b++;
					if ((b > 0) && ((k == 0) || ((k > 0) && (b >= Arr_longest[k / 2 - 1]))))
					{
						Arr_longest[k / 2] = b;
						if (Arr_longest[k / 2] != 1)
						{
							Arr_Mm[k + 1] = j;
							Arr_Mm[k] = j - (Arr_longest[k / 2] - 1);
						}
						else if (Arr_longest[k / 2] == 1)   //для одного элемента в подстроке
						{
							Arr_Mm[k + 1] = j;
							Arr_Mm[k] = j;
						}
					}
					if ((j == size - 1) && (b < Arr_longest[k / 2 - 1]))
					{
						i = j;
						k = k - 2;
						break;
					}
					else if ((j == size - 1) && (b == Arr_longest[k / 2 - 1]))
					{
						i = j;
						break;
					}
					continue;
				}
				if (isdigit(string[j]))
				{
					if ((b > 0) && ((k == 0) || ((k > 0) && (b >= Arr_longest[k / 2 - 1]))))
					{
						k = k + 2;
					}
					else if ((j == size - 1) && (b < Arr_longest[k / 2 - 1]))
					{
						k = k - 2;
					}
					b = 0;
					i = j;
				}
				break;
			}
		}
		length = k / 2;
		if ((length > 0) && (Arr_longest[length] == 0))
		{
			length = length - 1;
		}
		break;
	}
	if (length == -1)
	{
		cout << "Only numerals" << endl;
		system("pause");
		return 0;
	}

	int* max = new int[length];
	max[0] = 0;
	if (length > 0)
	{
		repid = 0;
		for (int i = 0; i < length; i++)
		{
			if (exit == 1)
			{
				break;
			}
			for (int j = i + 1; j <= length; j++)
			{

				if (Arr_longest[i] < Arr_longest[j])
				{
					if ((j == length))
					{
						repid = 1;
						max[repid] = j;
						longest = Arr_longest[j];
					};
					break;
				}
				else if ((Arr_longest[i] > Arr_longest[j]) && (Arr_longest[i] != Arr_longest[j]))
				{
					if ((j == length))
					{
						repid = 1;
						max[repid] = i;
						longest = Arr_longest[i];
						exit = 1;
						break;
					}
					exit = 0;
					continue;
				}
				else if (Arr_longest[i] >= Arr_longest[j])
				{
					if (repid == 0)
					{
						longest = Arr_longest[j];
						max[1] = i;
						max[2] = j;
						repid = 2;
					}
					else
					{
						repid = repid + 1;
						max[repid] = j;
					}
				}
			}
		}
	}
	else if (length == 0)
	{
		repid = 1;
		max[1] = 0;
		longest = Arr_longest[0];
	}

	//вывод нового массива(массивов)
	for (int z = 1; z <= repid; z++)
	{
		//создание из требуемой последовательности массива
		char* string_fin = new char[longest];
		m = Arr_Mm[max[z] * 2]; //нижняя грань
		M = Arr_Mm[max[z] * 2 + 1]; //верхняя грань

		for (int i = 0; i < longest; i++)
		{
			if (m <= M)
			{
				string_fin[i] = string[m];
				m++;
			}
		}
		//определение параметра для такой четности строки
		if (!(longest % 2))
			center = longest / 2;

		else if (longest % 2)
			center = ((float)longest) / 2 - 1;

		//определение палиндромности 
		for (int i = 0; i < center; i++)
		{
			if (string_fin[i] == string_fin[longest - i - 1])
			{
				palindr = 1;
				continue;
			}
			else
			{
				palindr = 0;
				break;
			}
		}
		//поворот не палиндрома
		if (palindr == 0)
		{
			for (int i = 0; i < center; i++)
			{
				swap = string_fin[i];
				string_fin[i] = string_fin[longest - i - 1];
				string_fin[longest - i - 1] = swap;
			}
			for (int i = 1; i <= z; i++)
			{
				for (int y = 0; y < longest; y++)
				{
					if (Arr_Mm[max[i] * 2] <= Arr_Mm[max[i] * 2 + 1])
					{
						string[Arr_Mm[max[i] * 2]] = string_fin[y];
						Arr_Mm[max[i] * 2] = Arr_Mm[max[i] * 2] + 1;
					}
					else
					{
						break;
					}
				}
			}
		}
		delete[] string_fin;
	}
	//вывод результата
	for (int i = 0; i < size; i++)
	{
		cout << string[i] << " ";
	}
	delete[] string;
	delete[] Arr_longest;
	delete[] Arr_Mm;

	system("pause");
	return 0;
}
