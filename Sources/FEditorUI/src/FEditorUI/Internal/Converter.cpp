/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Internal/Converter.h"

ImVec4 FEditorUI::Internal::Converter::ToImVec4(const Types::Color & p_value)
{
	return ImVec4(p_value.r, p_value.g, p_value.b, p_value.a);
}

FEditorUI::Types::Color FEditorUI::Internal::Converter::ToColor(const ImVec4 & p_value)
{
	return Types::Color(p_value.x, p_value.y, p_value.z, p_value.w);
}

ImVec2 FEditorUI::Internal::Converter::ToImVec2(const OvMaths::FVector2 & p_value)
{
	return ImVec2(p_value.x, p_value.y);
}

OvMaths::FVector2 FEditorUI::Internal::Converter::ToFVector2(const ImVec2 & p_value)
{
	return OvMaths::FVector2(p_value.x, p_value.y);
}
