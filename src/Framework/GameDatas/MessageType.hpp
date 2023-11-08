#pragma once

namespace CasaEngine
{
	enum struct MessageType : int
	{
		FRAME_CHANGE_EVENT,
		ANIMATION_FINISHED,

		COLLISION,

		CUSTOM // defined your message type after this
	};
}