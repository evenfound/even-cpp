/**
 * @file    Controls.h
 * @author  E. Pozdnyakov
 *
 * @brief   Entity Controls combined all control widgets for change parameters on
 *          main window app
 *
 * @date    Created on October 2, 2018, 7:49 PM
 */

#pragma once

#include <QWidget>
#include <QVBoxLayout>

/***************************************************************************//**
 * @brief   Entity Controls combined all control widgets for change parameters on
 *          main window app.
 * @details Distribute for layout and control Value changes widget
 *******************************************************************************/

class Controls: public QWidget {

        Q_OBJECT

    public:
        Controls();

        /** @brief  Add control object, derived from QWidget class */
        void addControl(QWidget* control_);

    private:
        QVBoxLayout *_layout;
};
