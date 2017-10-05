#include "SamsXmlParser.h"


namespace SamsXmlParser
{

	/* ---------------------------------- XML BLOCK ---------------------------------- */

	XmlBlock::XmlBlock() : name(""), children(), parameter(""), numberOfChildren(0)
	{
	}

	XmlBlock::~XmlBlock()
	{
		for each (XmlBlock* xml in children)
		{
			delete xml;
		}
		children.clear();
	}

	const XmlBlock* XmlBlock::GetChild(const std::string& name)
	{
		if (numberOfChildren > 0)
		{
			for each (XmlBlock* xml in children)
			{
				if (xml->GetName() == name)
				{
					return xml;
				}
			}
			// Child not found
			return nullptr;
		}
		else
		{
			// No child
			return nullptr;
		}
	}

	const XmlBlock* XmlBlock::GetChild(const int index)
	{
		if (index >= 0 && index < numberOfChildren)
		{
			return children[index];
		}
		return nullptr;
	}

	/* ---------------------------------- XML FILE ---------------------------------- */

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
		while (!endOfBlock && stream.get(c))
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
				case '<': // start of a tag
					if (!parseBlock(stream, *xml)) // returns false if it's a closing tag
						endOfBlock = true; // closing tag, so mark the end of the block
					break;
				case '\n':
					break;
				case '\t':
					break;
				case ' ':
					if (param == "")
						break;
				default:
					param += c; // Not part of a tag or whitespace so add to the param.
					break;
				}
			}
			secondChar = false;
		}

		// Processed the block, so can now add the block to it's parent.
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