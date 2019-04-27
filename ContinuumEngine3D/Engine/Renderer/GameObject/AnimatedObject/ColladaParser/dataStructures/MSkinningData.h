#ifndef MSKINNINGDATA_H
#define MSKINNINGDATA_H
#include "MVertexSkinData.h"

class MSkinningData
{
public:
	std::vector<std::string> jointOder;
	std::vector<MVertexSkinData> verticesSkinData;

	MSkinningData(std::vector<std::string> jointOder_, std::vector<MVertexSkinData> verticesSkinData_);
	~MSkinningData();
};

#endif
