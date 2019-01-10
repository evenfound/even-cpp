/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Catch.h
 * Author: zipper
 *
 * Created on August 27, 2018, 7:18 PM
 */

#ifndef CATCH_H
#define CATCH_H

#ifdef UNIX

#include <initializer_list>
#include <signal.h>
#include <unistd.h>

/** @brief Typedef callback catch signal function */
typedef void (*CloseFunc)();

/** @brief Extern object of callback function.*/
extern CloseFunc startClose;

/**
 * @brief System signals catcher
 * @param quitSignals
 */
void catchUnixSignals(std::initializer_list<int> quitSignals);
#endif

#endif /* CATCH_H */

