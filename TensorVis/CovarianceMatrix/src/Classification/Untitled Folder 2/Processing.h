#ifndef PROCESSING_FILE_H
#define PROCESSING_FILE_H

#include "tensor3dVoting.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <pcl/io/pcd_io.h>
#include "OctreeSerial.h"

#include "data_type.h"
#include "Display.h"

using namespace std;

/*****************************************************************************************

Class Name		:	Processing	
Purpose			:	Implementation of Kreylo's paper
Created by		:	Beena
Created date		:	
Modification		:
Modified Function	:

*****************************************************************************************/

class Processing 
{
  public:
    typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudType;
    typedef pcl::PointCloud<pcl::PointXYZ> cl;
    typedef pcl::PointXYZ PointT;
    typedef pcl::octree::OctreeContainerPointIndices LeafContainerT;
    typedef pcl::octree::OctreeContainerEmpty BranchContainerT;

    Processing() ;
    ~Processing();
    void setParams(float rmin, float rmax, float eps, float sigmin, float sigmax) ;
    void setFilePath(std::string filePath) ;
    bool fileRead();
    void classifyStructFeats();
    void computeEigenValues(float rmin, float rmax, float rmaxpt, float epsi, float scale);
    bool structFeatClassification();
    void clear();
    void reset();
    int getDataSize();
    void setDisplayMode(int displaymode, int pointmode);
    void display();
    void computeFDs();
    void buildOctree();
    void scale(vector<double>&x, vector<double>&y, vector<double>&z);
  
  private:
    
    string _filePath, _FileExtension, _fileNo;
    ftType _rmin, _rmax,  _rmaxpt,  _epsi,  _scale;

    float _sigmax, _sigmin,  _rcurve, _rsurface;
    int _displaymode, _pointmode;

    CloudType _inCloud;
    vector <float> _intensity;
    OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * _octree;

    vector <probfeatnode> _probval;
    vector <unsigned int> _ftPtsProp;

    tensor3dvoting *_ptclassifyObj;
    DisplayPoints *_displayObj;
};

#endif
