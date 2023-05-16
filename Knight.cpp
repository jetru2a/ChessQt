#pragma once
#include "Knight.hpp"
std::string gameLogic::Knight::showPiece() const {
	return color_[0] + std::string("Knight");
}


//les mouvement dans le board vont comme ceci:
// -9 -8 -7
// -1  0 +1
// +7 +8 +9
//(representation dune section du board de 9 piece)
int gameLogic::Knight::canMove(const int deplacementX, const int deplacementY, const bool) const
{
	//valide tant quil bouge de 2 range et 1 colonne ou 2 colonne et 1 range
	return 100 * ((abs(deplacementY) == 1 && abs(deplacementX) == 2) || (abs(deplacementY) == 2 && abs(deplacementX) == 1));
}
bool gameLogic::Knight::isKing() const { return false; }