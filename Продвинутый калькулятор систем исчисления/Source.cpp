#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

bool IsValidData(int Initial_number_system, int Final_number_system, std::string& number);
std::string ConversionDecimalToAnother(std::string value, int Final_number_system);
std::string ConversionAnotherToDecimal(std::string value, int Initial_number_system);
int ConversionFromCharToInt(char value);
void ConversionToChar(std::string& str, int value);

int main()
{
	std::setlocale(LC_ALL, "ru");
	int Initial_number_system, Final_number_system;
	std::string number;
	cout << "������� ��������� ������� ���������: ";
	cin >> Initial_number_system;
	cout << "������� �����: ";
	cin >> number;
	cout << "�������� ������� ��������� � ������� �� ������ ��������� �����(�� 16-������) : ";
	cin >> Final_number_system;
	try
	{
		IsValidData(Initial_number_system, Final_number_system, number);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		system("pause");
		return 1;
	}
	auto print = [](std::string number, int Initial_number_system, int Final_number_system) {
		cout << "����� " << number << " � ��������� ������� ���������: " << Initial_number_system
			<< " ����� ����� ����� � " << Final_number_system << " ������� ���������: ";
	};
	if (Initial_number_system == 10) // ������� �� 10 � ����� ������(������ �� 16-������)
	{
		print(number, Initial_number_system, Final_number_system);
		cout << "\n" << ConversionDecimalToAnother(number, Final_number_system) << "\n";
	}
	else if (Final_number_system == 10) // ������� �� ������ ������ � ����������
	{
		print(number, Initial_number_system, Final_number_system);
		cout << "\n" << ConversionAnotherToDecimal(number, Initial_number_system) << "\n";
	}
	else // ������� �� �� ���������� �� � ����������
	{
		print(number, Initial_number_system, Final_number_system);
		cout << "\n" << ConversionDecimalToAnother(ConversionAnotherToDecimal
		(number, Initial_number_system), Final_number_system) << "\n";
	}
	system("pause");
	return 0;
}

void ConversionToChar(std::string& str, int value)
{
	switch (value)
	{
	case 0:
		str.push_back('0');
		break;
	case 1:
		str.push_back('1');
		break;
	case 2:
		str.push_back('2');
		break;
	case 3:
		str.push_back('3');
		break;
	case 4:
		str.push_back('4');
		break;
	case 5:
		str.push_back('5');
		break;
	case 6:
		str.push_back('6');
		break;
	case 7:
		str.push_back('7');
		break;
	case 8:
		str.push_back('8');
		break;
	case 9:
		str.push_back('9');
		break;
	case 10:
		str.push_back('A');
		break;
	case 11:
		str.push_back('B');
		break;
	case 12:
		str.push_back('C');
		break;
	case 13:
		str.push_back('D');
		break;
	case 14:
		str.push_back('E');
		break;
	case 15:
		str.push_back('F');
		break;
	default:
		str.push_back(',');
		break;
	}
}

int ConversionFromCharToInt(char value)
{
	switch (value)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	case ',':
		return 0;
	}
}
// ������� �� ���������� � ������ ������� ���������� ������ �� 16
std::string ConversionDecimalToAnother(std::string value, int Final_number_system)
{
	std::string result, iPart="", dPart = "";
	double IntPart = 0, DoubPart = 0;
	IntPart = std::stoi(value);
	DoubPart = std::stod(value) - IntPart;
	//������� ����� �����
	while (IntPart > 0)
	{
		ConversionToChar(iPart,((int)IntPart % Final_number_system));
		IntPart = (int)IntPart / Final_number_system;
	}
	std::reverse(iPart.begin(), iPart.end());
	//������� ������� �����
	for (int i = 0; i < 5; i++)
	{
		ConversionToChar(dPart, ((int)(DoubPart * Final_number_system)));
		DoubPart = Final_number_system * DoubPart - int(DoubPart * Final_number_system);

	}
	result = iPart + ',' + dPart; // ���������� ����� � ������� ����� � ���� ������
	return result;
}
// ������� �� ������ ������ ����������(������ �� 16) � ����������
std::string ConversionAnotherToDecimal(std::string value, int Initial_number_system)
{
	double result = 0;
	auto f = [value]() {
		int degree = -1; // -1, �.�. ����� ��� � ����
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i] == ',')
			{
				break;
			}
			degree++;
		}
		return degree;
	};
	int degree = f();
	for (auto& val : value)
	{
		if (val != ',')
		{
			result += std::pow(Initial_number_system, (degree)) * ConversionFromCharToInt(val);
			degree--;
		}
	}
	return std::to_string(result);
}

bool IsValidData(int Initial_number_system, int Final_number_system, std::string& number)
{
	bool IsValid = 1;
	if (Final_number_system == Initial_number_system)
	{
		throw std::exception("�� ����� ���������� �������� ��������� � �������� ������� ���������");
		IsValid = 0;
	}
	if (number.empty())
	{
		throw std::exception("�� �� ����� �����");
		IsValid = 0;
	}
	if (ConversionFromCharToInt(number[0]) < 0)
	{
		throw std::exception("�� ����� ������������� �����");
		IsValid = 0;
	}
	if (Final_number_system <= 0 || Initial_number_system <= 0 || Final_number_system > 16 
		|| Initial_number_system > 16)
	{
		throw std::exception("�� ����� ������������ ������� ����������");
		IsValid = 0;
	}
	for (int i = 0; i < number.size(); i++) {
		if (ConversionFromCharToInt(number[0]) >= Initial_number_system)
		{
			throw std::exception("����� ������ �������� ������� ����������");
			IsValid = 0;
		}
	}
	for (int i = 0; i < number.size(); i++) // ������ ����� �� �������
	{
		if (number[i] == '.')
		{
			number[i] = ',';
			break;
		}
	}
	int Point�ounter = 0;
	for (auto& val : number) // �������� �� ���������� �������
	{
		if (val == ',')
			Point�ounter++;
		if (Point�ounter > 1)
		{
			throw std::exception("������������ �����");
			IsValid = 0;
		}
	}
	return IsValid;
}
