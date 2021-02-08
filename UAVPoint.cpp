#include "UAVPoint.h"

bool UAVPoint::initialize(Image* img,double height,double thestep)
{
    int rowgrid = img->getRow() / (num);
    int colgrid = img->getCol() / (num);
    this->step = thestep;
    ele = img;

    for (int i = 0; i < num; ++i)
    {
        y.push_back(rowgrid * i + rand() % rowgrid);
        x.push_back(colgrid * i + rand() % colgrid);
        z.push_back(img->at(0, y[i], x[i])+height);
    }

    return true;
}

bool UAVPoint::adjust(vector<vector<double>>& grad)
{
    for (int i = 0; i < num; ++i)
    {
        if (x[i] * (1 + grad[i][0] * step) < 0)
        {
            x[i] = 0;
        }
        else if (x[i] * (1 + grad[i][0] * step) >= ele->getCol())
        {
            x[i] = ele->getCol()-1;
        }
        else
        {
            x[i] = x[i] * (1 + grad[i][0] * step);
        }

        if (y[i] * (1 + grad[i][1] * step) < 0)
        {
            y[i] = 0;
        }
        else if (y[i] * (1 + grad[i][1] * step) >= ele->getRow())
        {
            y[i] = ele->getRow() - 1;
        }
        else
        {
            y[i] = y[i] * (1 + grad[i][1] * step);
        }

        z[i] = ele->at(0, y[i], x[i]);

        double gradx = grad[i][0];
        double grady = grad[i][1];
        double tx = x[i];
        double ty = y[i];

        double t = 0;
    }

    


    return true;
}
