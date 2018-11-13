/**
 * @file    Controls.сpp
 * @author  E. Pozdnyakov
 *
 * @brief   Entity Controls combined all control widgets for change parameters on
 *          main window app
 *
 * @date    Created on October 2, 2018, 7:49 PM
 */

#include "Controls.h"

//------------------------------------------------------------------------------
Controls::Controls()
    :_layout(new QVBoxLayout)
{
    setLayout(_layout);
    /*
    layout->addWidget(controlsGroup);
    layout->addWidget(stackedWidget);
    setLayout(layout);

    minimumSpinBox->setValue(0);
    maximumSpinBox->setValue(20);
    valueSpinBox->setValue(5);

    setWindowTitle(tr("Sliders"));
    */
}

//------------------------------------------------------------------------------
void Controls::addControl(QWidget* control_) {
    _layout->addWidget(control_);
    _layout->update();
}


