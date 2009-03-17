/*
 * common.h
 *
 *  Created on: 2009-feb-09
 *      Author: Johannes Wirde
 *     Licence: LGPL v3
 */

#ifndef COMMON_H_
#define COMMON_H_

#define OK 0
#define ERROR 1
#define TRUE 1
#define FALSE 0

#define CHECKPTR(x) \
	if (x == NULL) {\
		printf("%s:%d pointer is NULL!\n", __FILE__, __LINE__); \
		exit(1); \
	}

#endif /* COMMON_H_ */
