/*
 * libFilterFIR.c
 *
 *  Created on: Dec 10, 2013
 *      Author: fflasch
 */

#include "libFilter.h"
#include <stdio.h>
#include <stdlib.h>

void Filter_FIRDirForm_test(void)
{
   printf("Test\n");
}


double Filter_FIRDirForm_ProcessFilter(const double *pCoeffs,
								   	   unsigned int nrCoeffs,
								   	   double *storages,
								   	   double input)
{
	int i = 0;
	double outPut = 0;

	storages[0] = input;

	for(i=(nrCoeffs-1);i>=0;i--)
	{
	    outPut += storages[i]*pCoeffs[i];
	    storages[i] = storages[i-1];
	}

	return outPut;
}

