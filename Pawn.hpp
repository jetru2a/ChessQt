#pragma once
#include "Piece.hpp"
namespace gameLogic {
	class Pawn : public Piece {
	public:
		Pawn(std::string color) : Piece(color) {}
		std::string showPiece() const;
		int canMove(const int deplacementX, const int deplacementY, const bool capture = false) const;
		bool isKing() const;
	};
}