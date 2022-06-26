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



struct featprop
        {
        xyzType XYZ[3];
        int ct[3];
        int modct[3];
        int ndt[3];
        };


#endif
