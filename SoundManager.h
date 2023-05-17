#pragma once
#include <Trackable.h>
#include <unordered_map>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//SoundManager – holds sound samples and has functions to init/cleanup/play various sounds
class SoundManager : public Trackable
{
public:
	SoundManager() {}
	~SoundManager() { cleanup(); }

	bool init(int sampleCount);
	void cleanup();
	void addSample(const std::string& key, const std::string& filepath);
	void playSample(const std::string& key, bool loop);
	bool containsKey(const std::string& key);

private:
	std::unordered_map <std::string , ALLEGRO_SAMPLE*> mSoundMap;
	ALLEGRO_SAMPLE* loadSample(const std::string& filename);
};