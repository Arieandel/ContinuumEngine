#include "MSkinningData.h"



MSkinningData::MSkinningData(std::vector<std::string> jointOder_, std::vector<MVertexSkinData> verticesSkinData_)
{
	jointOder = jointOder_;
	verticesSkinData = verticesSkinData_;
}


MSkinningData::~MSkinningData()
{
}
