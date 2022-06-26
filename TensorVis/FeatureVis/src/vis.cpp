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
        FILE *fp = fopen(sFilePath.c_str(), "r");

  	if(fp == NULL) 
	{
   		printf("Invalid File path. Please select correct file\n");
   		return false;
  	}

        char buffer[1000];
        error = fgets(buffer, 30, fp);
        sscanf(buffer,"%d ", &cloudSize_);

        featdata.resize(cloudSize_);

            for(int i = 0; i < cloudSize_; i ++)
           {
                error =  fgets(buffer, 800, fp);
                sscanf(buffer,"%f %f %f %d %d %d %d %d %d %d %d %d",
                       &featdata[i].XYZ[0], &featdata[i].XYZ[1], &featdata[i].XYZ[2],
                  &featdata[i].ct[0], &featdata[i].ct[1], &featdata[i].ct[2],
                   &featdata[i].modct[0], &featdata[i].modct[1], &featdata[i].modct[2], &featdata[i].ndt[0], &featdata[i].ndt[1], &featdata[i].ndt[2]);
           }


 return true;
  
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
  if(cloudSize_ == 0 )
  {
    cout<<"Point cloud size is zero"<<endl;
    return false;
  }

  glPointSize(3.0);

  Color currentcolor ;

  int l_c = 0, l_ct = 0, l_ndt = 0;

  glBegin(GL_POINTS);

    for (size_t i = 0 ; i < cloudSize_ ; i++)
    {
        if(featdata[i].ct[1] == 1 && featdata[i].ndt[1] == 1)
        {
            currentcolor.set_red(1.0);
                        currentcolor.set_green(0.55);
                        currentcolor.set_blue(0.0);
            l_c++;
        }
        else if(featdata[i].ct[1] == 1 && featdata[i].ndt[1] == 0)
        {
            currentcolor.set_red(1.0);
            currentcolor.set_green(1.0);
            currentcolor.set_blue(0.0);
            l_ct++;
        }
        else if(featdata[i].ct[1] == 0 && featdata[i].ndt[1] == 1)
        {
            currentcolor.set_red(0.65);
            currentcolor.set_green(0.17);
            currentcolor.set_blue(0.17);
            l_ndt++;
        }
        else
            {
            currentcolor.set_red(0.6);
            currentcolor.set_green(0.6);
            currentcolor.set_blue(0.6);
            }

      glColor3d(currentcolor.red(), currentcolor.green(), currentcolor.blue()) ;
      glVertex3d(featdata[i].XYZ[0],featdata[i].XYZ[1], featdata[i].XYZ[2]);
    }

    cout<<"************************************"<<endl;


    cout<<"common line points ct and ndt  "<<l_c<<endl;
    cout<<"not line points ct and ndt  "<<l_ct<<endl;
     cout<<"not line points ct and ndt  "<<l_ndt<<endl;
     cout<<"************************************"<<endl;

  glEnd(); 

   return true;

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
    if(cloudSize_ == 0 )
    {
      cout<<"Point cloud size is zero"<<endl;
      return false;
    }

    glPointSize(3.0);

    Color currentcolor ;

    int l_c = 0, l_ct = 0, l_ndt = 0;

    glBegin(GL_POINTS);

      for (size_t i = 0 ; i < cloudSize_ ; i++)
      {
          if(featdata[i].modct[1] == 1 && featdata[i].ndt[1] == 1)
          {
              currentcolor.set_red(1.0);
                          currentcolor.set_green(0.55);
                          currentcolor.set_blue(0.0);
              l_c++;
          }
          else if(featdata[i].modct[1] == 1 && featdata[i].ndt[1] == 0)
          {
              currentcolor.set_red(1.0);
              currentcolor.set_green(1.0);
              currentcolor.set_blue(0.0);
              l_ct++;
          }
          else if(featdata[i].modct[1] == 0 && featdata[i].ndt[1] == 1)
          {
              currentcolor.set_red(0.65);
              currentcolor.set_green(0.17);
              currentcolor.set_blue(0.17);
              //currentcolor.set_red(0.65);
              //currentcolor.set_green(0.17);
              //currentcolor.set_blue(0.17);
              l_ndt++;
          }
          else
              {
                  currentcolor.set_red(0.6);
                  currentcolor.set_green(0.6);
                  currentcolor.set_blue(0.6);
              }

        glColor3d(currentcolor.red(), currentcolor.green(), currentcolor.blue()) ;
        glVertex3d(featdata[i].XYZ[0],featdata[i].XYZ[1], featdata[i].XYZ[2]);
      }

      cout<<"************************************"<<endl;


      cout<<"common line points modct and ndt  "<<l_c<<endl;
      cout<<"not line points modct and ndt  "<<l_ct<<endl;
       cout<<"not line points modct and ndt  "<<l_ndt<<endl;
       cout<<"************************************"<<endl;

    glEnd();

    return true;
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
  if(cloudSize_  == 0)
    return;

  else
  {
    // cout<<"type "<<type<<endl;

     if(type == 0)
     {
        //cout<<"point cloud"<<endl;
       // cloudDisplay();
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
