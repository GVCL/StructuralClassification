#include "tensor3dVoting.h"

#include <pcl/common/common.h> 
#include <pcl/common/eigen.h> 
#include <pcl/common/centroid.h> 
#include <teem/ten.h>
#include "eig3.h"
/*****************************************************************************************

Function Name		:	Processing::scale	
Purpose	of Function	:	
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void tensor3dvoting::setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
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
void tensor3dvoting::setOctree(OctreeXYZ<PointT,LeafContainerT, BranchContainerT > * octree)
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

void tensor3dvoting::setParams(float rmin, float rmax, float rmaxpt, float epsi, float scale)
{
    _rmin = rmin;
    _rmax = rmax;
    _rmaxpt = rmaxpt;
    _epsi = epsi;
    _scale = scale;

    _sigma = 1.0;
    _delta = 0.16;
}


/*****************************************************************************************

Function Name		:	Processing::scale	
Purpose	of Function	:	
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool tensor3dvoting::setAccumzero()
{
    if( _inCloud->points.size() == 0)
        return false;

    _accum.resize(_inCloud->points.size());

    for(size_t i = 0; i < _inCloud->points.size(); i++)
    {
        for(int j =0; j < 3; j++)
        {
            _accum[i].evec0[j] = 0.0;
            _accum[i].evec1[j] = 0.0;
            _accum[i].evec2[j] = 0.0;
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
tensorType tensor3dvoting::compute3DBallVote(ColumnVector V, float *weight)
{
    double norm, coeff, s, t;
    Matrix3d vv(3,3), voteTemp(3,3);
    tensorType ballTensorVote;
    Matrix3d I(3, 3);

    voteTemp.setZero();
    vv.setZero();
    I.setIdentity();

     s = V.norm(); // if s is zero

     t = (s*s)/(_sigma * _sigma);

     coeff = exp(-1.0 * t);

     *weight += coeff;

     if(V.norm() != 0.0)
        V = V.normalized();

    norm = V.transpose() * V; //if norm is zero
    norm = abs(norm);

    if(norm != 0.0)
    {
        vv = V * V.transpose();
        vv = vv / norm;  // if norm is zero
    }


    voteTemp = coeff * (I - vv);

    ballTensorVote.evec0[0] = voteTemp(0, 0);
    ballTensorVote.evec0[1] = voteTemp(0, 1);
    ballTensorVote.evec0[2] = voteTemp(0, 2);

    ballTensorVote.evec1[0] = voteTemp(1, 0);
    ballTensorVote.evec1[1] = voteTemp(1, 1);
    ballTensorVote.evec1[2] = voteTemp(1, 2);

    ballTensorVote.evec2[0] = voteTemp(2, 0);
    ballTensorVote.evec2[1] = voteTemp(2, 1);
    ballTensorVote.evec2[2] = voteTemp(2, 2);

    return ballTensorVote;
}
/*****************************************************************************************

Function Name		:	Processing::scale	
Purpose	of Function	:	
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool tensor3dvoting::addBallVote(size_t idx, tensorType ballTensorVote, float lambdaN)
{
		
    for(int j =0; j < 3; j++)
    {
        _accum[idx].evec0[j] = _accum[idx].evec0[j] + lambdaN * ballTensorVote.evec0[j];
        _accum[idx].evec1[j] = _accum[idx].evec1[j] + lambdaN * ballTensorVote.evec1[j];
        _accum[idx].evec2[j] = _accum[idx].evec2[j] + lambdaN * ballTensorVote.evec2[j];
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
bool tensor3dvoting::makeVector(pcl::PointXYZ p_i, pcl::PointXYZ p_j, ColumnVector *V)
{
	ColumnVector temp;

	temp(0,0) = double((p_j.x - p_i.x));
	temp(1,0) = double((p_j.y - p_i.y));
	temp(2,0) = double((p_j.z - p_i.z));
  
	double len = sqrt(temp(0, 0) * temp(0, 0) + temp(1, 0) * temp(1, 0) + temp(2, 0) * temp(2, 0));

	if(len == 0.0)
		return false;

	(*V)(0, 0) = temp(0, 0);
	(*V)(1, 0) = temp(1, 0);
        (*V)(2, 0) = temp(2, 0);

	return true;
}
/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void tensor3dvoting::getnormalizeTensor(size_t idx, float weight)
{
    if(weight == 0.0)
        return;

    for(int j =0; j < 3; j++)
    {
        _accum[idx].evec0[j] = _accum[idx].evec0[j]/weight;
        _accum[idx].evec1[j] = _accum[idx].evec1[j]/weight;
        _accum[idx].evec2[j] = _accum[idx].evec2[j]/weight;
    }

}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool tensor3dvoting::voteAccum(float radius)
{
    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;
    pcl::PointXYZ searchPoint, tempPoint;
    tensorType ballTensorVote;
    ColumnVector clVec;
    float weight;

    for(size_t i =0; i < _inCloud->points.size(); i++)
    {
        searchPoint = _inCloud->points[i];

        if(_octree->radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
        {
            weight = 0.0;

            for (size_t j = 0; j < pointIdxRadiusSearch.size (); j++)
            {
                tempPoint = _inCloud->points[pointIdxRadiusSearch[j]];

                if(makeVector(searchPoint, tempPoint, &clVec))
                {
                    ballTensorVote = compute3DBallVote(clVec, &weight);
                    addBallVote(i, ballTensorVote, 1.0);   // initially consider eigenvalue = 1.0

                }
            }

            getnormalizeTensor(i, weight);

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
void tensor3dvoting::prob_measure(vector <probfeatnode> *probval)
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


   while(radius <= _rmax)
   {
        cout<<"radius "<<radius<< " start "<<endl;
        _sigma = radius;
        setAccumzero();
        voteAccum(radius);
        probMeasure(probfeatVal);
        radius += dDeltaRadius;
        cout<<"radius "<<radius-dDeltaRadius<< " endl "<<endl;
    }

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

    probval->resize(_inCloud->points.size());
    for(size_t i = 0; i < _inCloud->points.size(); i++)
            (*probval)[i] = probfeatVal[i];


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
bool tensor3dvoting::probMeasure (vector<probfeatnode>&probfeatVal)
{
    if(probfeatVal.size() != _inCloud->points.size())
        return false;

    _glyphData.clear();
    _glyphData.resize(_inCloud->points.size());

    for(size_t i =0; i< _inCloud->points.size(); i++)
    {
        eigendecomposition(_glyphData[i], i);
        computeSaliencyVals(_glyphData[i]);
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

        probfeatVal[i].csclcp[0] += _glyphData[i].csclcp[0];
        probfeatVal[i].csclcp[1] += _glyphData[i].csclcp[1];
        probfeatVal[i].csclcp[2] += _glyphData[i].csclcp[2];


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
void tensor3dvoting::writeGlyphVars(float radius)
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
void tensor3dvoting::computeSaliencyVals(glyphVars &glyphtemp)
{

    float len = glyphtemp.evals[2] + glyphtemp.evals[1] + glyphtemp.evals[0];

    float cl = 0.0, cp = 0.0, cs = 0.0;

    if(len!= 0.0)
    {
        cl = (glyphtemp.evals[0] - glyphtemp.evals[1])/len; //ev0>ev1>ev2
        cp = (2*(glyphtemp.evals[1] - glyphtemp.evals[2]))/len ;//(2.0 * (eigen_values[1] - eigen_values[0]));
        cs = 1 - (cl+cp); //1.0 - cl - cp;
    }

    glyphtemp.csclcp[0] = cs;
    glyphtemp.csclcp[1] = cl;
    glyphtemp.csclcp[2] = cp;

}

/*****************************************************************************************

Function Name		:	Processing::scale
Purpose	of Function	:
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
void tensor3dvoting::glyphAnalysis(glyphVars &glyphtemp)
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

    evals[0] = glyphtemp.evals[2];   //ev0>ev1>ev2    //evals0>evals>1>evals2
    evals[1] = glyphtemp.evals[1];
    evals[2] = glyphtemp.evals[0];

    tenGlyphBqdUvEval(uv, evals);
    tenGlyphBqdAbcUv(abc, uv, 0.0);  // 3.0 for superquadric glyph, 0.0 for ellpsoid

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
void tensor3dvoting::getdiffusionvelocity(Eigen::Vector3f evals, metaVelData *diffVel)
{
    evals[0] = - evals[0]/_delta;   //ev2>ev1>ev0
    evals[1] = - evals[1]/_delta;
    evals[2] = - evals[2]/_delta;

    evals[0] = exp(evals[0]);
    evals[1] = exp(evals[1]);
    evals[2] = exp(evals[2]);


    (*diffVel).vel[0] = evals[2];    //ev0>ev1>ev2 ->vel2>vel1>vel0
    (*diffVel).vel[1] = evals[1];
    (*diffVel).vel[2] = evals[0];

    (*diffVel).index[0] = 2;
    (*diffVel).index[1] = 1;
    (*diffVel).index[2] = 0;

    return;
}
/*****************************************************************************************

Function Name		:	Processing::scale	
Purpose	of Function	:	
Input Params		:
Input/output Params	:
Output Params		:
*****************************************************************************************/
bool tensor3dvoting::eigendecomposition(glyphVars &glyphtemp, size_t idx)
{

    float A[3][3], V[3][3], d[3];
    Eigen::Vector3f eigen_values;
    metaVelData diffVel;

    for(int i = 0; i < 3; i++)
    {
        A[i][0] = _accum[idx].evec0[i];
        A[i][1] = _accum[idx].evec1[i];
        A[i][2] = _accum[idx].evec2[i];
    }
	
    eigen_decomposition(A, V, d); //d[2] > d[1] > d[0]

    eigen_values[0] = d[0] ;
    eigen_values[1] = d[1] ;
    eigen_values[2] = d[2] ;

    getdiffusionvelocity(eigen_values, &diffVel);

    glyphtemp.evals[2] = diffVel.vel[0];       //evals0>evals>1>evals2  //vel2>vel1>vel0
    glyphtemp.evals[1] = diffVel.vel[1];
    glyphtemp.evals[0] = diffVel.vel[2];

    glyphtemp.evecs[0] = V[0][diffVel.index[2]];
    glyphtemp.evecs[1] = V[1][diffVel.index[2]] ;
    glyphtemp.evecs[2] = V[2][diffVel.index[2]];

    glyphtemp.evecs[3] = V[0][diffVel.index[1]];
    glyphtemp.evecs[4] = V[1][diffVel.index[1]] ;
    glyphtemp.evecs[5] = V[2][diffVel.index[1]];

    glyphtemp.evecs[6] = V[0][diffVel.index[0]];
    glyphtemp.evecs[7] = V[1][diffVel.index[0]] ;
    glyphtemp.evecs[8] = V[2][diffVel.index[0]];

    return true;
        		
}


