#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);

    Q_INVOKABLE bool isGameOver();
    Q_INVOKABLE void setGameOver(bool value);

private:
    bool gameOver;
    int guessLeft;

public slots:
    void onGuessesLeftChanged(int guessLeft);

};

#endif // GAMEMANAGER_H
