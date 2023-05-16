#pragma once
#include "Piece.hpp"
namespace gameLogic {
	class King : public Piece {
	public:
		King(std::string color) : Piece(color) {}
		std::string showPiece() const;
		int canMove(const int deplacementX, const int deplacementY, const bool capture = false) const;
		bool isKing() const;
	public:
		bool inCheck = false;
	};
}