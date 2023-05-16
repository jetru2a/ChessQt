#pragma once
#include "Queen.hpp"

std::string gameLogic::Queen::showPiece() const {
	return color_[0] + std::string("Queen");
}


bool gameLogic::Queen::isKing() const { return false; }

//les mouvement dans le board vont comme ceci:
// -9 -8 -7
// -1  0 +1
// +7 +8 +9
//(representation dune section du board de 9 piece)
int gameLogic::Queen::canMove(const int deplacementX, const int deplacementY, const bool) const {
	int signY = ((0 < deplacementY) - (deplacementY < 0));
	int signX = ((0 < deplacementX) - (deplacementX < 0));
	//mouvement fou + mouvement tour
	return signY * ((deplacementY == deplacementX) * 9 + (deplacementY == -deplacementX) * 7)
		+ (deplacementY == 0) * signX + (deplacementX == 0) * signY * 8;
}