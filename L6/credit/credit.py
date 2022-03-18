from cs50 import get_string


def main():
    while True:
        card_number = get_string("Number: ")
        if checksum(card_number):
            break


def checksum(card_number):
    if len(card_number) == 15 or len(card_number) == 16 or len(card_number) == 13:
        # STEP 1
        # Multiply every other digit by 2, starting with the number’s second-to-last digit,
        # and then add those products’ digits together.
        index = len(card_number) - 2
        sum = 0
        while True:
            num = int(card_number[index])
            if num >= 0 and num < 5:
                sum = sum + num * 2
            else:
                sum = sum + 1 + num * 2 - 10
            index -= 2
            if index < 0:
                break

        # STEP 2
        # Add the sum to the sum of the digits that weren’t multiplied by 2.
        index = len(card_number) - 1
        while True:
            num = int(card_number[index])
            sum = sum + num
            index -= 2
            if index < 0:
                break

        # STEP 3
        # If the total’s last digit is 0 (or, put more formally, if the
        # total modulo 10 is congruent to 0), the number is valid!
        if sum % 10 == 0:
            # // Valid, get the first two digits of the card number
            # //All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55
            # //(they also have some other potential starting numbers which we won’t concern ourselves with for this problem);
            # //and all Visa numbers start with 4.
            Digit_1st = card_number[0]
            Digit_2st = card_number[1]
            if Digit_1st == '4':
                print("VISA")
            elif Digit_1st == '3' and (Digit_2st == '4' or Digit_2st == '7'):
                print("AMEX")
            elif Digit_1st == '5' and (Digit_2st == '1' or Digit_2st == '2' or Digit_2st == '3' or Digit_2st == '4' or Digit_2st == '5'):
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")

    return 1


main()