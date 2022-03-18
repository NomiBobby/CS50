import csv
import sys

from sys import argv


def main():

    # Check for command-line usage
    # Number of command-line arguements = name + database + sequence = 3
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
    else:
        database_name = argv[1]
        sequence_name = argv[2]

    # Read database file into a variable
    dict = {}
    with open(database_name, newline='') as csvfile:
        # Identify headers
        csvheader = next(csvfile).split(',')
        # Remove the \n from the last item
        csvheader[len(csvheader)-1] = csvheader[len(csvheader)-1].strip()
        STRlist = csvheader[1:]
        # print(f"The subsequences are: {STRlist}")
        # Load the dictionary
        csvfile.seek(0)
        csvreader = csv.DictReader(csvfile)
        for row in csvreader:
            dict[row["name"]] = row
        keys = list(dict)
        # print(keys)
        for name in keys:
            hitsList = []
            for STR in STRlist:
                hitsList = hitsList + [int(dict[name][STR])]
            dict[name] = hitsList
            # print(hitsList)
    # Test if Dictionary is working
    # print(dict["Ron"])

    # Read DNA sequence file into a variable
    with open(sequence_name, "r") as txt:
        sequence = txt.readline()
        # print(sequence)

    # Find longest match of each STR in DNA sequence
    hit = []
    for STR in STRlist:
        # print(f"Checking {STR}")
        hit = hit + [longest_match(sequence, STR)]

    # Check database for matching profiles
    for name in keys:
        if dict[name] == hit:
            print(name)
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                # print(start)
                # print(end)
                # print(sequence[start:end])
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()