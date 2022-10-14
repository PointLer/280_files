#include "player.h"
//reminder: always write ';' after a declaration of one class!

class Simple :public Player{
 public:
    int bet(unsigned int bankroll, unsigned int minimum){
        return minimum;//.h里有require至少剩minimum钱
    }

    bool draw(Card dealer, const Hand &player){
        HandValue hand = player.handValue();

        //hard count:
        if(!hand.soft){
            if(hand.count <= 11){
                return true;
            }
            else if(hand.count == 12){
                if(dealer.spot <= 1 || dealer.spot >= 5){
                    return true;
                }
            }
            else if(hand.count >= 13 && hand.count <= 16){
                if(dealer.spot >= 5){
                    return true;
                }
            }
        }

        //soft count:
        else{
            if(hand.count <= 17){
                return true;
            }
            else if(hand.count == 18){
                if((dealer.spot >= 1 && dealer.spot <= 4) || dealer.spot >= 7){
                    return true;
                }
            }
        }

        //other cases: (actually else for the 2 cases above)
        return false;
    }

    void expose(Card c){}

    void shuffled(){}
};

class Counting :public Player{
    int counting;
 public:
    Counting(): counting(0){};
    int bet(unsigned int bankroll, unsigned int minimum){
        if(counting >= 2 && bankroll >= 2 * minimum){
            return 2 * minimum;
        }
        return minimum;
    }

    bool draw(Card dealer, const Hand &player){
        return Simple().draw(dealer, player);
    }

    void expose(Card c){
        if(c.spot <= 4){
            counting ++;
        }
        else if(c.spot >= 8){
            counting --;
        }
    }

    void shuffled(){
        counting = 0;
    }
};

//static Simple *simple_player = new Simple;
//static Counting *counting_player = new Counting;

Player *get_Simple()
{
    static Simple simple_player;
    return &simple_player;
}

Player *get_Counting()
{
    static Counting counting_player;
    return &counting_player;
}


