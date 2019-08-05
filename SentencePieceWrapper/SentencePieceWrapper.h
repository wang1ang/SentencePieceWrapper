// SentencePieceWrapper.h

#pragma once
using namespace System;

namespace SentencePieceWrapper {

	public ref class SentencePiece
	{
	public:
		SentencePiece();
		bool Load(String^ filename);
		array<int> ^Encode(String^ sentencee);
	private:
		sentencepiece::SentencePieceProcessor *processor;
	};
}
