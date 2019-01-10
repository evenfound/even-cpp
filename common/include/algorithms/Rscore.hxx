/**
 * @file    Rscore.hxx
 * @author  E. Pozdnyakov
 *
 * @brief   Entity for count r-Score value from input parameters
 *
 * @date    Created on October 4, 2018, 3:43 PM
 */

#pragma once

#include "Config.hxx"

/***************************************************************************//**
 * @brief   Entity for count r-Score value from input parameters.
 * @details Distribute for base protocol mechanics
 *******************************************************************************/

namespace even {

class Rscore : public even::Config {
public:
        Rscore(std::initializer_list<even::Value> config_);

};

};
