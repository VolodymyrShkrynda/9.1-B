// B
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;

enum Spec { KN, INF, ME, FI, TN };
string SpecStr[] = { "Комп.наука", "Інформатика", "Математика та Економіка", "Фізика та Інформатика", "Трудове навчання" };

struct Student
{
	string prizv;
	int kurs;
	Spec spec;
	int physics;
	int math;
	union
	{
		int program;
		int metods;
		int pedag;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
double LineSearch(Student* p, const int N);
double LineSearch1(Student* p, const int N);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість студентів: "; cin >> N;

	Student* p = new Student[N];
	Create(p, N);
	Print(p, N);
	int cnt = LineSearch1(p, N);
	cout << "Кількість студентів,які навчаються на відмінно та добре:" << endl;
	cout << cnt << endl;
	int proc = LineSearch(p, N);
	cout << "Процент студентів, у яких середній бал менший 4:" << endl;
	cout << proc <<'%'<< endl;
	return 0;
}
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " Спеціальність: (0 - Комп.науки, 1 -Інформатика , 2 - Математика та економіка, 3 - Фізика та Інформатика,4 - Трудове навчання): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " Оцінка по фізиці: ";cin >> p[i].physics;
		cout << " Оцінка по математиці: ";cin >> p[i].math;
		switch (p[i].spec)
		{
		case KN:
			cout << " Оцінка по програмуванню : "; cin >> p[i].program;
			break;
		case INF:
			cout << " Оцінка по чисельним методам : "; cin >> p[i].metods;
			break;
		case ME:
		case FI:
		case TN:
			cout << " Оцінка з педагогіки: "; cin >> p[i].pedag;
			break;
		}
		cout << endl;

	}
}
void Print(Student* p, const int N)
{
	cout << "=============================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Предмет по фаху |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(3) << right << i + 1 << " ";
		cout << "|  " << setw(6) << left << p[i].prizv << "| " << setw(4) << right << p[i].kurs << "  "
			<< "| " << setw(6) << left << SpecStr[p[i].spec] << setw(4);
		cout << "   |" << setw(4) << right << p[i].physics << setw(4) << right << "| ";
		cout << setw(4) << right << p[i].math << setw(4) << right << "    | ";
		switch (p[i].spec)
		{
		case KN:
			cout << setw(4) << right << p[i].program << setw(8) << right << "    | "<<endl;
			break;
		case INF:
			cout << setw(4) << right << p[i].metods << setw(8) << right << "    | " << endl;
			break;
		case ME:
		case FI:
		case TN:
			cout << setw(4) << right << p[i].pedag << setw(8) << right << "| " << endl;
			break;
		}
	}
	cout << "==============================================================================" << endl;
}
double LineSearch(Student* p, const int N) {
	int n = 0,k=0;
	for (int i = 0; i < N; i++)
	{
		n++;
		switch (p[i].spec)
		{
		case KN:
			if (((p[i].program + p[i].physics + p[i].math) / 3) < 4)
			k++;
			break;
		case INF:
			if (((p[i].metods + p[i].physics + p[i].math) / 3) < 4)
				k++;
			break;
		case ME:
		case FI:
		case TN:
			if (((p[i].pedag + p[i].physics + p[i].math) / 3) < 4)
				k++;
			break;
		}
	}
	return 100*k/n;
}
double LineSearch1(Student* p, const int N) {
	int n = 0;
	for (int i = 0; i < N; i++)
	{
		switch (p[i].spec)
		{
		case KN:
			if ((p[i].program>3) &&  (p[i].physics>3) && (p[i].math>3))
				n++;
			break;
		case INF:
			if ((p[i].metods > 3) && (p[i].physics > 3) && (p[i].math > 3))
				n++;
			break;
		case ME:
		case FI:
		case TN:
			if ((p[i].pedag > 3) && (p[i].physics > 3) && (p[i].math > 3))
				n++;
			break;
		}
	}
	return n;
}