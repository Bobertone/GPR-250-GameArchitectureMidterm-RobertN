#pragma once
#include <Trackable.h>
#include <map>

//using namespace std;

/*	A class to hold all the GraphicsBuffers in the game(except the backbuffer which should still reside in the
		GraphicsSystem – although having a way of getting to it through the GraphicsBufferManager is not a bad
		idea)	*/
class GraphicsBuffer;

class GraphicsBufferManager : public Trackable
{
private:

	////-DATA-
		
	// A “map” of GraphicsBuffers
	std::map<std::string, GraphicsBuffer*> mBufferMap;

public:
	////-FUNCTIONS-
		
	// Constructor / destructor
	GraphicsBufferManager();
	~GraphicsBufferManager();

	// Some way of adding / deleting / getting GraphicsBuffers
	void addBuffer(std::string key, GraphicsBuffer* buffer);

	void deleteBuffer(std::string key);

	GraphicsBuffer* getBuffer(std::string key);

	// Clear - remove and delete all GraphicsBuffers
	//(not including the BackBuffer – GraphicsSystem should still clean that up itself)
	void clearMap();
};