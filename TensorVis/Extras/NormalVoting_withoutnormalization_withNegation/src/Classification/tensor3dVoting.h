#ifndef _TENSOR_3D_VOTING_H
#define _TENSOR_3D_VOTING_H

#include <stdio.h>
#include <vector>
#include "OctreeSerial.h"

#include "data_type.h"


using namespace std;
using namespace Eigen;

class tensor3dvoting
{
public:
    typedef Eigen::Matrix<double, 3, 1> ColumnVector;
    typedef Eigen::Matrix<double, 1 , 3> RowVector;
    typedef pcl::PointXYZ PointT;
    typedef pcl::octree::OctreeContainerPointIndices LeafContainerT;
    typedef pcl::octree::OctreeContainerEmpty BranchContainerT;
    typedef vector< vector< size_t > > NeighborCont;
    typedef std::vector<idxType> IndxCont;
    typedef std::vector<pcl::PointXYZ> PtCont;

		
    tensor3dvoting(){}

    void setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void setOctree(OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * octree);

    void setParams(float rmin, float rmax, float rmaxpt, float epsi, float scale);

    void prob_measure(vector <probfeatnode> *probval);



private:
    bool r_gpusearch(NeighborCont &neighs, ftType radius, idxType rmaxpts);

    bool gpuVoteAccum(float radius);

    void getnormalizeTensor(size_t idx, float weight);

    bool setAccumzero();

    tensorType compute3DBallVote(ColumnVector V, float *weight);

    bool addBallVote(size_t idx, tensorType ballTensorVote, float lambdaN);

    bool makeVector(pcl::PointXYZ p_i, pcl::PointXYZ p_j, ColumnVector *V);

    bool voteAccum(float radius);

    bool probMeasure(vector<probfeatnode>&probfeatVal);

    void writeGlyphVars(float radius);

    void computeSaliencyVals(glyphVars &glyphtemp);

    void glyphAnalysis(glyphVars &glyphtemp);

    bool eigendecomposition(glyphVars &glyphtemp, size_t idx);

    float _rmin, _rmax, _rmaxpt, _epsi, _scale;

    float _sigma;

    pcl::PointCloud<pcl::PointXYZ>::Ptr _inCloud;

    OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * _octree;

    vector < tensorType	> _accum;

    vector<glyphVars> _glyphData;

    /*void calacC()
            {
            _c = (-16.0 * log(0.1) * (_sigma - 1.0))/(3.14 * 3.14);
            }

    void calacRadius()
            {
            _radius = (-16.0 * log(0.1) * (_sigma - 1.0))/(3.14 * 3.14);
            }*/





};

#endif
