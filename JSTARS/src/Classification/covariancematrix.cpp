#include "covariancematrix.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Segment_3.h>

#include <pcl/common/common.h>
#include <pcl/common/eigen.h>
#include <pcl/common/centroid.h>
#include <teem/ten.h>
#include "eig3.h"

struct K : CGAL::Exact_predicates_inexact_constructions_kernel {};

typedef CGAL::Triangulation_euclidean_traits_xy_3<K>  Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;

typedef K::Point_3   Point;
typedef K::Triangle_3  Triangle_3;
typedef K::Vector_3  Vector_3;
typedef K::Segment_3  Segment_3;


void Barycentric(Point p, Point a, Point b, Point c, float &u, float &v, float &w);
int LineTriangleIntersection(Triangle_3 tri, Point p, Point q, Point& intersectionP);
static int fNdx = 0;
/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void CovarianceMatrix::setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    _inCloud = cloud;
}
/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void CovarianceMatrix::setOctree(OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * octree)
{
   _octree = octree;
}
/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/

void CovarianceMatrix::setParams(float rmin, float rmax, float rmaxpt, float epsi, float scale)
{
    _rmin = rmin;
    _rmax = rmax;
    _rmaxpt = rmaxpt;
    _epsi = epsi;
    _scale = scale;

    _sigma = 1.0;
}


/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool CovarianceMatrix::setAccumzero()
{
    if( _inCloud->points.size() == 0)
        return false;

    _accum.resize(_inCloud->points.size());
    averaged_tensors.resize(_inCloud->points.size());
    averaged_accum.resize(_inCloud->points.size());

    for(size_t i = 0; i < _inCloud->points.size(); i++)
    {
        for(int j =0; j < 3; j++)
        {
            _accum[i].evec0[j] = 0.0;
            _accum[i].evec1[j] = 0.0;
            _accum[i].evec2[j] = 0.0;

            averaged_tensors[i].evec0[j] = 0.0;
            averaged_tensors[i].evec1[j] = 0.0;
            averaged_tensors[i].evec2[j] = 0.0;

            averaged_accum[i].evec0[j] = 0.0;
            averaged_accum[i].evec1[j] = 0.0;
            averaged_accum[i].evec2[j] = 0.0;
        }
    }

    return true;
}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool CovarianceMatrix::voteAccum(float radius, vector<probfeatnode> &probfeatVal)
{
    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;
    pcl::PointXYZ searchPoint;
    Eigen::Matrix3f covariance_matrix;
    Eigen::Vector4f xyz_centroid;
    pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    temp_cloud->header = _inCloud->header;


    for(size_t i =0; i < _inCloud->points.size(); i++)
    {
        searchPoint = _inCloud->points[i];

//        probfeatVal[i].neighborhoodSize = 0;

        if(_octree->radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
        {
            temp_cloud->points.resize (pointIdxRadiusSearch.size());

//            probfeatVal[i].neighborhoodSize = pointIdxRadiusSearch.size ();

            for(size_t m = 0; m < pointRadiusSquaredDistance.size(); m++)
            {
                    temp_cloud->points[m] = _inCloud->points[pointIdxRadiusSearch[m]];
            }

            pcl::compute3DCentroid(*temp_cloud, xyz_centroid);
           // xyz_centroid[0] = searchPoint.x;
            //xyz_centroid[1] = searchPoint.y;
           // xyz_centroid[2] = searchPoint.z;

            pcl::computeCovarianceMatrix(*temp_cloud, xyz_centroid, covariance_matrix);

            _accum[i].evec0[0] = covariance_matrix(0, 0);
            _accum[i].evec0[1] = covariance_matrix(0, 1);
            _accum[i].evec0[2] = covariance_matrix(0, 2);

            _accum[i].evec1[0] = covariance_matrix(1, 0);
            _accum[i].evec1[1] = covariance_matrix(1, 1);
            _accum[i].evec1[2] = covariance_matrix(1, 2);

            _accum[i].evec2[0] = covariance_matrix(2, 0);
            _accum[i].evec2[1] = covariance_matrix(2, 1);
            _accum[i].evec2[2] = covariance_matrix(2, 2);

            pointIdxRadiusSearch.clear();
            pointRadiusSquaredDistance.clear();
        }

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
void CovarianceMatrix::prob_measure(vector <probfeatnode> *probval, vector<tensorType> *aggregated_tensor)
{
    double radius, dDeltaRadius;

    if(_scale == 0.0 || _rmin == 0.0 || _rmax == 0.0 || _rmin >= _rmax || _inCloud->points.size() == 0)
    {
            cout<<"invalid configuration parameters for classification module"<<endl;
            return;
    }

    dDeltaRadius = (_rmax - _rmin)/(_scale - 1.0);
    radius = _rmin;

    vector<probfeatnode> probfeatVal;

    probfeatVal.resize(_inCloud->points.size());

    for(size_t i =0; i < _inCloud->points.size(); i++)
    {
        probfeatVal[i].prob[0] = 0;
        probfeatVal[i].prob[1] = 0;
        probfeatVal[i].prob[2] = 0;

        probfeatVal[i].featStrength[0] = 0;
        probfeatVal[i].featStrength[1] = 0;
        probfeatVal[i].featStrength[2] = 0;

        probfeatVal[i].csclcp[0] = 0;
        probfeatVal[i].csclcp[1] = 0;
        probfeatVal[i].csclcp[2] = 0;


    }


//      _scale = 1.0;
//       radius = 0.05;

   while(radius <= _rmax)
    {
        cout<<"radius "<<radius <<" start"<<endl;
           setAccumzero();
           voteAccum(radius,probfeatVal);
//           probMeasure(probfeatVal);
           radius += dDeltaRadius;
           cout<<"radius "<<radius-dDeltaRadius<<" done"<<endl;

           for(size_t idx = 0; idx < _inCloud->points.size(); idx++)
           {
               averaged_accum[idx].evec0[0] += _accum[idx].evec0[0];
               averaged_accum[idx].evec0[1] += _accum[idx].evec0[1];
               averaged_accum[idx].evec0[2] += _accum[idx].evec0[2];

               averaged_accum[idx].evec1[0] += _accum[idx].evec1[0];
               averaged_accum[idx].evec1[1] += _accum[idx].evec1[1];
               averaged_accum[idx].evec1[2] += _accum[idx].evec1[2];

               averaged_accum[idx].evec2[0] += _accum[idx].evec2[0];
               averaged_accum[idx].evec2[1] += _accum[idx].evec2[1];
               averaged_accum[idx].evec2[2] += _accum[idx].evec2[2];
           }
   }

   // Single tensor
    for(size_t i = 0; i < _inCloud->points.size(); i++)
    {
        probfeatVal[i].csclcp[0] = 0;
        probfeatVal[i].csclcp[1] = 0;
        probfeatVal[i].csclcp[2] = 0;
        for(int j=0;j<3;j++)
        {
            averaged_tensors[i].evec0[j] /= _scale;
            averaged_tensors[i].evec1[j] /= _scale;
            averaged_tensors[i].evec2[j] /= _scale;
        }
    }

    // Since using 1 scale on combined tensor
    _scale = 1.0;
    _accum.swap(averaged_accum);
    probMeasure(probfeatVal);

    writeGlyphVars(radius - dDeltaRadius);

    for(size_t i = 0; i < _inCloud->points.size(); i++)
    {
        probfeatVal[i].prob[0] = probfeatVal[i].prob[0]/_scale;
        probfeatVal[i].prob[1] = probfeatVal[i].prob[1]/_scale;
        probfeatVal[i].prob[2] = probfeatVal[i].prob[2]/_scale;

        probfeatVal[i].featStrength[0] = probfeatVal[i].featStrength[0]/_scale;
        probfeatVal[i].featStrength[1] = probfeatVal[i].featStrength[1]/_scale;
        probfeatVal[i].featStrength[2] = probfeatVal[i].featStrength[2]/_scale;

        probfeatVal[i].csclcp[0] = probfeatVal[i].csclcp[0]/_scale;
        probfeatVal[i].csclcp[1] = probfeatVal[i].csclcp[1]/_scale;
        probfeatVal[i].csclcp[2] = probfeatVal[i].csclcp[2]/_scale;
    }


//    triangulate(_rmin, probfeatVal);

    probval->resize(_inCloud->points.size());
    for(size_t i = 0; i < _inCloud->points.size(); i++)
            (*probval)[i] = probfeatVal[i];

    aggregated_tensor->resize(_inCloud->points.size());
    for(size_t i = 0; i < _inCloud->points.size(); i++)
            (*aggregated_tensor)[i] = _accum[i];

    probfeatVal.clear();
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
Vote analysis according to modrhobahi paper and computing probability according to kreylo's paper.
*****************************************************************************************/
bool CovarianceMatrix::probMeasure (vector<probfeatnode>&probfeatVal)
{
    if(probfeatVal.size() != _inCloud->points.size())
        return false;

    _glyphData.clear();
    _glyphData.resize(_inCloud->points.size());

    for(size_t i =0; i< _inCloud->points.size(); i++)
    {
        eigendecomposition(_glyphData[i], i);
        computeSaliencyVals(_glyphData[i], i);
        glyphAnalysis(_glyphData[i]);

        glyphVars glyphtemp = _glyphData[i];

        if(glyphtemp.evals[2] == 0.0 && glyphtemp.evals[1] == 0.0 && glyphtemp.evals[0] == 0.0)
        {
             probfeatVal[i].prob[0] = probfeatVal[i].prob[0] + 1;
        }
        else
        {
            if(glyphtemp.evals[2] >= _epsi * glyphtemp.evals[0]) //ev0>ev1>ev2
                probfeatVal[i].prob[0] = probfeatVal[i].prob[0] + 1;

            if(glyphtemp.evals[1] < _epsi * glyphtemp.evals[0]) //ev0>ev1>ev2
               probfeatVal[i].prob[1] = probfeatVal[i].prob[1] + 1;

            if(glyphtemp.evals[2] < _epsi * glyphtemp.evals[0])  //ev0>ev1>ev2
                probfeatVal[i].prob[2] = probfeatVal[i].prob[2] + 1;


            probfeatVal[i].featStrength[0] += ((glyphtemp.evals[2] * glyphtemp.evals[1])/(glyphtemp.evals[0] * glyphtemp.evals[0]));
            probfeatVal[i].featStrength[1] += ((glyphtemp.evals[2] * (glyphtemp.evals[0] - glyphtemp.evals[1]))/(glyphtemp.evals[0] * glyphtemp.evals[1]));
            probfeatVal[i].featStrength[2] +=  glyphtemp.evals[2] /(glyphtemp.evals[0] + glyphtemp.evals[1] + glyphtemp.evals[2]);

        }

//        probfeatVal[i].csclcp[0] += _glyphData[i].csclcp[0];
//        probfeatVal[i].csclcp[1] += _glyphData[i].csclcp[1];
//        probfeatVal[i].csclcp[2] += _glyphData[i].csclcp[2];

        probfeatVal[i].csclcp[0] = _glyphData[i].csclcp[0];
        probfeatVal[i].csclcp[1] = _glyphData[i].csclcp[1];
        probfeatVal[i].csclcp[2] = _glyphData[i].csclcp[2];

        probfeatVal[i].sum_eigen = _glyphData[i].evals[0] + _glyphData[i].evals[1] + _glyphData[i].evals[2];
        if(_glyphData[i].evals[0] != 0)
        {
            probfeatVal[i].planarity = (_glyphData[i].evals[0] - _glyphData[i].evals[1]) / _glyphData[i].evals[0];
            probfeatVal[i].anisotropy = (_glyphData[i].evals[1] - _glyphData[i].evals[2]) / _glyphData[i].evals[0];
            probfeatVal[i].sphericity = (_glyphData[i].evals[0] - _glyphData[i].evals[2]) / _glyphData[i].evals[0];
        }
        else
        {
            probfeatVal[i].planarity = 0;
            probfeatVal[i].anisotropy = 0;
            probfeatVal[i].sphericity = 0;
        }
    }

    cout << "in probMeasure() scale = " << _scale << endl;

    // Uncomment to write eigenvalues per scale to file

//    char* filenames[6] = {"1.txt","2.txt","3.txt","4.txt","5.txt", "6.txt"};
//    ofstream fout(filenames[fNdx++]);
//    fout<< _glyphData.size()<<endl;
//    for(int i=0;i<probfeatVal.size(); i++) {
//        fout<< i<< " " << _glyphData[i].evals[0] << " "<< _glyphData[i].evals[1] << " "<< _glyphData[i].evals[2] << " " <<
//               _glyphData[i].evecs[0] << " " << _glyphData[i].evecs[1] << " " << _glyphData[i].evecs[2] << " " <<
//                _glyphData[i].evecs[3] << " " << _glyphData[i].evecs[4] << " " << _glyphData[i].evecs[5] << " " <<
//                _glyphData[i].evecs[6] << " " << _glyphData[i].evecs[7] << " " << _glyphData[i].evecs[8] << endl;
//    }
//    fout.close();

    return true;

}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void CovarianceMatrix::writeGlyphVars(float radius)
{
    if(_glyphData.size() == 0)
        return;

    ofstream fout("glyphvars.txt");
    fout<<_inCloud->points.size()<<"\n";

    fout<<radius<<"\n";

    for(size_t i = 0; i <_glyphData.size(); i++ )
    {
        fout <<_inCloud->points[i].x<<" "<<_inCloud->points[i].y<<" "<<_inCloud->points[i].z<<" ";
        fout<<_glyphData[i].evals[0]<<" "<<_glyphData[i].evals[1]<<" "<<_glyphData[i].evals[2]<<" ";
        fout<<_glyphData[i].evecs[0]<<" "<<_glyphData[i].evecs[1]<<" "<<_glyphData[i].evecs[2]<<" ";
        fout<<_glyphData[i].evecs[3]<<" "<<_glyphData[i].evecs[4]<<" "<<_glyphData[i].evecs[5]<<" ";
        fout<<_glyphData[i].evecs[6]<<" "<<_glyphData[i].evecs[7]<<" "<<_glyphData[i].evecs[8]<<" ";
        fout<<_glyphData[i].uv[0]<<" "<<_glyphData[i].uv[1]<<" ";
        fout<<_glyphData[i].abc[0]<<" "<<_glyphData[i].abc[1]<<" "<<_glyphData[i].abc[2]<<" ";
        fout<<_glyphData[i].csclcp[0]<<" "<<_glyphData[i].csclcp[1]<<" "<<_glyphData[i].csclcp[2]<<"\n"  ;
    }

    fout.close();
    _glyphData.clear();

}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void CovarianceMatrix::computeSaliencyVals(glyphVars &glyphtemp, int idx)
{

    float len = glyphtemp.evals[2] + glyphtemp.evals[1] + glyphtemp.evals[0];

    float cl = 0.0, cp = 0.0, cs = 0.0;

    if(len!= 0.0)
    {
        cl = (glyphtemp.evals[0] - glyphtemp.evals[1])/len; //ev0>ev1>ev2
        cp = (2*(glyphtemp.evals[1] - glyphtemp.evals[2]))/len ;//(2.0 * (eigen_values[1] - eigen_values[0]));
        cs = 1 - (cl+cp); //1.0 - cl - cp;

        // lamda0>lambda1>lambda2
        float lamda0 = glyphtemp.evals[0] / len;
        float lamda1 = glyphtemp.evals[1] / len;
        float lamda2 = glyphtemp.evals[2] / len;
        Eigen::MatrixXf e0(3,1);
        e0 << glyphtemp.evecs[0],glyphtemp.evecs[1],glyphtemp.evecs[2];
        e0.normalize();
        Eigen::MatrixXf e1(3,1);
        e1 << glyphtemp.evecs[3],glyphtemp.evecs[4],glyphtemp.evecs[5];
        e1.normalize();
        Eigen::MatrixXf e2(3,1);
        e2 << glyphtemp.evecs[6],glyphtemp.evecs[7],glyphtemp.evecs[8];
        e2.normalize();
        Eigen::Matrix3f T;
        T << 0,0,0,0,0,0,0,0,0;

        T += lamda0 * e0 * e0.transpose();
        T += lamda1 * e1 * e1.transpose();
        T += lamda2 * e2 * e2.transpose();

        averaged_tensors[idx].evec0[0] += T(0,0);
        averaged_tensors[idx].evec0[1] += T(0,1);
        averaged_tensors[idx].evec0[2] += T(0,2);

        averaged_tensors[idx].evec1[0] += T(1,0);
        averaged_tensors[idx].evec1[1] += T(1,1);
        averaged_tensors[idx].evec1[2] += T(1,2);

        averaged_tensors[idx].evec2[0] += T(2,0);
        averaged_tensors[idx].evec2[1] += T(2,1);
        averaged_tensors[idx].evec2[2] += T(2,2);
    }

    glyphtemp.csclcp[1] = cl;
    glyphtemp.csclcp[0] = cs;
    glyphtemp.csclcp[2] = cp;

}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void CovarianceMatrix::glyphAnalysis(glyphVars &glyphtemp)
{

    double eps=1e-4;
    double evals[3], uv[2], abc[3];

    double norm = sqrt(glyphtemp.evals[2] * glyphtemp.evals[2] + glyphtemp.evals[1]*glyphtemp.evals[1] + glyphtemp.evals[0] *glyphtemp.evals[0]);

    if(norm != 0)
    {
        glyphtemp.evals[2] = glyphtemp.evals[2]/norm;  //normalized the eigenvalues for superquadric glyph such that sqrt(lamda^2 + lambad^1 +lambda^0) = 1
        glyphtemp.evals[1] = glyphtemp.evals[1]/norm;
        glyphtemp.evals[0] = glyphtemp.evals[0]/norm;

    }


    evals[0] = glyphtemp.evals[2];   //ev0>ev1>ev2
    evals[1] = glyphtemp.evals[1];
    evals[2] = glyphtemp.evals[0];

   /* evecs[0] = glyphtemp.evecs[0];
    evecs[1] = glyphtemp.evecs[1];
    evecs[2] = glyphtemp.evecs[2];

    evecs[3] = glyphtemp.evecs[3];
    evecs[4] = glyphtemp.evecs[4];
    evecs[5] = glyphtemp.evecs[5];

    evecs[6] = glyphtemp.evecs[6];
    evecs[7] = glyphtemp.evecs[7];
    evecs[8] = glyphtemp.evecs[8];*/

    tenGlyphBqdUvEval(uv, evals);
    tenGlyphBqdAbcUv(abc, uv, 3.0);

    norm=ELL_3V_LEN(evals);

    if (norm<eps)
    {
      double weight=norm/eps;
      abc[0]=weight*abc[0]+(1-weight);
      abc[1]=weight*abc[1]+(1-weight);
      abc[2]=weight*abc[2]+(1-weight);
    }

    glyphtemp.uv[0] = uv[0];
    glyphtemp.uv[1] = uv[1];

    glyphtemp.abc[0] = abc[0];
    glyphtemp.abc[1] = abc[1];
    glyphtemp.abc[2] = abc[2];
}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool CovarianceMatrix::eigendecomposition(glyphVars &glyphtemp, size_t idx)
{

    float A[3][3], V[3][3], d[3];

    for(int i = 0; i < 3; i++)
    {
        A[i][0] = _accum[idx].evec0[i];
        A[i][1] = _accum[idx].evec1[i];
        A[i][2] = _accum[idx].evec2[i];
    }

    eigen_decomposition(A, V, d);

    glyphtemp.evals[2] = d[0] ;   //d[2] > d[1] > d[0]
    glyphtemp.evals[1] = d[1] ;
    glyphtemp.evals[0] = d[2] ;

    glyphtemp.evecs[0] = V[0][2];
    glyphtemp.evecs[1] = V[1][2] ;
    glyphtemp.evecs[2] = V[2][2];

    glyphtemp.evecs[3] = V[0][1];
    glyphtemp.evecs[4] = V[1][1] ;
    glyphtemp.evecs[5] = V[2][1];

    glyphtemp.evecs[6] = V[0][0];
    glyphtemp.evecs[7] = V[1][0] ;
    glyphtemp.evecs[8] = V[2][0];

    return true;

}
