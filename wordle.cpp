#include "wordle.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QColor>
#include <QRandomGenerator>
#include <QVector>



Wordle::Wordle(QObject *parent) : QObject(parent)
{
    m_guessedWords.clear();
    loadAllowedWords();
    initializeKeyColors();
}

void Wordle::setTargetWord(const QString &word){
    if(word.isEmpty()){
        int index = QRandomGenerator::global()->bounded(m_validWords.count());
        QVector<QString> vector = m_validWords.values().toVector();
        m_targetWord = vector[index];
    }else{
        m_targetWord = word;
    }

    m_guessedWords.clear();

    emit targetWordChanged();
    emit keyColorsChanged();
    emit guessedWordsChanged();
    emit feedbacksChanged();
    qDebug() << "target word changed" << m_targetWord;
}

bool Wordle::checkGuess(const QString &guess) {
    QString upperGuess = guess.toUpper();
    if (!isValidGuess(guess)){
        qDebug() << "Invalid word: " << guess;
        return false;
    }
    QString upperTargetWord = m_targetWord.toUpper();
    QString remainingLetters = upperTargetWord;

    if (upperGuess.length() != upperTargetWord.length())
        return false;

    QString feedback;

    for (int i = 0; i < upperTargetWord.length(); ++i) {
        QString letter = (QString) upperGuess[i];

        if (letter == upperTargetWord[i]) {
            remainingLetters = remainingLetters.replace(upperGuess[i], "");
            m_keyColors[letter] = QColor("green");
            feedback += upperGuess[i];
        }
        else {
            feedback += "-";
            m_keyColors[letter] = QColor("#3A3A3C");
        }
    }
    for (int i = 0; i < upperTargetWord.length(); ++i) {
        QString letter = (QString) upperGuess[i];

        if(remainingLetters.contains(upperGuess[i]) && upperGuess[i] != upperTargetWord[i]){
            remainingLetters = remainingLetters.replace(upperGuess[i], "");
            feedback.replace(i, 1, "+");
            m_keyColors[letter] = QColor("#B59F3B");
        }
    }

    emit keyColorsChanged();

    m_guessedWords.append(upperGuess);
    m_feedbacks.append(feedback);

    emit guessedWordsChanged();
    emit feedbacksChanged();
    int guessLeft = 6 - m_guessedWords.size();
    emit guessesLeftChanged(guessLeft);

    return (upperGuess == upperTargetWord);
}

void Wordle::clearGuesses(){
    m_guessedWords.clear();
    m_feedbacks.clear();
    initializeKeyColors();
}

bool Wordle::isValidGuess(const QString &guess){
    return m_validWords.contains(guess.toLower());
}


QVariantMap Wordle::keyColors() const {
    QVariantMap colorMap;
    for (const auto &key : m_keyColors.keys()) {
        colorMap[key] = m_keyColors[key].name();
    }
    return colorMap;
}

void Wordle::initializeKeyColors() {
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        m_keyColors[QString(letter)] = QColor("#818384");
    }
    m_keyColors[QString("Del")] = QColor("#818384");
    m_keyColors[QString("Enter")] = QColor("#818384");

}

void Wordle::loadAllowedWords(){
    //https://github.com/tabatkins/wordle-list/blob/main/words
    QFile file(":/words.txt");

    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString word = in.readLine().trimmed();
            if(!word.isEmpty()){
                m_validWords.insert(word);
            }
        }
        file.close();
    }else{
        qDebug() << "Failed to open allowed words";
    }
}

