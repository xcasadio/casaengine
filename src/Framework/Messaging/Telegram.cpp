#include  "Telegram.hpp"

namespace CasaEngine
{
	//these telegrams will be stored in a priority queue. Therefore the >
	//operator needs to be overloaded so that the PQ can sort the telegrams
	//by time priority. Note how the times must be smaller than
	//SmallestDelay apart before two Telegrams are considered unique.
	constexpr double SmallestDelay = 0.25;

	Telegram::Telegram() :
		Sender(0),
		Receiver(0),
		Msg(0),
		DispatchTime(-1),
		ExtraInfo(nullptr)
	{

	}

	Telegram::Telegram(double time, unsigned int sender, unsigned int receiver, unsigned int msg, void* info /*= nullptr*/) :
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		DispatchTime(time),
		ExtraInfo(info)
	{

	}

	bool operator==(const Telegram& t1, const Telegram& t2)
	{
		return fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay &&
			t1.Sender == t2.Sender &&
			t1.Receiver == t2.Receiver &&
			t1.Msg == t2.Msg;
	}

	bool operator<(const Telegram& t1, const Telegram& t2)
	{
		if (t1 == t2)
		{
			return false;
		}

		return  t1.DispatchTime < t2.DispatchTime;
	}

	std::ostream& operator<<(std::ostream& os, const Telegram& t)
	{
		os << "time: " << t.DispatchTime << "  Sender: " << t.Sender << "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;
		return os;
	}
}
