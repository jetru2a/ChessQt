#pragma once
#include "Pawn.hpp"

std::string gameLogic::Pawn::showPiece() const {
	return color_[0] + std::string("Pawn");
}


//les mouvement dans le board vont comme ceci:
// -9 -8 -7
// -1  0 +1
// +7 +8 +9
//(representation dune section du board de 9 piece)
int gameLogic::Pawn::canMove(int deplacementX, int deplacementY, bool capture) const {
	if (color_ == "black") {
		//avance droit
		if (deplacementX == 0 && !capture && (deplacementY == 1 || (!moved_ && deplacementY == 2)))
			return 8;
		//capture en diagonal
		else if (capture && deplacementY == 1 && abs(deplacementX) == 1)
			return 8 + deplacementX;
	}
	else {
		//avance droit
		if (deplacementX == 0 && !capture && (deplacementY == -1 || (!moved_ && deplacementY == -2)))
			return -8;
		//capture en diagonal
		else if (capture && deplacementY == -1 && abs(deplacementX) == 1)
			return -8 + deplacementX;
	}
	return 0;
}
bool gameLogic::Pawn::isKing() const { return false; }