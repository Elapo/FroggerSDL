//
// Created by Frederik on 29/02/2016.
//

#include <cstdlib>
#include <time.h>
#include "GameObject.h"
#include "keyNames.h"
#include <sstream>
#include <iostream>
#include <cmath>

namespace game_Core {
    GameObject::GameObject(AbstractFactory *AF, settings* s) {
        aFact = AF;
        this->s = s;
    }

    GameObject::~GameObject() {
        delete(player);
        aFact->close();
        delete (aFact);
        delete (regulator);
        entities.clear();
    }

    int GameObject::init() {
        srand(time(0));
        //init vars
        currEnemies = 0;
        level = 1;
        score = 0;
        enemySpeed = 0.1;
        pickupSpeed = 0.15;
        ammo = 10;

        if (aFact->init() != 1) {
            return 0;
        }
        player = aFact->createPlayer();
        entities.push_back(player);
        regulator = aFact->createFPSRegulator(120);
        spawnCars(6);
        updateText();
        return 1;
    }

    int GameObject::loop() {
        int type, input = 0;
        bool paused = false;
        //int counter = 0;
        start = clock();
        elapsed = 0;
        Entity * e;
        while (!quit) {
            current = clock();
            elapsed = (current - start)/CLOCKS_PER_SEC;
            updateText();
            if (!paused) {
                //Print DEBUG Info
                /*if (counter < 120) {
                    counter++;
                }
                else {
                    counter = 0;
                    for (unsigned int i = 0; i < entities.size(); i++) {
                        cout << "Entity " << i << ", Type: " << entities.at(i)->getType() << ", pos:" <<
                        entities.at(i)->getXco() << ", " << entities.at(i)->getYco() <<
                        "\n";
                    }
                    cout << "\n";
                }*/
                //End debug info
                regulator->startCap();
                aFact->update();
                for (unsigned int i = 0; i < entities.size(); i++) {
                    e = entities.at(i);
                    e->Draw();
                    type = e->getType();//0: car, 1:Player, 2:HP up, 3 ammo up, 4 bullet, 5 expiredBullet
                    if (type != 1 && type != 4 && type != 5) {
                        if (type == 0) {
                            e->move(enemySpeed, 0);
                        }
                        else {
                            e->move(pickupSpeed, 0);
                        }

                        if (e->getYco() > 3 && e->getXco() < -10) {
                            e->setCo(110, e->getYco());
                        }
                        else if (e->getYco() <= 3 && e->getXco() > 110) {
                            e->setCo(-10, e->getYco());
                        }
                    }
                    else if (type == 4) {//projectile
                        e->move(0, -0.4f);
                        int col = checkParticleCollision(e);
                        if(col != -1){
                            entities.erase(entities.begin()+i);
                            if(col > i){
                                entities.erase(entities.begin()+(col-1));
                                i-=1;
                            }
                            else{
                                entities.erase(entities.begin()+col);
                                i-=2;
                            }
                        }
                    }
                    else if (type == 5)//expiredParticle
                    {
                        entities.erase(entities.begin() + i);
                    }

                    if (type != 1 && type != 5 && checkCollision(e, player)) {
                        if (type == 0) { //if it's a car, kill player
                            killPlayer();
                            player->rumble(500);
                            break; //break from loop to delete cars, if we don't break we'll have a MAV in trying to access vector.
                        }
                        else if (type == 2) {//healthpack
                            lives++;
                            updateText();
                            entities.erase(entities.begin() + i);
                            aFact->playFX(2);
                        }
                        else if (type == 3) {
                            ammo++;
                            updateText();
                            entities.erase(entities.begin() + i);
                        }
                    }
                }
                aFact->endUpdate();
                regulator->cap();
                if (player->getYco() == 0) {
                    levelUp();
                }
            }
            input = player->getInput();
            switch (input) {
                case KEY_NONE:
                    break;
                case KEY_UP://up
                    if (!paused) {
                        player->move(0, -1);
                        aFact->playFX(1);
                        player->rumble(75);
                    }
                    break;
                case KEY_DOWN://down
                    if (!paused)player->move(0, 1);
                    player->rumble(75);
                    break;
                case KEY_LEFT://left
                    if (!paused)player->move(-2, 0);
                    break;
                case KEY_RIGHT://right
                    if (!paused)player->move(2, 0);
                    break;
                case KEY_QUIT:
                    quit = true;
                    break;
                case KEY_SPACE:
                    if (ammo > 0) {
                        entities.push_back(player->Shoot());
                        ammo--;
                        updateText();
                    }
                    break;
                case KEY_ENTER:
                    paused = !paused;
                    player->rumble(250);
                    updateText();
                default:
                    break;
            }
        }
        return 0;
    }
    int GameObject::checkParticleCollision(Entity *particle) {
        int approxLane = (int)ceil(particle->getYco()/s->getSettings()->gridSize);
        for(unsigned int i = 0; i < entities.size(); i++){
            Entity* temp = entities.at(i);
            if(temp->getYco() == approxLane){
                if(temp->getType() == 0) {
                    if (particle->getYco() < 4 && (particle->getXco() > temp->getXco() && particle->getXco() < temp->getXco() + 15)) {
                        return i;
                    }
                    else if (particle->getXco() > temp->getXco()  && particle->getXco() < temp->getXco() + 15) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }
    bool GameObject::checkCarOverlap(Entity *e, Entity *p) {
        if (e->getYco() == p->getYco()) {
            if (e->getYco() < 4) {
                return e->getXco() > p->getXco() - 17 && e->getXco() < p->getXco() + 15;
            }
            else {
                return e->getXco() > p->getXco() - 17 && e->getXco() < p->getXco() + 15;
            }
        }
        return false;
    }
    bool GameObject::checkCollision(Entity *e, Entity *p) {
        if (e->getType() == 0) {
            if (e->getYco() == p->getYco()) {
                if (e->getYco() < 4) {
                    return e->getXco() > p->getXco() - 14 && e->getXco() < p->getXco() + 8;
                }
                else {
                    return e->getXco() > p->getXco() - 14 && e->getXco() < p->getXco() + 6;
                }
            }
            return false;
        }
        else{
            if (e->getYco() == p->getYco()) {
                if (e->getYco() < 4) {
                    return e->getXco() > p->getXco() - 8 && e->getXco() < p->getXco() + 4;
                }
                else {
                    return e->getXco() > p->getXco() - 8 && e->getXco() < p->getXco() + 4;
                }
            }
            return false;
        }
    }

    void GameObject::updateText() {
        ostringstream oss;
        oss << "Score: " << score << " - Lives: " << lives << " - Ammo: " << ammo << " - Level: " << level <<
        " - HighScore: " << s->getUserData()->highScore << " - Time: " << elapsed;
        string scoreText = oss.str();
        aFact->renderText(0.0f, (s->getSettings()->gridSize - 1), 100.0f, 1, scoreText);
    }

    void GameObject::killPlayer() {
        lives--;
        player->setCo(50, s->getSettings()->gridSize - 2);
        if (lives <= 0) {
            if (score > s->getUserData()->highScore) {
                s->getUserData()->highScore = score;
            }
            if (level > s->getUserData()->highScore_level) {
                s->getUserData()->highScore_level = level;
            }
            level = 1;
            score = 0;
            lives = 3;
            ammo = 10;
            while (entities.back()->getType() != 1) {
                entities.pop_back();
            }
            currEnemies = 0;
            enemySpeed = 0.1;
            spawnCars(6);
        }
        updateText();
    }

    void GameObject::levelUp() {
        level++;
        score += level + lives * 10 - floor(elapsed/10);
        player->setCo(50, s->getSettings()->gridSize - 2);
        resetEnemies();
        if (currEnemies < 30) { //prevent ridiculous amounts
            spawnCars(3);
            enemySpeed += 0.02;
        }
        else {
            enemySpeed += 0.01; //for more longevity
        }
        start = clock();
        updateText();
        aFact->playFX(3);
    }

    void GameObject::resetEnemies() {
        int t;
        for (int i = 0; i < entities.size(); i++) {
            t = entities.at(i)->getType();
            if (!t) {
                setEnemyRandomPos(entities.at(i));
            }
            else if (t == 2 || t == 3) {
                entities.erase(entities.begin() + i);
            }
        }
        removeCarOverlap();
    }

    void GameObject::setEnemyRandomPos(Entity *e) {
        int newLane = getLane();
        int newX = getRandomX();
        if (newLane > 3) {
            newLane++;
        }
        else {
            if (newX > 100) {
                newX = (newX - 100) * -1;
            }
        }
        if ((newLane > 3 && e->getYco() <= 3) || (newLane <= 3 && e->getYco() > 3)) {
            e->flip();
        }
        e->setCo(newX, newLane);
    }

    int GameObject::getRandomX() {
        //random between 20-70
        return rand() % 100;//make this bigger and use different offsets when starting or respawning;
    }

    int GameObject::getLane() {
        int lane = rand() % 6 + 1; //random between 1 and 6
        return lane;
    }

    void GameObject::spawnCars(int amount) {
        int r = getRandomX();
        if (r < 5) {
            entities.push_back(aFact->createHealthPack(1));
            setEnemyRandomPos(entities.back());
        }
        else if (r > 95) {
            entities.push_back(aFact->createAmmoPack(1));
            setEnemyRandomPos(entities.back());
        }
        currEnemies += amount;
        for (int i = 0; i < amount; i++) {
            entities.push_back(aFact->createEnemy(1));
            setEnemyRandomPos(entities.back());
        }
        removeCarOverlap();
    }

    void GameObject::removeCarOverlap() {
        unsigned int j = 0;
        int tempX;
        for(int p= 0; p < 2; p++) {
            for (unsigned int i = 1; i < entities.size(); i++) {
                while (j < entities.size()) {
                    if (j != i && checkCarOverlap(entities.at(i), entities.at(j))) {
                        tempX = entities.at(i)->getXco();
                        tempX += 25;
                        entities.at(i)->setCo(tempX, entities.at(i)->getYco());
                    }
                    else {
                        j++;
                    };
                }
                j = 0;
            }
        }
    }
}

