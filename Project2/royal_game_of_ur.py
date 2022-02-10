"""
File:         royal_game_of_ur.py
Author:       Jabril Hall
Date:         11/13/2020
Section:      53
E-mail:       jhall14@umbc.edu
Description:  Play the royal game
"""

from sys import argv
from random import choice
from board_square_starter import BoardSquare, UrPiece


class RoyalGameOfUr:
    STARTING_PIECES = 7

    def __init__(self, board_file_name):
        self.board = None
        self.load_board(board_file_name)

    def load_board(self, board_file_name):
        """
        This function takes a file name and loads the map, creating BoardSquare objects in a grid.

        :param board_file_name: the board file name
        :return: sets the self.board object within the class
        """

        import json
        try:
            with open(board_file_name) as board_file:
                board_json = json.loads(board_file.read())
                self.num_pieces = self.STARTING_PIECES
                self.board = []
                for x, row in enumerate(board_json):
                    self.board.append([])
                    for y, square in enumerate(row):
                        self.board[x].append(BoardSquare(x, y, entrance=square['entrance'], _exit=square['exit'],
                                                         rosette=square['rosette'], forbidden=square['forbidden']))

                for i in range(len(self.board)):
                    for j in range(len(self.board[i])):
                        if board_json[i][j]['next_white']:
                            x, y = board_json[i][j]['next_white']
                            self.board[i][j].next_white = self.board[x][y]
                        if board_json[i][j]['next_black']:
                            x, y = board_json[i][j]['next_black']
                            self.board[i][j].next_black = self.board[x][y]
        except OSError:
            print('The file was unable to be opened. ')

    def draw_block(self, output, i, j, square):
        """
        Helper function for the display_board method
        :param output: the 2d output list of strings
        :param i: grid position row = i
        :param j: grid position col = j
        :param square: square information, should be a BoardSquare object
        """
        MAX_X = 8
        MAX_Y = 5
        for y in range(MAX_Y):
            for x in range(MAX_X):
                if x == 0 or y == 0 or x == MAX_X - 1 or y == MAX_Y - 1:
                    output[MAX_Y * i + y][MAX_X * j + x] = '+'
                if square.rosette and (y, x) in [(1, 1), (1, MAX_X - 2), (MAX_Y - 2, 1), (MAX_Y - 2, MAX_X - 2)]:
                    output[MAX_Y * i + y][MAX_X * j + x] = '*'
                if square.piece:
                    # print(square.piece.symbol)
                    output[MAX_Y * i + 2][MAX_X * j + 3: MAX_X * j + 5] = square.piece.symbol

    def display_board(self):
        """
        Draws the board contained in the self.board object

        """
        if self.board:
            output = [[' ' for _ in range(8 * len(self.board[i // 5]))] for i in range(5 * len(self.board))]
            for i in range(len(self.board)):
                for j in range(len(self.board[i])):
                    if not self.board[i][j].forbidden:
                        self.draw_block(output, i, j, self.board[i][j])

            print('\n'.join(''.join(output[i]) for i in range(5 * len(self.board))))

    def roll_d4_dice(self, n=4):
        """
        Keep this function as is.  It ensures that we'll have the same runs with different random seeds for rolls.
        :param n: the number of tetrahedral d4 to roll, each with one dot on
        :return: the result of the four rolls.
        """
        dots = 0
        for _ in range(n):
            dots += choice([0, 1])
        return dots

    def play_game(self):
        """
            Your job is to recode this function to play the game.
        """
        player1 = None
        player2 = None
        pieces_on_rosette = []

        players = {}
        for i in range(2):
            name = input("What is your name? ")
            players[name] = []
            if i == 0:
                print(name, "you will be white.")
            elif i == 1:
                print(name, "you will be black.")
            for j in range(self.STARTING_PIECES):
                if i == 0:
                    symbol = "W" + str(j + 1)
                    player1 = name
                    players[name].append(UrPiece("White", symbol))
                elif i == 1:
                    symbol = "B" + str(j + 1)
                    player2 = name
                    players[name].append(UrPiece("Black", symbol))
                else:
                    print("Only two people can play this game")
        for i in range(len(self.board)):
            for j in self.board[i]:
                if j.entrance and not j.next_black:
                    UrPiece.WhiteStart = j
                elif j.exit == "White":
                    UrPiece.WhiteEnd = j
                elif j.entrance and not j.next_white:
                    UrPiece.BlackStart = j
                elif j.exit == "Black":
                    UrPiece.BlackEnd = j

        quit_loop = False
        while not quit_loop:
            player1_won = True
            player2_won = True
            for i in players[player1]:
                if not i.complete:
                    player1_won = False

            for i in players[player2]:
                if not i.complete:
                    player2_won = False

            if player1_won or player2_won:
                quit_loop = True

            if not quit_loop:
                for i in players:
                    quit_loop2 = False
                    player_turn = i
                    while not quit_loop2:
                        quit_loop2 = True
                        self.display_board()
                        for x in players:
                            for y in players[x]:
                                if y.position and not y.position.piece == y:
                                    y.position = None

                        roll = self.roll_d4_dice()
                        print("You rolled", roll)
                        movable_pieces = []
                        completed_pieces = []
                        for j in range(len(players[player_turn])):
                            if players[player_turn][j].can_move(roll) and not players[player_turn][j].complete:
                                movable_pieces.append(players[player_turn][j])
                            elif players[player_turn][j].complete:
                                completed_pieces.append(players[player_turn][j])
                        if movable_pieces:
                            for j in range(len(movable_pieces)):
                                if not movable_pieces[j].position:
                                    print(j + 1, movable_pieces[j].symbol, "currently off the board")
                                else:
                                    print(j + 1, movable_pieces[j].symbol, movable_pieces[j].position.position)
                            for j in range(len(completed_pieces)):
                                print(completed_pieces[j].symbol, "has completed the race")
                            num = int(input("Which move do you wish to make? "))
                            while num - 1 >= len(movable_pieces):
                                num = int(input("That is not a choice, which move do you wish to make? "))
                            if movable_pieces[num - 1] in pieces_on_rosette:
                                pieces_on_rosette.remove(movable_pieces[num - 1])
                            movable_pieces[num - 1].move(roll)

                        else:
                            print("There are no moves to make with this roll")

                        for x in players:
                            for y in players[x]:
                                if y.position and y.position.rosette:
                                    if y not in pieces_on_rosette:
                                        quit_loop2 = False
                                        player_turn = x
                                        pieces_on_rosette.append(y)
                                        print("You have landed on a rosette, go again")


if __name__ == '__main__':
    file_name = input('What is the file name of the board json? ') if len(argv) < 2 else argv[1]
    rgu = RoyalGameOfUr(file_name)

    rgu.play_game()
