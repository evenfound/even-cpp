/**
 * @file    ChartEasy.cxx
 * @author  E. Pozdnyakov
 *
 * @brief   Entity of ChartEasy class methods.
 *
 * @date    Created on October 5, 2018, 01:26 PM
 */

#include "ChartEasy.hxx"
#include "Scene.hxx"
#include "Logger.hxx"

#include <QWidget>
#include <QtMath>

using namespace even;

//------------------------------------------------------------------------------
ChartEasy::ChartEasy(QWidget* parent_)
    : QWidget(parent_)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//------------------------------------------------------------------------------
void ChartEasy::setHorizontalRange(qreal min_, qreal max_) {
    _axis[0].min = min_;
    _axis[0].max = max_;
}

//------------------------------------------------------------------------------
void ChartEasy::setVerticalRange(qreal min_, qreal max_) {
    _axis[1].min = min_;
    _axis[1].max = max_;
}

//------------------------------------------------------------------------------
void ChartEasy::addSeries(int id_, qreal thin_, QColor color_, QString label_) {
    _series.insert(id_, { thin_, color_, label_});
}

//------------------------------------------------------------------------------
void ChartEasy::removeSeries(int id_) {
    _series.remove(id_);
}

//------------------------------------------------------------------------------
void ChartEasy::addSeriesPoint(int id_, qreal x_, qreal y_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->data.insert(x_, y_);
        INFO(20) << QString("add to series %1 x = %2, y = %3")
                    .arg(id_)
                    .arg(x_)
                    .arg(y_);
    }
}

//------------------------------------------------------------------------------
void ChartEasy::setSeriesColor(int id_, QColor color_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->color = color_;
    }
}

//------------------------------------------------------------------------------
void ChartEasy::setSeriesThin(int id_, int thin_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->thin = thin_;
    }
}

//------------------------------------------------------------------------------
void ChartEasy::buildScene(Scene *scene_)
{
    _drawAxis(scene_);
    for(auto &a: _series) {
        _drawSeries(a, scene_);
    }
//    scene_->restore();

}

//------------------------------------------------------------------------------
void ChartEasy::_drawAxis(Scene* scene_) const {

    // Clipping draw area
    scene_->setClipRegion(QRegion(
                              QRect(
                                  _axisMargin[3]
                                  , _axisMargin[0]
                                  , width() - _axisMargin[3] - _axisMargin[1]
                                  , height() - _axisMargin[2] - _axisMargin[0])));

    // Draw chart area
    scene_->drawRect({
                         _axisMargin[3]
                         , _axisMargin[0]
                         , width() - _axisMargin[3] - _axisMargin[1]
                         , height() - _axisMargin[2] - _axisMargin[0]
                     }
                     , QPen(_axisColor), QBrush(_backColor));

    // Paint between thin lines flags
    auto lowestX  = false;
    auto biggestX = false;
    auto lowestY  = false;
    auto biggestY = false;

    // Draw vertical lines
    qreal offset = 0;
    while(!lowestX || !biggestX ) {
        // Axis line opts
        auto thin = (offset == 0)? 0.8: 0.5;
        auto penStyle = (offset == 0)? Qt::SolidLine : Qt::DotLine;
        if(-offset > _axis[0].min * scene_->xFactor()) {
            scene_->drawLine(
                    -offset, _axis[1].min
                    , -offset, _axis[1].max
                    , QPen(_axisColor, thin, penStyle));
            scene_->drawText(
                    -offset, 0
                    , QString("%1").arg(-offset, 0, 'f', 1)
                    , {Qt::black});
        } else {
            lowestX = true;
        }
        if(offset < _axis[0].max * scene_->xFactor()) {
            scene_->drawLine(
                    offset, _axis[1].min
                    , offset, _axis[1].max
                    , QPen(_axisColor, thin, penStyle));
            scene_->drawText(
                    offset, 0
                    , QString("%1").arg(offset, 0, 'f', 1)
                    , {Qt::black});
        } else {
            biggestX = true;
        }
        offset += _axis[0].step;
    }

    // Draw horizontal lines
    offset = 0;
    while(!lowestY || !biggestY) {
        // Axis line opts
        auto thin = (offset == 0)? 0.8: 0.5;
        auto penStyle = (offset == 0)? Qt::SolidLine : Qt::DotLine;
        if(-offset > _axis[1].min * scene_->yFactor()) {
            scene_->drawLine(
                    _axis[0].min, -offset
                    , _axis[0].max, -offset
                    , QPen(_axisColor, thin, penStyle));
        } else {
            lowestY = true;
        }
        if(offset < _axis[1].max * scene_->yFactor()) {
            scene_->drawLine(
                    _axis[0].min, offset
                    , _axis[0].max, offset
                    , QPen(_axisColor, thin, penStyle));
        } else {
            biggestY = true;
        }
        offset += _axis[1].step;
    }

}

//------------------------------------------------------------------------------
void ChartEasy::paintEvent(QPaintEvent*)
{
    Scene scene(this ,
                _axisMargin
                , _axis[0].min, _axis[0].max
                , _axis[1].min, _axis[1].max);

    buildScene(&scene);

}


//------------------------------------------------------------------------------
void ChartEasy::_drawSeries(const Series& _series, Scene* scene_)
{
    if(_series.data.isEmpty())
        return;

    for(auto a = _series.data.begin(); a != _series.data.end() - 1; ++a) {
        scene_->drawLine(
                    a.key(), a.value()
                    , (a + 1).key(), (a + 1).value()
                    , {
                        {_series.color}
                        , _series.thin
                    });
//        INFO(10) << QString("Line %1 %2 %3 %4").arg(a.key()).arg(a.value()).arg((a + 1).key()).arg((a + 1).value());
    }
}

