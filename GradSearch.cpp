#include "GradSearch.h"

bool GradSearch::initialize(double themaxdis, double theepsilon,int thewin)
{
    maxdis = themaxdis;
    epsilon = theepsilon;
    winsize = thewin;

    gradvec.resize(point->getnum());
    for (int i = 0; i < point->getnum(); ++i)
    {
        gradvec[i].resize(2);
    }

    gradmat.resize(ele->getRow(), ele->getCol());

    return true;
}

bool GradSearch::calGrad()
{
    vector<double> thex = point->getX();
    vector<double> they = point->getY();
    int x, y;
    double mulgrad = 0;
    int leftx=winsize, rightx= winsize, upy= winsize, downy= winsize;

    for (int i = 0; i < point->getnum(); ++i)
    {
        x = thex[i];
        y = they[i];

        if (x <= winsize)leftx = x;
        if (ele->getCol() - x <= winsize)rightx = ele->getCol() - x;
        if (y <= winsize)upy = y;
        if (ele->getRow() - y <= winsize)downy = ele->getRow() - y;

        for (int m = 0; m < upy + downy; ++m)
        {
            for (int n = 0; n < leftx + rightx-1; ++n)
            {
                mulgrad += gradmat(y - upy + m, x - leftx + n + 1) - gradmat(y - upy + m, x - leftx + n);
            }
        }

        gradvec[i][0] = mulgrad / ((upy + downy) * (leftx + rightx));
        mulgrad = 0;

        for (int m = 0; m < upy + downy-1; ++m)
        {
            for (int n = 0; n < leftx + rightx; ++n)
            {
                mulgrad += gradmat(y - upy + m + 1, x - leftx + n) - gradmat(y - upy + m, x - leftx + n);
            }
        }

        gradvec[i][1] = mulgrad / ((upy + downy) * (leftx + rightx));
        mulgrad = 0;

    }

    return true;
}

bool GradSearch::update()
{
    for (int i = 0; i < ele->getRow(); ++i)
    {
        for (int j = 0; j < ele->getCol(); ++j)
        {
            gradmat(i, j) = calPotential(j, i);
        }
    }

    return true;
}

bool GradSearch::updataPoint()
{

    point->adjust(gradvec);

    return true;
}

double GradSearch::mean()
{
    Eigen::MatrixXd cm = gradmat.rowwise().mean();
    return cm(0,0);
}

double GradSearch::calPotential(int x, int y)
{
    double potential = 0;

    for (int i = 0; i < point->getnum(); ++i)
    {
        // calculate the distance from UAV position to any point on ground
        double r = sqrt((point->getX()[i]-x)* (point->getX()[i] - x)+(point->getY()[i]-y)* (point->getY()[i] - y)
                                    + (point->getZ()[i]-ele->at(0,y,x))* (point->getZ()[i] - ele->at(0, y, x)));

        potential += epsilon * (1 / double(r * r) - maxdis / double(r));

    }

    return potential;
}
