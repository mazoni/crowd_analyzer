#include "TerrainParser.h"	
#include "Vertex.h"
#include "Walkable.h"

#include <xercesc/parsers/XercesDOMParser.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

#include <xercesc/util/XMLChTranscoder.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <hash_map>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>



XERCES_CPP_NAMESPACE_USE

struct Edge {
	int a,b;
};


TerrainParser::TerrainParser(string terrainXml)
{
	// take a look at http://xerces.apache.org/xerces-c/program-dom-3.html#ConstructDOMLSParser
	this->terrainXml = terrainXml;
	cout << terrainXml << endl;
	Walkable* w = new Walkable(1);
	this->walkables.push_back(w);
	w = new Walkable(2);
	this->walkables.push_back(w);
	for(list<Walkable*>::iterator it = this->walkables.begin(); it != this->walkables.end(); ++it) 
	{
		w = *it;
		w->toString();
	}

}


TerrainParser::~TerrainParser(void)
{
}

list<Walkable*> parseWalkables(DOMElement* root, hash_map<int, Vertex*> vertexMap, hash_map<int, Edge> edgesMap) 
{
	XMLCh* walkableStr = XMLString::transcode("contextos");
	DOMNodeList* walkableList = root->getElementsByTagName(walkableStr);
	DOMNode* walkableNode = walkableList->item(0);
	XMLString::release(&walkableStr);

	DOMNodeList* walkables = walkableNode->getChildNodes();
	list<Walkable*> wList;	

	XMLCh* refAresta;
	refAresta = XMLString::transcode("refAresta"); 

	const XMLCh* walkableNodeName = XMLString::transcode("contexto");

	try {
		for(unsigned int i = 0; i < walkables->getLength(); i++) {
			DOMNode* walkable = walkables->item(i);
			DOMNodeList* edgeRefs = walkable->getChildNodes();
			Walkable *w = new Walkable(0);
			list<Vertex*> vertices;
			set<int> addedVertices;

			for(unsigned int j = 0; j< edgeRefs->getLength(); j++) {
				DOMNode* ref = edgeRefs->item(j);
			
				string nodeValue = XMLString::transcode(ref->getTextContent());
				const XMLCh* nodeName = ref->getNodeName();

				if (XMLString::equals(refAresta, nodeName)) {
					int vexAId = edgesMap[atoi(nodeValue.c_str())].a;
					int vexBId = edgesMap[atoi(nodeValue.c_str())].b;

					if( addedVertices.find(vexAId) == addedVertices.end()) 
					{
						Vertex* a = vertexMap[vexAId];
						vertices.push_back(a);
						addedVertices.insert(vexAId);
					}
					if( addedVertices.find(vexBId) == addedVertices.end()) 
					{
						Vertex* b = vertexMap[vexBId];
						vertices.push_back(b);
						addedVertices.insert(vexBId);
					}
				} 
			}
			if(!vertices.empty()) 
			{
				w->setVertices(vertices);
				wList.push_back(w);
			}
			
		}

	} catch( xercesc::XMLException& e ) {
      char* message = xercesc::XMLString::transcode( e.getMessage() );
      cout << "Error parsing file: " << message << flush;
      XMLString::release( &message );
   }

	return wList;

}

hash_map<int, Edge> parseEdges(DOMElement* root, hash_map<int, Vertex*> vertexMap) 
{
	XMLCh* edgesStr = XMLString::transcode("arestas");
	DOMNodeList* edgesList = root->getElementsByTagName(edgesStr);
	DOMNode* edgesNode = edgesList->item(0);
	XMLString::release(&edgesStr);

	DOMNodeList* edges = edgesNode->getChildNodes();
	hash_map<int, Edge> edgesMap;

	XMLCh* refVert1;
	XMLCh* refVert2;
	refVert1 = XMLString::transcode("refVertice1"); 
	refVert2 = XMLString::transcode("refVertice2"); 

	const XMLCh* edgeNodeName = XMLString::transcode("aresta");

	try {
		for(unsigned int i = 0; i < edges->getLength(); i++) {
			DOMNode* edge = edges->item(i);
			DOMNodeList* vexRefs = edge->getChildNodes();
			Edge e;

			for(unsigned int j = 0; j< vexRefs->getLength(); j++) {
				DOMNode* ref = vexRefs->item(j);
			
				string nodeValue = XMLString::transcode(ref->getTextContent());
				const XMLCh* nodeName = ref->getNodeName();

				if (XMLString::equals(refVert1, nodeName)) {
					e.a = atoi(nodeValue.c_str());
				} else if (XMLString::equals(refVert2, nodeName)) {
					e.b = atoi(nodeValue.c_str());
				}
			}

			if(XMLString::equals(edge->getNodeName(), edgeNodeName) ) {
				const XMLCh* attrName = XMLString::transcode("idAresta");
				DOMNamedNodeMap* attrs = edge->getAttributes();
				DOMNode* idAttr = attrs->getNamedItem(attrName);
				const char* edgeIdStr = XMLString::transcode(idAttr->getTextContent());
				int edgeId = atoi(edgeIdStr);
				edgesMap[edgeId] = e;
			}
			
		}

	} catch( xercesc::XMLException& e ) {
      char* message = xercesc::XMLString::transcode( e.getMessage() );
      cout << "Error parsing file: " << message << flush;
      XMLString::release( &message );
   }

	return edgesMap;
}


hash_map<int, Vertex*> parseVertex(DOMElement* root) 
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
	hash_map<int, Vertex*> vertexMap;

	const XMLCh* vertexNodeName = XMLString::transcode("vertice");

	try {
		for(unsigned int i = 0; i < vertexs->getLength(); i++) {
			DOMNode* vertex = vertexs->item(i);
			DOMNodeList* points = vertex->getChildNodes();
			Vertex* v = new Vertex();
			for(unsigned int j = 0; j< points->getLength(); j++) {
				DOMNode* point = points->item(j);
			
				string nodeValue = XMLString::transcode(point->getTextContent());
				const XMLCh* nodeName = point->getNodeName();

				if (XMLString::equals(posx, nodeName)) {
					v->x = atof(nodeValue.c_str());
					//cout << "Position X: " << v.x << endl;
				} else if (XMLString::equals(posy, nodeName)) {
					v->y = atof(nodeValue.c_str());
					//cout << "Position Y: " << v.y << endl;
				} else if (XMLString::equals(posz, nodeName)) {
					v->z = atof(nodeValue.c_str());
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
	hash_map<int, Vertex*> vertexMap = parseVertex(root);

	hash_map<int, Edge> edgesMap = parseEdges(root, vertexMap);

	this->walkables = parseWalkables(root, vertexMap, edgesMap);

	Vertex* v = vertexMap[37];

	cout << "Position X: " << v->x << endl;
	cout << "Position Y: " << v->y << endl;
	cout << "Position Z: " << v->z << endl;

	Edge e = edgesMap[4];
	cout << "Ref 1: " << e.a << endl;
	cout << "Ref 2: " << e.b << endl;

    delete parser;
    delete errHandler;



	/*Walkable* w = new Walkable(1);
	this->walkables.push_back(*w);
	w = new Walkable(2);
	this->walkables.push_back(*w);*/


	Walkable *w;
	list<Walkable*>::iterator it = this->walkables.begin();
	w = *it;
	w->toString();
	
	return 1;

}

