// This is the main DLL file.

#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "SentencePieceWrapper.h"
#include <locale>
#include <codecvt>

using namespace System::Runtime::InteropServices;
using namespace SentencePieceWrapper;
SentencePiece::SentencePiece()
{
	processor = new sentencepiece::SentencePieceProcessor();
}
bool SentencePiece::Load(String^ filename)
{
	std::string unmanaged = msclr::interop::marshal_as<std::string>(filename);
	auto status = processor->Load(unmanaged);
	/*
	if (!status.ok())
		return false;
	*/
	return true;
}

array<int>^ SentencePiece::Encode(String^ sentence)
{
	std::wstring unmanaged = msclr::interop::marshal_as<std::wstring>(sentence);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::string converted_str = converter.to_bytes(unmanaged);
	//wchar_t* wcharPtr = (wchar_t*)Marshal::StringToHGlobalAnsi(sentence).ToPointer();
	std::vector<int> ids;
	processor->Encode(converted_str, &ids);
	//Marshal::FreeHGlobal(IntPtr(wcharPtr));
	const int size = ids.size();
	array<int> ^temp = gcnew array<int>(size);
	for (int i = 0; i < size; i++) {
		temp[i] = ids[i];
	}
	return temp;
}
