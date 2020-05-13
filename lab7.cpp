#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

long double dy3_(double x);
long double dy4_(double x);
long double dy5_(double x);
long double dy6_(double x);
long double Teilor();
long double T1();
long double T2();
int fact(int x);//факториал

long double dy[7];
//long double dy[7] = { 1,0,0,dy3_(0),dy4_(0), dy5_(0), dy6_(0) }; //значения первых 6 производных в точке x=0
long double a = 0, b = 2;
long double h = (b - a) / 2;//постоянный шаг вдоль Ox
double yp;//для хранения предыдущего значения 
double e = 0.01;//точость
int main()
{
	cout << "please wait 10-30 second and open the graph.py" << endl;
	double pr;//для хранения следующего и предыдущего значений y для вычисления производной 
	ofstream fout, fout1, fout2;
	bool usl = false;
	do {
		dy[0] = 1;  dy[1] = 0;   dy[2] = 0;  dy[3] = dy3_(0); dy[4] = dy4_(0); dy[5] = dy5_(0);   dy[6] = dy6_(0);

		fout.open("Func.txt");
		fout1.open("Proizv.txt");
		fout2.open("FazTraekt.txt");
		for (long double i = a; i < b + h; i += h) {
			//запись значений производной
			pr = dy[0];


			fout << i << " " << dy[0] << endl;
			if (i < b) {
				fout2 << dy[0] << " ";

				dy[0] = Teilor();
				fout1 << i << " " << (dy[0] - pr) / h << endl;

				fout2 << (dy[0] - pr) / h << endl;
			}

			dy[1] = T1();
			dy[2] = T2();
			dy[3] = dy3_(i);
			dy[4] = dy4_(i);
			dy[5] = dy5_(i);
			dy[6] = dy6_(i);
		}
		if (usl && abs(dy[0] - yp) < e) { fout.close(); fout1.close(); fout2.close(); return 1; } //оценка погрешности по правилу Рунге
		else { yp = dy[0]; usl = true; h /= 10; fout.close(); fout1.close(); fout2.close(); }//если еще не добились желаемой точноси, уменьшаем шаг в 2 раза 
	} while (true);
	
}

//////////////////////////////////////////////////////////////////////////////////////////
int fact(int x) {//факториал
	int n = 1, i = 1;
	if (x == 0 || x == 1) return 1;
	else {
		while (i != x) {
			n *= i + 1;
			i++;
		}
	}
	return n;
}

long double Teilor() {//функция Тейлора для порядка 4
	return dy[0] + h * dy[1] + pow(h, 2) * dy[2] / 2 + pow(h, 3)* dy[3] / fact(3) + pow(h, 4) * dy[4] / fact(4);
}

long double T1() {// первая производная Тейлора (формула Тейлора для y')
	return dy[1] + h * dy[2] + pow(h, 2) * dy[3] / fact(2) + pow(h, 3) * dy[4] / fact(3) + pow(h, 4) * dy[5] / fact(4);
}

long double T2() {// вторая производная Тейлора (формула Тейлора для y'')
	return dy[2] + h * dy[3] + pow(h, 2) * dy[4] / fact(2) + pow(h, 3) * dy[5] / fact(3) + pow(h, 4) * dy[6] / fact(4);
}

long double dy3_(double x) {//формула 3-й производной (из условия)
	return 4 * dy[0] + sin(x) * exp(-x);
}
long double dy4_(double x) {//формула 4-й производной 
	return 4 * dy[1] + (cos(x) - sin(x)) * exp(-x);
}

long double dy5_(double x) {//формула 5-й производной 
	return 4 * dy[2] - 2 * cos(x) * exp(-x);
}

long double dy6_(double x) {//формула 6-й производной 
	return 4 * dy[3] + 2 * exp(-x) * (cos(x) - sin(x));
}