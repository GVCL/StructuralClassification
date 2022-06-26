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


#endif