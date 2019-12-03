#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{
    prepareNewGame();
    playerSymbolMap[Board::PlayerSymbol::NONE] = QString("NONE");
    playerSymbolMap[Board::PlayerSymbol::X] = QString("X");
    playerSymbolMap[Board::PlayerSymbol::O] = QString("O");
}

Game::~Game()
{

}

void Game::processMove(const int &board, const int &field)
{
    const QString whoseTurn = playerSymbolMap[gameState->getWhoseTurn()];
    if(gameState->makeMove(board, field))
    {
        emit markMove(board, field, whoseTurn);

        if(gameState->isBoardNotPlayable(board))
        {
            if(gameState->checkLocalWin() != Board::PlayerSymbol::NONE)
            {
                emit markLocalWin(board, whoseTurn);
            }
            if(gameState->gameEnded())
            {
                emit globalWin(whoseTurn);
                return;
            }
            playableBoards.removeOne(board);
        }

        if(gameState->getNextBoard() != 9)
            emit highlightPermittedBoards({gameState->getNextBoard()});
        else
            emit highlightPermittedBoards(playableBoards);

        emit updateWhoseTurn(playerSymbolMap[gameState->getWhoseTurn()]);
    }
}

void Game::prepareNewGame()
{
    gameState = std::unique_ptr<GameState>(new GameState());
    currentPlayerSymbol = Board::PlayerSymbol::X;
    playableBoards = {0,1,2,3,4,5,6,7,8};
}
