#ifndef HESSIAN_H
#define HESSIAN_H

#include <stdio.h>
#include <vector>
#include "OctreeSerial.h"

#include "data_type.h"


using namespace std;
using namespace Eigen;


class Hessian
{
public:
    Hessian(){}
    typedef Eigen::Matrix<double, 3, 1> ColumnVector;
    typedef Eigen::Matrix<double, 1 , 3> RowVector;
    typedef pcl::PointXYZ PointT;
    typedef pcl::octree::OctreeContainerPointIndices LeafContainerT;
    typedef pcl::octree::OctreeContainerEmpty BranchContainerT;

    void setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void setOctree(OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * octree);

    void setParams(float rmin, float rmax, float rmaxpt, float epsi, float scale);

    void prob_measure(vector <probfeatnode> *probval);

    void calculatePartialDerivative(float radius);

    void calculateSecondDerivative(float radius);

private:
    void getnormalizeTensor(size_t idx, float weight);

    bool setAccumzero();

    bool HessianMatrix(float radius);

    bool probMeasure(vector<probfeatnode>&probfeatVal, float radius);

    void writeGlyphVars(float radius);

    void computeSaliencyVals(glyphVars &glyphtemp, int i, float radius);

    void glyphAnalysis(glyphVars &glyphtemp);

    bool eigendecomposition(glyphVars &glyphtemp, size_t idx);

    void average_eigenvalues();

    float _rmin, _rmax, _rmaxpt, _epsi, _scale;

    float _sigma;

    pcl::PointCloud<pcl::PointXYZ>::Ptr _inCloud;

    OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * _octree;

    vector < tensorType	> _accum;

    vector<glyphVars> _glyphData;
    vector < tensorType	> averaged_tensors;

    vector <float> Ix;
    vector <float> Iy;
    vector <float> Ixx;
    vector <float> Iyy;
    vector <float> Ixy;
    vector <float> Iyx;

    double average_mu1;
    double average_mu2;
};


#endif // HESSIAN_H
