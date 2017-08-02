#include <iostream>
#include <SamsXmlParser.h>


int main()
{
	std::cout << "--- XML PARSER TEST ---" << std::endl;


	std::string filePath = "C:/Users/sam-m/Documents/GitHub/XmlParser/Debug/test.xml";

	std::cout << "Trying to read " << filePath.c_str() << std::endl;
	
	// Call the parse method
	SamsXmlParser::XmlFile* xmlFile = new SamsXmlParser::XmlFile();
	SamsXmlParser::XmlBlock* xml = xmlFile->ParseFile(filePath);

	std::cout << "Outputting data..." << std::endl;
	std::cout << "-----------------------------------------" << std::endl;

	// Get data from the parsed object
	std::cout << xml->GetName().c_str() << std::endl;


	std::cout << "-----------------------------------------" << std::endl;


	
	std::cout << "DONE" << std::endl;

	delete xmlFile;
}