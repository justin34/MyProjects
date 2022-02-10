"""
network.py is both the definition file for the Network class as well as the driver for the program.

In network you need to implement the functions which the driver will call for the all the different commands.
"""

import json
from phone import Phone
from switchboard import Switchboard

"""
import json
import csv (you can do either if you choose, or just use the regular file io)

Some constants below are for the driver, don't remove them unless you mean to.  
"""

HYPHEN = "-"
QUIT = 'quit'
SWITCH_CONNECT = 'switch-connect'
SWITCH_ADD = 'switch-add'
PHONE_ADD = 'phone-add'
NETWORK_SAVE = 'network-save'
NETWORK_LOAD = 'network-load'
START_CALL = 'start-call'
END_CALL = 'end-call'
DISPLAY = 'display'


class Network:
    def __init__(self):
        """
            Construct a network by creating the switchboard container object

            You are free to create any additional data/members necessary to maintain this class.
        """
        self.switchboards = []

    def load_network(self, filename):
        """
        :param filename: the name of the file to be loaded.  Assume it exists and is in the right format.
                If not, it's ok if your program fails.
        :return: success?
        """
        file = open(filename)
        file_as_str = ''
        for lines in file:
            file_as_str = file_as_str + lines
        loaded_dic = json.loads(file_as_str)
        for switchboard in loaded_dic["switchboards"]:
            self.add_switchboard(switchboard["area_code"])
            for phone in switchboard["phones"]:
                self.create_phone(switchboard["area_code"], phone)
        for switchboard in loaded_dic["switchboards"]:
            for connection in switchboard["connections"]:
                self.connect_switchboards(switchboard["area_code"], connection)
        file.close()

    def save_network(self, filename):
        """
        :param filename: the name of your file to save the network.  Remember that you need to save all the
            connections, but not the active phone calls (they can be forgotten between save and load).
            You must invent the format of the file, but if you wish you can use either json or csv libraries.
        :return: success?
        """
        save_dict = {
            'switchboards': [

            ]
        }

        for i in range(len(self.switchboards)):
            switchboard_dic = {'area_code': self.switchboards[i].area_code,
                               'phones': [],
                               'connections': []}
            for j in self.switchboards[i].phones:
                switchboard_dic['phones'].append(j.number)
            for j in self.switchboards[i].connections:
                switchboard_dic['connections'].append(j.area_code)

            save_dict["switchboards"].append(switchboard_dic)
        file = open(filename, "w")
        json_string = json.dumps(save_dict, indent=2)
        file.write(json_string)

        file.close()

    def add_switchboard(self, area_code):
        """
        add switchboard should create a switchboard and add it to your network.

        By default it is not connected to any other boards and has no phone lines attached.
        :param area_code: the area code for the new switchboard
        :return:
        """
        in_list = False
        for i in self.switchboards:
            if i.area_code == area_code:
                in_list = True
        if not in_list:
            self.switchboards.append(Switchboard(area_code))

    def connect_switchboards(self, area1, area2):
        """
            Connect switchboards should connect the two switchboards (creates a trunk line between them)
            so that long distance calls can be made.

        :param area1: area-code 1
        :param area2: area-code 2
        :return: success/failure
        """
        switchboard1 = None
        switchboard2 = None
        for i in self.switchboards:
            if i.area_code == area1:
                switchboard1 = i

        for i in self.switchboards:
            if i.area_code == area2:
                switchboard2 = i

        if not (switchboard1 and switchboard2):
            print("one of the are codes doesn't exist")
        else:
            switchboard1.add_trunk_connection(switchboard2)
            switchboard2.add_trunk_connection(switchboard1)

    def create_phone(self, area_code, phone_number):
        in_list = False
        for i in self.switchboards:
            if i.area_code == area_code:
                in_list = True
                i.add_phone(phone_number)
        if not in_list:
            print("Area code doesnt exist")

    def connect_call(self, area1, phone_num1, area2, phone_num2):

        for i in self.switchboards:
            if i.area_code == area1:
                for j in i.phones:
                    if j.number == phone_num1:
                        j.connect(area2, phone_num2)

    def disconnect(self, area, phone_num):
        for i in self.switchboards:
            if i.area_code == area:
                for j in i.phones:
                    if j.number == phone_num:
                        j.disconnect()

    def display(self):
        """
            Display should output the status of the phone network as described in the project.
        """

        for i in self.switchboards:
            print("Switchboard with area code:", i.area_code)
            print("\tTrunk lines are:")
            for j in i.connections:
                print("\t\tTrunk line connection to:", j.area_code)
            print("\tLocal phone numbers are:")
            for j in i.phones:
                if j.connected_phone:
                    print("\t\tPhone with number:", j.number, "is connected to",
                          str(j.connected_phone.switchboard.area_code) + '-' + str(j.connected_phone.number))
                else:
                    print("\t\tPhone with number:", j.number, "is not in use")


if __name__ == '__main__':
    the_network = Network()
    s = input('Enter command: ')
    while s.strip().lower() != QUIT:
        split_command = s.split()
        if len(split_command) == 3 and split_command[0].lower() == SWITCH_CONNECT:
            area_1 = int(split_command[1])
            area_2 = int(split_command[2])
            the_network.connect_switchboards(area_1, area_2)
        elif len(split_command) == 2 and split_command[0].lower() == SWITCH_ADD:
            the_network.add_switchboard(int(split_command[1]))
        elif len(split_command) == 2 and split_command[0].lower() == PHONE_ADD:
            number_parts = split_command[1].split(HYPHEN)
            area_code = int(number_parts[0])
            phone_number = int(''.join(number_parts[1:]))

            the_network.create_phone(area_code, phone_number)

        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_SAVE:
            the_network.save_network(split_command[1])
            print('Network saved to {}.'.format(split_command[1]))
        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_LOAD:
            the_network.load_network(split_command[1])
            print('Network loaded from {}.'.format(split_command[1]))
        elif len(split_command) == 3 and split_command[0].lower() == START_CALL:
            src_number_parts = split_command[1].split(HYPHEN)
            src_area_code = int(src_number_parts[0])
            src_number = int(''.join(src_number_parts[1:]))

            dest_number_parts = split_command[2].split(HYPHEN)
            dest_area_code = int(dest_number_parts[0])
            dest_number = int(''.join(dest_number_parts[1:]))

            the_network.connect_call(src_area_code, src_number, dest_area_code, dest_number)


        elif len(split_command) == 2 and split_command[0].lower() == END_CALL:
            number_parts = split_command[1].split('-')
            area_code = int(number_parts[0])
            number = int(''.join(number_parts[1:]))

            the_network.disconnect(area_code, number)
        elif len(split_command) >= 1 and split_command[0].lower() == DISPLAY:
            the_network.display()

        s = input('Enter command: ')
