#include "game/Scene.h"


template<size_t rows, size_t cols>
CubeGroup Scene::createGroup(int bricks[rows][cols], float scale, glm::vec4 color) {
    CubeGroup group;
    float midX = (float) cols / 2, midY = (float) rows / 2;
    for (int m = 0; m < rows; m++) {
        for (int n = 0; n < cols; n++) {
            if (bricks[m][n] > 0) {
                Cube cube{cubeHandler.empty};
                cube.position = glm::vec3{scale * ((float) n - midX), scale * (midY - (float) m), 0};
                cube.scale = glm::vec3{scale, scale, scale};
                cube.color = color;
                cube.update();
                group.cubes.push_back(cube);
            }
        }
    }
    return group;
}

Scene::Scene() {
    // Setup the room
    CubeGroup floorGroup, wallGroup;
    for (int m = -ROOM_SIZE; m <= ROOM_SIZE; m++) {
        for (int n = -ROOM_SIZE; n <= ROOM_SIZE; n++) {
            if (abs(m) == ROOM_SIZE || (abs(n) == ROOM_SIZE)) {
                for (int y = 1; y < ROOM_HEIGHT && (y < 2 || n < ROOM_SIZE - 1); y++) {
                    Cube wall{cubeHandler.brick};
                    wall.position = glm::vec3{(float) m, y, (float) n};
                    wall.update();
                    wallGroup.cubes.push_back(wall);
                }
            } else {
                Cube floor{cubeHandler.brick};
                floor.position = glm::vec3{(float) m, 0, (float) n};
                floor.update();
                floorGroup.cubes.push_back(floor);
            }
        }
    }
    room.groups.push_back(std::make_shared<CubeGroup>(floorGroup));
    room.groups.push_back(std::make_shared<CubeGroup>(wallGroup));
    floorGroup.position = glm::vec3{0, ROOM_HEIGHT, 0};
    floorGroup.update();
    room.groups.push_back(std::make_shared<CubeGroup>(floorGroup));

    // Create the logo
    CubeGroup logoGroup = createGroup<7, 5>(logoBricks, 0.1f);
    logoGroup.pitch = 0.8f;
    logoGroup.position = glm::vec3{0, 0, 0.5};
    logoGroup.update();
    logo.groups.push_back(std::make_shared<CubeGroup>(logoGroup));
    logoGroup.yaw = glm::pi<float>();
    logoGroup.position = glm::vec3{0, 0, -0.5};
    logoGroup.update();
    logo.groups.push_back(std::make_shared<CubeGroup>(logoGroup));
    logoGroup.yaw = glm::pi<float>() / 2.0f;
    logoGroup.position = glm::vec3{0.5, 0, 0};
    logoGroup.update();
    logo.groups.push_back(std::make_shared<CubeGroup>(logoGroup));
    logoGroup.yaw = 3 * glm::pi<float>() / 2.0f;
    logoGroup.position = glm::vec3{-0.5, 0, 0};
    logoGroup.update();
    logo.groups.push_back(std::make_shared<CubeGroup>(logoGroup));
    logo.position = glm::vec3{0, 3, 0};
    logo.update();

    // Load the numbers
    for (int i = 0; i < 10; i++) {
        numbers[i] = createGroup<15, 15>(numberBricks[i], 0.08f);
        numbers[i].yaw = glm::pi<float>();
        numbers[i].update();
    }

    // Load the buttons
    playEnabled = createGroup<15, 15>(playBricks, 0.1f, glm::vec4{0, 1, 0, 1});
    playEnabled.yaw = glm::pi<float>();
    playEnabled.update();
    playDisabled = createGroup<15, 15>(playBricks, 0.1f);
    playDisabled.yaw = glm::pi<float>();
    playDisabled.update();
    stopEnabled = createGroup<15, 15>(stopBricks, 0.1f, glm::vec4{1, 0, 0, 1});
    stopDisabled = createGroup<15, 15>(stopBricks, 0.1f);

    // Create the display
    CubeGroup watch = createGroup<15, 15>(watchBricks, 0.1f);
    watch.position = glm::vec3{3, -0.8f, 0};
    watch.update();
    display.groups.push_back(std::make_shared<CubeGroup>(watch));
    CubeGroup skull = createGroup<15, 15>(skullBricks, 0.1f);
    skull.position = glm::vec3{3, 0.9f, 0};
    skull.update();
    display.groups.push_back(std::make_shared<CubeGroup>(skull));
    Cube screen{cubeHandler.empty};
    screen.scale = glm::vec3{9.0f, 4.0f, 0.1f};
    screen.color = glm::vec4{0.1f, 0.1f, 0.1f, 0.1f};
    screen.position = glm::vec3{0, 0, 0.5f};
    screen.update();
    display.cubes.push_back(screen);
    display.position = glm::vec3{0, 6, 10};
    display.pitch = -0.8;
    display.update();
    for (int i = 0; i < 3; i++) {
        time[i] = std::make_shared<CubeGroup>();
        time[i]->position = {1.0f - 1.0f * (float) i, -0.8f, 0};
        time[i]->update();
        time[i]->groups.push_back(std::make_shared<CubeGroup>(numbers[i]));
        display.groups.push_back(time[i]);
        score[i] = std::make_shared<CubeGroup>();
        score[i]->position = {1.0f - 1.0f * (float) i, 0.9f, 0};
        score[i]->update();
        score[i]->groups.push_back(std::make_shared<CubeGroup>(numbers[i]));
        display.groups.push_back(score[i]);
    }
    play = std::make_shared<CubeGroup>();
    play->position = {-3.0f, 0.9f, 0};
    play->groups.push_back(std::make_shared<CubeGroup>(playEnabled));
    play->update();
    display.groups.push_back(play);
    stop = std::make_shared<CubeGroup>();
    stop->position = {-3.0f, -0.8f, 0};
    stop->groups.push_back(std::make_shared<CubeGroup>(stopDisabled));
    stop->update();
    display.groups.push_back(stop);

    // Place the buttons
    playButton.position = glm::vec3{-3, 6.5f, 9};
    playButton.update();
    stopButton.position = glm::vec3{-3, 5.5f, 10.5f};
    stopButton.update();
}

bool Scene::intersects(const Cube &target, const ShotEvent &shotEvent) {
    // Calculate the angle
    glm::vec3 direct = target.position - shotEvent.start;
    double scalar = glm::dot(shotEvent.direction, direct);
    double alpha = acos((scalar) / (glm::length(shotEvent.direction) * glm::length(direct)));
    if (alpha > glm::pi<float>() / 2.0f) return false;

    // Calculate the direct distance
    double distance = glm::distance(shotEvent.start, target.position);

    // Calculate the minimum distance
    double minDistance = distance * sin(alpha);
    if (target.scale.x / 1.4f > minDistance) return true;
    return false;
}

void Scene::checkIntersections(const ShotEvent &shotEvent) {
    if (intersects(playButton, shotEvent)) {
        *play->groups[0] = playDisabled;
        *stop->groups[0] = stopEnabled;
        game.start();
    };
    if (intersects(stopButton, shotEvent)) {
        *play->groups[0] = playEnabled;
        *stop->groups[0] = stopDisabled;
        game.stop();
    };
    for (int i = 0; i < game.targets.size(); i++) {
        if (intersects(game.targets[i].target, shotEvent)) game.onHit(i);
    }
}

void Scene::updateDisplay(std::shared_ptr<CubeGroup> valueDisplay[3], int value) {
    if (value >= 0) {
        *valueDisplay[0]->groups[0] = numbers[value / 100];
        *valueDisplay[1]->groups[0] = numbers[(value % 100) / 10];
        *valueDisplay[2]->groups[0] = numbers[value % 10];
    } else {
        *play->groups[0] = playEnabled;
        *stop->groups[0] = stopDisabled;
    }
}

void Scene::update() {
    // Update the game
    game.update();

    // Update the displays
    updateDisplay(score, game.score);
    updateDisplay(time, game.time);

    // Draw the room
    cubeHandler.draw(room);
    cubeHandler.draw(display);

    // Draw the logo
    logo.yaw = (float) glfwGetTime();
    logo.update();
    cubeHandler.draw(logo);
}