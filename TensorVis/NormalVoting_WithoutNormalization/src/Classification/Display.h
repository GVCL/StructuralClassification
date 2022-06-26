#ifndef DISPLAYPOINT_FILE_H
#define DISPLAYPOINT_FILE_H

#include <stdio.h>
#include <vector>
#include <string>
#include "data_type.h"
#include <pcl/io/pcd_io.h>
/*****************************************************************************************
******************************************************************************************

Global Variables 

******************************************************************************************
*****************************************************************************************/

using namespace std;

class DisplayPoints
{
public:
	typedef	std::vector<ftType> PtContainer;
	typedef	std::vector<ftType> InetensityContainer;
	typedef std::vector<probfeatnode> FeatValContainer;
	typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudType;


        DisplayPoints(CloudType *cloud, vector<float>*intensity, vector <probfeatnode> *probval, vector <unsigned int> *ftPtsProp)
           :_inCloud(*cloud),_intensity(*intensity), _probval(*probval), _ftPtsProp(*ftPtsProp)
	{}
	~DisplayPoints();
;

	void drawSpectrum(void);
	
	bool lasDisplay();
	
	bool plyDisplay();



	bool renderStructFDs(int pointMode);

private:
	CloudType &_inCloud;
	vector<float> &_intensity;
  	vector <probfeatnode> &_probval;
        vector <unsigned int> &_ftPtsProp;

        void renderCurvature();
	
	void idxPtCloudFeat();

	void csclcpDisplay();

        void drawLineFatures();

};


#endif
