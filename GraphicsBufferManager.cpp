#include "GraphicsBufferManager.h"
#include "Unit.h"

GraphicsBufferManager::GraphicsBufferManager()
{
	mBufferMap = std::map<std::string, GraphicsBuffer*>();
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	clearMap();
}

void GraphicsBufferManager::addBuffer(std::string key, GraphicsBuffer* buffer)
{
	if (mBufferMap.count(key) == 0)
	{
		mBufferMap.insert({ key, buffer });
		//mBufferMap.insert(std::map<std::string, GraphicsBuffer*>::value_type(key, buffer));
		//mBufferMap[key] = buffer;
		//mBufferMap.emplace(key, buffer);
	}
	else
	{
		std::cout << "This key is already being used" << std::endl;
	}
}

void GraphicsBufferManager::deleteBuffer(std::string key)
{
	delete mBufferMap[key];
	mBufferMap.erase(key);
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(std::string key)
{
	if (mBufferMap.count(key) != 0)
	{
		return mBufferMap[key];
	}
	else
	{
		std::cout << "This key is empty" << std::endl;
		return nullptr;
	}
}

void GraphicsBufferManager::clearMap()
{
	for (auto pair : mBufferMap) 
	{
		delete pair.second;
	}
	mBufferMap.clear();
}
