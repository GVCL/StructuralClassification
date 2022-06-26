#include "Display.h"
#include "Color.h"
#include <GL/gl.h>
#include <iostream>

/*****************************************************************************************

Function Name		:	PointClassificaton::probMeasure	
Purpose	of Function	:	
Calls			:	PointClassificaton::CurvatureEstimation
Input Params		:	
Output Params		:	T *curve, T *disc, T *spherical
Return			:	int
Remarks			:

*****************************************************************************************/

bool DisplayPoints::lasDisplay()
{
	if(_inCloud->points.size() <= 0)
		return false;

   	glBegin(GL_POINTS);
	
  	for(size_t i = 0; i <_inCloud->points.size(); i++)
		{ 
			double temp = _intensity[i];
  			glColor3d(temp, temp, temp) ;
      		glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
		}
  	glEnd();
	return true;
}
/*****************************************************************************************

Function Name		:	PointClassificaton::probMeasure	
Purpose	of Function	:	
Calls			:	PointClassificaton::CurvatureEstimation
Input Params		:	
Output Params		:	T *curve, T *disc, T *spherical
Return			:	int
Remarks			:

*****************************************************************************************/

bool DisplayPoints::plyDisplay()
{

	if(_inCloud->points.size() <= 0)
		return false;

	glBegin(GL_POINTS);

  	glColor3f(0.5f, 0.5f, 0.5f);

	for (size_t i = 0; i <_inCloud->points.size(); i++)
	{ 
      	glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
	}
  	glEnd();

	return true;
}

/*****************************************************************************************

Function Name		:	PointClassificaton::probMeasure	
Purpose	of Function	:	
Calls			:	PointClassificaton::CurvatureEstimation
Input Params		:	
Output Params		:	T *curve, T *disc, T *spherical
Return			:	int
Remarks			:

*****************************************************************************************/
bool DisplayPoints::renderStructFDs(int pointMode)
{
	if(_inCloud->points.size() <= 0 || _probval.size()<=0)
		return false;

        if(pointMode == 1)
	{
		idxPtCloudFeat();   ////reduced point cloud with feature value
	}
        else if(pointMode == 2)
	{
		renderCurvature();
	}
        else if(pointMode == 3)
	{
		csclcpDisplay();
        }
        else if(pointMode == 4)
        {
            drawLineFatures();

        }
	
	
	return true;
}
/*****************************************************************************************

Function Name		:	PointClassificaton::probMeasure	
Purpose	of Function	:	
Calls			:	PointClassificaton::CurvatureEstimation
Input Params		:	
Output Params		:	T *curve, T *disc, T *spherical
Return			:	int
Remarks			:

*****************************************************************************************/
void DisplayPoints::idxPtCloudFeat()
{

   	glBegin(GL_POINTS);
	
    for (size_t i = 0; i <_inCloud->points.size(); i++)
    {
        glColor3f(_probval[i].prob[1], _probval[i].prob[2], _probval[i].prob[0]);
      	glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
    }

  	glEnd();
	return;
}
/*****************************************************************************************

Function Name		:	PointClassificaton::probMeasure	
Purpose	of Function	:	
Calls			:	PointClassificaton::CurvatureEstimation
Input Params		:	
Output Params		:	T *curve, T *disc, T *spherical
Return			:	int
Remarks			:

*****************************************************************************************/
void DisplayPoints::renderCurvature()
{

	Color currentcolor ;
   	glBegin(GL_POINTS);
	
  	for(size_t i = 0; i <_inCloud->points.size(); i++)
	{ 
            currentcolor = currentcolor.findColor(_probval[i].featStrength[2], 0.0, 1.0) ;
            glColor3d(currentcolor.red(), currentcolor.green(), currentcolor.blue()) ;
            glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
	}

  	glEnd();
	return;
}
/*****************************************************************************************

Function Name		:	PointClassificaton::probMeasure	
Purpose	of Function	:	
Calls			:	PointClassificaton::CurvatureEstimation
Input Params		:	
Output Params		:	T *curve, T *disc, T *spherical
Return			:	int
Remarks			:

*****************************************************************************************/
void DisplayPoints::csclcpDisplay()
{
   	glBegin(GL_POINTS);
	
  	for (size_t i = 0; i <_inCloud->points.size(); i++)
	{ 	
            glColor3f(_probval[i].csclcp[1], _probval[i].csclcp[2], _probval[i].csclcp[0]);
	    glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
	}

  	glEnd();
	return;

}
/*****************************************************************************************

Function Name		:	FltkForm::drawSpectrum
Purpose	of Function	:	draw Spectrum
Author/date		:	Beena-
Modified by/date	:
Calls			:	Color::findColor, Color::red, Color::green, Color::blue
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
void DisplayPoints::drawLineFatures()
{
    glBegin(GL_POINTS);


    for (size_t i = 0; i <_inCloud->points.size(); i++)
    {
        if(_ftPtsProp[i] == 1)
        {
            glColor3f(0, 0, 1);
            glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
        }
        else if(_ftPtsProp[i] == 2)
        {
            glColor3f(1, 0, 0);
            glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
        }
        else  if(_ftPtsProp[i] == 3)
        {
            glColor3f(0, 1, 0);
            glVertex3f(_inCloud->points[i].x, _inCloud->points[i].y, _inCloud->points[i].z);
        }
    }

    glEnd();
    return;

}

/*****************************************************************************************

Function Name		:	FltkForm::drawSpectrum	
Purpose	of Function	:	draw Spectrum
Author/date		:	Beena-
Modified by/date	:
Calls			:	Color::findColor, Color::red, Color::green, Color::blue	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/

void DisplayPoints::drawSpectrum(void)
{
  	Color currentcolor ;
  //	double vmin, vmax, v;

  	glBegin(GL_QUAD_STRIP) ;

  	for (int i = -3 ; i <= 4 ; i++) 
	{
  		double k = i + 3;
  		currentcolor = currentcolor.findColor(k/7.0, 0.0, 1.0) ;
  		glColor3d(currentcolor.red(), currentcolor.green(), currentcolor.blue()) ;
  		glVertex3d(1.70, (double)i/4.0, 0.0) ;
  		glVertex3d(1.80, (double)i/4.0, 0.0) ;
  	}

	glEnd() ;

}

