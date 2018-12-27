/**
 * @file    ChartRscore.сpp
 * @author  E. Pozdnyakov
 *
 * @brief   Entity Algorithm r-Score counter.
 *
 * @date    Created on October 2, 2018, 6:07 PM
 */

#include "ChartRscore.h"
#include "Logger.hxx"

#include <qmath.h>

using namespace std;
using namespace even;
//------------------------------------------------------------------------------
ChartRscore::ChartRscore(Config* config_, QWidget *parent, Qt::WindowFlags wFlags)
    : ChartEasy(parent) //QChart::ChartTypeCartesian, , wFlags
    , _rscore(config_)
{
    setMargin(10, 10, 10, 10);
    setHorizontalRange(-0.1, 1.1);
    setVerticalRange(-0.1, 1.5);
    addSeries(0, 2, Qt::red);
    addSeries(1, 2, Qt::green);
    setVerticalStep(0.1);
    setHorizontalStep(0.1);
    for(auto i = 0.0; i <= 100.0; ++i) {
        addSeriesPoint(0, i/100, 1 + qLn(i/20.0)/(i/20.0 + 1));
        addSeriesPoint(1, i/100, 1/3.0 - qLn(i/20.0)/(i/20.0 + 1));
    }
}

//------------------------------------------------------------------------------
ChartRscore::~ChartRscore()
{
}




