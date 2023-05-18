#pragma once
#include <Trackable.h>
#include <string>

class DataManager :public Trackable
{
public:
	DataManager(std::string filepath);

	float getFloat(const std::string& key);
	std::string getString(const std::string& key);

private:
	std::string mFilepath;

};

