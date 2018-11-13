/**
 * @file    Scene.h
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 17, 2018, 05:04 PM
 */

#pragma once

#include <QFont>
#include <QFontMetrics>
#include <QVector>
#include <QHash>
#include <QMap>
#include <QPainter>

namespace even {

/***************************************************************************//**
 * @brief   Entity of the QPainter derived object contained graphics drawing axis
 *          and any labels for drawing 2D data queues.
 * @details Distribute for any graphics showing algorithms
 *******************************************************************************/

class Scene : public QPainter {
    public:
        /**
         * @brief Scene Entity constructor
         * @param device_   - pointer to QPaintDevice where Series will be drawing
         * @param margin_   - margin of chart area
         * @param xmin_     - lowest horizontal axe parameter
         * @param xmax_     - higest horizontal axe parameter
         * @param ymin_     - lowest vertical axe parameter
         * @param ymax_     - higest vertical axe parameter
         */
        Scene(QPaintDevice* device_,
              qreal margin_[4], qreal xmin_, qreal xmax_, qreal ymin_, qreal ymax_);
        ~Scene() = default;

        /** @brief  Draw line on scene */
        void drawLine(qreal x1_, qreal y1_, qreal x2_, qreal y2_, const QPen& pen_);

        /** @brief  Draw rectangle */
        void drawRect(const QRectF &rect_, const QPen& pen_, const QBrush& brush_);

        /** @brief  Draw text on rect_ position */
        void drawText(qreal x_, qreal y_, QString text_, QPen pen_);

        /** @brief  Draw text on chart in QRect position */
        void drawRectOnChart(const QRectF& rect_, const QPen &pen_, const QBrush &brush_);

        /** @brief Take calculated scale factor by X */
        inline qreal xFactor() const { return _scale_x; }

        /** @brief Take calculated scale factor by Y */
        inline qreal yFactor() const { return _scale_y; }

    private:
        qreal           _margin[4];             ///< @brief Margin of chart area
        qreal           _xmin;                  ///< @brief Lowest horizontal axe parameter
        qreal           _xmax;                  ///< @brief Higest horizontal axe parameter
        qreal           _ymin;                  ///< @brief Lowest vertical axe parameter
        qreal           _ymax;                  ///< @brief Higest vertical axe parameter
        qreal           _scale_x        = 0.0;  ///< @brief Scale factor by X
        qreal           _scale_y        = 0.0;  ///< @brief Scale factor by Y
        qreal           _oldScale_x     = 0.0;  ///< @brief Previous value of scale by X
        qreal           _fontStretch    = 100.0;
        QFont           _font;                  ///< @brief Font for drawing
        QFontMetrics    _fontMetrics;           ///< @brief Font metrics
};

};
