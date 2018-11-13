/**
 * @file    ChartRscore.h
 * @author  E. Pozdnyakov
 *
 * @brief   Entity Algorithm r-Score counter.
 *
 * @date    Created on October 2, 2018, 6:07 PM
 */

#pragma once

#include "Config.hxx"
#include "ChartEasy.hxx"


/***************************************************************************//**
 * @brief   Entity Algorithm r-Score counter..
 * @details Distribute for count and display function line on drawing coordiantes
 *          place object entity.
 *******************************************************************************/
class ChartRscore: public even::ChartEasy {

        Q_OBJECT

    public:
        /**
         * @brief @brief  Constructor automatically creating parameters array
         * @param config_   - pointer to Config object
         * @param parent    - pointer to parent drawing surface
         * @param wFlags    - drawing flags
         */

        ChartRscore(even::Config* config_,
                    QWidget *parent = nullptr,
                    Qt::WindowFlags wFlags = 0);

        ~ChartRscore() final;

    public slots:

    private:
        even::Config*   _rscore     = nullptr;
};
