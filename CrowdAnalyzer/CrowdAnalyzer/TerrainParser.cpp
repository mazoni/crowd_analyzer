#include "TerrainParser.h"	
#include <xercesc/parsers/XercesDOMParser.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

#include <xercesc/util/XMLChTranscoder.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <hash_map>
#include<iostream>
#include <stdexcept>
#include <string>



XERCES_CPP_NAMESPACE_USE

struct Vertex {
	string x,y,z;
};

TerrainParser::TerrainParser(string terrainXml)
{
	// take a look at http://xerces.apache.org/xerces-c/program-dom-3.html#ConstructDOMLSParser
	this->terrainXml = terrainXml;
	cout << terrainXml << endl;
	Walkable* w = new Walkable(1);
	this->walkables.push_back(*w);
	w = new Walkable(2);
	this->walkables.push_back(*w);
	for(list<Walkable>::iterator it = this->walkables.begin(); it != this->walkables.end(); ++it) 
	{
		it->toString();
	}

}


TerrainParser::~TerrainParser(void)
{
}


hash_map<int, Vertex> parseVertex(DOMElement* root) 
{
		XMLCh* vertexStr = XMLString::transcode("vertices"); 
	DOMNodeList* vertexList = root->getElementsByTagName(vertexStr);
	DOMNode* vertexNode = vertexList->item(0);
	XMLString::release(&vertexStr);

	XMLCh* posx;
	XMLCh* posy;
	XMLCh* posz;
	posx = XMLString::transcode("posx"); 
	posy = XMLString::transcode("posy"); 
	posz = XMLString::transcode("posz"); 

	//gets the vertice element
	DOMNodeList* vertexs = vertexNode->getChildNodes();
	hash_map<int, Vertex> vertexMap;

	const XMLCh* vertexNodeName = XMLString::transcode("vertice");

	try {
		for(unsigned int i = 0; i < vertexs->getLength(); i++) {
			DOMNode* vertex = vertexs->item(i);
			DOMNodeList* points = vertex->getChildNodes();
			Vertex v;
			for(unsigned int j = 0; j< points->getLength(); j++) {
				DOMNode* point = points->item(j);
			
				string nodeValue = XMLString::transcode(point->getTextContent());
				const XMLCh* nodeName = point->getNodeName();

				if (XMLString::equals(posx, nodeName)) {
					v.x = nodeValue;
					//cout << "Position X: " << v.x << endl;
				} else if (XMLString::equals(posy, nodeName)) {
					v.y = nodeValue;
					//cout << "Position Y: " << v.y << endl;
				} else if (XMLString::equals(posz, nodeName)) {
					v.z = nodeValue;
					//cout << "Position Z: " << v.z << endl;
				}
			}

			if(XMLString::equals(vertex->getNodeName(), vertexNodeName) ) {
				const XMLCh* attrName = XMLString::transcode("idVertice");
				DOMNamedNodeMap* attrs = vertex->getAttributes();
				DOMNode* idAttr = attrs->getNamedItem(attrName);
				const char* vertexIdStr = XMLString::transcode(idAttr->getTextContent());
				int vertexId = atoi(vertexIdStr);
				vertexMap[vertexId] = v;
			}
			
			
			//cout << XMLString
			//DOMNode* idAttr = attrs->getNamedItem(attrName);
			//char* vertexId = XMLString::transcode(idAttr->getTextContent());
			//vertexMap[vertexId] = v;
			//XMLString::release(&vertexId);
		}

	} catch( xercesc::XMLException& e ) {
      char* message = xercesc::XMLString::transcode( e.getMessage() );
      cout << "Error parsing file: " << message << flush;
      XMLString::release( &message );
   }


	XMLString::release(&posx);
	XMLString::release(&posy);
	XMLString::release(&posz);

	return vertexMap;
}


int TerrainParser::parseTerrain(void) 
{

	try {
         XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
                << message << "\n";
        XMLString::release(&message);
		return 0;		
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try {
		parser->parse(this->terrainXml.c_str());
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (...) {
        cout << "Unexpected Exception \n" ;
        return -1;
    }

	DOMDocument* doc = parser->getDocument();
	DOMElement* root = doc->getDocumentElement();

	//gets the vertices element
	hash_map<int, Vertex> vertexMap = parseVertex(root);
	Vertex v = vertexMap[37];

	cout << "Position X: " << v.x << endl;
	cout << "Position Y: " << v.y << endl;
	cout << "Position Z: " << v.z << endl;

    delete parser;
    delete errHandler;
	
	Walkable* w = new Walkable(1);
	this->walkables.push_back(*w);
	w = new Walkable(2);
	this->walkables.push_back(*w);

	///*for(list<Walkable>::iterator it = this->walkables.begin(); it != this->walkables.end(); ++it) 
	//{
	//	it->toString();
	//}*/

	return 1;

}

