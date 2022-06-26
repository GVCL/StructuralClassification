#ifndef FILE_READ_H
#define FILE_READ_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "data_type.h"
#include <pcl/io/pcd_io.h>


using namespace std;

/*****************************************************************************************

Class Name		:	FileRead	
Purpose			:	read the input file and store data(x,y,z coordinates and intensity values) in the vectors data structure
Created by		:	Beena
Created date		:	
Modification		:
Modified Function	:

*****************************************************************************************/
class FileRead 
{
  public:
    typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudType;

    FileRead(){}
    ~FileRead(){}


    string getFileType(std::string sFilePath);
    bool read(string sFilePath, vector<double>&x, vector<double>&y, vector<double>&z, vector <float>&intensity);

    void displayLasInfo();

	private:
    bool lasFileRead(const string sFilePath,vector<double>&x, vector<double>&y, vector<double>&z, vector <float>&intensity);
    bool plyFileRead(const string sFilePath, vector<double>&x, vector<double>&y, vector<double>&z, vector <float>&intensity);
    bool readOriginalPtCloud(string filename, vector<double>&x, vector<double>&y, vector<double>&z, vector <float>&intensity);
    bool offFileRead(string filename,vector<double>&x, vector<double>&y, vector<double>&z, vector <float>&intensity);
    bool readLasFileHeaderInfo(FILE *fp);

    SLasHeaderBlock _stPubBlk; 

};


#endif
