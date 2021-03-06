/*
 * =====================================================================================
 *
 *       Filename:  ServerLoadingState.cpp
 *
 *    Description:
 *
 *        Created:  12/01/2019 21:58:21
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/ApplicationStateStack.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "Config.hpp"
#include "GameState.hpp"
#include "ServerLoadingState.hpp"

ServerLoadingState::ServerLoadingState(Client &client) : m_client(client) {
	m_shader.createProgram();
	m_shader.addShader(GL_VERTEX_SHADER, "resources/shaders/basic.v.glsl");
	m_shader.addShader(GL_FRAGMENT_SHADER, "resources/shaders/basic.f.glsl");
	m_shader.linkProgram();

	m_text.setFont(gk::ResourceHandler::getInstance().get<gk::Font>("font-default"));
	m_text.setCharacterSize(8 * 6);
	m_text.setText("Loading world...");
	m_text.setColor(gk::Color::White);
	m_text.setPosition(SCREEN_WIDTH / 2.0 - m_text.getLocalBounds().width / 2.0, 200);

	m_textShadow.setFont(gk::ResourceHandler::getInstance().get<gk::Font>("font-default"));
	m_textShadow.setCharacterSize(8 * 6);
	m_textShadow.setText(m_text.text());
	m_textShadow.setColor(gk::Color{70, 70, 70, 255});
	m_textShadow.setPosition(m_text.getPosition().x + 6, m_text.getPosition().y + 6);
}

void ServerLoadingState::update() {
	if (m_hasBeenDrawn)
		m_stateStack->push<GameState>(m_client);
}

void ServerLoadingState::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.shader = &m_shader;
	target.setView(target.getDefaultView());
	target.draw(m_textShadow, states);
	target.draw(m_text, states);

	m_hasBeenDrawn = true;
}

