mod:block {
	id = "",
	name = "Air",
	texture = 0,
}

mod:block {
	id = "dirt",
	name = "Dirt",
	-- texture = 37, -- Vanilla
	texture = 102, -- Faithful 32x
}

mod:block {
	id = "cobblestone",
	name = "Cobblestone",
	-- texture = 38, -- Vanilla
	texture = 103, -- Faithful 32x
	hardness = 2,
	harvest_requirements = 1,
}

mod:block {
	id = "grass",
	name = "Grass",
	-- texture = 226, -- Vanilla
	texture = 219, -- Faithful 32x
	item_drop = {
		id = mod:id()..":dirt",
		amount = 1
	}
}

mod:block {
	id = "leaves",
	name = "Leaves",
	-- texture = 266, -- Vanilla
	texture = 2, -- Faithful 32x
	hardness = 0.5,
}

mod:block {
	id = "wood",
	name = "Wood",
	-- texture = 277, -- Vanilla
	texture = 330, -- Faithful 32x
	hardness = 2
}

mod:block {
	id = "stone",
	name = "Stone",
	-- texture = 402, -- Vanilla
	texture = 457, -- Faithful 32x
	hardness = 1.5,
	harvest_requirements = 1,
	item_drop = {
		id = mod:id()..":cobblestone",
		amount = 1
	},
}

mod:block {
	id = "sand",
	name = "Sand",
	-- texture = 369, -- Vanilla
	texture = 437, -- Faithful 32x
}

mod:block {
	id = "water",
	name = "Water",
	-- texture = 457, -- Vanilla
	texture = 500, -- Faithful 32x
}

mod:block {
	id = "glass",
	name = "Glass",
	-- texture = 168, -- Vanilla
	texture = 209, -- Faithful 32x
}

mod:block {
	id = "ore_coal",
	name = "Coal Ore",
	-- texture = 36, -- Vanilla
	texture = 101, -- Faithful 32x
	hardness = 3,
	harvest_requirements = 1,
	item_drop = {
		id = mod:id()..":coal",
		amount = 1
	},
}

mod:block {
	id = "planks",
	name = "Planks",
	-- texture = 316, -- Vanilla
	texture = 332, -- Faithful 32x
}

mod:block {
	id = "glowstone",
	name = "Glowstone",
	-- texture = 218, -- Vanilla
	texture = 211, -- Faithful 32x
}

dofile("mods/workbench.lua")
dofile("mods/furnace.lua")

mod:block {
	id = "ore_iron",
	name = "Iron Ore",
	-- texture = 254, -- Vanilla
	texture = 251, -- Faithful 32x
	hardness = 3,
	harvest_requirements = 1,
}

mod:block {
	id = "slab_planks",
	name = "Plank Slab",
	-- texture = 316, -- Vanilla
	texture = 332, -- Faithful 32x
}

mod:block {
	id = "flower",
	name = "Flower",
	-- texture = 150, -- Vanilla
	texture = 129, -- Faithful 32x
	hardness = 0.05,
	draw_type = 1,
}

for i = 18, 31 do
	mod:block {
		id = "undefined" .. i,
		name = "Undefined",
		texture = 4,
	}
end

