/*****************************************
** File:    Game.cpp
** Project: CMSC 202 Project 5, Fall 2021
** Author:  Jabril Hall
** Date:    12/6/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Game.h.
*/

#include "Game.h"

Game::Game(string f_fileName) {
    m_fileName = f_fileName;

}

Game::~Game() {
    for (Villain* & m_villain : m_villains) {
        delete m_villain;
    }

    for(Hero* hero: m_heroes){
        delete hero;
    }

}

void Game::LoadFile() {
    fstream file;
    file.open(m_fileName, ios::in);
    if(file.is_open()){
        string profession, name, desc, strHp, strCombat, strRarity;
        int hp, combat, rarity;

        while(getline(file, profession, '|')){
            getline(file, name, '|');
            getline(file, desc, '|');
            getline(file, strHp, '|');
            getline(file, strCombat, '|');
            getline(file, strRarity, '\n');

            hp = stoi(strHp);
            combat = stoi(strCombat);
            rarity = stoi(strRarity);

            if(profession == "HERO"){
                m_heroes.push_back(new Hero(name, desc, hp, combat, rarity));
            }else{
                m_villains.push_back(new Villain(name, desc, hp, combat, rarity));
            }
        }

        cout << "Heros loaded: " << m_heroes.size() <<" Villains Loaded:"<< m_villains.size() <<" Total Loaded:"\
        << m_heroes.size() + m_villains.size() << endl;


    } else {
        cout << "COULDN'T OPEN FILE" << endl;
    }
}

void Game::MainMenu() {

    int choice;
    cout << "What would you like to do?:\n"
            "1. See All Heroes\n"
            "2. See All Villains\n"
            "3. See Your Heroes\n"
            "4. Try to Acquire a New Hero\n"
            "5. Train a Hero\n"
            "6. Enter a Wizard Battle\n"
            "7. Exit" << endl;
    cin >> choice;

    while (choice != 7) {

        switch (choice) { // sets action
            case 1:
                PrintHeroes();
                break;
            case 2:
                PrintVillains();
                break;
            case 3:
                PrintMyHeroes();
                break;
            case 4:
                AcquireHero();
                break;
            case 5:
                TrainHero();
                break;
            case 6:
                Battle();
                break;
            default:
                cout << "That's not a choice" << endl;
        }

        cout << "What would you like to do?:\n"
                "1. See All Heroes\n"
                "2. See All Villains\n"
                "3. See Your Heroes\n"
                "4. Try to Acquire a New Hero\n"
                "5. Train a Hero\n"
                "6. Enter a Wizard Battle\n"
                "7. Exit" << endl;
        cin >> choice;
    }
}

void Game::PrintHeroes() {
    for(Hero* &hero: m_heroes){
        cout << *hero << endl;
    }
}

void Game::PrintVillains() {
    for(Villain* & m_villain : m_villains){
        cout << *m_villain << endl;
    }
}

void Game::PrintMyHeroes() {
    if(m_myHeroes.size() == 0){
        cout << "You have no heroes yet! You should try to acquire some first!" << endl;
        return;
    }

    m_myHeroes.Display();

}

void Game::AcquireHero() {
    if(m_myHeroes.size() >= MAX_HEROES){
        cout << "You have enough heros try battling some villians" << endl;
        return;
    }
    int choice;
    cout << "How rare of a wizard would you like to recruit?: \n"
         "1. Very Common (Very High Probability)\n"
         "2. Common (High Probability)\n"
         "3. Uncommon (Normal Probability)\n"
         "4. Rare (Low Probability)\n"
         "5. Ultra Rare (Extremely Low Probability)" << endl;
    cin >> choice;

    while(choice > 5 || choice < 1){
        cin.clear();
        cout << "How rare of a wizard would you like to recruit?: \n"
                "1. Very Common (Very High Probability)\n"
                "2. Common (High Probability)\n"
                "3. Uncommon (Normal Probability)\n"
                "4. Rare (Low Probability)\n"
                "5. Ultra Rare (Extremely Low Probability)" << endl;
        cin >> choice;
    }


    FoundHero(choice-1);

}

void Game::FoundHero(int rarity) {
    int randomNumber = (rand() % 100) + 1;
    int percentage = RARITY[rarity];
    if (randomNumber > percentage){
        cout << "No one was willing to join your team" << endl;
        return;
    }
    for(Hero* hero: m_heroes){
        bool inlist = false;
        for (int i = 0; i < m_myHeroes.size(); ++i) {
            if(hero->GetName() == m_myHeroes.operator[](i)->GetName()){
                inlist = true;
            }
        }
        if(hero->GetRarity() == rarity+1 && !inlist){
            m_myHeroes.Push(hero);
            cout << hero->GetName() << " agreed to join your group";
            break;
        }
    }
}

void Game::TrainHero() {
    if(m_myHeroes.size() == 0){
        cout << "You dont have any heros to train" << endl;
        return;
    }

    if(m_myHeroes.size() == 1){
        m_myHeroes.operator[](0)->Train();
        return;
    }

    int choice;
    cout << "Who do you want to train?" << endl;
    m_myHeroes.Display();
    cin >> choice;

    while(choice > m_myHeroes.size()){
        cin.clear();
        cout << "Who do you want to train?" << endl;
        m_myHeroes.Display();
        cin >> choice;
    }

    m_myHeroes.operator[](choice-1)->Train();
}

void Game::Battle() {
    PrepareVillains();
    PrepareHeroes();

    cout << SEP << endl;
    cout << "The battle begins:" << endl;

    ResolveBattle();

    m_bVillains.Clear();
    m_bHeroes.Clear();

}

void Game::PrepareVillains() {
    int choice;
    cout << "How many villians do you want to fight" << endl;
    cin >> choice;

    while(choice > MAX_VILLAINS || choice < 1){
        cin.clear();
        cout << "How many villians do you want to fight" << endl;
        cin >> choice;
    }

    for (int i = 0; i < choice; ++i){
        int randomVillainNumber = (rand() % m_villains.size()) + 1;
        Villain* vil = m_villains[randomVillainNumber];
        Villain* newVillain = new Villain(vil->GetName(), vil->GetDesc(),
                                          vil->GetHp(), vil->GetCombat(), vil->GetRarity());
        m_bVillains.Push(newVillain);
        delete newVillain;
    }

    cout << SEP << "\nThe enemy wizards stand ready to battle" << endl;
    m_bVillains.Display();
    cout << SEP << endl;
}

void Game::PrepareHeroes() {

    cout << SEP << endl;
    cout << "Add from 1 to 5 heroes to your battle roster\n"
            "Enter -1 when done" << endl;
    m_myHeroes.Display();

    int choice;
    cin >> choice;
    int numWizards = 0;
    while(choice != -1 && numWizards <= MAX_HEROES){
        if (choice > m_myHeroes.size() || choice < -1)
            continue;

        Hero* hero = m_myHeroes.operator[](choice-1);
        Hero* newHero = new Hero(hero->GetName(), hero->GetDesc(),
                                 hero->GetHp(), hero->GetCombat(), hero->GetRarity());
        m_bHeroes.Push(newHero);
        delete newHero;
        numWizards++;


        cout << SEP << endl;
        cout << "Add from 1 to 5 heroes to your battle roster\n"
                "Enter -1 when done" << endl;
        m_myHeroes.Display();
        cin >> choice;

    }

    cout << SEP << "\nThe hero wizards stand ready to battle" << endl;
    m_bHeroes.Display();
    cout << SEP << endl;
}

void Game::ResolveBattle() {
    while (!m_bHeroes.IsEmpty() && !m_bVillains.IsEmpty()){
        int totalHpBars = 15;
        char bar = '-';
        int numHeroHpBars = totalHpBars;
        int numVilHpBars =  totalHpBars;
        Hero* hero = m_bHeroes.Front();
        Villain* villain = m_bVillains.Front();
        double heroTotalHP = hero->GetHp();
        double vilTotalHP = villain->GetHp();
        cout << SEP << endl;
        cout << *m_bHeroes.Front() << " vs " << *m_bVillains.Front() << ": " << endl;

        while (hero->GetHp() > 0 && villain->GetHp() > 0){
            cout << hero->GetName() << "\n HP| " << hero->GetHp() << "/" << heroTotalHP << string(numHeroHpBars, bar) <<\
            string(15-numHeroHpBars, ' ') <<" |" << endl;
            cout << villain->GetName() << "\n HP| " << villain->GetHp() << "/" << vilTotalHP << string(numVilHpBars, bar) << \
            string(15-numVilHpBars, ' ')<< " |" << endl;

            cout << endl;

            hero->Attack();
            villain->SetHp(villain->GetHp() - hero->GetCombat());
            numVilHpBars = (int) ((villain->GetHp() / vilTotalHP) * totalHpBars);

            if(villain->GetHp() <= 0)
                break;

            cout << hero->GetName() << "\n HP| " << hero->GetHp() << "/" << heroTotalHP << string(numHeroHpBars, bar) <<\
            string(15-numHeroHpBars, ' ') <<" |" << endl;
            cout << villain->GetName() << "\n HP| " << villain->GetHp() << "/" << vilTotalHP << string(numVilHpBars, bar) << \
            string(15-numVilHpBars, ' ')<< " |" << endl;

            cout << endl;

            villain->Attack();
            hero->SetHp(hero->GetHp() - villain->GetCombat());
            numHeroHpBars = (int) ((hero->GetHp() / heroTotalHP) * totalHpBars);

            if(hero->GetHp() <= 0)
                break;
        }

        cout << hero->GetName() << "\n HP| " << hero->GetHp() << "/" << heroTotalHP << string(numHeroHpBars, bar) <<\
            string(15-numHeroHpBars, ' ') <<" |" << endl;
        cout << villain->GetName() << "\n HP| " << villain->GetHp() << "/" << vilTotalHP << string(numVilHpBars, bar) << \
            string(15-numVilHpBars, ' ')<< " |" << endl;

        if(hero->GetHp() <= 0){
            cout << hero->GetName() << " has been defeated" << endl;
            m_bHeroes.Pop();
        }else if (villain->GetHp() <= 0){
            cout << villain->GetName() << " has been defeated" << endl;
            m_bVillains.Pop();
        }

    }

    if (m_bHeroes.IsEmpty()){
        cout << "The villians win" << endl;
    } else {
        cout << "The Heros win" << endl;
    }
}