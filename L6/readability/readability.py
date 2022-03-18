from cs50 import get_string


def main():
    text = get_string("Text: ")
    # print(text)

    num_letters = count_letters(text)
    # print(f"{num_letters} letter(s)")

    num_words = count_words(text)
    # print(f"{num_words} word(s)")

    num_scentences = count_scentences(text)
    # print("{num_scentences} scentence(s)")

    L = 100 / num_words * num_letters
    S = 100 / num_words * num_scentences
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 1 and index <= 15:
        print(f"Grade {round(index)}")
    else:
        print("Grade 16+")


def count_letters(text):
    num_letters = 0
    for i in range(len(text)):
        if (text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z'):
            num_letters += 1
    return num_letters


def count_words(text):
    # from text[0], find next space
    num_words = 0
    total_length = len(text)
    for i in range(total_length):
        if text[i] == " ":
            num_words += 1

    # for the last word in the string, it does not have a spece at the end
    num_words += 1
    return num_words


def count_scentences(text):
    num_scentences = 0
    total_length = len(text)
    for i in range(total_length):
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            num_scentences += 1
    return num_scentences


main()