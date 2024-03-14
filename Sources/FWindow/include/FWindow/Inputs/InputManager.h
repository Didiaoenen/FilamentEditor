/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <unordered_map>

#include "FWindow/Window.h"
#include "FWindow/Inputs/EKey.h"
#include "FWindow/Inputs/EKeyState.h"
#include "FWindow/Inputs/EMouseButton.h"
#include "FWindow/Inputs/EMouseButtonState.h"

namespace FWindow::Inputs
{
	/**
	* Handles inputs (Mouse and keyboard)
	*/
	class InputManager
	{
	public:
		/**
		* Create the window
		* @param p_windowSettings
		*/
		InputManager(Window& p_window);

		/**
		* Destroy the input manager by removing listeners on the window
		*/
		~InputManager();

		/**
		* Return the current state of the given key
		* @param p_key
		*/
		EKeyState GetKeyState(EKey p_key) const;

		/**
		* Return the current state of the given mouse button
		* @param p_button
		*/
		EMouseButtonState GetMouseButtonState(EMouseButton p_button) const;

		/**
		* Return true if the given key has been pressed during the frame
		* @param p_key
		*/
		bool IsKeyPressed(EKey p_key) const;

		/**
		* Return true if the given key has been released during the frame
		* @param p_key
		*/
		bool IsKeyReleased(EKey p_key) const;

		/**
		* Return true if the given mouse button has been pressed during the frame
		* @param p_button
		*/
		bool IsMouseButtonPressed(EMouseButton p_button) const;

		/**
		* Return true if the given mouse button has been released during the frame
		* @param p_button
		*/
		bool IsMouseButtonReleased(EMouseButton p_button) const;

		/**
		* Return the current mouse position relative to the window
		*/
		std::pair<double, double> GetMousePosition() const;

		/**
		* Clear any event occured
		* @note Should be called at the end of every game tick
		*/
		void ClearEvents();

	private:
		void OnKeyPressed(int p_key);
		void OnKeyReleased(int p_key);
		void OnMouseButtonPressed(int p_button);
		void OnMouseButtonReleased(int p_button);

	private:
		Window& m_window;

		FTools::Eventing::ListenerID m_keyPressedListener;
		FTools::Eventing::ListenerID m_keyReleasedListener;
		FTools::Eventing::ListenerID m_mouseButtonPressedListener;
		FTools::Eventing::ListenerID m_mouseButtonReleasedListener;

		std::unordered_map<EKey, EKeyState>					m_keyEvents;
		std::unordered_map<EMouseButton, EMouseButtonState>	m_mouseButtonEvents;
	};
}