#include "map.h"
#include "game.h"

Map::Map() {}

void Map::loadMap() {
	sf::Texture wallTexture;
	sf::Texture paveTexture;
	wallTexture.loadFromFile("assets/wall.png");
	paveTexture.loadFromFile("assets/pave.png");

	/*mapFile.clear();
	mapFile.seekg(0, mapFile.beg);
	line.clear();*/
	mapFile.open("assets/mapFile.txt");
	int y = 0;
	int yEnemy = 0;
	int yInteractables = 0;
	while (getline(mapFile, line)) {
		for (int i = 0; i < 24; i++) {
			if (line[i] == '#') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("wall", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
			else if (line[i] == ' ') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
			else if (line[i] == 'l') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("lock", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
			else if (line[i] == 'c') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));

				enemies.emplace_back(std::vector<std::unique_ptr<Enemy>>());
				enemies[yEnemy].emplace_back(std::make_unique<ChaserEnemy>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			else if (line[i] == 'p') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				enemies.emplace_back(std::vector<std::unique_ptr<Enemy>>());
				enemies[yEnemy].emplace_back(std::make_unique<PatrollingEnemy>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			else if (line[i] == 's') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				objects.emplace_back(std::vector<std::unique_ptr<Interactable>>());
				objects[yInteractables].emplace_back(std::make_unique<Potion>((float)i * 50.f, (float)y * 50.f));
				yInteractables++;
			}
			else if (line[i] == 'k') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				objects.emplace_back(std::vector<std::unique_ptr<Interactable>>());
				objects[yInteractables].emplace_back(std::make_unique<Key>((float)i * 50.f, (float)y * 50.f));
				yInteractables++;
			}
		}
		y++;
	}
	y = 0;
	yEnemy = 0;
	yInteractables = 0;
	mapFile.close();
}