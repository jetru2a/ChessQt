#pragma once
#include "Piece.hpp"
namespace gameLogic {
	class TryMove {
	public:
		TryMove(int positionIn, int positionOut, gameLogic::Board* boardP);
		~TryMove();
	private:
		std::unique_ptr<Piece> replacedPiece;
		gameLogic::Board* boardP;
		int positionIn;
		int positionOut;
	};
}