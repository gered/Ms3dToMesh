#include <stdio.h>
#include <string>
#include <exception>

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

	std::string meshFile = "";
	if (extension.length() > 0)
	{
		meshFile = file;
		meshFile.erase(meshFile.find_last_of('.'), std::string::npos);
		meshFile.append(".mesh");
	}

	Ms3d *ms3d = new Ms3d();
	if (!ms3d->Load(file))
	{
		printf("Error loading MS3D file.\n\n");
		return 1;
	}
	if (!ms3d->ConvertToMesh(meshFile, scaleFactor))
	{
		printf("Error converting MS3D to MESH.\n\n");
		return 1;
	}

	printf("Finished converting to %s\n", meshFile.c_str());

	return 0;
}
