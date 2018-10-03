/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdio>
#include "Catch.h"
#include "Logger.hxx" 

#ifdef UNIX
using namespace std;

/** @brief Global pointer to close callback function
 * using from main loop
 */

CloseFunc startClose = NULL;

/**
 * @brief Signal catch initializer
 * @param ignoreSignals
 */
void ignoreUnixSignals(std::initializer_list<int> ignoreSignals) {
    // all these signals will be ignored.
    for (int sig : ignoreSignals)
        signal(sig, SIG_IGN);
}

/**
 * @brief System signal catcher
 * @param quitSignals
 */
void catchUnixSignals(std::initializer_list<int> quitSignals) {
    auto handler = [](int sig) -> void {
        // blocking and not aysnc-signal-safe func are valid
        INFO(15) << "Quit the application by signal(" << sig << ").";
        /**
         * Close globals...!!
         */
        if (startClose)
            startClose();
    };

    sigset_t blocking_mask;
    sigemptyset(&blocking_mask);
    for (auto sig : quitSignals)
        sigaddset(&blocking_mask, sig);

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_mask = blocking_mask;
    sa.sa_flags = 0;

    for (auto sig : quitSignals)
        sigaction(sig, &sa, nullptr);
}

#endif
