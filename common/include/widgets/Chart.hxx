/**
 * @file    ValueSlider.h
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 5, 2018, 12:34 PM
 */

#pragma once

#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QVector>
#include <QHash>
#include <QMap>
#include <QPainter>

/***************************************************************************//**
 * @brief   Entity of the window contained graphics drawing axis and any labels
 *          for drawing 2D data queues.
 * @details Distribute for any graphics showing algorithms
 *******************************************************************************/

namespace even {

class Chart : public QGraphicsView {

        Q_OBJECT

    public:

        /** @brief  Any Chart internal entities properties enam */
        enum Property{
            Vertical,   ///< @brief Axe vertical direction
            Horizontal  ///< @brief Axe horizontal direction
        };

        /** @brief  Sub Entity describes axe of chart */
        struct Axe {
                qreal       min     = 0.0f;         ///< @brief Max value of coordinate axe
                qreal       max     = 100.0f;       ///< @brief Min value of coordinate axe
                qreal       step    = 10.0f;        ///< @brief Step of marker on axe
                bool        visible = false;        ///< @brief Flag axe visibility
                Property    prop    = Horizontal;   ///< @brief By default axe is Horizontal
        };

        /** @brief  Entity of Chart line */
        struct Series
        {
                int                 thin    = 1;        ///< @brief Thin of series line
                QColor              color   = Qt::red;  ///< @brief Color of series line
                QString             label   = "";       ///< @brief Label of series line
                QGraphicsItemGroup* group   = nullptr;  ///< @brief Pointer to GraphicsView group
                QMap<qreal, qreal>  data;               ///< @brief Array of series data
        };

        explicit Chart(QWidget* parent = nullptr);

        /** @brief  Set horizonatal axe range */
        void setHorizontalRange(qreal min_, qreal max_);

        /** @brief  Set vertical axe range */
        void setVerticalRange(qreal min_, qreal max_);

        /** @brief  Set axis color */
        inline void setAxisColor(QColor color_) {
            _axisColor = color_;
        }

        /** @brief  Set axis line thin */
        inline void setAxisThin(int thin_) {
            _axisThin = thin_;
        }

        /** @brief  Set axis legend font size */
        inline void setAxisFontSize(int pt_) {
            _axisFsize = pt_;
        }

        /** @brief  Set margin from window border */
        void setMargin(int top_, int right_, int bottom_, int left_) {
            _axisMargin[0] = top_;
            _axisMargin[1] = right_;
            _axisMargin[2] = bottom_;
            _axisMargin[3] = left_;
        }

        /** @brief  Add series data container */
        void addSeries(int id_, int thin_ = 1, QColor color_= Qt::red, QString label_ = "");

        /** @brief  Remove series data container */
        void removeSeries(int id_);

        /** @brief Add data point to series tail */
        void addSeriesPoint(int id_, qreal x_, qreal y_);

        /** @brief Set serias line color */
        void setSeriesColor(int id_, QColor color_);

        /** @brief Set series line thin */
        void setSeriesThin(int id_, int thin_);

        /** @brief Build scene with all series and axis drawing */
        void buildScene();

    private:
        /** @brief Draw series */
        void _drawSeries(const Series& _series);

        /** @brief Remove all items from group */
        void _deleteItemsFromGroup(QGraphicsItemGroup *group_);

        /** @brief  Overload resizeEvenet from app event loop */
        void resizeEvent(QResizeEvent *event) override;

        /** @brief Set scale and init scale factors by axis */
        void setScale();

        /** @brief Draw axis */
        void drawAxis();

        QGraphicsScene      _scene;                         ///< @brief Scene for drawing
        Axe                 _axis[2];                       ///< @brief Array of axis objects
        QColor              _axisColor      = Qt::gray;     ///< @brief Axis line color
        QColor              _backColor      = Qt::white;    ///< @brief Background color
        int                 _axisThin       = 1;            ///< @brief Axis line thin
        int                 _axisFsize      = 10;           ///< @brief Axis label font size
        qreal               _axisMargin[4]  = {20,20,20,20};///< @brief Margin offset values
        QHash<int, Series>  _series;                        ///< @brief Array of Series
        qreal               _scale_x        = 1.0;          ///< @brief Scale factor by X
        qreal               _scale_y        = 1.0;          ///< @brief Scale factor by Y
        QGraphicsItemGroup  _axisGroup;
};

};
