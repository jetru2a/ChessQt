#include "TryMove.hpp"
#include "Piece.hpp"

gameLogic::TryMove::TryMove(int positionIn, int positionOut, gameLogic::Board* boardP) 
	: positionIn(positionIn), positionOut(positionOut), boardP(boardP), replacedPiece(boardP->movePiece(positionIn, positionOut)) {}
gameLogic::TryMove::~TryMove() {
	boardP->movePiece(positionOut, positionIn);
	if (replacedPiece !=nullptr)
		boardP->placePiece(move(replacedPiece), positionOut);
}