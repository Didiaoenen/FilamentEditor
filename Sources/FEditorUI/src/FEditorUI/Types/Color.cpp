/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Types/Color.h"

const FEditorUI::Types::Color FEditorUI::Types::Color::Red		= { 1.f, 0.f, 0.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Green		= { 0.f, 1.f, 0.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Blue		= { 0.f, 0.f, 1.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::White		= { 1.f, 1.f, 1.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Black		= { 0.f, 0.f, 0.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Grey		= { 0.5f, 0.5f, 0.5f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Yellow		= { 1.f, 1.f, 0.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Cyan		= { 0.f, 1.f, 1.f };
const FEditorUI::Types::Color FEditorUI::Types::Color::Magenta	= { 1.f, 0.f, 1.f };

FEditorUI::Types::Color::Color(float p_r, float p_g, float p_b, float p_a) : r(p_r), g(p_g), b(p_b), a(p_a)
{
}

bool FEditorUI::Types::Color::operator==(const Color & p_other)
{
	return this->r == p_other.r && this->g == p_other.g && this->b == p_other.b && this->a == p_other.a;
}

bool FEditorUI::Types::Color::operator!=(const Color & p_other)
{
	return !operator==(p_other);
}
