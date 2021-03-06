#pragma once

#include "Event.h"

namespace gbc
{
	class JoystickConnectEvent : public Event
	{
	public:
		JoystickConnectEvent(int jid, bool connect);
		EVENT_CLASS_TYPE(EventType::JoystickConnect);
		EVENT_CLASS_CATEGORY(EventCategory_Device | EventCategory_Application);

		inline int GetJID() const noexcept { return jid; }
		inline bool IsConnected() const noexcept { return connect; }

		virtual std::string ToString() const override;
	private:
		int jid;
		bool connect;
	};

	class MonitorConnectEvent : public Event
	{
	public:
		MonitorConnectEvent(bool connect);
		EVENT_CLASS_TYPE(EventType::MonitorConnect);
		EVENT_CLASS_CATEGORY(EventCategory_Device | EventCategory_Application);

		inline bool IsConnected() const noexcept { return connect; }

		virtual std::string ToString() const override;
	private:
		bool connect;
	};
}