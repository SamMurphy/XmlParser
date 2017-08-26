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
		std::string parameter;

		XmlBlock* parent;

		int numberOfChildren;

	public:
		void SetName(const std::string& pName) { name = pName; }
		void AddChild(XmlBlock* pChild) { children.push_back(pChild); numberOfChildren++; pChild->SetParent(this); }
		void SetParam(const std::string& pParam) { parameter = pParam; }

		const std::string& GetName() const { return name; }
		const std::vector<XmlBlock*> GetChildren() const { return children; }
		const std::string& GetParameter() const { return parameter; }

		const XmlBlock* GetChild(const std::string& name);
		const XmlBlock* GetChild(const int index);
		const XmlBlock* GetParent() { return parent; }
		const int GetNumberOfChildren() { return numberOfChildren; }

	protected:
		void SetParent(XmlBlock* pParent) { parent = pParent; }

	};
}

