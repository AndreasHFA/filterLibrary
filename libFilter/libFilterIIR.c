/*
 ============================================================================
 Name        : libFilter.c
 Author      : Franz Flasch
 Version     :
 Copyright   :
 Description : Filtering Library wich supports reading of automatically generated
 	 	 	   headerfiles e.g. from Matlab.
 ============================================================================
 */

#include "libFilter.h"
#include <stdio.h>
#include <stdlib.h>


void Filter_IIRDirForm2_GetCoeffFromMatlabForm(Filter_SOS_DirForm2_t *pFilter,
								   	   const double *NUM,
								   	   const double *DEN,
								   	   unsigned int sectionNr,
								   	   unsigned int lastSection)
{
	/* At first store the inputGain */
	pFilter->inputGain = NUM[(sectionNr*6)];

	/* Get the outPut Gain if it is the last SOS section to read */
	if(lastSection)
	{
		pFilter->outputGain = NUM[(sectionNr*6)+6];
	}
	else pFilter->outputGain = 1;

	/* Get the filter coefficients NUMERATOR */
	pFilter->b[0] = NUM[(sectionNr*6)+3];
	pFilter->b[1] = NUM[(sectionNr*6)+4];
	pFilter->b[2] = NUM[(sectionNr*6)+5];

	/* Get the filter coefficients DENUMINATOR */
	pFilter->a[0] = DEN[(sectionNr*6)+3];
	pFilter->a[1] = DEN[(sectionNr*6)+4];
	pFilter->a[2] = DEN[(sectionNr*6)+5];

	/* Now set the storages to zero */
	pFilter->w[0] = pFilter->w[1] = pFilter->w[2] = 0;
}

void Filter_IIRDirForm2_InitSections(Filter_SOS_DirForm2_t *pFilter,
						 const double *numerator,
						 const double *denominator,
						 unsigned int nrSections)
{
	unsigned int i = 0;

	for(i=0;i<(nrSections-1);i++)
	{
		Filter_IIRDirForm2_GetCoeffFromMatlabForm(&pFilter[i], &numerator[0], &denominator[0], i, 0);
	}
	Filter_IIRDirForm2_GetCoeffFromMatlabForm(&pFilter[i], &numerator[0], &denominator[0], i, 1);
}

double Filter_IIRDirForm2_ProcessOneSection(Filter_SOS_DirForm2_t *pFilter, double input)
{
	/* Shift values */
	pFilter->w[2] = pFilter->w[1];
	pFilter->w[1] = pFilter->w[0];

	pFilter->w[0] = (input*pFilter->inputGain)-(pFilter->a[1]*pFilter->w[1]) - (pFilter->a[2]*pFilter->w[2]);
	return pFilter->outputGain*((pFilter->b[0]*pFilter->w[0]) + (pFilter->b[1]*pFilter->w[1]) + (pFilter->b[2]*pFilter->w[2]));
}

double Filter_IIRDirForm2_ProcessCombinedSections(Filter_SOS_DirForm2_t *pFilter, double input, unsigned int nrSections)
{
	double tmpValue = input;
	unsigned int i = 0;

	tmpValue = Filter_IIRDirForm2_ProcessOneSection(&pFilter[0], tmpValue);
	for(i=1;i<(nrSections);i++)
	{
		tmpValue = Filter_IIRDirForm2_ProcessOneSection(&pFilter[i], tmpValue);
	}

	return tmpValue;
}

void Filter_IIRDirForm2_Print(Filter_SOS_DirForm2_t *pFilter)
{
	/* Test print */
	printf("Numerator:\n");
	printf("b0: 	%f\n", pFilter->b[0]);
	printf("b1: 	%f\n", pFilter->b[1]);
	printf("b2: 	%f\n", pFilter->b[2]);

	printf("\nDenuminator:\n");
	printf("a0: 	%f\n", pFilter->a[0]);
	printf("a1: 	%f\n", pFilter->a[1]);
	printf("a2: 	%f\n", pFilter->a[2]);

	printf("\nGains:\n");
	printf("input: 	%f\n", pFilter->inputGain);
	printf("output: %f\n", pFilter->outputGain);

	printf("\nStorages:\n");
	printf("w0: 	%f\n", pFilter->w[0]);
	printf("w1: 	%f\n", pFilter->w[1]);
	printf("w2: 	%f\n", pFilter->w[2]);
}

