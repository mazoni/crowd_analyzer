#include<iostream>
#include<fstream>
#include<string>
#include "Bootstrap.h"
#include "GUIManager.h"


using namespace std;


int main(int argc, char* argv[]) 
{
		if(argc < 5) { // Not enough arguments
		cout << "Please verify if the both parameters (terrain and simulation) were informed." << endl;
		cout << "The correct usage is: -t <terrainFile> -s <simulationFile>" << endl;
	} else { // verify existence of the informed parameters
		cout << "Loading files..." << endl;
		string terrainFileStr, simulationFile;

        for (int i = 1; i < argc; i++) { // set arguments to variables
			if (strcmp(argv[i], "-t") == 0) {
				terrainFileStr = argv[i+1];
			} else if (strcmp(argv[i], "-s") == 0) {
				simulationFile = argv[i+1];
			} 

		}

		ifstream terrainFile;
		terrainFile.open(terrainFileStr);

		if(!terrainFile.good()) {
			cout << "Terrain file \""<< terrainFileStr.c_str() << "\" not found." << endl ;
		}

		//TODO also test simulation file


		Bootstrap* initializer = new Bootstrap(terrainFileStr);
		initializer->run();		

	}

	//renderWindow();

	return 0;
}
