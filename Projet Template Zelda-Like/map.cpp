#include "map.h"
#include "game.h"

Map::Map() {}

void Map::loadMap(Player& player) {
	//sf::Texture wallTexture;
	//sf::Texture paveTexture;
	//wallTexture.loadFromFile("assets/wall.png");
	//paveTexture.loadFromFile("assets/pave.png");

	/*mapFile.clear();
	mapFile.seekg(0, mapFile.beg);
	line.clear();*/
	mapFile.open("assets/mapFile.txt");
	int y = 0;
	int yEnemy = 0;
	int yInteractables = 0;
	while (getline(mapFile, line)) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == '#') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("wall", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
			else if (line[i] == ' ') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
			//CHASER
			else if (line[i] == 'c') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				enemies.emplace_back(std::make_unique<ChaserEnemy>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			//PATROLLING
			else if (line[i] == 'p') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				enemies.emplace_back(std::make_unique<PatrollingEnemy>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			//SPEED POTION
			else if (line[i] == 'b') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				objects.emplace_back(std::make_shared<Bomb>((float)i * 50.f, (float)y * 50.f));
				yInteractables++;
			}
			//KEY
			else if (line[i] == 'k') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				if (/*player.key1 == false ||*/ player.lock1opened == false) {
					objects.emplace_back(std::make_shared<Key>("key1", (float)i * 50.f, (float)y * 50.f));
				}
				yInteractables++;
			}
			else if (line[i] == 'P') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("pnj", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
			//LOCK
			else if (line[i] == 'l') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				if (player.lock1opened == false) {
					mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
					mapObjects[y].emplace_back(std::make_unique<MapEntities>("lock", "lock1", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				}
			}
			else if (line[i] == '1') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("checkpoint", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
			}
		}
		y++;
	}
	y = 0;
	yEnemy = 0;
	yInteractables = 0;
	mapFile.close();
}