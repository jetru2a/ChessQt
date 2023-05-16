#pragma once
#include "Rook.hpp"

std::string gameLogic::Rook::showPiece() const {
	return color_[0] + std::string("Rook");
}

//les mouvement dans le board vont comme ceci:
// -9 -8 -7
// -1  0 +1
// +7 +8 +9
//(representation dune section du board de 9 piece)
int gameLogic::Rook::canMove(const int deplacementX,const int deplacementY, bool) const {
	int signX = (0 < deplacementX) - (deplacementX < 0);
	int signY = (0 < deplacementY) - (deplacementY < 0);
	//avance de -1/+1 si horizontale, -8/+8 si vertical
	return (deplacementY == 0) * signX + (deplacementX == 0) * signY * 8;
}
bool gameLogic::Rook::isKing() const { return false; }