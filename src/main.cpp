#include <stdio.h>
#include <string>
#include <exception>

#include "meshfile.h"
#include "ms3d/ms3d.h"

int main(int argc, char **argv)
{
	printf("MS3D-to-MESH Converter\n");

	if (argc == 1)
	{
		printf("No input file specified.\n");
		printf("Usage: ms3dtomesh.exe [--scale=<scale factor>] [inputfile]\n\n");
		return 1;
	}

	// input file is always the last argument
	std::string file = argv[argc - 1];

	// default option values
	float scaleFactor = 1.0f;

	// find any options and update their values
	for (int i = 1; i < argc - 1; ++i)
	{
		std::string arg = argv[i];

		if (arg.substr(0, 8) == "--scale=")
		{
			// scale factor

			if (arg.length() == 8)
			{
				printf("Missing scale factor.\n");
				return 1;
			}

			scaleFactor = (float)atof(arg.substr(8).c_str());

			if (scaleFactor == 0.0f)
			{
				printf("Invalid or 0.0 scale factor.\n");
				return 1;
			}
		}
	}

	// find file extension part of the string in the input filename
	// we will use this to make an appropriate output mesh filename *and*
	// to make an XML metadata filename
	std::string extension;
	try
	{
		extension = file.substr(file.find_last_of('.'), std::string::npos);
		for (unsigned int i = 0; i < extension.size(); ++i)
			extension[i] = tolower(extension[i]);
	}
	catch (std::exception &e)
	{
		extension = "";
	}
	
	// make sure the ms3d file didn't have some other extension for some reason
	// which might conflict with our automatic mesh and metadata filename
	// creation ...
	if (extension == ".mesh" || extension == ".xml")
	{
		printf("Bad input filename extension.\n\n");
		return 1;
	}

	// create mesh filename based on ms3d filename
	std::string meshFile = file;
	if (extension.length() > 0)
		meshFile.erase(meshFile.find_last_of('.'), std::string::npos);
	meshFile.append(".mesh");
	
	std::string metadataFile = file;
	if (extension.length() > 0)
		metadataFile.erase(metadataFile.find_last_of('.'), std::string::npos);
	metadataFile.append((".xml"));

	// load the MS3D ...
	Ms3d *ms3d = new Ms3d();
	if (!ms3d->Load(file))
	{
		printf("Error loading MS3D file.\n\n");
		return 1;
	}
	
	// attempt to load a metadata file
	// TODO: write this
	
	// convert to a mesh file
	// TODO: pass in loaded metadata object
	if (!ConvertToMeshFile(meshFile, ms3d, scaleFactor))
	{
		printf("Error converting MS3D to MESH.\n\n");
		return 1;
	}

	printf("Finished converting to %s\n", meshFile.c_str());

	return 0;
}
