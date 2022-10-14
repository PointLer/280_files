#include "hand.h"

Hand::Hand(){
    this->discardAll();
}

void Hand::discardAll(){
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card c){//有些数值不知道对不对
    //if the card is 2-10:
    if(0 <= c.spot && c.spot < 9){
        //if hard now:
        if(!curValue.soft){
            curValue.count = curValue.count + 2 + c.spot;
        }
        //if soft now:
        else{
            if(2 + c.spot + curValue.count <= 21) {
                curValue.count = curValue.count + 2 + c.spot;
            }
            else{
                curValue.soft = false;
                curValue.count = curValue.count - 8 + c.spot;
            }
        }
    }
    //if the card c is an ace:
    else if(c.spot == 12){
        //if hard now:
        if(!curValue.soft){
            if(curValue.count >= 11){
                curValue.count += 1;
            }
            else{
                curValue.soft = true;
                curValue.count += 11;
            }
        }
        //if soft now:
        else{
            curValue.count += 1;
        }
    }
    //if the card is J, Q or K:
    else{
        //if hard now:
        if(!curValue.soft){
            curValue.count += 10;
        }
        //if soft now:
        else{
            if(curValue.count <= 11){
                curValue.count += 10;
            }
            else{
                curValue.soft = false;
            }
        }
    }
}

HandValue Hand::handValue() const{
    return curValue;
}