#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Image.h"
using namespace std;

class UAVPoint
{
public:
	UAVPoint(int pointnum):num(pointnum){}
	~UAVPoint(){}
	bool initialize(Image* img,double height,double thestep);
	bool adjust(vector<vector<double>>& grad);
	int getnum() { return num; }

	vector<double>& getX() { return x; }
	vector<double>& getY() { return y; }
	vector<double>& getZ() { return z; }

private:

	vector<double> x;
	vector<double> y;
	vector<double> z;

	Image* ele;
	int num;
	double step;
};

