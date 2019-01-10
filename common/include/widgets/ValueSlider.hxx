/**
 * @file    ValueSlider.h
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 2, 2018, 7:49 PM
 */

#pragma once

#include "Value.hxx"

#include <QGroupBox>
#include <QSlider>
#include <QLabel>

namespace even {

/***************************************************************************//**
 * @brief   Entity of the group box element, contained slider and window box
 *          for display current value level.
 * @details Distribute for change object Value class
 *******************************************************************************/

class ValueSlider : public QGroupBox
{
        Q_OBJECT

    public:
        /**
         * @brief Slider for sliding change of value
         * @param value_    - same value parameter
         * @param parent    - parent window
         */
        ValueSlider(QObject* value_,
                    QWidget *parent = nullptr);

    signals:
        void valueChanged(int value);

    public slots:
        void setValue(int value);

    private:
        Value   *_value     = nullptr;
        QSlider *_slider    = nullptr;
        QLabel  *_minLabel  = nullptr;
        QLabel  *_maxLabel  = nullptr;
        QLabel  *_valueLabel= nullptr;
};
};
