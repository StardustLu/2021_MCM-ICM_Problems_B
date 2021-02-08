#include <iostream>
#include "Image.h"
#include "UAVPoint.h"
#include "GradSearch.h"
using namespace std;

int main()
{
	/************************  parament  ****************************/
	double kiloscalar = 0.1;				// pixel per kilometer
	double step = 10;						// grad per step
	int pointnum = 4;						// numbers of UAV
	double height = 200;					// UAV height above ground
	int epoch = 10;
	/****************************************************************/
	srand((unsigned int)(time(NULL)));
	string imgpath = "F:/test/MathModel/Data/ele/ele1.tif";
	Image ele;
	ele.getPath(imgpath);
	ele.loadData(0);

	UAVPoint point(pointnum);
	point.initialize(&ele,height,step);

	cout << "origin point" << endl;
	for (int i = 0; i < point.getnum(); ++i)
	{
		cout << point.getX()[i] << " " << point.getY()[i] << " " << point.getZ()[i] << endl;
	}

	

	GradSearch search(&ele, &point);
	search.initialize(5);

	for (int i = 0; i < epoch; ++i)
	{
		search.update();
		search.calGrad();
		search.updataPoint();
		cout << endl;
		cout << "Epoch "<<i+1<<" : " << search.mean() << endl;
		for (int i = 0; i < point.getnum(); ++i)
		{
			cout << point.getX()[i] << "," ;
		}
		cout << endl;
		for (int i = 0; i < point.getnum(); ++i)
		{
			cout << point.getY()[i] << "," ;
		}
		cout << endl;
		for (int i = 0; i < point.getnum(); ++i)
		{
			cout << point.getZ()[i] << ",";
		}
		cout << endl;
	}




	return 0;
}
