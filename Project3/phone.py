"""
    Phone Class Starter Code

    This code defines the basic functionality that you need from a phone.
    When these functions are called they should communicate with the
    switchboards to find a path
"""


class Phone:
    def __init__(self, number, switchboard, connected_phone=None):
        """
        :param number: the phone number without area code
        :param switchboard: the switchboard to which the number is attached.
        """
        self.number = number
        self.switchboard = switchboard
        self.connected_phone = connected_phone

    def connect(self, area_code, other_phone_number):
        """
        The connect method should take the destination area code and the destination number and try to connect either
         locally if the call is local, or through the switchboards to the other area code and finally check to see if
         there is a phone number that matches the other_phone_number.  If so it should connect, as long as the other
         phone is not already connected, and as long as the original phone is not connected.

        :param area_code: the area code of the other phone number
        :param other_phone_number: the other phone number without the area code
        :return: **this you must decide in your implementation**
        """
        other_phone = self.switchboard.connect_call(area_code, other_phone_number, self.switchboard, [])
        if self.connected_phone:
            print("This phone is already connected to", self.connected_phone.number)
        elif not other_phone:
            print(str(self.switchboard.area_code) + "-" + str(self.number), "and", str(area_code) + '-' +
                  str(other_phone_number), "were not connected")
        else:
            print(str(self.switchboard.area_code) + "-" + str(self.number), "and", str(area_code) + '-' +
                  str(other_phone_number), "are now connected")
            self.connected_phone = other_phone
            other_phone.connected_phone = self

    def disconnect(self):
        """
        This function should return the connection status to disconnected.  You need
        to use new members of this class to determine how the phone is connected to
        the other phone.

        You should also make sure to disconnect the other phone on the other end of the line.
        :return: **depends on your implementation**
        """
        if self.connected_phone:
            print("Hanging up...")
            print("Disconnected")
            self.connected_phone.connected_phone = None
            self.connected_phone = None
        else:
            print("Phone is not connected to any other phone")

