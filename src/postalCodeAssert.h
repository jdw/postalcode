/*
 * postCodeAssert.h
 *
 *  Created on: 2009-feb-10
 *      Author: johwi
 */

#ifndef POSTCODEASSERT_H_
#define POSTCODEASSERT_H_

#include <stdlib.h>

#define ASSERTTRUE(x) \
	if (!(x)) { \
		printf("%s:%d '%s', returned FALSE!\n", __FILE__, __LINE__, #x); \
		exit(1); \
	}

#define ASSERTFALSE(x) \
	if ((x)) { \
		printf("%s:%d '%s', returned TRUE!\n", __FILE__, __LINE__, #x); \
		exit(1); \
	}

void runAssertionTests();


#endif /* POSTCODEASSERT_H_ */
