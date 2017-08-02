#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <iostream>

#include <XmlBlock.h>

namespace SamsXmlParser
{

	class XmlFile
	{
	public:
		XmlFile();
		~XmlFile();

		XmlBlock* ParseFile(const std::string& filePath);

	private:
		XmlBlock* mainBlock;

	private:
		bool parseBlock(std::ifstream& stream, XmlBlock& parentBlock);
		void skipComment(std::ifstream& stream);
		void skipToEndOfTag(std::ifstream& stream);

	};

}
