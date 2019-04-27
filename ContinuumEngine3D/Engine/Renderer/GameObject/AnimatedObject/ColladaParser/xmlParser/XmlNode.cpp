#include "XmlNode.h"



XmlNode::XmlNode()
{
	name = "";
}

XmlNode::XmlNode(std::string name_)
{
	name = name_;
	
}


XmlNode::~XmlNode()
{
}


std::string XmlNode::getName() {
	return name;
}

std::string XmlNode::getData() {
	return data;
}

std::string XmlNode::getAttribute(std::string attr_) {
	if (!attributes.empty()) {
		return attributes[attr_];
	}
	else {
		return NULL;
	}
}

XmlNode* XmlNode::getChild(std::string childName_) {
	if (childNodes.size() != 0) {

		for (int i = 0; i < childNodes.size(); i++) {

			nodes.push_back(childNodes[childName_][i]);
	
			if (nodes[i]->getName() == childName_) {
				return nodes[i];
			}

		}
	}
	return nullptr;
}

std::vector<XmlNode*> XmlNode::getChildren(std::string name_) {
	if (!childNodes.empty()) {
		std::vector<XmlNode*> children = childNodes[name_];
		if (!children.empty()) {
			return children;
		}
	}
	return std::vector<XmlNode*>();
}


XmlNode* XmlNode::getChildWithAttribute(std::string childName_, std::string attr_, std::string value_) {
	std::vector<XmlNode*> children = getChildren(childName_);
	if (children.empty()) {
		return nullptr; //  XmlNode();
	}
	for (XmlNode* child : children) {
		std::string val = child->getAttribute(attr_);
		if (value_ == val) {
			return child;
		}
	}
	return nullptr;// XmlNode();
}

void XmlNode::addAttribute(std::string attr_, std::string value_) {
	attributes[attr_] = value_;
}

void XmlNode::addChild(XmlNode* child_) {

	std::vector<XmlNode*> childs = childNodes[child_->name];
	if (childs.empty()) {
		childNodes[child_->name] = list;
	}
	list.push_back(child_);
}

void XmlNode::setData(std::string data_) {
	data = data_;
}

void XmlNode::setName(std::string name_) {
	name = name_;
}