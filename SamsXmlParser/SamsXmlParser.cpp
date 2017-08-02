#include "pch.h"
#include "SamsXmlParser.h"


namespace SamsXmlParser
{

	XmlFile::XmlFile()
	{
		mainBlock = new XmlBlock();
	}

	XmlFile::~XmlFile()
	{
		delete mainBlock;
	}

	XmlBlock* XmlFile::ParseFile(const std::string& filePath)
	{
		mainBlock->SetName("Main");

		std::ifstream fileStream;
		fileStream.open(filePath);

		if (fileStream.is_open())
		{
			char c;
			while (fileStream.get(c))
			{
				// Beggining of block
				if (c == '<')
				{
					parseBlock(fileStream, *mainBlock);
				}
			}
		}


		return mainBlock;
	}

	bool XmlFile::parseBlock(std::ifstream& stream, XmlBlock& parentBlock)
	{
		char c;
		bool secondChar = true;
		bool foundName = false;
		bool checkForEnd = false;

		bool endOfBlock = false;

		std::string name = "";
		std::string param = "";
		XmlBlock* xml = new XmlBlock();
		while (stream.get(c) && !endOfBlock)
		{
			// Check if its a comment
			if (secondChar && c == '!')
			{
				skipComment(stream);
				delete xml;
				return true;
			}
			// Check if its a closing tag, if so skip to the end of the tag and
			// return false to indicate that this wasn't a real block.
			else if (secondChar && c == '\/')
			{
				skipToEndOfTag(stream);
				delete xml;
				return false;
			}
			// Look for the name of the tag.
			else if (!foundName)
			{
				if (c == '>')
				{
					foundName = true;
					xml->SetName(name);
					continue;
				}
				name += c;
			}
			// Not a comment, end tag, and have found the name so process the body.
			else
			{
				switch (c)
				{
				case '<':
					if (!parseBlock(stream, *xml))
						endOfBlock = true;
					break;
				case '\n':
					break;
				case '\t':
					break;
				default:
					param += c;
					break;
				}
			}
			secondChar = false;
		}
		xml->SetParam(param);
		parentBlock.AddChild(xml);
	}

	void XmlFile::skipComment(std::ifstream& stream)
	{
		char c;
		bool firstDashFound = false;
		bool checkForEnd = false;
		while (stream.get(c))
		{
			if (checkForEnd)
			{
				if (c == '>')
					return;
				else
				{
					checkForEnd = false;
					firstDashFound = false;
				}
			}
			if (c == '-')
			{
				if (firstDashFound)
					checkForEnd = true;
				else
					firstDashFound = true;
			}
		}
	}

	void XmlFile::skipToEndOfTag(std::ifstream& stream)
	{
		char c;
		while (stream.get(c))
		{
			if (c == '>')
			{
				return;
			}
		}
	}
}