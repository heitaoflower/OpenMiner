/*
 * =====================================================================================
 *
 *       Filename:  TerrainGenerator.cpp
 *
 *    Description:
 *
 *        Created:  12/06/2018 22:47:04
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <glm/gtc/noise.hpp>

#include "Config.hpp"
#include "BlockType.hpp"
#include "ServerChunk.hpp"
#include "TerrainGenerator.hpp"
#include "World.hpp"

void TerrainGenerator::generate(ServerChunk &chunk) const {
	// basicGeneration(chunk);
	testCraftGeneration(chunk);
}

void TerrainGenerator::basicGeneration(ServerChunk &chunk) const {
	for(u8 z = 0 ; z < CHUNK_DEPTH ; z++) {
		for(u8 x = 0 ; x < CHUNK_WIDTH ; x++) {
			float n = noise2d((x + chunk.x() * CHUNK_WIDTH) / 256.0, (z + chunk.z() * CHUNK_DEPTH) / 256.0, 5, 0.5) * 4;
			float h = 10 + n * 2;

			for(u8 y = 0 ; y < CHUNK_HEIGHT ; y++) {
				if(y + chunk.y() * CHUNK_HEIGHT < h) {
					chunk.setBlockRaw(x, y, z, 1);
				} else {
					chunk.setBlockRaw(x, y, z, 0);
				}
			}
		}
	}
}

void TerrainGenerator::testCraftGeneration(ServerChunk &chunk) const {
	srand(1337);
	for(int z = 0 ; z < CHUNK_DEPTH ; z++) {
		for(int x = 0 ; x < CHUNK_WIDTH ; x++) {
			// Land height
			float n = noise2d((x + chunk.x() * CHUNK_WIDTH) / 256.0, (z + chunk.z() * CHUNK_DEPTH) / 256.0, 4, 0.5) * 4;
			float h = 10 + n * 2;

			// Land blocks
			for(int y = 0 ; y < CHUNK_HEIGHT ; y++) {
				// Are we above "ground" level?
				if(y + chunk.y() * CHUNK_HEIGHT >= h) {
					// if we are not yet up to sea level, fill with water blocks
					if(y + chunk.y() * CHUNK_HEIGHT < SEALEVEL) {
						chunk.setBlockRaw(x, y, z, BlockType::Water);
						continue;
					// Otherwise we are in the air
					} else {
						// A tree!
						if(chunk.getBlock(x, y - 1, z) == BlockType::Grass && (rand() % 256) == 0 && n < 4) {
							// Trunk
							h = (rand() & 0x3) + 3;
							for(int i = 0 ; i < h ; i++) {
								chunk.setBlockRaw(x, y + i, z, BlockType::Wood);

								chunk.lightmap().addSunlight(x, y + i, z, 15);
							}

							// Leaves
							for(int ix = -3 ; ix <= 3 ; ix++) {
								for(int iy = -3 ; iy <= 3 ; iy++) {
									for(int iz = -3 ; iz <= 3 ; iz++) {
										if(ix * ix + iy * iy + iz * iz < 8 + (rand() & 1) && !chunk.getBlock(x + ix, y + h + iy, z + iz)) {
											chunk.setBlockRaw(x + ix, y + h + iy, z + iz, BlockType::Leaves);

											chunk.lightmap().addSunlight(x + ix, y + h + iy, z + iz, 15);
										}
									}
								}
							}
						}
						else if(chunk.getBlock(x, y - 1, z) == BlockType::Grass && (rand() & 0xff) == 0) {
							chunk.setBlockRaw(x, y, z, BlockType::Flower);
							chunk.lightmap().addSunlight(x, y, z, 15);
						}
						else {
							chunk.lightmap().addSunlight(x, y, z, 15);
						}
						break;
					}
				}

				// Random value used to determine land type
				float r = noise3d_abs((x + chunk.x() * CHUNK_WIDTH) / 256.0, (y + chunk.y() * CHUNK_HEIGHT) / 256.0 + 16, (z + chunk.z() * CHUNK_DEPTH) / 256.0, 5, 0.5) * 4;

				// Sand layer
				if(n * 4 + r * 5 < 4) {
					chunk.setBlockRaw(x, y, z, BlockType::Sand);
				}
				// Dirt layer, but use grass blocks for the top
				else if(n + r * 5 < 6 * 8 && n * 10 + r * 5 > 30) {
					chunk.setBlockRaw(x, y, z, (h < SEALEVEL - 5 || y + chunk.y() * CHUNK_HEIGHT < h - 1) ? BlockType::Dirt : BlockType::Grass);
				}
				else {
					chunk.setBlockRaw(x, y, z, BlockType::Stone);
				}

				// Caves
				float n2 = noise2d((x + chunk.x() * CHUNK_WIDTH) / 256.0, (z + chunk.z() * CHUNK_DEPTH) / 256.0, 8, 0.3) * 4;
				float r2 = noise3d_abs((x + chunk.x() * CHUNK_WIDTH) / 512.0f, (y + chunk.y() * CHUNK_HEIGHT) / 512.0f, (z + chunk.z() * CHUNK_DEPTH) / 512.0f, 4, 0.1);
				float r3 = noise3d_abs((x + chunk.x() * CHUNK_WIDTH) / 512.0f, (y + chunk.y() * CHUNK_HEIGHT) / 128.0f, (z + chunk.z() * CHUNK_DEPTH) / 512.0f, 4, 1);
				float r4 = n2 * 5 + r2 * r3 * 20;
				if (r4 > 6 && r4 < 8) {
					chunk.setBlockRaw(x, y - 1, z, 0);
					chunk.setBlockRaw(x, y, z, 0);
					chunk.setBlockRaw(x, y + 1, z, 0);
				}
				else if (r < 0.3) {
					chunk.setBlockRaw(x, y, z, BlockType::CoalOre);
				}
				else if (r > 0.3 && r < 0.5) {
					chunk.setBlockRaw(x, y, z, BlockType::IronOre);
				}
				else if (r4 > 8.2 && r4 < 10) {
					chunk.setBlockRaw(x, y, z, BlockType::Stone);
				}
			}
		}
	}
}

float TerrainGenerator::noise2d(float x, float y, int octaves, float persistence) {
	float sum = 0;
	float strength = 1.0;
	float scale = 1.0;

	for(int i = 0 ; i < octaves ; i++) {
		sum += strength * glm::simplex(glm::vec2(x, y) * scale);
		scale *= 2.0;
		strength *= persistence;
	}

	return sum;
}

float TerrainGenerator::noise3d_abs(float x, float y, float z, int octaves, float persistence) {
	float sum = 0;
	float strength = 1.0;
	float scale = 1.0;

	for(int i = 0 ; i < octaves ; i++) {
		sum += strength * fabs(glm::simplex(glm::vec3(x, y, z) * scale));
		scale *= 2.0;
		strength *= persistence;
	}

	return sum;
}

