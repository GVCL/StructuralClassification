#include "FileRead.h"
/*****************************************************************************************

Function Name		:	FileRead::getFileType	
Purpose	of Function	:	This function draw the co-ordinate x-axis and y-axis of the graph.
Calls			:	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
std::string FileRead::getFileType(std::string sFilePath)
{
    if(sFilePath.find_last_of(".") != std::string::npos)
      	return sFilePath.substr(sFilePath.find_last_of(".")+1);
    else return "NULL";
}

/*****************************************************************************************

Function Name		:	FileRead::read	
Purpose	of Function	:	read the file and store the 3d point data-sets in the buffer
Calls			:	FileRead::getFileType, FileRead::lasFileRead, FileRead::plyFileRead

Input Params		:	std::string sFilePath

Output Params		:	XYZ *xCoord, XYZ *yCoord, XYZ *zCoord, FACE *nFacesTriangles, 
				INTENSITY *vusnIntensity
Return			:
Remarks			:

*****************************************************************************************/
bool FileRead::read(string sFilePath, CloudType &cloudData, vector <float>&intensity)
{
	bool nErrorCode;
	std::string sFileType = getFileType(sFilePath);

	if (!sFileType.compare("las"))
	{
		nErrorCode = lasFileRead(sFilePath, cloudData, intensity);

  displayLasInfo();
	}

	else if(!sFileType.compare("ply"))
	{
		nErrorCode = plyFileRead(sFilePath, cloudData, intensity);	
	}
  else if(!sFileType.compare("txt"))
  {
      nErrorCode = readOriginalPtCloud(sFilePath, cloudData, intensity);
  }
	else
	{
		std::cout<<"Invalid File type. Please select the correct file"<<std::endl;
		nErrorCode = false;
	}

	return nErrorCode;
}

/*****************************************************************************************

Function Name		:	FileRead::displayLasInfo	
Purpose	of Function	:	display las file header information
Calls			:	
Input Params		:
Output Params		:
Return			:
Remarks			:

*****************************************************************************************/
void FileRead::displayLasInfo()
	{
  	std::cout<<"LAS Version No. "<<(int)_stPubBlk.ucVerMaj<<"."<<(int)_stPubBlk.ucVerMin<<std::endl;
  	std::cout<<"Format Id "<<(int)_stPubBlk.ucFormatID<<std::endl;
  	std::cout<<"Record length "<<_stPubBlk.usnRecLength<<std::endl;
  	std::cout<<"TOtal points "<<_stPubBlk.usnNumOfPoint<<std::endl;

    std::cout<<"TOtal points by return 0 "<<_stPubBlk.usnNumOfPointReturn[0]<<std::endl;
    std::cout<<"TOtal points by return 1 "<<_stPubBlk.usnNumOfPointReturn[1]<<std::endl;
    std::cout<<"TOtal points by return 2 "<<_stPubBlk.usnNumOfPointReturn[2]<<std::endl;
    std::cout<<"TOtal points by return 3 "<<_stPubBlk.usnNumOfPointReturn[3]<<std::endl;
    std::cout<<"TOtal points by return 4 "<<_stPubBlk.usnNumOfPointReturn[4]<<std::endl;
    
	}

/*****************************************************************************************

Function Name   : FileRead::lasFileRead 
Purpose of Function : read las file
Calls     : 
Input Params    : const std::string sFilePath
Output Params   : XYZ *xCoord, XYZ *yCoord, XYZ *zCoord, INTENSITY *vusnIntensity
Return      :
Remarks     :

*****************************************************************************************/
bool FileRead::readLasFileHeaderInfo(FILE *fp)
{

  char cLasSign[4];

  fseek(fp, 0, SEEK_SET);
  int nErrorCode = fread (cLasSign, 1, 4, fp);

  if(nErrorCode == 0)
      return false;

  if(cLasSign[0] == 'L' && cLasSign[1] == 'A' && cLasSign[2] == 'S' && cLasSign[3] == 'F')
  { 
    printf("Valid signature and Las File\n");
  }
  else
  {
    printf("Invalid signature and Las file\n");
    return false;
  }
    
  fseek(fp, 24, SEEK_SET);
  nErrorCode = fread(&_stPubBlk.ucVerMaj, 1, 1, fp);  
  nErrorCode = fread(&_stPubBlk.ucVerMin, 1, 1, fp);  

  fseek (fp, 104, SEEK_SET);
  nErrorCode = fread (&_stPubBlk.ucFormatID, 1, 1, fp);   //error in displaying
  nErrorCode = fread (&_stPubBlk.usnRecLength, 2, 1, fp);
  nErrorCode = fread (&_stPubBlk.usnNumOfPoint, 4, 1, fp);
  nErrorCode = fread (&_stPubBlk.usnNumOfPointReturn[0], 4, 1, fp);
  nErrorCode = fread (&_stPubBlk.usnNumOfPointReturn[1], 4, 1, fp);
  nErrorCode = fread (&_stPubBlk.usnNumOfPointReturn[2], 4, 1, fp);
  nErrorCode = fread (&_stPubBlk.usnNumOfPointReturn[3], 4, 1, fp);
  nErrorCode = fread (&_stPubBlk.usnNumOfPointReturn[4], 4, 1, fp);

  fseek(fp, 96, SEEK_SET);
  nErrorCode = fread (&_stPubBlk.ulnOffset, 4, 1, fp);

  fseek(fp, 131, SEEK_SET);
  nErrorCode = fread (&_stPubBlk.dXScale, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.dYScale, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.dZScale, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.dXOffset, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.dYOffset, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.dZOffset, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.xmax, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.xmin, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.ymax, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.ymin, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.zmax, 8, 1, fp);
  nErrorCode = fread (&_stPubBlk.zmin, 8, 1, fp);

  return true;
}

/*****************************************************************************************

Function Name		:	FileRead::lasFileRead	
Purpose	of Function	:	read las file
Calls			:	
Input Params		:	const std::string sFilePath
Output Params		:	XYZ *xCoord, XYZ *yCoord, XYZ *zCoord, INTENSITY *vusnIntensity
Return			:
Remarks			:

*****************************************************************************************/
bool FileRead::lasFileRead(const string sFilePath, CloudType &cloudData, vector <float>&intensity)
{
    int lnTempPoint, error;    //4 byte
    unsigned short usnTempIntensity;   // 2byte
    bool err;

    FILE *fp = fopen(sFilePath.c_str(), "r");

    if(fp == NULL)
    {
        printf("Invalid File path. Please select correct file\n");
        return false;
    }

    err = readLasFileHeaderInfo(fp);

    if(err == false)
    {
        printf("Error in las header info\n");
        return false;
    }

    // Fill in the cloud data
    cloudData->width    = _stPubBlk.usnNumOfPoint;
    cloudData->height   = 1;
    cloudData->is_dense = false;
    cloudData->points.resize (cloudData->width * cloudData->height);
    intensity.resize(_stPubBlk.usnNumOfPoint);

    for(size_t nIndex = 0; nIndex <_stPubBlk.usnNumOfPoint ; nIndex++) //_stPubBlk.usnNumOfPoint
    {
        fseek(fp, _stPubBlk.ulnOffset, SEEK_SET);

        error = fread (&lnTempPoint, 4, 1, fp);
        cloudData->points[nIndex].x = (ftType)lnTempPoint * _stPubBlk.dXScale + _stPubBlk.dXOffset;

         error = fread (&lnTempPoint, 4, 1, fp);
        cloudData->points[nIndex].y = (ftType)lnTempPoint * _stPubBlk.dYScale + _stPubBlk.dYOffset;

        error = fread (&lnTempPoint, 4, 1, fp);
        cloudData->points[nIndex].z = (ftType)lnTempPoint * _stPubBlk.dZScale + _stPubBlk.dZOffset;

        error = fread (&usnTempIntensity, 2, 1, fp);
        intensity[nIndex] = (ftType)usnTempIntensity/255.0;

        if(error == 0)
            return false;
    }

    return true;
}


/*****************************************************************************************
Function Name		:	FileRead::plyFileRead	
Purpose	of Function	:	read ply file data
Calls			:	FileRead::LoadFace
Input Params		:	std::string sFilePath
Output Params		:	XYZ *xCoord, XYZ *yCoord, XYZ *zCoord, FACE *nFacesTriangles
Return			:
Remarks			:
*****************************************************************************************/
bool FileRead::plyFileRead(const string sFilePath,  CloudType &cloudData, vector <float>&intensity)
{
  FILE *file;
  char buffer[1000];
    int nTotalConnectedPoints, nTotalFaces;
	bool errorCode;

  file = fopen(sFilePath.c_str(), "r");
  if(file == NULL)
  {
    printf("Invalid Input File. Please Select the correct file.\n");
    return false;
  }
  // Find number of vertices
  fseek(file,0,SEEK_SET);
	while(strncmp( "element vertex", buffer, strlen("element vertex")) != 0  )
 	{
  	errorCode = fgets(buffer,300,file);			// format
 	}
  strcpy(buffer, buffer+strlen("element vertex"));
 	sscanf(buffer,"%i", &nTotalConnectedPoints);
  // Find number of faces
  fseek(file, 0, SEEK_SET);
  while(strncmp( "element face", buffer, strlen("element face")) != 0  )
  {
    errorCode = fgets(buffer, 300, file);			// format
  }
	strcpy(buffer, buffer+strlen("element face"));
	sscanf(buffer,"%i", &nTotalFaces);
	// go to end_header
  while(strncmp( "end_header", buffer, strlen("end_header")) != 0  )
  {
    errorCode = fgets(buffer,300,file);			// format
  }
    // Fill in the cloud data
  cloudData->width    = nTotalConnectedPoints;
  cloudData->height   = 1;
  cloudData->is_dense = false;
  cloudData->points.resize (cloudData->width * cloudData->height);
  intensity.resize(nTotalConnectedPoints);

  for(int iterator = 0; iterator < nTotalConnectedPoints; iterator++)
  {
    float t1, t2, t3;
    errorCode = fgets(buffer,300,file);
    sscanf(buffer,"%f %f %f", &t1, &t2, &t3);
    cloudData->points[iterator].x = t1;
		cloudData->points[iterator].y = t2;
 		cloudData->points[iterator].z = t3;
    intensity[iterator] = 0.5;
  }

  return true;
}

/*****************************************************************************************

Function Name   : FltkForm::process 
Purpose of Function : 
Calls     : Processing::clear(), Processing::setFilePath(), Processing::process()
Input Params    :
Output Params   :
Return      :
Remarks     :

*****************************************************************************************/
bool FileRead::readOriginalPtCloud(string filename, CloudType &cloudData, vector <float>&intensity)
{
  bool errorCode;
  FILE *fp = fopen(filename.c_str(), "r");
  if(fp == NULL) 
  {
    printf("Invalid File path. Please select correct file\n");
    return false;
  }
  size_t total;
  char buffer[1000];
  fgets(buffer,300,fp);
  sscanf(buffer, "%d ", &total, fp);

  cloudData->width    = total;
  cloudData->height   = 1;
  cloudData->is_dense = false;
  cloudData->points.resize (cloudData->width * cloudData->height);
  intensity.resize(total);

  for( size_t i = 0 ; i < total ; ++i)
  {
    int index;
    unsigned int itt, itt1, itt2;
    float t1, t2, t3, t4;
    errorCode = fgets(buffer,300,fp);
    sscanf(buffer,"%d %f %f %f %u %u %u %f", &index, &t1, &t2, &t3, &itt, &itt1, &itt2, &t4);
    cloudData->points[i].x = t1;
    cloudData->points[i].y = t2;
    cloudData->points[i].z = t3;
    intensity[i] = itt/255.0;
  }

  return true;

}
