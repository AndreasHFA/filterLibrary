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
#include "stdint.h"
#include <sys/time.h>

#define FILTER_SECTIONS ((MWSPT_NSEC-1)/2)

char *buffer;


double readWavFile(char *filePath, uint32_t index)
{
    long lsize;
    int result;
    double retVal=0;

    int16_t *pWav=NULL;

    FILE *wavFile;

    wavFile = fopen("/home/franz/Desktop/test.wav", "rb");

    if(wavFile == NULL)
    {
        printf("Error\n");
        return 1;
    }

    fseek(wavFile, 0 , SEEK_END);
    lsize = ftell(wavFile);
    rewind(wavFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lsize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lsize,wavFile);
    if (result != lsize) {fputs ("Reading error",stderr); exit (3);}

    pWav=(int16_t *)&buffer[0];

    if(index < lsize)
    {
        retVal=(double)pWav[index];
    }

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose (wavFile);
    free (buffer);
    return retVal;
}



int main(void)
{
   struct timeval start, end;
   long utime, seconds, useconds;

	int i = 0;
	double FIRstorages[BL];

	Filter_SOS_DirForm2_t myFilter[FILTER_SECTIONS];

	Filter_IIRDirForm2_InitSections(&myFilter[0], &NUM[0][0], &DEN[0][0], FILTER_SECTIONS);

//	for(i=0;i<7;i++)
//	{
//		printf("FilterNr: %d", i);
//		Filter_PrintSOS(&myFilter[i]);
//	}

//	for(i=0;i<100;i++)
//	{
//		printf("%f\n", Filter_IIRDirForm2_ProcessCombinedSections(&myFilter[0], 1, FILTER_SECTIONS));
//	}
//
//	Filter_FIRDirForm_test();

   memset(&FIRstorages, 0, sizeof(double)*BL);
   printf("%f\n", Filter_FIRDirForm_ProcessFilter(&B[0], BL, &FIRstorages[0], 1));
    for(i=0;i<100;i++)
    {
        printf("%f\n", Filter_FIRDirForm_ProcessFilter(&B[0], BL, &FIRstorages[0], 0));
    }

   memset(&FIRstorages, 0, sizeof(double)*BL);
   printf("\n\n%f\n", Filter_FIRDirForm_ProcessFilterFast(&B[0], BL, &FIRstorages[0], 1));
   for(i=0;i<100;i++)
   {
     printf("%f\n", Filter_FIRDirForm_ProcessFilterFast(&B[0], BL, &FIRstorages[0], 0));
   }

#define MEASUREROUNDS 100000

   memset(&FIRstorages, 0, sizeof(double)*BL);
   gettimeofday(&start, NULL);
	Filter_FIRDirForm_ProcessFilter(&B[0], BL, &FIRstorages[0], 1);
   for(i=0;i<MEASUREROUNDS;i++)
   {
     Filter_FIRDirForm_ProcessFilter(&B[0], BL, &FIRstorages[0], 0);
   }
   gettimeofday(&end, NULL);

   seconds  = end.tv_sec  - start.tv_sec;
   useconds = end.tv_usec - start.tv_usec;
   utime = ((seconds) * 1000000 + useconds);
   printf("Elapsed time: %ld microseconds\n", utime);

   memset(&FIRstorages, 0, sizeof(double)*BL);
   gettimeofday(&start, NULL);
   Filter_FIRDirForm_ProcessFilterFast(&B[0], BL, &FIRstorages[0], 1);
   for(i=0;i<MEASUREROUNDS;i++)
   {
     Filter_FIRDirForm_ProcessFilterFast(&B[0], BL, &FIRstorages[0], 0);
   }
   gettimeofday(&end, NULL);

   seconds  = end.tv_sec  - start.tv_sec;
   useconds = end.tv_usec - start.tv_usec;
   utime = ((seconds) * 1000000 + useconds);
   printf("Elapsed time: %ld microseconds\n", utime);



//    for(i=0;i<500;i++)
//    {
//        printf("%14f %14f %6d\n", readWavFile("d", i+100), Filter_FIRDirForm_ProcessFilter(&B, BL, &FIRstorages, readWavFile("d", i+100)), i);
//    }

	return EXIT_SUCCESS;
}
