/*
 * =====================================================================================
 *
 *       Filename:  InventoryWidget.hpp
 *
 *    Description:
 *
 *        Created:  21/06/2018 01:08:40
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INVENTORYWIDGET_HPP_
#define INVENTORYWIDGET_HPP_

#include <gk/graphics/RectangleShape.hpp>

#include "MouseItemWidget.hpp"

class Client;

class InventoryWidget : public Widget {
	public:
		InventoryWidget(Client &client, Widget *parent = nullptr)
			: Widget(parent), m_client(client) {}

		void init(Inventory &inventory, unsigned int offset = 0, unsigned int size = 0);

		void onMouseEvent(const SDL_Event &event, MouseItemWidget &mouseItemWidget, bool isReadOnly = false);

		const ItemWidget *currentItemWidget() const { return m_currentItemWidget; }

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		Client &m_client;

		Inventory *m_inventory = nullptr;

		u16 m_inventoryWidth = 0;
		u16 m_inventoryHeight = 0;

		std::vector<ItemWidget> m_itemWidgets;
		ItemWidget *m_currentItemWidget = nullptr;

		gk::RectangleShape m_selectedItemBackground{16, 16, gk::Color{255, 255, 255, 80}};
};

#endif // INVENTORYWIDGET_HPP_
