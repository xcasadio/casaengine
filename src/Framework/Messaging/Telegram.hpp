#pragma once

#include "CA_Export.hpp"

#include <iostream>
#include <math.h>

namespace CasaEngine
{
	struct CA_EXPORT Telegram
	{
		Telegram();
		Telegram(double time, unsigned int sender, unsigned int receiver, unsigned int msg, void* info = nullptr);

		unsigned int          Sender;
		unsigned int          Receiver;
		unsigned int          Msg;
		//messages can be dispatched immediately or delayed for a specified amount
		//of time. If a delay is necessary this field is stamped with the time 
		//the message should be dispatched.
		double       DispatchTime;
		void* ExtraInfo;
	};

	bool operator==(const Telegram& t1, const Telegram& t2);
	bool operator<(const Telegram& t1, const Telegram& t2);
	std::ostream& operator<<(std::ostream& os, const Telegram& t);
}
