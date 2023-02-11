"""
File:         board_square.py
Author:       Jabril Hall
Date:         11/13/2020
Section:      53
E-mail:       jhall14@umbc.edu
Description:  handle movement for royal game
"""


class UrPiece:
    WhiteStart = None
    BlackStart = None
    WhiteEnd = None
    BlackEnd = None

    def __init__(self, color, symbol):
        self.color = color
        self.position = None
        self.complete = False
        self.symbol = symbol

    def move(self, num_moves):
        if not self.position:
            num_moves -= 1
            if self.color == "White" and self.WhiteStart:
                self.position = self.WhiteStart
            elif self.color == "Black" and self.BlackStart:
                self.position = self.BlackStart

            else:
                print("You need to define starts")
            self.position.piece = self

        if self.color == "White" and not num_moves == 0:
            self.position.piece = None
            for i in range(num_moves):
                if not self.position == self.WhiteEnd:
                    self.position = self.position.next_white
                else:
                    self.complete = True
        elif self.color == "Black" and not num_moves == 0:
            self.position.piece = None
            for i in range(num_moves):
                if not self.position == self.BlackEnd:
                    self.position = self.position.next_black
                else:
                    self.complete = True
        if not self.complete:
            self.position.piece = self

    def can_move(self, num_moves):
        quit_loop = False
        copy = UrPiece(self.color, self.symbol)
        copy.position = self.position
        if num_moves == 0:
            return False

        if not copy.position:
            num_moves -= 1
            moved = False
            if copy.color == "White" and self.WhiteStart:
                if num_moves > 0 or (num_moves == 0 and not self.WhiteStart.piece):
                    copy.position = self.WhiteStart
                    moved = True
            elif copy.color == "Black" and self.BlackStart:
                if num_moves > 0 or (num_moves == 0 and not self.BlackStart.piece):
                    copy.position = self.BlackStart
                    moved = True

            if not moved:
                quit_loop = True
                num_moves += 1

        while not quit_loop:
            moved = False
            if num_moves > 0:
                if copy.color == "White":
                    if not copy.position == self.WhiteEnd:
                        if not copy.position.next_white.piece or (
                                copy.position.next_white.piece.color == "Black" and not copy.position.next_white.rosette
                        ) or (copy.position.next_white.piece and num_moves > 1):
                            copy.position = copy.position.next_white
                            num_moves -= 1
                            moved = True
                    else:
                        if not num_moves == 1:
                            quit_loop = True
                        else:
                            num_moves = 0
                elif copy.color == "Black":
                    if not copy.position == self.BlackEnd:
                        if not copy.position.next_black.piece or (
                                copy.position.next_black.piece.color == "White" and not copy.position.next_black.rosette
                        ) or (copy.position.next_black.piece and num_moves > 1):
                            copy.position = copy.position.next_black
                            num_moves -= 1
                            moved = True
                    else:
                        if not num_moves == 1:
                            quit_loop = True
                        else:
                            num_moves = 0
            if not moved or num_moves == 0:
                quit_loop = True

        if num_moves == 0:
            return True
        else:
            return False


class BoardSquare:
    def __init__(self, x, y, entrance=False, _exit=False, rosette=False, forbidden=False):
        self.piece = None
        self.position = (x, y)
        self.next_white = None
        self.next_black = None
        self.exit = _exit
        self.entrance = entrance
        self.rosette = rosette
        self.forbidden = forbidden

    def load_from_json(self, json_string):
        import json
        loaded_position = json.loads(json_string)
        self.piece = None
        self.position = loaded_position['position']
        self.next_white = loaded_position['next_white']
        self.next_black = loaded_position['next_black']
        self.exit = loaded_position['exit']
        self.entrance = loaded_position['entrance']
        self.rosette = loaded_position['rosette']
        self.forbidden = loaded_position['forbidden']

    def jsonify(self):
        next_white = self.next_white.position if self.next_white else None
        next_black = self.next_black.position if self.next_black else None
        return {'position': self.position, 'next_white': next_white, 'next_black': next_black, 'exit': self.exit,
                'entrance': self.entrance, 'rosette': self.rosette, 'forbidden': self.forbidden}
