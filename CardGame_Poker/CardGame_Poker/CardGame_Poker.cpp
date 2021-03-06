#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string suits[4];
string ranks[13];

class Card {
public:
    int suit;
    int rank;
};

int compareCards(const void* card1, const void* card2) {
    return (*(Card*)card1).rank - (*(Card*)card2).rank;
}

class Deck {
public:
    Deck() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards[i * 13 + j].suit = i;
                cards[i * 13 + j].rank = j;
            }
        }
        setlocale(LC_ALL, "Russian");
        suits[0] = "Б";
        suits[1] = "П";
        suits[2] = "Ч";
        suits[3] = "К";
        ranks[0] = "2";
        ranks[1] = "3";
        ranks[2] = "4";
        ranks[3] = "5";
        ranks[4] = "6";
        ranks[5] = "7";
        ranks[6] = "8";
        ranks[7] = "9";
        ranks[8] = "1";
        ranks[9] = "В";
        ranks[10] = "Д";
        ranks[11] = "K";
        ranks[12] = "Т";
    }

    void print() {
        setlocale(LC_ALL, "Russian");
        cout << "Раскладываю карты..." << endl;
        for (int i = 0; i < 52; i++)
            cout << ranks[cards[i].rank] << suits[cards[i].suit] << endl;
        cout << endl;
    }

    void shuffle() {
        setlocale(LC_ALL, "Russian");
        top = 51;
        int x;
        Card tempCard;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards[i * 13 + j].suit = i;
                cards[i * 13 + j].rank = j;
            }
        }
        cout << "Тасую и раздаю карты..." << endl << endl;

        for (int i = 0; i < 52; i++) {
            x = rand() % 52;
            tempCard = cards[i];
            cards[i] = cards[x];
            cards[x] = tempCard;
        }
    }

    Card hitme() {
        top--;
        return cards[top + 1];
    }

private:
    int top;
    Card cards[52];
};

class Player {
public:
    string name;
    int money;
    Card cards[2];
    int playing;
    int round;
    int goodToGo;
};

class PokerGame {
public:
    void start(string name) {
        for (int i = 0; i < 6; i++) {
            players[i].money = 1000;
            players[i].playing = 1;
        }
        players[0].name = "Sasha";
        players[1].name = "Liza";
        players[2].name = "Nikita";
        players[3].name = "Ignat";
        players[4].name = name;
        players[5].name = "Polina";
        startGame();
    }


    void deal() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 2; j++) {
                if (players[i].playing) {
                    players[i].cards[j] = deck1.hitme();
                }
            }
        }
        for (int i = 0; i < 5; i++)
            tableCards[i].rank = -1;
    }

    void flop() {
        for (int i = 0; i < 3; i++)
            tableCards[i] = deck1.hitme();
    }

    void turn() {
        tableCards[3] = deck1.hitme();
    }

    void river() {
        tableCards[4] = deck1.hitme();
    }

    void printTable() {
        setlocale(LC_ALL, "Russian");
        cout << "  " << ((players[0].playing) ? (players[0].name) : "      ") << "         " << ((players[1].playing) ? (players[1].name) : "     ") << "           "
            << ((players[2].playing) ? (players[2].name) : "    ") << endl;
        cout << "   $" << setw(4) << ((players[0].playing) ? (players[0].money) : 0) << "         $" << setw(4) << ((players[1].playing) ? (players[1].money) : 0)
            << "           $" << setw(4) << ((players[2].playing) ? (players[2].money) : 0) << endl;
        cout << "     _____________________________" << endl;
        cout << "    / " << ((bind == 0) ? "@" : " ") << "            " << ((bind == 1) ? "@" : " ") << "            " << ((bind == 2) ? "@" : " ") << " \\" << endl;
        cout << "   /  ___   ___   ___   ___   ___  \\" << endl;
        cout << "   | | " << ((tableCards[0].rank) >= 0 ? ranks[tableCards[0].rank] : " ") << " | | " << ((tableCards[1].rank) >= 0 ? ranks[tableCards[1].rank] : " ") << " | | " << ((tableCards[2].rank) >= 0 ? ranks[tableCards[2].rank] : " ") << " | | "
            << ((tableCards[3].rank) >= 0 ? ranks[tableCards[3].rank] : " ") << " | | " << ((tableCards[4].rank) >= 0 ? ranks[tableCards[4].rank] : " ") << " | |" << endl;
        cout << "   | | " << ((tableCards[0].rank) >= 0 ? suits[tableCards[0].suit] : " ") << " | | " << ((tableCards[1].rank) >= 0 ? suits[tableCards[1].suit] : " ") << " | | " << ((tableCards[2].rank) >= 0 ? suits[tableCards[2].suit] : " ") << " | | "
            << ((tableCards[3].rank) >= 0 ? suits[tableCards[3].suit] : " ") << " | | " << ((tableCards[4].rank) >= 0 ? suits[tableCards[4].suit] : " ") << " | |" << endl;
        cout << "   | |___| |___| |___| |___| |___| |" << endl;
        cout << "   |                               |" << endl;
        cout << "   |          Банк = $" << setw(4) << pot << "         |" << endl;
        cout << "   \\                               /" << endl;
        cout << "    \\_" << ((bind == 5) ? "@" : "_") << "_____________" << ((bind == 4) ? "@" : "_") << "___________" << ((bind == 3) ? "@" : "_") << "_/" << endl;
        cout << endl;
        cout << "  " << ((players[5].playing) ? (players[5].name) : "      ") << "          " << ((players[4].playing) ? (players[4].name) : "      ") << "         "
            << ((players[3].playing) ? (players[3].name) : "    ") << endl;
        cout << "   $" << setw(4) << ((players[5].playing) ? (players[5].money) : 0) << "          $" << setw(4) << ((players[4].playing) ? (players[4].money) : 0)
            << "         $" << setw(4) << ((players[3].playing) ? (players[3].money) : 0) << endl;
        cout << endl;
        if (players[4].round) {
            cout << "   Ваша рука:" << endl;
            cout << "    ___    ___" << endl;
            cout << "   | " << ranks[players[4].cards[0].rank] << " |  | " << ranks[players[4].cards[1].rank] << " |" << endl;
            cout << "   | " << suits[players[4].cards[0].suit] << " |  | " << suits[players[4].cards[1].suit] << " |" << endl;
            cout << "   |___|  |___|" << endl << endl;
        }

    }

private:
    Player players[6];
    Deck deck1;
    int bind;
    Card tableCards[5];
    int pot, action, bet, rational, betOn, winner, maxPoints, roundWinner;
    int handPoints[6];
    int bestHand[6][3];

    int playersLeft() {
        int count = 0;
        for (int i = 0; i < 6; i++)
            if (players[i].money > 0)
                count++;
        return count;
    }

    int computerAction(int playerNum) {
        if (players[playerNum].cards[0].rank < 8 && players[playerNum].cards[1].rank < 8) {
            if (players[playerNum].cards[0].rank != players[playerNum].cards[1].rank)
                return 0;
            else
                return 1;
        }

        else if (players[playerNum].cards[0].rank < 10 && players[playerNum].cards[1].rank < 10) {
            if (players[playerNum].cards[0].rank != players[playerNum].cards[1].rank)
                return 1;
            else
                return 2;
        }
        else {
            return 2;
        }
    }

    /*checks if someone still got bet/call*/
    int playersToBet() {
        for (int i = 0; i < 6; i++)
            if (players[i].round == 1 && players[i].goodToGo == 0)
                return 1;

        return 0;
    }

    void takeBets() {
        setlocale(LC_ALL, "Russian");
        betOn = 0;
        for (int k = 0; k < 6; k++)
            players[k].goodToGo = 0;

        for (int k = bind + 1; k < bind + 7; k++) {
            /* human player actions */
            if (k % 6 == 4 && players[4].round) {
                if (betOn) {
                    cout << "Ваши действия: (1) СБРОСИТЬ (3) ПОСТАВИТЬ/ОТВЕТИТЬ ";
                    cin >> action;
                    while (action != 1 && action != 3) {
                        cout << "Неккоректный ввод." << endl;
                        cout << "Ваши действия: (1) СБРОСИТЬ (3) ПОСТАВИТЬ/ОТВЕТИТЬ ";
                        cin >> action;
                    }
                }
                else {
                    cout << "Ваши действия: (1) СБРОСИТЬ (2) ПРОПУСТИТЬ (3) ПОСТАВИТЬ/ОТВЕТИТЬ ";
                    cin >> action;
                    while (action < 1 || action>3) {
                        cout << "Неккоректный ввод." << endl;
                        cout << "Ваши действия: (1) СБРОСИТЬ (2) ПРОПУСТИТЬ (3) ПОСТАВИТЬ/ОТВЕТИТЬ ";
                        cin >> action;
                    }
                }
                cout << endl;
                if (action == 1)
                    players[4].round = 0;
                else if (action == 2)
                    continue;
                else {
                    if (betOn) {
                        pot += betOn;
                        players[4].money -= betOn;
                        players[4].goodToGo = 1;
                    }
                    else {
                        cout << "Сколько вы хотите поставить: ";
                        cin >> bet;
                        while (bet > players[4].money || bet < 1) {
                            cout << "Неккоректный ввод для ставки." << endl;
                            cout << "Сколько вы хотите поставить: ";
                            cin >> bet;
                            cout << endl << endl;
                        }
                        pot += bet;
                        players[4].money -= bet;
                        betOn = bet;
                        players[4].goodToGo = 1;
                    }
                }
            }

            /* computers actions */
            else {
                if (players[k % 6].round == 0)
                    continue;
                rational = rand() % 2;
                if (rational) {
                    action = computerAction(k % 6);
                }
                else {
                    action = rand() % 3;
                }
                if (action == 0) {
                    players[k % 6].round = 0;
                    cout << players[k % 6].name << " сбросил/а карты..." << endl << endl;
                }
                else if (action == 1 && betOn == 0) {
                    cout << players[k % 6].name << " пропустил/а." << endl << endl;
                    continue;
                }
                else {
                    if (betOn) {
                        pot += betOn;
                        players[k % 6].money -= betOn;
                        cout << players[k % 6].name << " отвечает!" << endl << endl;
                        players[k % 6].goodToGo = 1;
                    }
                    else {
                        bet = (rand() % (players[k % 6].money / 3) + 10);
                        pot += bet;
                        players[k % 6].money -= bet;
                        cout << '\a';
                        cout << players[k % 6].name << " ставит " << bet << endl << endl;
                        betOn = bet;
                        players[k % 6].goodToGo = 1;
                    }
                }

            }
        }

        if (betOn && playersToBet()) {
            for (int k = bind + 1; k < bind + 7; k++) {
                if (k % 6 == 4) {
                    if (players[4].round && players[4].goodToGo == 0) {
                        cout << "Ваши действия: (1) СБРОСИТЬ (3) ПОСТАВИТЬ/ОТВЕТИТЬ ";
                        cin >> action;
                        while (action != 1 && action != 3) {
                            cout << "Неккоректный ввод." << endl;
                            cout << "Ваши действия: (1) СБРОСИТЬ (3) ПОСТАВИТЬ/ОТВЕТИТЬ ";
                            cin >> action;
                            cout << endl << endl;
                        }
                        if (action == 1)
                            players[4].round = 0;
                        else {
                            pot += betOn;
                            players[4].money -= betOn;
                            players[4].goodToGo = 1;
                        }
                    }
                }

                else {
                    if (players[k % 6].round == 0 || players[k % 6].goodToGo == 1)
                        continue;
                    action = rand() % 2;
                    if (action == 0) {
                        players[k % 6].round = 0;
                        cout << players[k % 6].name << " сбросил/а карты..." << endl << endl;
                    }
                    else {
                        pot += betOn;
                        players[k % 6].money -= betOn;
                        cout << players[k % 6].name << " отвечает!" << endl << endl;
                        players[k % 6].goodToGo = 1;
                    }
                }
            }
        }
    }

    int oneLeft() {
        int count = 0;
        for (int k = 0; k < 6; k++)
            if (players[k].round)
                count++;
        if (count == 1)
            return 1;
        else
            return 0;
    }

    int getWinner() {
        int winner;
        for (int k = 0; k < 6; k++)
            if (players[k].round)
                winner = k;
        return winner;
    }

    int getScore(Card hand[]) {
        qsort(hand, 5, sizeof(Card), compareCards);
        int straight, flush, three, four, full, pairs, high;
        int k;

        straight = flush = three = four = full = pairs = high = 0;
        k = 0;

        /*checks for flush*/
        while (k < 4 && hand[k].suit == hand[k + 1].suit)
            k++;
        if (k == 4)
            flush = 1;

        /* checks for straight*/
        k = 0;
        while (k < 4 && hand[k].rank == hand[k + 1].rank - 1)
            k++;
        if (k == 4)
            straight = 1;

        /* checks for fours */
        for (int i = 0; i < 2; i++) {
            k = i;
            while (k < i + 3 && hand[k].rank == hand[k + 1].rank)
                k++;
            if (k == i + 3) {
                four = 1;
                high = hand[i].rank;
            }
        }

        /*checks for threes and fullhouse*/
        if (!four) {
            for (int i = 0; i < 3; i++) {
                k = i;
                while (k < i + 2 && hand[k].rank == hand[k + 1].rank)
                    k++;
                if (k == i + 2) {
                    three = 1;
                    high = hand[i].rank;
                    if (i == 0) {
                        if (hand[3].rank == hand[4].rank)
                            full = 1;
                    }
                    else if (i == 1) {
                        if (hand[0].rank == hand[4].rank)
                            full = 1;
                    }
                    else {
                        if (hand[0].rank == hand[1].rank)
                            full = 1;
                    }
                }
            }
        }

        if (straight && flush)
            return 170 + hand[4].rank;
        else if (four)
            return 150 + high;
        else if (full)
            return 130 + high;
        else if (flush)
            return 110;
        else if (straight)
            return 90 + hand[4].rank;
        else if (three)
            return 70 + high;

        /* checks for pairs*/
        for (k = 0; k < 4; k++)
            if (hand[k].rank == hand[k + 1].rank) {
                pairs++;
                if (hand[k].rank > high)
                    high = hand[k].rank;
            }

        if (pairs == 2)
            return 50 + high;
        else if (pairs)
            return 30 + high;
        else
            return hand[4].rank;
    }

    int tryHand(int array[], int player) {
        Card hand[5];

        /* get cards from table and player */
        for (int i = 1; i < 4; i++)
            hand[i - 1] = tableCards[array[i]];

        for (int i = 0; i < 2; i++)
            hand[i + 3] = players[player].cards[i];

        return getScore(hand);

    }

    void evaluateHands() {
        int stack[10], k;
        int currentPoints;

        for (int q = 0; q < 6; q++) {
            if (players[q].round) {
                stack[0] = -1; /* -1 is not considered as part of the set */
                k = 0;
                while (1) {
                    if (stack[k] < 4) {
                        stack[k + 1] = stack[k] + 1;
                        k++;
                    }

                    else {
                        stack[k - 1]++;
                        k--;
                    }

                    if (k == 0)
                        break;

                    if (k == 3) {
                        currentPoints = tryHand(stack, q);
                        if (currentPoints > handPoints[q]) {
                            handPoints[q] = currentPoints;
                            for (int x = 0; x < 3; x++)
                                bestHand[q][x] = stack[x + 1];
                        }
                    }
                }

            }
        }
    } /*end of evaluateHands() */

    void printWinningHand(int winner) {
        setlocale(LC_ALL, "Russian");
        Card winningHand[5];
        for (int i = 0; i < 3; i++)
            winningHand[i] = tableCards[bestHand[winner][i]];

        for (int i = 0; i < 2; i++)
            winningHand[i + 3] = players[winner].cards[i];

        qsort(winningHand, 5, sizeof(Card), compareCards);

        cout << "  Выигрышная комбинация:" << endl;
        cout << "   ___   ___   ___   ___   ___" << endl;
        cout << "  | " << ranks[winningHand[0].rank] << " | | " << ranks[winningHand[1].rank] << " | | " << ranks[winningHand[2].rank] << " | | " << ranks[winningHand[3].rank] << " | | " << ranks[winningHand[4].rank] << " |" << endl;
        cout << "  | " << suits[winningHand[0].suit] << " | | " << suits[winningHand[1].suit] << " | | " << suits[winningHand[2].suit] << " | | " << suits[winningHand[3].suit] << " | | " << suits[winningHand[4].suit] << " |" << endl;
        cout << "  |___| |___| |___| |___| |___|" << endl;
        cout << endl << endl;

    }

    /* main gameplay function*/
    void startGame() {
        setlocale(LC_ALL, "Russian");
        int i = 0;


        while (playersLeft() > 1) {
            /* starting default values*/
            for (int z = 0; z < 6; z++)
                if (players[z].money < 1) {
                    players[z].playing = 0;
                    players[z].round = 0;
                }
            for (int z = 0; z < 6; z++) {
                if (players[z].playing)
                    players[z].round = 1;
                handPoints[z] = -1;
            }
            for (int x = 0; x < 6; x++) {
                for (int y = 0; y < 3; y++) {
                    bestHand[x][y] = -1;
                }
            }

            /* checking for game over*/
            if (players[4].playing == 0) {
                cout << "У вас закончились деньги." << endl;
                cout << "Игра закончилась." << endl;
                break;
            }

            bind = i % 6;

            /* paying bind */
            pot = 20;
            if (players[bind].money >= 20)
                players[bind].money -= 20;
            else
                players[bind].playing = 0;

            cout << "Приготовьтесь к раунду " << (i + 1) << "..." << endl;

            deck1.shuffle();

            /* pre-flop */
            deal();
            printTable();
            takeBets();
            if (oneLeft()) {
                winner = getWinner();
                cout << players[winner].name << " выйграл $" << pot << endl << endl;
                i++;
                continue;
            }

            /* flop */
            flop();
            cout << endl;
            printTable();
            takeBets();
            if (oneLeft()) {
                winner = getWinner();
                cout << players[winner].name << " выйграл $" << pot << endl << endl;
                i++;
                continue;
            }

            /* turn */
            turn();
            cout << endl;
            printTable();
            takeBets();
            if (oneLeft()) {
                winner = getWinner();
                cout << players[winner].name << " выйграл $" << pot << endl << endl;
                i++;
                continue;
            }

            /* river */
            river();
            cout << endl;
            printTable();
            takeBets();

            evaluateHands();

            /*find and declare round winner*/
            maxPoints = 0;
            for (int q = 0; q < 6; q++) {
                if (players[q].round) {
                    if (handPoints[q] > maxPoints) {
                        maxPoints = handPoints[q];
                        roundWinner = q;
                    }
                }
            }
            cout << endl;
            cout << players[roundWinner].name << " выйграл $" << pot << " с комбинацией ";
            if (maxPoints < 30)
                cout << "СТАРШАЯ КАРТА";
            else if (maxPoints < 50)
                cout << "ПАРА";
            else if (maxPoints < 70)
                cout << "ДВЕ ПАРЫ";
            else if (maxPoints < 90)
                cout << "СЕТ";
            else if (maxPoints < 110)
                cout << "СТРИТ";
            else if (maxPoints < 130)
                cout << "ФЛЕШ";
            else if (maxPoints < 150)
                cout << "ФУЛЛ ХАУС";
            else if (maxPoints < 170)
                cout << "КАРЕ";
            else
                cout << "СТРИТ ФЛЕШ";
            cout << endl << endl;

            printWinningHand(roundWinner);

            players[roundWinner].money += pot;

            i++;
        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    string name;
    PokerGame game1;

    srand(time(NULL));

    cout << "Добро пожаловать в Консольный Покер!" << endl << endl;
    cout << "\tЗдесь как подсказка, будут находится комбинации: " << endl << endl;
    cout << "\t\tСТАРШАЯ КАРТА - это 1 карта. Выигрывает стоящая выше по рангу " << endl;
    cout << "\t\tПАРА – это 2 одинаковые карты " << endl;
    cout << "\t\tДВЕ ПАРЫ – 4 карты, среди которых собраны по 2 одинаковых по рангу " << endl;
    cout << "\t\tСЕТ – 3 карты одного ранга " << endl;
    cout << "\t\tСТРИТ – 5 собранных по порядку карт любой масти " << endl;
    cout << "\t\tФЛЕШ – 5 одномастных карт " << endl;
    cout << "\t\tФУЛЛ ХАУС – комбинация, включающая в себя «Пару» и «Тройку» одновременно " << endl;
    cout << "\t\tКАРЕ – 4 карты одного ранга " << endl;
    cout << "\t\tСТРИТ ФЛЕШ – 5 карт одной масти по порядку " << endl << endl;
    cout << "Введите свое имя на латинице: ";
    cin >> name;

    cout << "Отлично " << name << " приступим к игре!" << endl << endl;

    game1.start(name);

    return 0;
}