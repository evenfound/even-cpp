/**
 * @file    main.сpp
 * @author  E. Pozdnyakov
 *
 * @brief   main file of project.
 *
 * @date    Created on October 2, 2018, 7:49 PM
 */

#include "ChartRscore.h"
#include "Controls.h"
#include "ValueSlider.hxx"
#include "Rscore.hxx"

#include <QtWidgets/QApplication>
#include <QHBoxLayout>

using namespace even;

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controls window;

    Rscore rscore({
                      {0.5f, "contribution", "Относительный вклад мощности", {0.0f, 1.0f, 10.0f}},
                      {0.1f, "ping", "Относительная скорость работы сети", {0.5f, 1.0f, 20.0f}},
                      {0.2f, "activity", "Активность", {0.2f, 1.0f, 20.0f}},
                      {0.2f, "foundity", "Относительная капитализация", {0.01f, 1.0f, 20.0f}},
                });

    ChartRscore *chart = new ChartRscore(&rscore);

    //chart->setTitle("r-Score sample counter..");
    //chart->legend()->hide();
    //chart->setAnimationOptions(QChart::AllAnimations);

    //QGraphicsView chartView(chart);
    //chartView.setRenderHint(QPainter::Antialiasing);

    window.addControl(chart);
    for(auto &c: rscore) {
        window.addControl(new ValueSlider(&c));
    }

    window.resize(400, 600);
    window.show();

    return a.exec();
}

