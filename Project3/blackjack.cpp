
#include "deck.h"
#include "rand.h"
#include "player.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
const unsigned int Minimum = 5;

//EFFECT：shuffle the deck for 7 times and update the player state.
void shuffling(Deck &play_deck, Player *play_game);

//REQUIRE: the deck is not empty.
//EFFECT: deal a card for the player and update the player state.
void deal_up_player(Deck &play_deck, Hand& hand, Player *play_game);

//REQUIRE: the deck is not empty.
//EFFECT: deal a face-up card for the dealer and update the player state.
void deal_up_dealer(Deck &play_deck, Hand& hand, Player *play_game, Card &up);

//REQUIRE: the deck is not empty.
//EFFECT: deal the hold card for the dealer.
void deal_down(Deck &play_deck, Hand& hand, Card &down);

int main(int argc, char *argv[]){
    //initialization from command lines:
    unsigned int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    string mode = argv[3];

    //game initializing:
    Deck play_deck;
    Player *play_game;
    Hand player_hand, dealer_hand;
    Card up_card, hole_card;//the dealer's cards
    int thishand = 1;
    int wager;

    //mode initializing
    if(mode == "simple") play_game = get_Simple();
    else  play_game = get_Counting();

    //first shuffling 7 times:
    shuffling(play_deck, play_game);

    //hands:
    while(bankroll >= Minimum && thishand <= hands){
        cout << "Hand " << thishand++ << " bankroll " << bankroll << endl;

        //initializing hands
        player_hand.discardAll();
        dealer_hand.discardAll();

        //check if reshuffling is needed:
        if(play_deck.cardsLeft() < 20){
            shuffling(play_deck, play_game);
        }

        //check the wager:
        wager = play_game->bet(bankroll, Minimum);
        cout << "Player bets " << wager << endl;

        //add cards and announce up ones:
        deal_up_player(play_deck, player_hand, play_game);
        deal_up_dealer(play_deck, dealer_hand, play_game, up_card);
        deal_up_player(play_deck, player_hand, play_game);
        deal_down(play_deck, dealer_hand, hole_card);

        //check if natural 21 is met:
        if(player_hand.handValue().count == 21){
            bankroll += (3 * wager) / 2;
            cout << "Player dealt natural 21\n";
        }
    
        //if no natural 21, player plays his hand:
        while(play_game->draw(up_card, player_hand)){
            Card new_card = play_deck.deal();
            player_hand.addCard(new_card);
            play_game->expose(new_card);
            cout << "Player dealt "<< SpotNames[new_card.spot] << " of "<<SuitNames[new_card.suit] << endl;
        }
        cout << "Player's total is " << player_hand.handValue().count << endl;

        //check if busting:
        if(player_hand.handValue().count > 21){
            cout << "Player busts\n";
            bankroll -= wager;
            continue;
        }
        //expose hole card:
        cout << "Dealer's hole card is " << SpotNames[hole_card.spot] << " of " << SuitNames[hole_card.suit] << endl;
        play_game->expose(hole_card);
        //dealer's hand as player not busted:
        while(dealer_hand.handValue().count < 17){
            Card new_card = play_deck.deal();
            dealer_hand.addCard(new_card);
            play_game->expose(new_card);
            cout << "Dealer dealt "<< SpotNames[new_card.spot] << " of "<<SuitNames[new_card.suit] << endl;
        }
        //announce and check the dealer if busted:
        cout << "Dealer's total is " << dealer_hand.handValue().count << endl;
        if(dealer_hand.handValue().count > 21){
            cout << "Dealer busts\n";
            bankroll += wager;
            continue;
        }
        //compare dealer and player as both not busted:
        if(player_hand.handValue().count > dealer_hand.handValue().count){
            cout << "Player wins\n";
            bankroll += wager;
        }
        else if(player_hand.handValue().count < dealer_hand.handValue().count){
            cout << "Dealer wins\n";
            bankroll -= wager;
        }
        else{
            cout << "Push\n";
        }
    }
    //announce the outcome:
    cout << "Player has " << bankroll << " after " << thishand - 1 << " hands\n";
    return 0;
}


void shuffling(Deck &play_deck, Player *play_game){
    play_deck.reset();
    cout << "Shuffling the deck\n";
    for(int i = 0; i < 7; i++){
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        play_deck.shuffle(cut);
    }
    play_game->shuffled();
}

void deal_up_player(Deck &play_deck, Hand& hand, Player *play_game){
    Card up_card = play_deck.deal();
    hand.addCard(up_card);
    cout << "Player dealt "<< SpotNames[up_card.spot] << " of "<<SuitNames[up_card.suit] << endl;
    play_game->expose(up_card);
}

void deal_up_dealer(Deck &play_deck, Hand& hand, Player *play_game, Card &up){
    up = play_deck.deal();
    hand.addCard(up);
    cout << "Dealer dealt "<< SpotNames[up.spot] << " of "<<SuitNames[up.suit] << endl;
    play_game->expose(up);
}

void deal_down(Deck &play_deck, Hand& hand, Card &down){
    down = play_deck.deal();
    hand.addCard(down);
}