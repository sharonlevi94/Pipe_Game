#pragma once
//============================ include section ===============================
#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
/*============================================================================*/
class Resources
{
	//========================== public section ==============================
public:
	static Resources& instance();
	//============================ gets section ===============================
	//const sf::SoundBuffer& getSound(int) const;
	const sf::Texture& getBackground();
	const sf::Texture& getTexture(int)const;
	//=========================== method section ==============================
	//void playSound(int key);
	//void playMusic();
	//void pauseMusic();
	//========================= private section ===============================
private:
	//========================= members section ===============================
	std::map<int, std::unique_ptr <sf::Texture>> m_texture;
	//std::map<int, std::unique_ptr<sf::SoundBuffer>> m_soundBuffers;
	//sf::Music m_music;
	//sf::Sound m_sound;
	int m_backgroundLevelState = 1;
	//================= constractors and destractors section =================
	Resources();
	//============================ sets section ===============================
	void setBackgrounds();
	void setLogos();
	void setObjects();
	//void setSounds();
};