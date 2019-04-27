#include "XmlParser.h"




XmlParser::XmlParser()
{

}


XmlParser::~XmlParser()
{
}


XmlNode* XmlParser::loadXmlFile(MyFile file_) {



	file_.getInputStream();
	buffer = file_.getReader();
	XmlNode* node = loadNode(buffer);
	return node;
}


void XmlParser::addData(std::string line_, XmlNode* node_) {
	int size = line_.size();
	int index1 = 0;
	int index2 = 0;
	bool first = true;

	for (int i = 0; i < size; i++) {
		if (line_.substr(i, 1) == ">") {
			break;
		}
		index1++;
	}

	for (int i = 0; i < size; i++) {
		if (line_.substr(i, 1) == "<") {
			if (first) {
				first = false;
			}
			else {
				break;
			}
		}
		index2++;
	}



	if (index2 != size) {
		std::string data = line_.substr(index1 + 1, (index2 - (index1 + 1)));
		node_->setData(data);
	}
	
}

void XmlParser::addAttributes(std::vector<std::string> titleParts_, XmlNode* node_) {
	for (int i = 0; i < titleParts_.size(); i++) {

		if (titleParts_[i].find("=") != std::string::npos) {
			addAttribute(titleParts_[i], node_);
		}
	}
}


void XmlParser::addAttribute(std::string attributeLine_, XmlNode* node_) {
	//Pattern ATTR_NAME = Pattern.compile("(.+?)=");
	//Pattern ATTR_VAL = Pattern.compile("\"(.+?)\"");


	size_t n = std::count(attributeLine_.begin(), attributeLine_.end(), '=');
	int begin = 0;
	std::vector<int> equalSigns;

	for (int i = 0; i < n; i++) {
		std::size_t temp = attributeLine_.substr(begin + 1).find("=");
		begin += temp + 1;
		equalSigns.push_back(begin);

	}

	std::vector<int> untilSpaces;
	for (int i = 0; i < equalSigns.size(); i++) {
		int j = 0;
		for (int m = 0; m < equalSigns[i]; m++) {
			if (attributeLine_[equalSigns[i] - j] == ' ') {
				untilSpaces.push_back(j);
				break;
			}
			else
			{
				j++;
			}
		}
	}

	std::vector<int> untilQuot;
	for (int i = 0; i < equalSigns.size(); i++) {
		int j = 0;
		for (int m = 0; m < attributeLine_.size(); m++) {
			if (attributeLine_[equalSigns[i]+2 + j] == '"') {
				untilQuot.push_back(j);
				break;
			}
			else
			{
				j++;
			}
		}
	}


	for (int i = 0; i < equalSigns.size(); i++) {

		std::string name = attributeLine_.substr((equalSigns[i] + 1) - untilSpaces[i], untilSpaces[i] - 1);
		std::string value = attributeLine_.substr((equalSigns[i] + 2) , untilQuot[i]);
		node_->addAttribute(name, value);
		std::cout << name << " " << value << std::endl;
	}


}


std::string XmlParser::getStartTag(std::string line_) {

	std::vector<int> untilleft;
	for (int i = 0; i < line_.size(); i++) {

		if (line_[i] == '<') {
			untilleft.push_back(i);
			break;
		}	
	}

	std::vector<int> untilright;
	for (int i = 0; i < line_.size(); i++) {

		if (line_[i] == '>') {
			untilright.push_back(i);
			break;
		}
	}

	std::string subs = line_.substr(untilleft[0] +1, untilright[0] - (untilleft[0] + 1));
	return subs;
}
bool XmlParser::getLine() {

	line = buffer;
	std::size_t temp = line.substr(0, 100000).find("\n");
	if (temp != std::string::npos) {
		newSBuffer = line.substr(0, temp);
		line.erase(0, temp + 1);
		int n = line.size();
		char* newCBuffer;
		newCBuffer = new char[(int)(n + 1)];

		for (int i = 0; i < line.size(); i++) {
			newCBuffer[i] = line[i];
		}

		buffer = newCBuffer;

		return true;
	}
	else {
		return false;
	}


}

XmlNode* XmlParser::loadNode(char* buffer_) {

	//std::ifstream in(file.path, std::ios::in);
	buffer = buffer_;


	
	//std::getline(in, line)
	//;
	getLine();

		if (newSBuffer.substr(0, 2) != "<?") {
			int tokenFound = 0;
			bool firstFound = false;
			for (int i = 0; i < newSBuffer.size(); i++) {
				if (newSBuffer.substr(i, 1) == " ") {

				}
				else {
					if (firstFound == false) {
						firstFound = true;
						if (newSBuffer.substr(i, 2) == "</") {
							return nullptr; //&XmlNode();
							

						}
						else {
							std::string startTag = getStartTag(newSBuffer);
							XmlNode* tempNode = new XmlNode(); //XmlNode(startTag.substr(0, startTag.find(" ")));
							tempNode->setName(startTag.substr(0, startTag.find(" ")));
							addAttribute(newSBuffer, tempNode);
							addData(newSBuffer, tempNode);

							size_t c1 = newSBuffer.find("</");
							size_t c2 = newSBuffer.find("/>");

							if (c1 != std::string::npos || c2 != std::string::npos) {
								return tempNode;
							}

							XmlNode* childNode = nullptr;
							while ((childNode = loadNode(buffer)) != nullptr ) 
							{
								tempNode->addChild(childNode);
							}

							return tempNode;
						}
					}
				}
			}

		}
		else {
			loadNode(buffer);
			//file.close();
		}
	
	
}