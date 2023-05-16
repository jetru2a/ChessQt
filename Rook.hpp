#pragma once
#include "Piece.hpp"
namespace gameLogic {
	class Rook : public Piece {
	public:
		Rook(std::string color) : Piece(color) {}
		std::string showPiece() const;
		int canMove(const int deplacementX, const int deplacementY, const bool capture = false) const;
		bool isKing() const;
	};
}