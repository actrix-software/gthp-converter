#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

int main(int, char** Args) {

	std::string CurrentPath = Args[0];
	std::string PicturePath = Args[1];

	CurrentPath.replace(CurrentPath.find_last_of("\\") + 1, CurrentPath.length(), ""); 

	std::string PictureName = PicturePath.substr(PicturePath.find_last_of("\\") + 1); 

	PicturePath.replace(PicturePath.find_last_of("\\") + 1, PicturePath.length(), ""); 

	std::string FileName = PictureName.substr(0, PictureName.length() - 5);

	int Count = std::distance(std::filesystem::directory_iterator(PicturePath), std::filesystem::directory_iterator{});

	std::vector<std::vector<unsigned char>> Files;

	for (int i = 1; i <= Count; i++) {

		std::string TempFile = PicturePath + FileName + std::to_string(i) + ".png";

		std::vector<unsigned char> FileBytes;

		std::ifstream File(TempFile, std::ios::binary);

		if (File.good()) {

			File.seekg(0, std::ios::end);

			size_t FileSize = File.tellg();

			File.seekg(0);

			FileBytes.resize(FileSize);

			File.read((char*)FileBytes.data(), FileSize);

			File.close();
		}

		Files.push_back(FileBytes);
	}

	auto HeaderName = FileName.replace(FileName.length() - 1, FileName.length(), "");

	std::ofstream HeaderFile(CurrentPath + HeaderName + ".hpp");

	if (HeaderFile.good()) {

		HeaderFile << "#pragma once \n\n#include <vector>\n\nnamespace " << HeaderName << "Frames {\n\n";
		
		for (int i = 0; i < Count; i++) {

			HeaderFile << "    unsigned char " << HeaderName << "_" << i + 1 << "[] = {";

			for (int j = 0; j < Files[i].size(); j++) {

				std::stringstream HexData;

				HexData << " 0x" << std::setbase(16) << std::setw(2) << std::setfill('0') << (unsigned)Files[i][j];
				
				HeaderFile << HexData.str();

				if (j != Files[i].size()) {

					HeaderFile << ",";
				}
			}

			HeaderFile << " };\n";
		}

		HeaderFile << "}\n\n";

		HeaderFile << "std::vector<std::pair<unsigned char*, int>> " << HeaderName << " = {\n\n";

		for (int i = 0; i < Count; i++) {

			HeaderFile << "    std::make_pair(" << HeaderName << "Frames::" << HeaderName << "_" << i + 1 << ", sizeof(" << HeaderName << "Frames::" << HeaderName << "_" << i + 1 << "))";

			if (i != Count) {

				HeaderFile << ",\n";
			}
 		}

		HeaderFile << "};\n";


		HeaderFile.close();
	}

	system("pause");
}
