#pragma once
#include "King.hpp"

std::string gameLogic::King::showPiece() const {
	if (inCheck)
		return color_[0] + std::string("KingC");
	return color_[0] + std::string("King");
}


//les mouvement dans le board vont comme ceci:
// -9 -8 -7
// -1  0 +1
// +7 +8 +9
//(representation dune section du board de 9 piece)
int gameLogic::King::canMove(const int deplacementX, const int deplacementY, const bool) const {
	//est valide tant quil bouge de une case
	return 100 * (abs(deplacementY) <= 1 && abs(deplacementX) <= 1) +
	50 * (deplacementY == 0 && abs(deplacementX) == 2 && !moved_);
}

bool gameLogic::King::isKing() const { return true; }
