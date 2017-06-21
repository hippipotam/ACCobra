/*
 * log.h
 *
 *  Created on: Jun 9, 2017
 *      Author: rik
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>

#define INFO_LOG() std::cout << "[ " << __FUNCTION__ << " ] [ INFO ]: "
#define DEBUG_LOG() std::cout << "[ " << __FUNCTION__ << " ] [ DEBUG ]: "
#define ERROR_LOG() std::cerr << "[ " << __FUNCTION__ << " ] [ ERROR ]: "

//#define INFO_LOG(...) fprintf(cerr, __VA_ARGS__);
//cout << "[ INFO ]-[ " << __FUNCTION__ << " ]: " << __VA_ARGS__ << endl
#define ERR_LOG(x) 	std::cerr << "[ ERRO+ ]-[ " << __FUNCTION__ << " ]: " << x << std::endl




#endif /* LOG_H_ */
