/*
 * =====================================================================================
 *
 *       Filename:  ItemWidget.cpp
 *
 *    Description:
 *
 *        Created:  21/06/2018 01:11:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "ItemWidget.hpp"
#include "Registry.hpp"

ItemWidget::ItemWidget(Inventory &inventory, u16 x, u16 y, Widget *parent)
	: Widget(18, 18, parent), m_inventory(inventory), m_x(x), m_y(y)
{
	m_cube.setPosition(-12.7, -14.6, 0);
	// m_cube.setPosition(8.5, 14, 0);
	// m_cube.setRotation(-172, glm::vec3{0.42, -0.2, 1});

	m_image.load("texture-items");
	m_image.setPosition(1, 1, 0);
	m_image.setClipRect(0, 0, 0, 0);
}

void ItemWidget::update() {
	const u16 tileSize = 32;

	if (stack().item().isBlock())
		m_cube.updateVertexBuffer(Registry::getInstance().getBlock(stack().item().id()));
	else {
		m_image.setClipRect(stack().item().textureID() % 16 * tileSize, stack().item().textureID() / 16 * tileSize, tileSize, tileSize);
		m_image.setScale(16.0f / tileSize, 16.0f / tileSize);
	}

	m_text.setText(std::to_string(stack().amount()));
	m_text.setPosition(16 - 4 - 6 * floor(log10(stack().amount())), 16 - 6, 0);
}

void ItemWidget::setStack(const std::string &name, unsigned int amount) {
	m_inventory.setStack(m_x, m_y, name, amount);
	update();
}

void ItemWidget::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.transform *= getTransform();

	if (stack().item().isBlock() && stack().item().id())
		target.draw(m_cube, states);
	else if (stack().amount() >= 1)
		target.draw(m_image, states);

	if (stack().amount() != 1)
		target.draw(m_text, states);
}

