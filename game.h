#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <gamestate.hpp>

class Game : public QObject
{
    Q_OBJECT

    public:
    explicit Game(QObject *parent = nullptr);
    ~Game();

    signals:
    void markMove(const int &board, const int &field, const QString symbol);
    void markLocalWin(const int &board, const QString symbol);
    void updateWhoseTurn(const QString symbol);
    void globalWin(const QString symbol);
    void highlightPermittedBoards(const QVector<int> permittedBoards);

    public slots:
    void processMove(const int &board, const int &field);
    void prepareNewGame();

    private:
    std::unique_ptr<GameState> gameState;
    Board::PlayerSymbol currentPlayerSymbol;
    QVector<int> playableBoards;
    std::map<Board::PlayerSymbol, QString> playerSymbolMap;
};

#endif // GAME_H
