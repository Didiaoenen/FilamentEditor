/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FWindow/Dialogs/FileDialog.h"

namespace FWindow::Dialogs
{
	/**
	* Dialog window that asks the user to select a file from the disk
	*/
	class OpenFileDialog : public FileDialog
	{
	public:
		/**
		* Constructor
		* @param p_dialogTitle
		*/
		OpenFileDialog(const std::string& p_dialogTitle);

		/**
		* Add a supported file type to the dialog window
		* @param p_label
		* @param p_filter
		*/
		void AddFileType(const std::string& p_label, const std::string& p_filter);
	};
}