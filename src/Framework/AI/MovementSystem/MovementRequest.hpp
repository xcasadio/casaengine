#pragma once

#ifndef MovementRequest_h
#define MovementRequest_h

#include  "MovementStyle.hpp"
#include  "Maths/Vector3.hpp"
#include  "Entities/BaseEntity.hpp"

namespace CasaEngine
{

	// When you queue a movement request you will get a request id back.
	// This ID is used when you want to cancel a queued request.
	// (Wrapper around 'unsigned int' but provides type safety.)
	// An ID of 0 represents an invalid/uninitialized ID.
	struct MovementRequestID
	{
		unsigned int id;

		MovementRequestID() : id(0) {}
		MovementRequestID(unsigned int _id) : id(_id) {}
		MovementRequestID& operator++() { ++id; return *this; }
		bool operator == (unsigned int otherID) const { return id == otherID; }
		operator unsigned int() const { return id; }

		static MovementRequestID Invalid() { return MovementRequestID(); }
	};

	// Passed along as a parameter to movement request callbacks.
	struct MovementRequestResult
	{
		enum Result
		{
			Success,
			Failure,

			// Alias for 'Success' to increase readability in callback code.
			ReachedDestination = Success,
		};

		enum FailureReason
		{
			NoReason,
			CouldNotFindPathToRequestedDestination,
			CouldNotMoveAlongDesignerDesignedPath,
			FailedToProduceSuccessfulPlanAfterMaximumNumberOfAttempts,
		};

		MovementRequestResult(
			const MovementRequestID& _id,
			const Result _result,
			const FailureReason _failureReason)
			: requestID(_id)
			, result(_result)
			, failureReason(_failureReason)
		{
		}

		MovementRequestResult(
			const MovementRequestID& _id,
			const Result _result)
			: requestID(_id)
			, result(_result)
			, failureReason(NoReason)
		{
		}

		bool operator == (const Result& rhs) const
		{
			return result == rhs;
		}

		operator bool() const
		{
			return result == Success;
		}

		const MovementRequestID requestID;
		const Result result;
		const FailureReason failureReason;
	};

	// Contains everything needed for the movement system to make informed
	// decisions about movement. You specify where you want to move
	// and how you want to do it. You can receive information about
	// your request by setting up a callback function.
	struct MovementRequest
	{
		//typedef Functor1<const MovementRequestResult&> Callback;

		enum Type
		{
			MoveTo,
			Stop,
		};

		MovementRequest()
			: destination(0, 0, 0)
			, type(MoveTo)
			//, callback(0)
			, entityID(0)
			//, dangersFlags(eMNMDangers_None)
			, considerActorsAsPathObstacles(false)
			, lengthToTrimFromThePathEnd(0.0f)
		{
		}

		MovementStyle style;
		Vector3 destination;
		Type type;
		//Callback callback;
		unsigned int entityID;
		//MNMDangersFlags dangersFlags;
		bool considerActorsAsPathObstacles;
		float lengthToTrimFromThePathEnd;
	};

	// Contains information about the status of a request.
	// You'll see if it's in a queue, path finding, or
	// what block of a plan it's currently executing.
	struct MovementRequestStatus
	{
		MovementRequestStatus() : currentBlockIndex(0), id(NotQueued) {}

		struct BlockInfo
		{
			BlockInfo() : name(0) {}
			BlockInfo(const char* _name) : name(_name) {}

			const char* name;
		};

		//typedef StaticDynArray<BlockInfo, 32> BlockInfos;

		enum ID
		{
			NotQueued,
			Queued,
			FindingPath,
			ExecutingPlan
		};

		operator ID () const { return id; }

		//BlockInfos blockInfos;
		unsigned int currentBlockIndex;
		ID id;
	};

#if defined(COMPILE_WITH_MOVEMENT_SYSTEM_DEBUG)
	inline void ConstructHumanReadableText(IN const MovementRequestStatus& status, OUT stack_string& statusText)
	{
		switch (status)
		{
		case MovementRequestStatus::Queued:
		{
			statusText = "Request In Queue";
			break;
		}

		case MovementRequestStatus::FindingPath:
		{
			statusText.Format("Finding Path");
			break;
		}

		case MovementRequestStatus::ExecutingPlan:
		{
			statusText = "Executing Plan: ";

			const size_t totalBlockInfos = status.blockInfos.size();
			for (size_t index = 0; index < totalBlockInfos; ++index)
			{
				if (index != 0)
					statusText += " ";

				const bool active = (index == status.currentBlockIndex);

				if (active)
					statusText += "[";

				statusText += status.blockInfos[index].name;

				if (active)
					statusText += "]";
			}

			break;
		}

		case MovementRequestStatus::NotQueued:
		{
			statusText = "Request Not Queued";
			break;
		}

		default:
		{
			statusText = "Unknown Status";
			break;
		}
		}
	}
#endif // COMPILE_WITH_MOVEMENT_SYSTEM_DEBUG

}

#endif // MovementRequest_h