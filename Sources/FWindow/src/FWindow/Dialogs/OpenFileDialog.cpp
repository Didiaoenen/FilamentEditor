/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FWindow/Dialogs/OpenFileDialog.h"

#include <Windows.h>

FWindow::Dialogs::OpenFileDialog::OpenFileDialog(const std::string & p_dialogTitle) : FileDialog(GetOpenFileNameA, p_dialogTitle)
{
}

void FWindow::Dialogs::OpenFileDialog::AddFileType(const std::string & p_label, const std::string & p_filter)
{
	m_filter += p_label + '\0' + p_filter + '\0';
}
