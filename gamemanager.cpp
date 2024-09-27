#include "wordle.h"
#include "gamemanager.h"




GameManager::GameManager(QObject *parent) : QObject(parent), gameOver(false)
{

}

bool GameManager::isGameOver(){
    return gameOver;
}

void GameManager::setGameOver(bool value){
    gameOver = value;
}

void GameManager::onGuessesLeftChanged(int guessLeft) {
    if (guessLeft <= 0) {
        setGameOver(true);
    }
}
