#include "aitMesh.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

using namespace std;


void Render_function(string s , vector<aitVertex>& vertices , vector<glm::vec3>& vVector , vector<glm::vec3>& vnVector)
{
	//read in f_string minus 'f' part , read in pointer reference to private variable vertices, read in reference vVector  and vnVector vectors

	stringstream st(s); // create new stringstream to read in line using string s read in from method Render_function
	string fpart ; // used to read in string to convert into int to point to create v/vn part
	int count = 0; // used to count amount of delimiters found, to read in variables correctly
	glm::vec3 aitVertexV; // used to read in v part of aitVertex to be pushed back later
	glm::vec3 aitVertexVn; // used to read in vn part of aitVertex to be pushed back later
	while(getline(st,fpart,'/')) // use getline, read in stringstream and split it into different parts using delimiter '/'
	{
		if (count == 0)
		{
			aitVertexV = vVector[stoi(fpart) -1]; //read in first number , using stoi to convert string to int , and setting fpart -1 since vVector starts at 0 for, 1 for 2 etc
		}
		if (count == 2)
		{
			aitVertexVn = vnVector[stoi(fpart) -1];
			count = 0; //same as above, except set count to 0 in order to read every part in properly
		}
		count++; //increase count for each delimiter
	}
	vertices.push_back(aitVertex(aitVertexV,aitVertexVn)); //push back to vertices using values gotten from aitVertexV and aitVertexVn
}

bool aitMesh::loadFromObj(std::string path)
{

	ifstream myfile;// ifstream stream class to read from files

	string line ;
	stringstream ss;
	vector<glm::vec3> vVector;
	vector<glm::vec3> vnVector;
	std::vector<int> fVector;
	myfile.open (path);// ifstream stream class to read from files

	if(myfile.is_open())
	{
		
		while (getline(myfile,line))
		{
			if(line.substr(0,2) == "v ")
			{ 
				ss << line.substr(2); // Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
				float floats[3];  // loops through each line,inserts each input into a temp array
				for(int i = 0; i < 3;i++)
				{
					ss >> floats[i];
				}
				
				vVector.push_back(glm::vec3(floats[0],floats[1],floats[2]));
				ss.clear();
			}
			
			else if(line.substr(0,2) == "vn")
			{
				string subline = line.substr(2);
				ss << line.substr(2);
				float floats[3];  // loops through each line,inserts each input into a temp array
				for(int i = 0; i < 3;i++)
				{
					ss >> floats[i];
				}
				
				vnVector.push_back(glm::vec3(floats[0],floats[1],floats[2]));
				ss.clear();
			}
			
			else if(line.substr(0,2) == "f ")
			{
				
				ss << line.substr(2);
				string strings[3];

				for(int i = 0; i < 3;i++)
				{
					ss >> strings[i];
				}
				ss.clear();
				
				
				Render_function(strings[0] , vertices , vVector , vnVector); //to create each vertice contained in the f_line
				Render_function(strings[1] , vertices , vVector , vnVector);
				Render_function(strings[2] , vertices , vVector , vnVector);
				
			}
			


		}

		
		
	}
    



	/*
	aitVertex v1(glm::vec3(1.000000, 0.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v2(glm::vec3(-1.000000, 0.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v3(glm::vec3(0.000000, -1.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v4(glm::vec3(2.000000, 0.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v5(glm::vec3(-2.000000, 0.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v6(glm::vec3(0.000000, 2.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	*/
	

	return true;
}

