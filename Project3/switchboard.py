"""
    Switchboard class

"""

from phone import Phone


class Switchboard:
    def __init__(self, area_code, phones=None, connections=None):
        """
        :param area_code: the area code to which the switchboard will be associated.
        """
        self.area_code = area_code
        if not phones:
            self.phones = []
        else:
            self.phones = phones
        if not connections:
            self.connections = []
        else:
            self.phones = phones

    def add_phone(self, phone_number):
        """
        This function should add a local phone connection by creating a phone object
        and storing it in this class.  How you do that is up to you.

        :param phone_number: phone number without area code
        :return: depends on implementation / None
        """
        in_list = False
        for i in range(len(self.phones)):
            if self.phones[i].number == phone_number:
                in_list = True
        if not in_list:
            self.phones.append(Phone(phone_number, self))
        else:
            print("That phone number is already on this switchboard")

    def add_trunk_connection(self, switchboard):
        """
        Connect the switchboard (self) to the switchboard (switchboard)

        :param switchboard: should be either the area code or switchboard object to connect.
        :return: success/failure, None, or it's up to you
        """
        in_list = False
        for i in range(len(self.connections)):
            if self.connections[i].area_code == switchboard.area_code:
                in_list = True

        if not in_list:
            self.connections.append(switchboard)

        else:
            print("That switchboard is already connected to this switchboard")

    def connect_call(self, area_code, number, switchboard, previous_codes):
        """
        This must be a recursive function.

        :param switchboard:
        :param area_code: the area code to which the destination phone belongs
        :param number: the phone number of the destination phone without area code.
        :param previous_codes: you must keep track of the previously tracked codes
        :return: Depends on your implementation, possibly the path to the destination phone.
        """
        if switchboard.area_code == area_code:
            for i in range(len(switchboard.phones)):
                if switchboard.phones[i].number == number:
                    return switchboard.phones[i]

            print("Phone number doesnt exist in this area code")
            return None
        elif switchboard.area_code in previous_codes:
            return None

        for i in switchboard.connections:
            phone = switchboard.connect_call(area_code, number, i, previous_codes)
            if phone:
                return phone

        previous_codes.append(switchboard.area_code)
        return None

    def __str__(self):
        final_string = ''
        string = str(self.area_code)
        final_string = final_string + string + " phones:"
        for i in self.phones:
            final_string = string + "," + str(i.number)
        final_string = final_string + " connections:"
        for i in self.connections:
            final_string = final_string + "," + str(i.area_code)

        return final_string
