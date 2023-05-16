#pragma once
#include "Bishop.hpp"



std::string gameLogic::Bishop::showPiece() const {
	return color_[0] + std::string("Bishop");
}

//les mouvement dans le board vont comme ceci:
// -9 -8 -7
// -1  0 +1
// +7 +8 +9
//(representation dune section du board de 9 piece)
int gameLogic::Bishop::canMove(const int deplacementX, const int deplacementY, const bool) const {
	int signY = (0 < deplacementY) - (deplacementY < 0);
	//bouge de -9/+9 si en ligne \, bouge de -7/+7 si en ligne /
	return signY * ((deplacementY == deplacementX) * 9 + (deplacementY == -deplacementX) * 7);
}

bool gameLogic::Bishop::isKing() const { return false; }