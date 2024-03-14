/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditor/Panels/Hierarchy.h"
#include "FEditor/Core/EditorActions.h"

#include <FEditorUI/Widgets/Buttons/Button.h>
#include <FEditorUI/Widgets/Selection/CheckBox.h>
#include <FEditorUI/Widgets/Visual/Separator.h>
#include <FEditorUI/Plugins/DDSource.h>
#include <FEditorUI/Plugins/DDTarget.h>

#include <OvDebug/Logger.h>

#include <OvCore/Global/ServiceLocator.h>

#include <OvCore/ECS/Components/CCamera.h>
#include <OvCore/ECS/Components/CPointLight.h>
#include <OvCore/ECS/Components/CDirectionalLight.h>
#include <OvCore/ECS/Components/CSpotLight.h>
#include <OvCore/ECS/Components/CAmbientBoxLight.h>
#include <OvCore/ECS/Components/CAmbientSphereLight.h>
#include <OvCore/ECS/Components/CPhysicalBox.h>
#include <OvCore/ECS/Components/CPhysicalSphere.h>
#include <OvCore/ECS/Components/CPhysicalCapsule.h>
#include <OvCore/ECS/Components/CAudioSource.h>
#include <OvCore/ECS/Components/CAudioListener.h>

#include <FEditorUI/Plugins/ContextualMenu.h>

#include "FEditor/Utils/ActorCreationMenu.h"

class ActorContextualMenu : public FEditorUI::Plugins::ContextualMenu
{
public:
    ActorContextualMenu(OvCore::ECS::Actor* p_target, FEditorUI::Widgets::Layout::TreeNode& p_treeNode, bool p_panelMenu = false) :
        m_target(p_target),
        m_treeNode(p_treeNode)
    {
        using namespace FEditorUI::Panels;
        using namespace FEditorUI::Widgets;
        using namespace FEditorUI::Widgets::Menu;
        using namespace OvCore::ECS::Components;

        if (m_target)
        {
            auto& focusButton = CreateWidget<FEditorUI::Widgets::Menu::MenuItem>("Focus");
            focusButton.ClickedEvent += [this]
            {
                EDITOR_EXEC(MoveToTarget(*m_target));
            };

            auto& duplicateButton = CreateWidget<FEditorUI::Widgets::Menu::MenuItem>("Duplicate");
            duplicateButton.ClickedEvent += [this]
            {
                EDITOR_EXEC(DelayAction(EDITOR_BIND(DuplicateActor, std::ref(*m_target), nullptr, true), 0));
            };

            auto& deleteButton = CreateWidget<FEditorUI::Widgets::Menu::MenuItem>("Delete");
            deleteButton.ClickedEvent += [this]
            {
                EDITOR_EXEC(DestroyActor(std::ref(*m_target)));
            };

			auto& renameMenu = CreateWidget<FEditorUI::Widgets::Menu::MenuList>("Rename to...");

			auto& nameEditor = renameMenu.CreateWidget<FEditorUI::Widgets::InputFields::InputText>("");
			nameEditor.selectAllOnClick = true;

			renameMenu.ClickedEvent += [this, &nameEditor]
			{
				nameEditor.content = m_target->GetName();
			};

			nameEditor.EnterPressedEvent += [this](std::string p_newName)
			{
				m_target->SetName(p_newName);
			};
        }

		auto& createActor = CreateWidget<FEditorUI::Widgets::Menu::MenuList>("Create...");
        FEditor::Utils::ActorCreationMenu::GenerateActorCreationMenu(createActor, m_target, std::bind(&FEditorUI::Widgets::Layout::TreeNode::Open, &m_treeNode));
	}

	virtual void Execute() override
	{
		if (m_widgets.size() > 0)
			FEditorUI::Plugins::ContextualMenu::Execute();
	}

private:
	OvCore::ECS::Actor* m_target;
	FEditorUI::Widgets::Layout::TreeNode& m_treeNode;
};

void ExpandTreeNode(FEditorUI::Widgets::Layout::TreeNode& p_toExpand, const FEditorUI::Widgets::Layout::TreeNode* p_root)
{
	p_toExpand.Open();

	if (&p_toExpand != p_root && p_toExpand.HasParent())
	{
		ExpandTreeNode(*static_cast<FEditorUI::Widgets::Layout::TreeNode*>(p_toExpand.GetParent()), p_root);
	}
}

std::vector<FEditorUI::Widgets::Layout::TreeNode*> nodesToCollapse;
std::vector<FEditorUI::Widgets::Layout::TreeNode*> founds;

void ExpandTreeNodeAndEnable(FEditorUI::Widgets::Layout::TreeNode& p_toExpand, const FEditorUI::Widgets::Layout::TreeNode* p_root)
{
	if (!p_toExpand.IsOpened())
	{
		p_toExpand.Open();
		nodesToCollapse.push_back(&p_toExpand);
	}

	p_toExpand.enabled = true;

	if (&p_toExpand != p_root && p_toExpand.HasParent())
	{
		ExpandTreeNodeAndEnable(*static_cast<FEditorUI::Widgets::Layout::TreeNode*>(p_toExpand.GetParent()), p_root);
	}
}

FEditor::Panels::Hierarchy::Hierarchy
(
	const std::string & p_title,
	bool p_opened,
	const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	auto& searchBar = CreateWidget<FEditorUI::Widgets::InputFields::InputText>();
	searchBar.ContentChangedEvent += [this](const std::string& p_content)
	{
		founds.clear();
		auto content = p_content;
		std::transform(content.begin(), content.end(), content.begin(), ::tolower);

		for (auto& [actor, item] : m_widgetActorLink)
		{
			if (!p_content.empty())
			{
				auto itemName = item->name;
				std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

				if (itemName.find(content) != std::string::npos)
				{
					founds.push_back(item);
				}

				item->enabled = false;
			}
			else
			{
				item->enabled = true;
			}
		}

		for (auto node : founds)
		{
			node->enabled = true;

			if (node->HasParent())
			{
				ExpandTreeNodeAndEnable(*static_cast<FEditorUI::Widgets::Layout::TreeNode*>(node->GetParent()), m_sceneRoot);
			}
		}

		if (p_content.empty())
		{
			for (auto node : nodesToCollapse)
			{
				node->Close();
			}

			nodesToCollapse.clear();
		}
	};

	m_sceneRoot = &CreateWidget<FEditorUI::Widgets::Layout::TreeNode>("Root", true);
	static_cast<FEditorUI::Widgets::Layout::TreeNode*>(m_sceneRoot)->Open();
	m_sceneRoot->AddPlugin<FEditorUI::Plugins::DDTarget<std::pair<OvCore::ECS::Actor*, FEditorUI::Widgets::Layout::TreeNode*>>>("Actor").DataReceivedEvent += [this](std::pair<OvCore::ECS::Actor*, FEditorUI::Widgets::Layout::TreeNode*> p_element)
	{
		if (p_element.second->HasParent())
			p_element.second->GetParent()->UnconsiderWidget(*p_element.second);

		m_sceneRoot->ConsiderWidget(*p_element.second);

		p_element.first->DetachFromParent();
	};
    m_sceneRoot->AddPlugin<ActorContextualMenu>(nullptr, *m_sceneRoot);

	EDITOR_EVENT(ActorUnselectedEvent) += std::bind(&Hierarchy::UnselectActorsWidgets, this);
	EDITOR_CONTEXT(sceneManager).SceneUnloadEvent += std::bind(&Hierarchy::Clear, this);
	OvCore::ECS::Actor::CreatedEvent += std::bind(&Hierarchy::AddActorByInstance, this, std::placeholders::_1);
	OvCore::ECS::Actor::DestroyedEvent += std::bind(&Hierarchy::DeleteActorByInstance, this, std::placeholders::_1);
	EDITOR_EVENT(ActorSelectedEvent) += std::bind(&Hierarchy::SelectActorByInstance, this, std::placeholders::_1);
	OvCore::ECS::Actor::AttachEvent += std::bind(&Hierarchy::AttachActorToParent, this, std::placeholders::_1);
	OvCore::ECS::Actor::DettachEvent += std::bind(&Hierarchy::DetachFromParent, this, std::placeholders::_1);
}

void FEditor::Panels::Hierarchy::Clear()
{
	EDITOR_EXEC(UnselectActor());

	m_sceneRoot->RemoveAllWidgets();
	m_widgetActorLink.clear();
}

void FEditor::Panels::Hierarchy::UnselectActorsWidgets()
{
	for (auto& widget : m_widgetActorLink)
		widget.second->selected = false;
}

void FEditor::Panels::Hierarchy::SelectActorByInstance(OvCore::ECS::Actor& p_actor)
{
	if (auto result = m_widgetActorLink.find(&p_actor); result != m_widgetActorLink.end())
		if (result->second)
			SelectActorByWidget(*result->second);
}

void FEditor::Panels::Hierarchy::SelectActorByWidget(FEditorUI::Widgets::Layout::TreeNode & p_widget)
{
	UnselectActorsWidgets();

	p_widget.selected = true;

	if (p_widget.HasParent())
	{
		ExpandTreeNode(*static_cast<FEditorUI::Widgets::Layout::TreeNode*>(p_widget.GetParent()), m_sceneRoot);
	}
}

void FEditor::Panels::Hierarchy::AttachActorToParent(OvCore::ECS::Actor & p_actor)
{
	auto actorWidget = m_widgetActorLink.find(&p_actor);

	if (actorWidget != m_widgetActorLink.end())
	{
		auto widget = actorWidget->second;

		if (widget->HasParent())
			widget->GetParent()->UnconsiderWidget(*widget);

		if (p_actor.HasParent())
		{
			auto parentWidget = m_widgetActorLink.at(p_actor.GetParent());
			parentWidget->leaf = false;
			parentWidget->ConsiderWidget(*widget);
		}
	}
}

void FEditor::Panels::Hierarchy::DetachFromParent(OvCore::ECS::Actor & p_actor)
{
	if (auto actorWidget = m_widgetActorLink.find(&p_actor); actorWidget != m_widgetActorLink.end())
	{
		if (p_actor.HasParent() && p_actor.GetParent()->GetChildren().size() == 1)
		{
			if (auto parentWidget = m_widgetActorLink.find(p_actor.GetParent()); parentWidget != m_widgetActorLink.end())
			{
				parentWidget->second->leaf = true;
			}
		}

		auto widget = actorWidget->second;

		if (widget->HasParent())
			widget->GetParent()->UnconsiderWidget(*widget);

		m_sceneRoot->ConsiderWidget(*widget);
	}
}

void FEditor::Panels::Hierarchy::DeleteActorByInstance(OvCore::ECS::Actor& p_actor)
{
	if (auto result = m_widgetActorLink.find(&p_actor); result != m_widgetActorLink.end())
	{
		if (result->second)
		{
			result->second->Destroy();
		}

		if (p_actor.HasParent() && p_actor.GetParent()->GetChildren().size() == 1)
		{
			if (auto parentWidget = m_widgetActorLink.find(p_actor.GetParent()); parentWidget != m_widgetActorLink.end())
			{
				parentWidget->second->leaf = true;
			}
		}

		m_widgetActorLink.erase(result);
	}
}

void FEditor::Panels::Hierarchy::AddActorByInstance(OvCore::ECS::Actor & p_actor)
{
	auto& textSelectable = m_sceneRoot->CreateWidget<FEditorUI::Widgets::Layout::TreeNode>(p_actor.GetName(), true);
	textSelectable.leaf = true;
	textSelectable.AddPlugin<ActorContextualMenu>(&p_actor, textSelectable);
	textSelectable.AddPlugin<FEditorUI::Plugins::DDSource<std::pair<OvCore::ECS::Actor*, FEditorUI::Widgets::Layout::TreeNode*>>>("Actor", "Attach to...", std::make_pair(&p_actor, &textSelectable));
	textSelectable.AddPlugin<FEditorUI::Plugins::DDTarget<std::pair<OvCore::ECS::Actor*, FEditorUI::Widgets::Layout::TreeNode*>>>("Actor").DataReceivedEvent += [&p_actor, &textSelectable](std::pair<OvCore::ECS::Actor*, FEditorUI::Widgets::Layout::TreeNode*> p_element)
	{
		if (p_actor.IsDescendantOf(p_element.first))
		{
			OVLOG_WARNING("Cannot attach \"" + p_element.first->GetName() + "\" to \"" + p_actor.GetName() + "\" because it is a descendant of the latter.");
			return;
		}

		p_element.first->SetParent(p_actor);
	};
	auto& dispatcher = textSelectable.AddPlugin<FEditorUI::Plugins::DataDispatcher<std::string>>();

	OvCore::ECS::Actor* targetPtr = &p_actor;
	dispatcher.RegisterGatherer([targetPtr] { return targetPtr->GetName(); });

	m_widgetActorLink[targetPtr] = &textSelectable;

	textSelectable.ClickedEvent += EDITOR_BIND(SelectActor, std::ref(p_actor));
	textSelectable.DoubleClickedEvent += EDITOR_BIND(MoveToTarget, std::ref(p_actor));
}