"""
File:    pyopoly.py
Author:  Jabril Hall
Date:    10/27/2020
Section: 53
E-mail:  jhall14@umbc.edu
Description:
  make simple monopoly
"""

from sys import argv
from random import randint, seed
from board_methods import load_map, display_board

if len(argv) >= 2:
    seed(argv[1])


def initiate_players(num_players, base_money):
    players = {}
    for i in range(num_players):
        string = "Player number " + str(i + 1) + ", what is your name? "
        name = input(string)
        player = {
            'symbol': input("what symbol do you want your character to use? "),
            'money': base_money,
            'properties_owned': {},
            'position': 0
        }
        players[name] = player
    return players


def play_turn(player, places, players, go_money):
    roll = randint(1, 6) + randint(1, 6)
    pass_go = False
    is_bankrupt = False
    if players[player]["position"] + roll < len(places):
        players[player]["position"] += roll
    else:
        players[player]["position"] += roll
        players[player]["position"] -= len(places) - 1
        pass_go = True

    place = places[players[player]["position"]]
    display_board(format_display(players, places))
    print(player + ", you rolled a " + str(roll))
    print(player, "you landed on", place["Place"])
    if pass_go:
        print("You passed go and earned", go_money)
        players[player]["money"] += go_money

    for i in players:
        if place["Place"] in players[i]["properties_owned"]:
            if not player == i:
                if players[i]["properties_owned"][place["Place"]]["building"]:
                    print(i, "owns this property and owns a building. You have payed them", place['BuildingRent'],
                          "dollars")
                    players[player]["money"] -= int(place['BuildingRent'])
                    players[i]["money"] += int(place['BuildingRent'])
                else:
                    print(i, "owns this property. You have payed them", place['Rent'], "dollars")
                    players[player]["money"] -= int(place['Rent'])
                    players[i]["money"] += int(place['Rent'])
        if players[i]["money"] < 0:
            is_bankrupt = True

    if is_bankrupt:
        choice = '5'
    else:
        choice = input("\t1) Buy Property\n\t2) Get Property Info\n\t3) Get Player Info\n\t4) Build a "
                       "Building\n\t5) End Turn\n\t \n\tWhat do you want do?\n ")

    while not choice == '5':
        if choice == '1':
            buy_property(player, players, places)
        elif choice == '2':
            get_property_info(places, players)
        elif choice == '3':
            get_player_info(players)
        elif choice == '4':
            build_building(player, players, places)
        choice = input("\t1) Buy Property\n\t2) Get Property Info\n\t3) Get Player Info\n\t4) Build a "
                       "Building\n\t5) End Turn\n\t \n\tWhat do you want do?\n ")


def build_building(player, players, places):
    available_places = []
    for i in players[player]['properties_owned']:
        for j in range(len(places)):
            if i == places[j]["Place"] and not players[player]["properties_owned"][i]["building"]:
                print(places[j]["Place"], places[j]["Abbrev"], places[j]["BuildingCost"])
                available_places.append(places[j]["Place"])
                available_places.append(places[j]["Abbrev"])

    choice = input("Which property do you want to build a building on? ")
    if choice in available_places:
        for i in range(len(places)):
            if choice == places[i]["Place"] or choice == places[i]["Abbrev"]:
                players[player]['properties_owned'][places[i]["Place"]]["building"] = True
                print("You have built the building for", places[i]["Place"])
    else:
        print("The property either has a building, isn't yours, or doesn't exist")


def format_display(players, places):
    formatted_list = []
    for i in range(len(places)):
        symbol = ''
        for player in players:
            if players[player]["position"] == i:
                symbol += players[player]["symbol"]
        formatted_string = places[i]['Abbrev'] + "\n" + symbol.ljust(5)
        formatted_list.append(formatted_string)
    return formatted_list


def get_property_info(places, players):
    place_name = input("For which property do you want to get the information? ")
    inlist = False
    place = {}
    owned = "Bank"
    building = 'No'
    for i in range(len(places)):
        if place_name == places[i]["Place"] or place_name == places[i]["Abbrev"]:
            inlist = True
            place = places[i]

    if inlist:
        for i in players:
            if place["Place"] in players[i]["properties_owned"]:
                owned = i
                if players[i]["properties_owned"][place["Place"]]["building"]:
                    building = "Yes"
        print("\t\t" + place["Place"])
        print("\t\tPrice:", place["Price"])
        print("\t\tOwned:", owned)
        print("\t\tBuilding:", building)
        print("\t\tRent:", place["Rent"] + ",", place["BuildingRent"] + " (with building)")


def get_player_info(players):
    print("The players are:")
    for i in players:
        print("\t", i)
    player = input("Which player do you wish to know about? ")
    for i in players:
        if player == i:
            print()
            print("Player Name:", i)
            print("Player Symbol", players[i]['symbol'])
            print("Current Money:", players[i]['money'])
            print()
            print("Properties:")
            print()
            if bool(players[i]["properties_owned"]):
                for j in players[i]["properties_owned"]:
                    print("\t", j, "with building:", players[i]["properties_owned"][j]["building"])
            else:
                print("\tno properties")
            print()


def play_game(starting_money, pass_go_money, board_file, num_players):
    players_playing = initiate_players(num_players, starting_money)
    quit_loop = False

    while not quit_loop:
        for single_player in players_playing:
            if not quit_loop:
                play_turn(single_player, board_file, players_playing, pass_go_money)

            if players_playing[single_player]['money'] < 0:
                print(single_player, "is bankrupt the game ends")
                quit_loop = True


def buy_property(player, players, places):
    bought = False
    place = places[players[player]["position"]]
    for i in players:
        if place["Place"] in players[i]["properties_owned"]:
            bought = True
            if player == i:
                print("You already own this property")
            else:
                print(i, "already owns this property")
    if int(place["Price"]) < 0:
        bought = True
        print(place["Place"] + " cannot be bought")
    if not bought:
        confirmation = input("The property is unowned, do you want to buy it? ")
        if confirmation.lower() == "y" or "yes":
            if players[player]["money"] >= int(place["Price"]):
                players[player]["properties_owned"][place["Place"]] = {'building': False}
                players[player]["money"] -= int(place["Price"])
                print("You have bought", place['Place'])
            else:
                print("You dont have enough money to buy " + place["Place"])


if __name__ == "__main__":
    base_money_val = 1500
    money_pass_go = 200
    num_players_val = 2
    # num_players_val = int(input("How many players? 1-5 "))
    while not 1 <= num_players_val <= 5:
        print("please put a number between 1 and 5")
        num_players_val = int(input("How many players? 1-5 "))
    places_file = load_map("proj1_board1.csv")
    play_game(base_money_val, money_pass_go, places_file, num_players_val)
