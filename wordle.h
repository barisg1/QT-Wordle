#pragma once

#ifndef WORDLE_H
#define WORDLE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSet>
#include <QMap>
#include <QColor>
#include <QVariantMap>

class Wordle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList guessedWords READ guessedWords NOTIFY guessedWordsChanged)
    Q_PROPERTY(QStringList feedbacks READ feedbacks NOTIFY feedbacksChanged)
    Q_PROPERTY(QString targetWord READ targetWord WRITE setTargetWord NOTIFY targetWordChanged)
    Q_PROPERTY(QVariantMap keyColors READ keyColors NOTIFY keyColorsChanged)


public:
    explicit Wordle(QObject *parent = nullptr);

    QStringList guessedWords() const {return m_guessedWords;}
    QStringList feedbacks() const {return m_feedbacks;}
    QString targetWord() const {return m_targetWord;}
    QVariantMap keyColors() const;

    Q_INVOKABLE bool checkGuess(const QString &guess);
    Q_INVOKABLE void clearGuesses();
    Q_INVOKABLE bool isValidGuess(const QString &guess);


public slots:
    void setTargetWord(const QString &word);

signals:
    void guessedWordsChanged();
    void feedbacksChanged();
    void targetWordChanged();
    void keyColorsChanged();
    void guessesLeftChanged(int guessLeft);

private:
    QStringList m_guessedWords;
    QStringList m_feedbacks;
    QString m_targetWord;
    QSet<QString> m_validWords;
    QMap<QString, QColor> m_keyColors;

    void loadAllowedWords();
    void initializeKeyColors();


};

#endif // WORDLE_H
