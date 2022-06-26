#include "vis.h"
#include <GL/gl.h>
#include <algorithm>
#include "Color.h"


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
	FILE *fp = fopen(sFilePath.c_str(), "r");

  	if(fp == NULL) 
	{
   		printf("Invalid File path. Please select correct file\n");
   		return false;
  	}

    int _scale;
    float _rmin, _rmax, _epsillon;
  	char buffer[1000];
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

    cout<<"cloud size "<<cloudSize_<<endl;
    //cout<<"DataField size "<<totDataField_<<endl;
    //cout<<"sigma "<<sigma_<<endl;
    cout<<"radius "<<_epsillon<<endl;


    for(int i = 0; i < cloudSize_; i ++)
   		{
    		error =  fgets(buffer, 800, fp);
    	sscanf(buffer,"%f %f %f %f %f %f %f %f %f %f %d", &cloud_[i].XYZI[0],
            &cloud_[i].XYZI[1], &cloud_[i].XYZI[2], &cloud_[i].XYZI[3], 
          &cloud_[i].lslllp[0], &cloud_[i].lslllp[1], &cloud_[i].lslllp[2], 
           &cloud_[i].csclcp[0], &cloud_[i].csclcp[1], &cloud_[i].csclcp[2], &cloud_[i].fetureType);
   		}

  
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
