#ifndef XMLNODE_H
#define XMLNODE_H

#include <map>
#include <vector>

class XmlNode
{
public:

	std::string name;
	std::map<std::string, std::string> attributes = std::map<std::string, std::string>();
	std::string data;
	std::map<std::string, std::vector<XmlNode*>> childNodes;
	std::vector<XmlNode*> list;
	std::vector<XmlNode*> nodes;
	std::string getName();
	std::string getData();
	std::string getAttribute(std::string attr_);
	XmlNode* getChild(std::string childName_);
	XmlNode* getChildWithAttribute(std::string childName_, std::string attr_, std::string value_);
	std::vector<XmlNode*> getChildren(std::string name_);
	void addAttribute(std::string attr_, std::string value_);
	void addChild(XmlNode* child_);
	void setData(std::string data_);
	void setName(std::string name_);

	XmlNode();
	XmlNode(std::string name_);
	~XmlNode();
};

#endif