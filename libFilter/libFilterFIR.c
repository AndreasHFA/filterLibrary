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

double Filter_FIRDirForm_ProcessFilterFast(const double *pCoeffs,
                                 unsigned int nrCoeffs,
                                 double *storages,
                                 double input)
{
   static int count = 0;
   int i = 0;
   int forwardCnt = 0;
   int backwardCnt = 0;
   double outPut = 0;

   if(count>=nrCoeffs)
   {
      count=0;
   }

   forwardCnt=(nrCoeffs-1)-count;
   backwardCnt=count;

   storages[count] = input;

   /* Calculate the first value by hand */
   outPut += storages[count]*pCoeffs[0];

   for(i=0;i<backwardCnt;i++)
   {
      outPut += storages[(count-1)-i]*pCoeffs[(nrCoeffs-2)-i];
   }

   for(i=1;i<forwardCnt;i++)
   {
      outPut += storages[count+i]*pCoeffs[i];
   }

   count++;
   return outPut;
}

