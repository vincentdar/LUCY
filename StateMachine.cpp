#include "StateMachine.h"

namespace LUCY
{
	void LUCY::StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		m_isAdding = true;
		m_isReplacing = isReplacing;

		m_newState = std::move(newState);
	}

	void LUCY::StateMachine::RemoveState()
	{
		m_isRemoving = true;
	}

	void LUCY::StateMachine::ProcessStateChanges()
	{
		if (m_isRemoving && !m_states.empty())
		{
			m_states.pop();
			if (!m_states.empty())
			{
				m_states.top()->VResume();
			}
			else
			{
				m_stackEmpty = true;
			}
			m_isRemoving = false;
		}

		if (m_isAdding)
		{
			if (!m_states.empty())
			{
				if (m_isReplacing)
				{
					m_states.pop();
				}
				else
				{
					m_states.top()->VPause();
				}
			}

			m_states.push(std::move(m_newState));
			m_states.top()->VInit();
			m_isAdding = false;
		}
	}

	StateRef& LUCY::StateMachine::GetActiveState()
	{
		return m_states.top();
	}
	bool StateMachine::StackEmpty()
	{
		return m_stackEmpty;
	}
}

