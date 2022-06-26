#include "vis.h"
#include <GL/gl.h>
#include <algorithm>
#include "Color.h"
#include "fstream"

bool compareFeat(double i, double j) { return i<j; }
/*****************************************************************************************

Function Name		:	Processing::scale	
Purpose	of Function	:	
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/

bool vis::fileread(std::string sFilePath)
{
	bool error;
        FILE *fp = fopen("/home/iiit-b/QtSDK/TensorsVis/salienctVis/data/Vase/ct_vase_prob.txt", "r");

  	if(fp == NULL) 
	{
   		printf("Invalid File path. Please select correct file\n");
   		return false;
  	}

    int _scale;
    float _rmin, _rmax, _epsillon;

  	char buffer[1000];
         int l_p, s_p, p_p;


  	error = fgets(buffer, 30, fp);
    sscanf(buffer,"%d ", &cloudSize_);

    error = fgets(buffer, 30, fp);
  sscanf(buffer,"%f ", &_rmin);

    error = fgets(buffer, 30, fp);
    sscanf(buffer,"%f ", &_rmax);

    error = fgets(buffer, 30, fp);
    sscanf(buffer,"%d ", &_scale);

     error = fgets(buffer, 30, fp);
    sscanf(buffer,"%f ", &_epsillon);



    cloud_.resize(cloudSize_);

    featdata.resize(cloudSize_);

    for(int i = 0; i < cloudSize_; i ++)
   {
    		error =  fgets(buffer, 800, fp);
    	sscanf(buffer,"%f %f %f %f %f %f %f %f %f %f %d", &cloud_[i].XYZI[0],
            &cloud_[i].XYZI[1], &cloud_[i].XYZI[2], &cloud_[i].XYZI[3], 
          &cloud_[i].lslllp[0], &cloud_[i].lslllp[1], &cloud_[i].lslllp[2], 
           &cloud_[i].csclcp[0], &cloud_[i].csclcp[1], &cloud_[i].csclcp[2], &cloud_[i].fetureType);
   }



   for(size_t i =0; i < cloudSize_; i++)
   {
       featdata[i].XYZ[0] = cloud_[i].XYZI[0];
        featdata[i].XYZ[1] = cloud_[i].XYZI[1];
         featdata[i].XYZ[2] = cloud_[i].XYZI[2];
       l_p = 0;
       s_p = 0;
       p_p = 0;

        if(cloud_[i].csclcp[0] >= cloud_[i].csclcp[1] && cloud_[i].csclcp[0] >= cloud_[i].csclcp[2])
            p_p = 1;

        if(cloud_[i].csclcp[1] >= cloud_[i].csclcp[0] && cloud_[i].csclcp[1] >= cloud_[i].csclcp[2])
            l_p = 1;

        if(cloud_[i].csclcp[2] >= cloud_[i].csclcp[0] && cloud_[i].csclcp[2] >= cloud_[i].csclcp[1])
            s_p = 1;


        featdata[i].ct[0]  = p_p;
        featdata[i].ct[1]  = l_p;
        featdata[i].ct[2]  = s_p;


   }

   /////////////////////////////////////////
  //////////////////////////////////////


   FILE *fp1 = fopen("/home/iiit-b/QtSDK/TensorsVis/salienctVis/data/Vase/modct_vase_prob.txt", "r");
   if(fp1 == NULL)
   {
           printf("Invalid File path. Please select correct file\n");
           return false;
   }


   error = fgets(buffer, 30, fp1);
sscanf(buffer,"%d ", &cloudSize_);

error = fgets(buffer, 30, fp1);
sscanf(buffer,"%f ", &_rmin);

error = fgets(buffer, 30, fp1);
sscanf(buffer,"%f ", &_rmax);

error = fgets(buffer, 30, fp1);
sscanf(buffer,"%d ", &_scale);

error = fgets(buffer, 30, fp1);
sscanf(buffer,"%f ", &_epsillon);



cloud_.resize(cloudSize_);

featdata.resize(cloudSize_);

for(int i = 0; i < cloudSize_; i ++)
{
           error =  fgets(buffer, 800, fp1);
   sscanf(buffer,"%f %f %f %f %f %f %f %f %f %f %d", &cloud_[i].XYZI[0],
       &cloud_[i].XYZI[1], &cloud_[i].XYZI[2], &cloud_[i].XYZI[3],
     &cloud_[i].lslllp[0], &cloud_[i].lslllp[1], &cloud_[i].lslllp[2],
      &cloud_[i].csclcp[0], &cloud_[i].csclcp[1], &cloud_[i].csclcp[2], &cloud_[i].fetureType);
}



for(size_t i =0; i < cloudSize_; i++)
{
  featdata[i].XYZ[0] = cloud_[i].XYZI[0];
   featdata[i].XYZ[1] = cloud_[i].XYZI[1];
    featdata[i].XYZ[2] = cloud_[i].XYZI[2];
  l_p = 0;
  s_p = 0;
  p_p = 0;

   if(cloud_[i].csclcp[0] >= cloud_[i].csclcp[1] && cloud_[i].csclcp[0] >= cloud_[i].csclcp[2])
       p_p = 1;

   if(cloud_[i].csclcp[1] >= cloud_[i].csclcp[0] && cloud_[i].csclcp[1] >= cloud_[i].csclcp[2])
       l_p = 1;

   if(cloud_[i].csclcp[2] >= cloud_[i].csclcp[0] && cloud_[i].csclcp[2] >= cloud_[i].csclcp[1])
       s_p = 1;


   featdata[i].modct[0]  = p_p;
   featdata[i].modct[1]  = l_p;
   featdata[i].modct[2]  = s_p;


}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
FILE *fp2 = fopen("/home/iiit-b/QtSDK/TensorsVis/salienctVis/data/Vase/ndt_vase_prob.txt", "r");
if(fp2 == NULL)
{
        printf("Invalid File path. Please select correct file\n");
        return false;
}

error = fgets(buffer, 30, fp2);
sscanf(buffer,"%d ", &cloudSize_);

error = fgets(buffer, 30, fp2);
sscanf(buffer,"%f ", &_rmin);

error = fgets(buffer, 30, fp2);
sscanf(buffer,"%f ", &_rmax);

error = fgets(buffer, 30, fp2);
sscanf(buffer,"%d ", &_scale);

error = fgets(buffer, 30, fp2);
sscanf(buffer,"%f ", &_epsillon);



cloud_.resize(cloudSize_);

featdata.resize(cloudSize_);

for(int i = 0; i < cloudSize_; i ++)
{
        error =  fgets(buffer, 800, fp2);
sscanf(buffer,"%f %f %f %f %f %f %f %f %f %f %d", &cloud_[i].XYZI[0],
    &cloud_[i].XYZI[1], &cloud_[i].XYZI[2], &cloud_[i].XYZI[3],
  &cloud_[i].lslllp[0], &cloud_[i].lslllp[1], &cloud_[i].lslllp[2],
   &cloud_[i].csclcp[0], &cloud_[i].csclcp[1], &cloud_[i].csclcp[2], &cloud_[i].fetureType);
}



for(size_t i =0; i < cloudSize_; i++)
{
featdata[i].XYZ[0] = cloud_[i].XYZI[0];
featdata[i].XYZ[1] = cloud_[i].XYZI[1];
 featdata[i].XYZ[2] = cloud_[i].XYZI[2];
l_p = 0;
s_p = 0;
p_p = 0;

if(cloud_[i].csclcp[0] >= cloud_[i].csclcp[1] && cloud_[i].csclcp[0] >= cloud_[i].csclcp[2])
    p_p = 1;

if(cloud_[i].csclcp[1] >= cloud_[i].csclcp[0] && cloud_[i].csclcp[1] >= cloud_[i].csclcp[2])
    l_p = 1;

if(cloud_[i].csclcp[2] >= cloud_[i].csclcp[0] && cloud_[i].csclcp[2] >= cloud_[i].csclcp[1])
    s_p = 1;


featdata[i].ndt[0]  = p_p;
featdata[i].ndt[1]  = l_p;
featdata[i].ndt[2]  = s_p;


}


///////////////////////////////////
/////////////////////////////////
ofstream fout("featclass.txt");
    fout<<cloudSize_<<"\n";



   for(size_t i =0; i < cloudSize_; i++)
   {



       fout<<featdata[i].XYZ[0]<<" "<<featdata[i].XYZ[1]<<" "<<featdata[i].XYZ[2]<<" ";
       fout<<featdata[i].ct[0]<<" "<<featdata[i].ct[1]<<" "<<featdata[i].ct[2]<<" ";
       fout<<featdata[i].modct[0]<<" "<<featdata[i].modct[1]<<" "<<featdata[i].modct[2]<<" ";
       fout<< featdata[i].ndt[0]<<" "<<featdata[i].ndt[1]<<" "<<featdata[i].ndt[2]<<"\n";

   }
   fout.close();

  
}

/*****************************************************************************************

Function Name   : Processing::scale 
Purpose of Function : 
Input Params    :
Input/output Params :
Output Params   :
*****************************************************************************************/
bool vis::cloudDisplay()
{
  if(cloud_.size() == 0 ) 
  {
    cout<<"Point cloud size is zero"<<endl;
    return false;
  }

  glPointSize(2.0);

  Color currentcolor ;

  glBegin(GL_POINTS);

    for (size_t i = 0 ; i < cloud_.size() ; i++)
    {
      glColor3d(cloud_[i].lslllp[1], cloud_[i].lslllp[2], cloud_[i].lslllp[0]) ;
      glVertex3d(cloud_[i].XYZI[0], cloud_[i].XYZI[1], cloud_[i].XYZI[2]);     
    }

  glEnd(); 

}

/*****************************************************************************************

Function Name   : Processing::scale 
Purpose of Function : 
Input Params    :
Input/output Params :
Output Params   :
*****************************************************************************************/
bool vis::colorClCpCs()
{
  if(cloud_.size() == 0 ) 
  {
    cout<<"Point cloud size is zero"<<endl;
    return false;
  }
  glPointSize(2.0);
  Color currentcolor ;

  glBegin(GL_POINTS);

  for (size_t i = 0 ; i < cloud_.size() ; i++)
  {
 
    glColor3d(cloud_[i].csclcp[1], cloud_[i].csclcp[2], cloud_[i].csclcp[0]) ;
    glVertex3d(cloud_[i].XYZI[0], cloud_[i].XYZI[1], cloud_[i].XYZI[2]);     
}
  
  glEnd();  
}
/*****************************************************************************************

Function Name   : Processing::scale 
Purpose of Function : 
Input Params    :
Input/output Params :
Output Params   :
*****************************************************************************************/
void vis::drawSingleGlyph(int idx)
{

}
/*****************************************************************************************

Function Name   : Processing::scale 
Purpose of Function : 
Input Params    :
Input/output Params :
Output Params   :
*****************************************************************************************/
void vis::drawGlyph()
{
    if(cloud_.size() == 0 ) 
  {
    cout<<"Point cloud size is zero"<<endl;
    return;
  }

  glPointSize(2.0);

  Color currentcolor ;

  glBegin(GL_POINTS);

    for (size_t i = 0 ; i < cloud_.size() ; i++)
    {
      glColor3d(cloud_[i].XYZI[3], cloud_[i].XYZI[3], cloud_[i].XYZI[3]) ;
      glVertex3d(cloud_[i].XYZI[0], cloud_[i].XYZI[1], cloud_[i].XYZI[2]);     
    }

  glEnd(); 

}
/*****************************************************************************************

Function Name   : Processing::scale 
Purpose of Function : 
Input Params    :
Input/output Params :
Output Params   :
*****************************************************************************************/
void vis::drawColorMap(int type)
{
  //cout<<"_tempTensorAtt "<<_tempTensorAtt.size()<<endl;

  //cout<<"_tensorAtt "<<_tensoratt->size()<<endl;
  if(cloud_.size()  == 0)
    return;

  else
  {
    // cout<<"type "<<type<<endl;

     if(type == 0)
     {
        //cout<<"point cloud"<<endl;
        cloudDisplay();
     }
     else if(type == 1)
     {
        //cout << "ClCsCp color map" << endl; 
          colorClCpCs();
     }

   /* else if(type == 2)
     {
        //cout << "SaliencyVals color map" << endl; 
       // colorClCpCs();
        drawGlyph();
        //colorSaliencyVals();
        //drawCriticalGlyph();
     }*/
     else
        cout << "Wrong parameter for color map" << endl;

  }

   return;  
}
