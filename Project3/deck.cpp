#include "deck.h"

Deck::Deck(){
    this -> reset();
}

void Deck::reset(){
    //initialize the suits:
    for(int i = 0; i < 13; i++) deck[i].suit = SPADES; 
    for(int j = 13; j < 26; j++) deck[j].suit = HEARTS;
    for(int p = 26; p < 39; p++) deck[p].suit = CLUBS;
    for(int q = 39; q < DeckSize; q++) deck[q].suit = DIAMONDS;

    //initialize the spots:
    for(int m = 0; m < DeckSize; m += 13){
        deck[m].spot = TWO;
        deck[m+1].spot = THREE;
        deck[m+2].spot = FOUR;
        deck[m+3].spot = FIVE;
        deck[m+4].spot = SIX;
        deck[m+5].spot = SEVEN;
        deck[m+6].spot = EIGHT;
        deck[m+7].spot = NINE;
        deck[m+8].spot = TEN;
        deck[m+9].spot = JACK;
        deck[m+10].spot = QUEEN;
        deck[m+11].spot = KING;
        deck[m+12].spot = ACE;
    }

    //initialize next card to deal with:
    this->next = 0;
}

void Deck::shuffle(int n){
    int min = n <= DeckSize / 2 ? n : DeckSize - n;
    Card temp[DeckSize];
    for(int i = 0; i < DeckSize; i++){
        temp[i] = deck[i];
    }

    for(int i = 0; i < min; i++){
        deck[2 * i] = temp[i + n];
        deck[2 * i + 1] = temp[i];
    }
    if(n > min){
        for(int i = min; i < n; i++){
            deck[min + i] = temp[i];
        }
    }

    next = 0;
}

Card Deck::deal(){//也许会有问题？exception没有体现
    if(next == DeckSize){
        DeckEmpty error;
        throw error;
    }
    else{
        return deck[next++];
    }
}

int Deck::cardsLeft(){
    return DeckSize - next;
}