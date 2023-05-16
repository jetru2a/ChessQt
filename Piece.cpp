#pragma once
#include "Piece.hpp"



bool Piece::isWhite() { return color_ == "white"; }
void Piece::hasMoved() {
	moved_ = true;
}
std::string Piece::getColor() {
	return color_;
}