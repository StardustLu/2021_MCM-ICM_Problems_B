#pragma once
#include "Image.h"
#include "UAVPoint.h"

class GradSearch
{
public:
	GradSearch(Image* img,UAVPoint* p):ele(img),point(p){}
	~GradSearch(){}

	bool initialize(double themaxdis,double theepsilon=1, int thewin=5);			// initialize the object         
	bool calGrad();																	// calculate the mean grad of x and y 
	bool update();																	// update grad matrix 
	bool updataPoint();																// update the position of UAV
	double mean();

private:

	double calPotential(int x, int y);												// the potential function : p(r)= \epsilon * ( \frac{1}{r^2} - \frac{maxdis}{r} )

	vector<vector<double>> gradvec;

	double maxdis, epsilon;
	int winsize;																	// half of the grad window size

	Eigen::MatrixXd gradmat;
	Image* ele;
	UAVPoint* point;
};

