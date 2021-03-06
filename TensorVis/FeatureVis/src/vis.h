#ifndef _VIS_POINTCLOUD_H
#define _VIS_POINTCLOUD_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

#include "common_datatype.h"

using namespace std;



/*****************************************************************************************

Class Name		:	Processing	
Purpose			:	Implementation of Kreylo's paper
Created by		:	Beena
Created date		:	
Modification		:
Modified Function	:

*****************************************************************************************/

class vis
	{


	
	public:
	vis() 
	{
            cloudSize_ =0;
	}
	
	~vis(){}

	bool fileread(std::string sFilePath);
	bool colorClCpCs();
	bool cloudDisplay();

	void drawColorMap(int type);
	void drawGlyph();
	void drawSingleGlyph(int idx);


	private:
                int cloudSize_;
                vector<featprop> featdata;
                //vector <float> curvVal;
	
	};
	
#endif
