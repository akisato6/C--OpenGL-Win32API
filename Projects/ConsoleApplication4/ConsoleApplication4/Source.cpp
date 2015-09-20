/*
フーリエ級数（ステップ関数）
*/
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

double PI = acos(-1.0);
double e = 2.7182818284590452354;

double a = 1.0;
double L = 1.0;
double l = 0.5;
double x_max = 4.0;

int main(void){

	for (int m_max = 2; m_max <= 32; m_max *= 2){ // 級数の項数を指定
		ostringstream fname1;
		fname1 << "step-" << m_max << ".data"; //出力ファイル名
		string fname1_s = fname1.str();
		ofstream fout;
		fout.open(fname1_s.c_str());

		for (double x = 0.0; x <= x_max; x += 0.001){ //実空間の刻み幅
			double sum = 0.0;
			for (int m = 1; m <= m_max; m++){
				sum += (sin(PI*double(m)*l / L) * cos(PI*double(m)*(2.0*x - l) / L)) / double(m);
			}
			double f = a * 0.5 - 2.0 *a * sum / PI;
			fout << x << " " << f << endl;
		}
		cout << m_max << endl;
	}

	return 0;
}