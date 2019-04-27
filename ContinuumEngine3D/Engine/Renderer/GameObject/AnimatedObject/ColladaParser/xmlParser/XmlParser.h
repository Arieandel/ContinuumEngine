#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "XmlNode.h"
#include "../../../../ContinuumEngine_v0.00/Engine/GlobalElements/MyFile.h"



class XmlParser
{
public:
	//MyFile file; //MyFile("Engine/GlobalElements/Resources/Models/model.dae");
	char* buffer = NULL;
	std::string line;
	std::string newSBuffer;
	bool getLine();
	XmlNode* loadXmlFile(MyFile file_);
	XmlNode* loadNode(char* buffer_);
	void addData(std::string line_, XmlNode* node_);
	void addAttributes(std::vector<std::string> titleParts_, XmlNode* node_);
	void addAttribute(std::string attributeLine_, XmlNode* node_);
	std::string getStartTag(std::string line_);
	XmlParser();
	~XmlParser();
};

#endif