#ifndef DATATYPE_COMMON_H
#define DATATYPE_COMMON_H

#include <teem/ten.h>
#include <stdio.h>

using namespace std;
/*****************************************************************************************
******************************************************************************************

Global Variables

******************************************************************************************
*****************************************************************************************/
typedef float	xyzType;
typedef int	idxType;
typedef unsigned short inten;



struct metaDatat
	{
	xyzType XYZI[4];
	xyzType lslllp[3];
	xyzType csclcp[3];
	idxType fetureType;
	};

struct featprop
        {
        xyzType XYZ[3];
        xyzType ct[3];
        xyzType modct[3];
        xyzType ndt[3];
        };


#endif
