#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<Windows.h>
#include <cctype>
#include <algorithm>
using namespace std;

template <typename T>
string toString(T val) {
	ostringstream oss;					//�������� ���������� ������
	oss << val;							//������ ���� � �����
	return oss.str();					//����� ���� ���� ������
}
class Month {
public:
	Month(string str) {					//� ������� ����������� ��� ��� ���������� ������
		for (int i = 0; i < 12; ++i) {
			day[i] = new string * [count_day[i]];
			year[i] = new int* [count_day[i]];
		}
		//loadFromFile(str);				//�������� � �����
	}
	/*void delEvent(int num, string month_t) {		//�������� ������� (����� ���; ����� (��������))
		if (validator(num + 1, month_t)) {				//�������� �� ���������� �����
			string month = setReg(month_t);				//������� ��������� ���� �������� (������ �������, � ��������� ���������)
			int tmp = getMonthNum(month) - 1;			//���������� ����� ������
			if (!day[tmp][num - 1].empty()) {			//���� � ���� ���� ���� �������, �� ��������
				for (int i = 0; i < numb; ++i) {		//����� ������� ��� � ����������� �� ������� ��� ����������
					if (number[tmp][i] + 1 == num) {	//���� ��� ������ ����, �� ������� ���������� �� �������
						day[tmp][num - 1] = { "" };
						number[tmp][i] = 0;
						if (count_events[tmp] > 1) for (i; i < count_events[tmp]; ++i) number[tmp][i] = number[tmp][i + 1];		//�������� �� ��������� �������
						break;
					}
				}
				--numb;
				++count_del;
				--count_events[tmp];
				if (count_events[tmp] == 0)
					num_month[getLastRec()] = -1;		//���� ��� ���� ��������� ������� � ������, �� ������� ������ �� ���� ������
			}
		}
	}*/
	void setEvent(int num_d, int time_e, string event, string month) {		//���������� ������� (����� ���; �������; �����)
		if (validator(num_d, month)) {
			string month = setReg(month);					//������� ��������� ���� �������� (������ �������, � ��������� ���������)
			int month_n = (getMonthNum(month) - 1);				//���������� ����� ������
			getArray(month_n, num_d, time_e, event);
			/*/day[tmp][num] = event;
			getNumberArray(num, tmp);
			for (int i = 0; i < 12; ++i) {
				if (num_month[i] == tmp) {				//����� ������� ������ ������ ������
					flag = true;
					break;
				}
			}
			if (!flag) {								//���� ������ ������ �� ����, �� ������ ����� ������
				++tmp_tmp;
				num_month[tmp_tmp] = tmp;
			}
			++numb;
			index[tmp][num] = numb;*/
		}
	}
void showMonths() {			//����� �������
	int tmp = 0;			//������ ���-�� ���� � ������, �� �� ������ ���� ������ 7
	cout << "������ ��� -  " << num_year << "\n\n";
	int tmp2 = x;					//��������� ���������� ��������, ������ ����� ������ ��������, �� ���� �������� �� �������
	for (int q = 0; q < 12; ++q) {
		if (tmp2 >= 7) tmp2 -= 7;				//���� ������ ����� ������ "7", �� �� ��� �� ��������� � ��������� ������ � ����� �������� 7 
		else if (tmp2 < 0) tmp2 += 7;			//���� ������, �� ��� ��� �� ����������, ��� ���������� 7
		cout << "\n" << month_name[q] << "\n";
		cout << "��\t��\t��\t��\t��\t��\t��\n\n";

		for (int w = 0; w < tmp2; ++w) {		//����� ������� ��-�� �������� (���� ������ = ���� ���)
			cout << " \t";
			++tmp;								//���� ���� ��������� ��� ����
		}
		for (int i = 0; i < count_day[q]; ++i) {
			if (tmp == 7) {		//���� 7 ����, ��
				cout << "\n";	//������ ������� ������ �
				tmp = 0;		//��������
			}
			++tmp;

			cout << year[q][i] << "\t";								//������ ������� ����� ���
		}
		cout << "\n\n";													//����� ������� ������ ��� �������� ������
		tmp2 = tmp;														//������ � ������ ������ ����� = ���������� ���� � ��������� ������ � �����������
		tmp = 0;														//���-�� ��������
	}
}


/*void backup() {										//����������
	string tmp = toString(num_year);
	tmp += ".txt";
	ofstream backupFile(tmp, ios_base::trunc);		//������� ���� � ��������� ����
	for (int q = 0; q < 12; ++q) {
		if (num_month[q] != -1) {					//��������� ������ �� ���, � ������� ��������� �������
			backupFile << "\n!" << month_name[num_month[q]] << endl;		//�������� ������("!" �������� ��� ���� ����� �������)
			for (int i = 0; i < count_events[num_month[q]]; ++i)
				if (i != 0)		//���� �� ���� ����� ������ ������ �������, ��
					backupFile << endl << "?" << number[num_month[q]][i] + 1 << " " << day[num_month[q]][number[num_month[q]][i]];		//������ "?" � ���������
				else
					backupFile << number[num_month[q]][i] + 1 << " " << day[num_month[q]][number[num_month[q]][i]];
		}
		else
			break;
	}
	backupFile.close();								//��������� ����
}*/
void setYear(int year) {			//�������� ���� � ����������� �������
	bool flag = false;
	int near_vis_year;				//��������� ������� ���������� ���
	num_year = year;
	while (!flag) {
		if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) flag = true;		//���� ��� �� ���������� ���
		else
			--year;																			//�������� ���� ���
	}
	near_vis_year = year;
	int tmp = searchOffestVisYear(near_vis_year, near_vis_year / 100);		//���� � ������� ��� ����������� ������� ���� ��������� ������� ���������� ��� � �������� 
	int raz = num_year - near_vis_year;										//�������� ����� ��������� ����� � ��� ����������
	if (near_vis_year == num_year) {										//���� ����������, �� 
		x = (tmp + raz) - 2;												//������ ��������� ������ �������� � �������, �� ����� ������� 2 (������ ������ ���)
		count_day[1] = 29;													//� � ������� 29 ����
	}
	else																	//�����
		x = (tmp + raz) - 1;												//�� ������� �������� ������ 1 (���� ������ ������ ���)
}
string setReg(string tmp) {								//��������� �������� (������ �������, � ��������� ���������)
	tmp[0] = toupper(tmp[0]);							//������ ����� ���������
	for (int i = 1; i < tmp.size(); ++i) {
		tmp[i] = tolower(tmp[i]);						//��������� ��� ���������
	}
	return tmp;											//������� ������
}
private:
	void getArray(int month_n, int day_n, int time, string event) {
		
	}
	/*void setMonth() {									//�������� ������� � �����
		for (int q = 0; q < 12; ++q)					//12 �������
			for (int i = 0; i < count_day[q]; ++i)		//��������������� ���-�� ���� �� ���������
				year[q][i] = i + 1;						//���������� �����
	}*/
	/*void loadFromFile(string str) {										//�������� �� �����
		setMonth();														//���������� �������� ������� � ������
		ifstream inputFile(str.c_str());								//���� ���� � ��������� ���� ����, �� ������
		if (inputFile.is_open()) {										//���� ���� ��������
			if (!inputFile.eof()) {										//���� ���� �� ������� �� �����
				int month = -1;											//����� ������
				int mon = -1;											//���������� ������� � ��������� ;����� ������ ��� ���������� ������� � �������� � ������� ���������� � ��� ������� (num_month)
				while (!inputFile.eof()) {								//������ ����, ���� �� ����� �� �����
					char tmp2 = ' ';									//��������������� ����; ���������� ��� �������� ������� ("!" - ���� ����� �������: "?" - ���� ����� ��� ��� � ������� ������������ � ����)
					int tmp = 0;										//����� ���
					string tmp_str = " ";								//�������� ������
					inputFile >> tmp2;
					if (tmp2 == '!') {
						inputFile >> tmp_str;							//������ ������
						month = getMonthNum(tmp_str) - 1;				//����������� ������ ������
						inputFile >> tmp;								//������ ������ ���
						inputFile.ignore();								//����������� ������� ��� ������� ������ getline
						getline(inputFile, day[month][tmp - 1]);		//������ ������� �� ����� � ������ � ������ ������� [����� ������] [����� ���]
						getNumberArray(tmp - 1, month);					//���������� ������ ������ ��� � ������ ���� ����������� ������� ���� � ���������
						++numb;											//���������� ���-�� �������
						++mon;											//���������� ���-�� �������, ������ � ����� ����� ����� �����
						index[month][tmp - 1] = numb;					//���������� ������ ������� � ������, ����� ��� ������ ���������, ��� � ��������� ����������
																		//���������������� �������, ������������ � ����� ������������������ ��������� ��� �������
						num_month[mon] = month;							//���������� ������ ������ � ������ � �������� � ������� ���� �������
																		//[���������������� �����, ����� ���� ����� ������� ����������]
					}
					else if (tmp2 == '?') {
						inputFile >> tmp;								//������ ������ ���
						getline(inputFile, day[month][tmp - 1]);		//������ ������� �� ����� � ������ � ������ ������� [����� ������] [����� ���]
						getNumberArray(tmp - 1, month);					//���������� ������ ������ ��� � ������ ���� ����������� ������� ���� � ���������
						++numb;											//���������� ���-�� �������
						index[month][tmp - 1] = numb;					//���������� ������ ������� � ������, ����� ��� ������ ���������, ��� � ��������� ����������
																		//���������������� �������, ������������ � ����� ������������������ ��������� ��� �������
					}
				}
				inputFile.close();										//�������� ��������� �����
			}
		}
	}*/
	int searchOffestVisYear(int a, int year) {			//����� ������� ��� ����������� ����
		int tmp = a % 100;				//��������� ��� ����� ��� ������ �� �������
		int i, max, j;
		if (year % 2 != 0) {			//���� ��� �� 20 ���, ��
			i = 1;						//�������� � ������ ������� �
			j = 0;						//� ������� �������, ��
			max = 5;					//�� 4 ������

		}
		else {							//�����
			i = 4;						//� 4 ������
			j = 3;						//�� 4 �������
			max = 8;					//�� 8 ������

		}
		for (i; i < max; ++i) {						//����� �� 
			for (j; j < 8; ++j) {					//�������� ����������
				if (tmp == offest[i][j]) {			//���� ������ ���������
					return offest[0][j];			//����� ����� ������� ������ (0-�� ������)
				}
			}
			j = 0;
		}
	}

	bool validator(int num, string month) {			//�������� ���������� �����
		int count = count_day[getMonthNum(month) - 1];		//���-�� ���� � ������
		if ((num <= count) && (num > 0)) return true;
		else
			return false;
	}


	int getMonthNum(string s) {									//����������� ������ ������
		if (s == "������") return 1;
		else
			if (s == "�������") return 2;
			else
				if (s == "����") return 3;
				else
					if (s == "������") return 4;
					else
						if (s == "���") return 5;
						else
							if (s == "����") return 6;
							else
								if (s == "����") return 7;
								else
									if (s == "������") return 8;
									else
										if (s == "��������") return 9;
										else
											if (s == "�������") return 10;
											else
												if (s == "������") return 11;
												else
													if (s == "�������") return 12;
													else
														return -1;
	}
	int offest[8][7] = { {6, 4, 2, 0, 5, 3, 1},
						 {4, 8, 12, 16, 20, 24 ,28},
						 {32, 36, 40, 44, 48, 52, 56},
						 {60, 64, 68, 72, 76, 80, 84},
						 {88, 92, 96, 0, 4, 8, 12 },
						 {16, 20, 24, 28, 32, 36, 40},
						 {44, 48, 52, 56, 60, 64, 68},
						 {68, 76, 80, 84, 88, 92, 96}
	}; 									//������� � ����������� ������ � ���������������� ���������			
	string*** day = new string * *[12];					//������ � ��������� [����� ������] [����� ���]
	int*** year = new int** [12];					//������ � �������� ���� [����� ������] [����� ���]
	int x;								//����� �������
	int num_year;						//����� ���������� ����
	int count_day[12] = { 31, 28,31,30,31,30,31,31,30,31,30,31 };		//���-�� ���� � ������� �� ��������� [����� ������]
	string month_name[12] = { "������", "�������","����" ,"������","���" ,"����" ,"����" ,"������" ,"��������" ,"�������","������", "�������" };	//������ �������� ������� [����� ������]

};
int main() {

	SetConsoleCP(1251);							//����������� �������
	SetConsoleOutputCP(1251);					//����������� �������
	setlocale(LC_ALL, "rus");					//�������� ������� ����

	while (true) {								//������� ���� ���������
		system("color 70");						//���� ������� (����� ��� � ������ �����)
		system("cls");							//������� �������
		int year = 0;
		cout << "������� ���\n";
		cin >> year;
		string tmp = toString(year);			//�������������� ���� � ������ ��� �������� �����
		tmp += ".txt";							//�������� � ���� ".txt" ��� ������������ �������� �����
		Month month(tmp);						//���������� ������ � ������ ���������� ����						
		month.setYear(year);					//�������� ���� (����������� �������)
		while (true) {	/*						//����� ���� ���������
			system("cls");						//������� �������
			month.showMonths();					//����� �������
			string tmp_str, tmp_str2;			//���� ������; ���� ������
			int tmp_int;						//����� ���
			month.showEvents();					//����� �������
			cout << "����� ������������� �������, ������� => �������������\n����� �������� ���, ������� => �����\n����� �����, ������� ����� ������\n\n";
			cin >> tmp_str;
			tmp_str = month.setReg(tmp_str);		//������� ��������� ���� �������� (������ �������, � ��������� ���������)
			if (tmp_str == "�������������") {
				cout << "\n����� ������� �������, ������� => �������\n����� �������� ��� �������� �������, ������� => ��������\n\n";
				cin >> tmp_str;
				tmp_str = month.setReg(tmp_str);	//������� ��������� ���� �������� (������ �������, � ��������� ���������)
				if (tmp_str == "�������") {
					cout << "\n�������� �����\n";
					cin >> tmp_str;
					cout << "\n�������� ����\n";
					cin >> tmp_int;
					month.delEvent(tmp_int, tmp_str);		//������� �������� �������
				}
				else
					if (tmp_str == "��������") {
						cout << "\n�������� �����\n";
						cin >> tmp_str2;
						cout << "\n�������� ����\n";
						cin >> tmp_int;
						cout << "\n������� �������\n";
						cin.ignore();
						getline(cin, tmp_str);
						tmp_str2 = month.setReg(tmp_str2);
						month.setEvent(tmp_int, tmp_str, tmp_str2);			//���������� �������
					}
			}
			else
				if (tmp_str == "�����") break;
				else
					return 0;
			month.backup();							//����� (���������� � ����)*/
		}
	}
	return 0;
}