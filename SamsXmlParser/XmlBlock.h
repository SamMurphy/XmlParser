#pragma once
#include <vector>

namespace SamsXmlParser
{
	class XmlBlock sealed
	{
	public:
		XmlBlock();
		~XmlBlock();

	private:
		std::string name;
		std::vector<XmlBlock*> children;
		std::string param;

		int numberOfChildren;

	public:
		void SetName(const std::string& pName) { name = pName; }
		void AddChild(XmlBlock* pChild) { children.push_back(pChild); numberOfChildren++; }
		void SetParam(const std::string& pParam) { param = pParam; }

		const std::string& GetName() const { return name; }
		const std::vector<XmlBlock*> GetChildren() const { return children; }
		const std::string& GetParam() const { return param; }

		const XmlBlock* GetChild(const std::string& name);
		const XmlBlock* GetChild(const int index);

	};
}

