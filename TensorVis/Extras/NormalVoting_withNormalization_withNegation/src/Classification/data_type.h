#ifndef DATATYPE_COMMON_H
#define DATATYPE_COMMON_H

#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <vector>

using namespace std;

typedef float ftType;
typedef int idxType;

const double MIN_X = -1.0 ;
const double MIN_Y = -1.0 ;
const double MIN_Z = -1.0 ;
const double MAX_X = 1.0 ;
const double MAX_Y = 1.0 ;
const double MAX_Z = 1.0 ;
const double DEL_X = MAX_X-MIN_X ;
const double DEL_Y = MAX_Y-MIN_Y ;
const double DEL_Z = MAX_Z-MIN_Z ;


struct SLasHeaderBlock 
{
  	unsigned char ucVerMaj;   //1 byte
  	unsigned char ucVerMin;  //1 byte
  	unsigned char ucFormatID;  //1 byte
  	unsigned short usnRecLength;  //2byte
  	unsigned int usnNumOfPoint;    //4 byte	
  	unsigned int usnNumOfPointReturn[5];    //20 byte	
  	unsigned int ulnOffset;   //4 byte
  	double dXScale;
  	double dYScale;
  	double dZScale;
  	double dXOffset;
  	double dYOffset;
  	double dZOffset;

  	double xmax;
  	double xmin;

  	double ymax;
  	double ymin;

  	double zmax;
  	double zmin;
};

struct probfeatnode
{
    ftType prob[3]; //prob 0 = spher, 1 = curve, 2 = disc
    ftType featStrength[3]; // 0 =spher, 1 = curve, 2 = disc
    ftType csclcp[3];
};

struct featProps
{
  int type; // 0 - line, 1 - surface, 2   - surface and line - transition points
  //critcal line  - 3
  //critical surface - 4 (bY default al line points are in critical surface points)
  //critical line and  critical surface - 5 - transition points 

  float n_ps; // point type density  - 4
  float n_ls; // line type density - 0 
  float n_surfs; //surface type density - 1 
  float n_pls; // line and  point density 0 and 4  
  float n_psusfs;  // surface and  surface density 0 and 4
};

struct CovarianceMatrix
{
  float3 data[3];
};



struct glyphVars
{
    float evals[3];
    float evecs[9];
    float uv[2];
    float abc[3];
    float csclcp[3];
};

struct tensorType
{
    float evec0[3];
    float evec1[3];
    float evec2[3];
};

#endif
