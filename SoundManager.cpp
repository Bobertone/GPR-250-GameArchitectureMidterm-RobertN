#include "SoundManager.h"

bool SoundManager::init(int numSamplesToReserve)
{
	return al_install_audio() && al_init_acodec_addon() && al_reserve_samples(numSamplesToReserve);
}

void SoundManager::cleanup()
{
	for (auto& keySamplePair : mSoundMap)
	{
		delete keySamplePair.second;
	}
	mSoundMap.clear();
}

void SoundManager::addSample(const std::string& key, const std::string& filepath)
{
	ALLEGRO_SAMPLE* sample = loadSample(filepath);
	if (sample == nullptr) { std::cout << "file at " + filepath + " not found"<<std::endl; }
	if (containsKey(key))
	{
		delete mSoundMap[key];
	}

	mSoundMap.insert(make_pair(key, sample));
}

ALLEGRO_SAMPLE* SoundManager::loadSample(const std::string& filename)
{
	return al_load_sample(filename.c_str());
}

void SoundManager::playSample(const std::string& key, bool loop)
{
	if (loop)
	{
		al_play_sample(mSoundMap[key], 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_LOOP, nullptr);
	}
	else
	{
		al_play_sample(mSoundMap[key], 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
	}
}

bool SoundManager::containsKey(const std::string& key)
{
	return (mSoundMap.find(key) == mSoundMap.end());
}