#include "pch.h"
#include "XmlBlock.h"


namespace SamsXmlParser
{

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

}
