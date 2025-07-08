// Game Suite Project: Craps, Blackjack, Hangman
// CS 201R - Program 3

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

// ----------------------------- Craps ----------------------------- //
void playCraps() {
    srand(time(0));
    int money = 50;
    char choice;

    cout << "\nWelcome to Craps!\n";
    do {
        if (money <= 0) {
            cout << "You have no more money left. Game over.\n";
            break;
        }

        int bet;
        do {
            cout << "You have $" << money << ". Enter bet amount: ";
            cin >> bet;
        } while (bet <= 0 || bet > money);

        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;
        int sum = die1 + die2;

        cout << "You rolled " << die1 << " + " << die2 << " = " << sum << endl;

        if (sum == 7 || sum == 11) {
            cout << "You win!\n";
            money += bet;
        }
        else if (sum == 2 || sum == 3 || sum == 12) {
            cout << "You lose!\n";
            money -= bet;
        }
        else {
            int point = sum;
            cout << "Point is set to " << point << ". Rolling until you hit point or 7...\n";
            while (true) {
                die1 = rand() % 6 + 1;
                die2 = rand() % 6 + 1;
                sum = die1 + die2;
                cout << "Rolled: " << sum << endl;
                if (sum == point) {
                    cout << "You hit your point! You win!\n";
                    money += bet;
                    break;
                }
                else if (sum == 7) {
                    cout << "Rolled a 7. You lose!\n";
                    money -= bet;
                    break;
                }
            }
        }

        cout << "Your current balance: $" << money << endl;
        cout << "Play again? (Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    cout << "Thanks for playing! Final balance: $" << money << "\n";
}

// -------------------------- Blackjack ---------------------------- //
struct Card {
    string rank, suit;
};

int getCardValue(const Card& card) {
    if (card.rank == "A") return 11;
    if (card.rank == "K" || card.rank == "Q" || card.rank == "J") return 10;
    return stoi(card.rank);
}

int calculateHandValue(vector<Card>& hand) {
    int total = 0;
    int aceCount = 0;
    for (Card& c : hand) {
        int val = getCardValue(c);
        total += val;
        if (c.rank == "A") aceCount++;
    }
    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }
    return total;
}

void dealCard(vector<Card>& deck, vector<Card>& hand) {
    hand.push_back(deck.back());
    deck.pop_back();
}

void printHand(const vector<Card>& hand, string owner) {
    cout << owner << "'s Hand: ";
    for (const Card& c : hand) cout << c.rank << c.suit << " ";
    cout << "(Total: " << calculateHandValue(const_cast<vector<Card>&>(hand)) << ")\n";
}

void playBlackjack() {
    srand(time(0));
    cout << "\nWelcome to Blackjack!\n";
    char again;

    do {
        vector<Card> deck;
        string suits[] = { "H", "D", "S", "C" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

        for (string suit : suits) {
            for (string rank : ranks) {
                deck.push_back({ rank, suit });
            }
        }

        random_shuffle(deck.begin(), deck.end());

        vector<Card> player, dealer;
        dealCard(deck, player);
        dealCard(deck, dealer);
        dealCard(deck, player);
        dealCard(deck, dealer);

        printHand(player, "Player");

        char choice;
        while (calculateHandValue(player) < 21) {
            cout << "Would you like another card? (Y/N): ";
            cin >> choice;
            if (toupper(choice) == 'Y') {
                dealCard(deck, player);
                printHand(player, "Player");
            }
            else break;
        }

        if (calculateHandValue(player) > 21) {
            cout << "Bust! Dealer wins.\n";
        }
        else {
            printHand(dealer, "Dealer");
            while (calculateHandValue(dealer) <= 17) {
                dealCard(deck, dealer);
                printHand(dealer, "Dealer");
            }

            int playerVal = calculateHandValue(player);
            int dealerVal = calculateHandValue(dealer);

            if (dealerVal > 21 || playerVal > dealerVal) cout << "You win!\n";
            else if (dealerVal == playerVal) cout << "PUSH!\n";
            else cout << "Dealer wins.\n";
        }

        cout << "Play again? (Y/N): ";
        cin >> again;
    } while (toupper(again) == 'Y');
}

// ---------------------------- Hangman ---------------------------- //
void playHangman() {
    ifstream file("words.txt");
    if (!file) {
        cout << "Could not open words.txt\n";
        return;
    }

    vector<string> words;
    string word;
    while (file >> word) words.push_back(word);

    srand(time(0));
    string answer = words[rand() % words.size()];
    string guessWord(answer.size(), '_');

    int wrong = 0;
    vector<char> guessed;

    cout << "\nWelcome to Hangman!\n";

    while (guessWord != answer && wrong < 6) {
        cout << "Word: " << guessWord << "  Wrong guesses: " << wrong << endl;
        cout << "Enter a letter: ";
        char ch;
        cin >> ch;
        ch = tolower(ch);

        if (find(guessed.begin(), guessed.end(), ch) != guessed.end()) {
            cout << "Already guessed.\n";
            continue;
        }

        guessed.push_back(ch);
        bool found = false;
        for (int i = 0; i < answer.size(); i++) {
            if (tolower(answer[i]) == ch) {
                guessWord[i] = answer[i];
                found = true;
            }
        }

        if (!found) wrong++;
    }

    if (guessWord == answer) cout << "You guessed it! The word was " << answer << endl;
    else cout << "You lost! The word was " << answer << endl;
}

// ----------------------------- Main ------------------------------ //
int main() {
    char choice;
    do {
        cout << "\nChoose a game:\n";
        cout << "C: Craps\nB: Blackjack\nH: Hangman\nE: Exit\nEnter your choice: ";
        cin >> choice;

        switch (toupper(choice)) {
        case 'C': playCraps(); break;
        case 'B': playBlackjack(); break;
        case 'H': playHangman(); break;
        case 'E': cout << "Thanks for playing!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (toupper(choice) != 'E');

    return 0;
}