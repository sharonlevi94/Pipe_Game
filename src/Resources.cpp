//============================= include section ==============================
#include "Resources.h"
#include <map>
#include "Macros.h"
//============================= public section ===============================
//==================== Constructors & destructors section ====================
Resources::Resources() 
	//m_music()
{
	this->m_texture.clear();
	//this->m_soundBuffers.clear();
	//this->m_music.setVolume(MUSIC_VOLUME);
	this->setBackgrounds();
	this->setLogos();
	this->setObjects();
	//this->setSounds();
}
//============================================================================
Resources& Resources::instance() {
	static Resources inst;
	return(inst);
}
//============================== gets section ================================
//============================================================================
const sf::Texture& Resources::getBackground() {	
	return (*this->m_texture.find(BACKGROUND)->second);
}
//============================================================================
const sf::Texture& Resources::getTexture(int textureKey)const {
	return (*this->m_texture.find(textureKey)->second);
}
//============================================================================
/*const sf::SoundBuffer& Resources::getSound(int soundKey) const {
	return(*this->m_soundBuffers.find(soundKey)->second);
}*/
//============================ methods section ===============================
/*void Resources::playMusic() {
	this->m_music.openFromFile(MUSIC_PATH);
	this->m_music.play();
	this->m_music.setLoop(true);
}*/
//============================================================================
//void Resources::pauseMusic() { this->m_music.pause(); }

//============================ private section ===============================
//============================== sets section ================================
void Resources::setBackgrounds() {
	std::unique_ptr<sf::Texture> texturesCreator;

	//adding game's backgrounds path
	texturesCreator = std::make_unique<sf::Texture>();

	this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
		(BACKGROUND, std::move(texturesCreator)));

	this->m_texture[BACKGROUND]->loadFromFile(BACKGROUND_PATH);
}
//============================================================================
void Resources::setLogos() {
	std::unique_ptr<sf::Texture> texturesCreator;
	texturesCreator = std::make_unique<sf::Texture>();
	this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
		(GAME_LOGO, std::move(texturesCreator)));
	this->m_texture[GAME_LOGO]->loadFromFile(GAME_LOGO_PATH);
}
//============================================================================
void Resources::setObjects() {

	std::unique_ptr<sf::Texture> texturesCreator;

    texturesCreator = std::make_unique<sf::Texture>();
    this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
                                   (STRAIGHT_PIPE_E, std::move(texturesCreator)));
    this->m_texture[STRAIGHT_PIPE_E]->loadFromFile(STRAIGHT_PIPE_PATH);

	texturesCreator = std::make_unique<sf::Texture>();
	this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
		(CORNER_PIPE_E, std::move(texturesCreator)));
	this->m_texture[CORNER_PIPE_E]->loadFromFile(CORNER_PIPE_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
                                   (T_PIPE_E, std::move(texturesCreator)));
    this->m_texture[T_PIPE_E]->loadFromFile(T_PIPE_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
                                   (PLUS_PIPE_E, std::move(texturesCreator)));
    this->m_texture[PLUS_PIPE_E]->loadFromFile(PLUS_PIPE_PATH);

//    texturesCreator = std::make_unique<sf::Texture>();
//    this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
//                                   (SQUARE, std::move(texturesCreator)));
//    this->m_texture[SQUARE]->loadFromFile(SQUARE_PATH);
//
//    texturesCreator = std::make_unique<sf::Texture>();
//    this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
//                                   (SQUARE, std::move(texturesCreator)));
//    this->m_texture[SQUARE]->loadFromFile(SQUARE_PATH);
//
//    texturesCreator = std::make_unique<sf::Texture>();
//    this->m_texture.insert(std::pair<int, std::unique_ptr <sf::Texture>>
//                                   (SQUARE, std::move(texturesCreator)));
//    this->m_texture[SQUARE]->loadFromFile(SQUARE_PATH);

}
//============================================================================
/*void Resources::setSounds() {
	//std::unique_ptr<sf::SoundBuffer> soundsCreator;

	soundsCreator = std::make_unique<sf::SoundBuffer>();
	this->m_soundBuffers.insert(std::pair<int, std::unique_ptr <sf::SoundBuffer>>
		(CLICK_SOUND, std::move(soundsCreator)));
	this->m_soundBuffers[CLICK_SOUND]->loadFromFile(CLICK_SOUND_PATH);
}*/
//============================ methods section ===============================
/*void Resources::playSound(int key) {
	m_sound.setBuffer(this->getSound(key));
	m_sound.play();
}*/
//============================================================================
