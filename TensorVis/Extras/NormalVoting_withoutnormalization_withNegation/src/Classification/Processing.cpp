#include "Processing.h"
#include "FileRead.h"
#include <iostream>
#include <fstream>

bool comparede(double i, double j) { return i<j; }

//bool compareint(int i, int j) { return i<j; }

/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode	
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
				critical curve node and critical disc node
Calls			:	
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/

Processing::Processing(): _inCloud(new cl)
{ 
    _filePath = "NULL";
    _FileExtension = "NULL";
    _fileNo = "NULL";
    _ptclassifyObj = new tensor3dvoting();
    _displayObj = new DisplayPoints(&_inCloud, &_intensity, &_probval, &_ftPtsProp);

    _octree = new OctreeXYZ<PointT,LeafContainerT, BranchContainerT >(0.0005);  //resolution = 0.0005

    _rmin = 0.009;
    _rmax = 0.011;


   _rmaxpt = 500;
   _epsi = 0.5;
 //  _scale = 4.0;

   _scale = 3.0;
  
   _sigmax = 1.7;
   _sigmin = 0.2;

  	
}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode	
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
				critical curve node and critical disc node
Calls			:	
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/

void Processing::setParams(float rmin, float rmax, float eps, float sigmin, float sigmax) 
{ 
   /*_rmin = rmin;
   _rmax = rmax;
  
   _epsi = eps;
   _sigmax = sigmax;
   _sigmin = sigmin;

   _epsi = 0.5;

    _scale = 3.0;
   _rmaxpt = 500;*/
    _rmin = 0.02;
    _rmax = 0.04;

          _rmaxpt = 500;
          _epsi = 0.5;
        //  _scale = 4.0;

          _scale = 3.0;

          _sigmax = 1.7;
          _sigmin = 0.2;
}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode	
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
				critical curve node and critical disc node
Calls			:	
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/

void Processing::setFilePath(std::string filePath) 
{ 
	_filePath.assign(filePath); 
}

/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode	
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
				critical curve node and critical disc node
Calls			:	
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
bool Processing::fileRead()
{
	bool nErrorCode;

	if(_filePath == "NULL")
	{
   		std::cout<<"Invalid File Path"<<std::endl;
   		return false;
   	}
 	else
	{
                FileRead *readObject = new FileRead;
		nErrorCode = readObject->read(_filePath, _inCloud, _intensity);
		_FileExtension = readObject->getFileType(_filePath);
		delete readObject;
	}

        if(_FileExtension == "las" || _FileExtension == "ply" || _FileExtension == "off"|| _FileExtension == "xyz")
            scale();

        buildOctree();

        cout<<"total size "<<_inCloud->points.size()<<endl;

	return nErrorCode;
}

/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void Processing::scale()
{
    if(_inCloud->points.size() == 0)
        return;


    float minX, minY, minZ, maxX, maxY, maxZ; //,  minIntensity, maxIntensiy,
    float DelX, DelY, DelZ;

    float minxr, maxxr, minyr, maxyr, minzr, maxzr, delxr, delyr, delzr;
    float scale_fac = 2.0;

    vector<double> tempData;

    tempData.resize(_inCloud->points.size());

    for(size_t i = 0; i < _inCloud->points.size(); i++)
        tempData[i] = _inCloud->points[i].x;

    minX = *std::min_element(tempData.begin(), tempData.end(), comparede);
    maxX = *std::max_element(tempData.begin(), tempData.end(), comparede);

    for(size_t i = 0; i < _inCloud->points.size(); i++)
        tempData[i] = _inCloud->points[i].y;

    minY = *std::min_element(tempData.begin(), tempData.end(), comparede);
    maxY = *std::max_element(tempData.begin(), tempData.end(), comparede);

    for(size_t i = 0; i < _inCloud->points.size(); i++)
        tempData[i] = _inCloud->points[i].z;

    minZ = *std::min_element(tempData.begin(), tempData.end(), comparede);
    maxZ = *std::max_element(tempData.begin(), tempData.end(), comparede);

    tempData.clear();

    DelX = maxX - minX;
    DelY = maxY - minY;
    DelZ = maxZ - minZ;

    if(DelX >= DelY && DelX >= DelZ)
    {
            minxr = 0.0;
            maxxr = 1.0 * scale_fac;

            minyr = 0;
            maxyr = DelY/DelX * scale_fac;

            minzr = 0.0;
            maxzr =  (DelZ/DelX) * scale_fac;
    }
    else if(DelY >= DelX && DelY >= DelZ)
    {
            minxr = 0;
            maxxr = DelX/DelY * scale_fac;

            minyr = 0.0;
            maxyr = 1.0 * scale_fac;

            minzr = 0.0;
            maxzr = (DelZ/DelY) * scale_fac;
    }
    else if(DelZ >= DelX && DelZ >= DelY)
    {
            //cout<<"notify it "<<endl;
            minxr = 0.0;
            maxxr = DelX/DelZ * scale_fac;

            minyr = 0.0;
            maxyr = DelY/DelZ * scale_fac;

            minzr = 0.0;
            maxzr = 1.0 * scale_fac;
    }

    delxr = maxxr - minxr;
    delyr = maxyr - minyr;
    delzr = maxzr - minzr;

    cout<<"DelX "<<DelX<<endl;
    cout<<"DelY "<<DelY<<endl;
    cout<<"DelZ "<<DelZ<<endl;

    for(size_t i =0; i < _inCloud->points.size(); i++)
    {
        _inCloud->points[i].x = delxr *(_inCloud->points[i].x  - minX)/DelX;
        _inCloud->points[i].y = delyr * (_inCloud->points[i].y - minY)/DelY;
        _inCloud->points[i].z = delzr * (_inCloud->points[i].z - minZ)/DelZ;
    }

}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void Processing::buildOctree()
{
    _octree->setInputCloud (_inCloud);
    _octree->addPointsFromInputCloud ();
}

/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode	
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
				critical curve node and critical disc node
Calls			:	
Input Params		buildOctree():	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void Processing::classifyStructFeats()
{
	if(_sigmin <= 0.0 || _rmin <= 0.0 || _rmax <= 0.0 || _rmin >= _rmax || _epsi <= 0.0 || _sigmax <=0.0 || _sigmin >= _sigmax )
	{
		cout<<"invalid configuration parameters for classification module"<<endl;
		return;
	}

        _ptclassifyObj->setInputCloud(_inCloud);
        _ptclassifyObj->setOctree(_octree);
        _ptclassifyObj->setParams(_rmin, _rmax, _rmaxpt,  _epsi, _scale);
        _ptclassifyObj->prob_measure(&_probval);
        structFeatClassification();


        ofstream fout("prob.txt");
        fout<<_inCloud->points.size()<<"\n";
        fout<<_rmin<<"\n";
        fout<<_rmax<<"\n";
        fout<<_scale<<"\n";
        fout<<_epsi<<"\n";

       for(size_t i =0; i < _inCloud->points.size(); i++)
       {
           fout<<_inCloud->points[i].x<<" "<<_inCloud->points[i].y<<" "<<_inCloud->points[i].z<<" "<<_intensity[i]<<" ";
           fout<< _probval[i].prob[0]<<" "<<_probval[i].prob[1]<<" "<<_probval[i].prob[2]<<" ";
           fout<< _probval[i].csclcp[0]<<" "<<_probval[i].csclcp[1]<<" "<<_probval[i].csclcp[2]<<" "<< _ftPtsProp[i]<<"\n";

       }
       fout.close();


}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode	
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
				critical curve node and critical disc node
Calls			:	
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
bool Processing::structFeatClassification()
{
        size_t i, pts_sz = _inCloud->points.size();
	
	if(_probval.size() == 0 || pts_sz != _probval.size())
	{
		cout<<"there are no points to classify "<<endl;
                return false;
	}

        _ftPtsProp.resize(pts_sz);

        size_t l_c = 0, l_s =  0, l_p =0;

        for(i = 0; i < pts_sz; i++)
        {

            if(_probval[i].csclcp[0] >= _probval[i].csclcp[1] && _probval[i].csclcp[0] >= _probval[i].csclcp[2])
            {
                _ftPtsProp[i] = 1;
                l_s++;
            }

            else if(_probval[i].csclcp[1] >= _probval[i].csclcp[0] && _probval[i].csclcp[1] >= _probval[i].csclcp[2])
            {
                _ftPtsProp[i] = 2;
                l_c++;
            }

            else if(_probval[i].csclcp[2] >= _probval[i].csclcp[1] && _probval[i].csclcp[2] >= _probval[i].csclcp[0])
            {
                _ftPtsProp[i] = 3;
                l_p++;
            }
            else
                 _ftPtsProp[i] = 0;

        }

        cout<<"number of line-type features "<<l_c<<endl;
        cout<<"number of  critical features "<<l_s<<endl;
          cout<<"number of surface-type features "<<l_p<<endl;

        return true;

}

/*****************************************************************************************

Function Name		:	Processing::clear	
Purpose	of Function	:	
Author/date		:	Beena-15/04/2013.
Modified by/date	:
Calls			:	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
int Processing::getDataSize()
{
	return _inCloud->points.size();
}

/*****************************************************************************************

Function Name		:	Processing::clear	
Purpose	of Function	:	
Author/date		:	Beena-15/04/2013.
Modified by/date	:
Calls			:	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
void Processing::reset()
{
	_probval.clear();
	_ftPtsProp.clear();
}

/*****************************************************************************************

Function Name		:	Processing::clear	
Purpose	of Function	:	
Author/date		:	Beena-15/04/2013.
Modified by/date	:
Calls			:	|| _ftPtsProp[i] == 2
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
void Processing::clear()
{
	_inCloud->points.clear();

	_intensity.clear();

	reset();

}
/*****************************************************************************************

Function Name		:	Processing::clear	
Purpose	of Function	:	
Author/date		:	Beena-15/04/2013.
Modified by/date	:
Calls			:	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
void Processing::setDisplayMode(int displaymode, int pointmode)
 {
 	_displaymode = displaymode;
 	_pointmode = pointmode;
 }
/*****************************************************************************************

Function Name		:	Processing::clear	
Purpose	of Function	:	
Author/date		:	Beena-15/04/2013.
Modified by/date	:
Calls			:	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
void Processing::display()
{

    if(_displaymode == 0 || (_displaymode == 1 && _pointmode == 0))
	{

           // if((!_FileExtension.compare("las") || !_FileExtension.compare("txt")))
                    _displayObj->lasDisplay();
          //  else if (!_FileExtension.compare("ply"))
                 //   _displayObj->plyDisplay();

	}
    else if(_displaymode == 1)
     _displayObj->renderStructFDs(_pointmode);
   // else if(_displaymode == 2)
    //   ;

}


