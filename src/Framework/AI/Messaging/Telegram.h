#pragma once

#include "CA_Export.h"

#include <iostream>
#include <math.h>

namespace CasaEngine
{
	struct CA_EXPORT Telegram
	{
		unsigned int          Sender;
		unsigned int          Receiver;
		unsigned int          Msg;
		//messages can be dispatched immediately or delayed for a specified amount
		//of time. If a delay is necessary this field is stamped with the time 
		//the message should be dispatched.
		double       DispatchTime;
		const void* ExtraInfo;

		Telegram() :
			Sender(0),
			Receiver(0),
			Msg(0),
			DispatchTime(-1),
			ExtraInfo(nullptr)
		{
		}

		Telegram(double time, unsigned int sender, unsigned int receiver, unsigned int msg, void* info = nullptr) :
			Sender(sender),
			Receiver(receiver),
			Msg(msg),
			DispatchTime(time),
			ExtraInfo(info)
		{}

	};

	//these telegrams will be stored in a priority queue. Therefore the >
	//operator needs to be overloaded so that the PQ can sort the telegrams
	//by time priority. Note how the times must be smaller than
	//SmallestDelay apart before two Telegrams are considered unique.
	constexpr double SmallestDelay = 0.25;


	inline bool operator==(const Telegram& t1, const Telegram& t2)
	{
		return fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay &&
			t1.Sender == t2.Sender &&
			t1.Receiver == t2.Receiver &&
			t1.Msg == t2.Msg;
	}

	inline bool operator<(const Telegram& t1, const Telegram& t2)
	{
		if (t1 == t2)
		{
			return false;
		}

		return  t1.DispatchTime < t2.DispatchTime;
	}

	inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
	{
		os << "time: " << t.DispatchTime << "  Sender: " << t.Sender << "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;
		return os;
	}
}
