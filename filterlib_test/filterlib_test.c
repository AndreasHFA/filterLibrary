/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Franz Flasch
 Version     :
 Copyright   : Your copyright notice
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libFilter/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */

#include "libFilter.h"
#include "matLabFilter.h"
#include "stdlib.h"

#define FILTER_SECTIONS ((MWSPT_NSEC-1)/2)


int main(void)
{
	int i = 0;

	Filter_SOS_DirForm2_t myFilter[FILTER_SECTIONS];

	Filter_InitSections(&myFilter[0], &NUM[0][0], &DEN[0][0], FILTER_SECTIONS);

//	for(i=0;i<7;i++)
//	{
//		printf("FilterNr: %d", i);
//		Filter_PrintSOS(&myFilter[i]);
//	}

	for(i=0;i<100;i++)
	{
		printf("%f\n", Filter_ProcessCombinedSections(&myFilter[0], 1, FILTER_SECTIONS));
	}

	return EXIT_SUCCESS;
}
