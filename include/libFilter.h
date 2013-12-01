#ifndef libFilter_H
#define libFilter_H

#include "stdio.h"

typedef struct Filter_SOS_DirForm2_s
{
	/* SOS relevant */
	double b[3];	/* numerator coefficients */
	double a[3];	/* denuminator coefficients */
	double inputGain;
	double outputGain;
	double w[3];	/* storages */

}Filter_SOS_DirForm2_t;

void Filter_InitGetCoeffFromMatlabForm(Filter_SOS_DirForm2_t *pFilter,
								   	   const double *NUM,
								   	   const double *DEN,
								   	   unsigned int sectionNr,
								   	   unsigned int lastSection);

void Filter_InitSections(Filter_SOS_DirForm2_t *pFilter,
						 const double *numerator,
						 const double *denominator,
						 unsigned int nrSections);

double Filter_ProcessOneSection(Filter_SOS_DirForm2_t *pFilter,
								double input);

double Filter_ProcessCombinedSections(Filter_SOS_DirForm2_t *pFilter,
									  double input,
									  unsigned int nrSections);

void Filter_PrintSOS(Filter_SOS_DirForm2_t *pFilter);



#endif
