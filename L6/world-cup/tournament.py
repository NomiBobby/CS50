# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")
    teams = []
    # Read teams into memory from file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            # print(row)
            row["rating"] = int(row["rating"])
            # print(row)
            teams.append(row)
    # print(teams)
    counts = {}
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        # print(f"Running {i}th simulation:, the length of the teams is {len(teams)}")
        # print(teams)
        # winner is a string
        winner = simulate_tournament(teams)
        # print(f"The winner is {winner}")
        # print()
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1
    # print(f"Counts: {counts}")
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    # print(f"{team1} vs {team2}")
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    # print(f"{rating1} vs {rating2}")
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    # print(f"Prabability is {probability}, ", end="")
    randomnum = random.random()
    # print(f"Random number is {randomnum}, ", end="")
    if randomnum < probability:
        a = team1["team"]
        # print(f"The winner is {a}")
    else:
        b = team2["team"]
        # print(f"The winner is {b}")

    return randomnum < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    # print()
    # print(f"Simulating {len(teams)}")
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            # print(f"appened {teams[i]}")
            winners.append(teams[i])
            # print()
        else:
            winners.append(teams[i + 1])
            # print(f"appened {teams[i+1]}")
            # print()

    # print("The winners are")
    # print(winners)
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    localTeam = teams.copy()
    while True:
        winner_list = simulate_round(localTeam)
        # print(f"Winners are: {winner_list}")
        localTeam = winner_list
        # print(f"The length of the winner list is{len(winner_list)}")
        if len(winner_list) == 1:
            break

    return winner_list[0]["team"]


if __name__ == "__main__":
    main()