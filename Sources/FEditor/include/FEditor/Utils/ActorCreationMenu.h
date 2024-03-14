/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <functional>

namespace FEditorUI::Widgets::Menu
{
    class MenuList;
}

namespace OvCore::ECS
{
    class Actor;
}

namespace FEditor::Utils
{
    /**
    * Class exposing tools to generate an actor creation menu
    */
    class ActorCreationMenu
    {
    public:
        /**
        * Disabled constructor
        */
        ActorCreationMenu() = delete;

        /**
        * Generates an actor creation menu under the given MenuList item.
        * Also handles custom additionnal OnClick callback
        * @param p_menuList
        * @param p_parent
        * @param p_onItemClicked
        */
        static void GenerateActorCreationMenu(FEditorUI::Widgets::Menu::MenuList& p_menuList, OvCore::ECS::Actor* p_parent = nullptr, std::optional<std::function<void()>> p_onItemClicked = {});
    };
}
