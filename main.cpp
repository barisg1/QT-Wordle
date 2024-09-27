#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "wordle.h"
#include "gamemanager.h"
uint pcg_hash(uint input)
{
    uint state = input * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GameManager *gameManager = new GameManager();
    engine.rootContext()->setContextProperty("gameManager", gameManager);

    Wordle *wordle = new Wordle();
    engine.rootContext()->setContextProperty("wordle", wordle);

    QObject::connect(wordle, &Wordle::guessesLeftChanged, gameManager, &GameManager::onGuessesLeftChanged);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

