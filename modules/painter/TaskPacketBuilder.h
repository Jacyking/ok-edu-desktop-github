
#ifndef TASK_PACKET_BUILDER_H__
#define TASK_PACKET_BUILDER_H__

#include <string>
#include <memory>

#include <base/logs.h>

#include "SharedPaintTaskFactory.h"
#include "SharedPaintTask.h"

namespace TaskPacketBuilder
{

	using namespace painter;

	class CExecuteTask
	{
	public:
		static std::string make(std::shared_ptr<CSharedPaintTask> task, const std::string *target = nullptr)
		{

			std::string data = task->serialize();
			DEBUG_LOG(("data===%1").arg(qstring(data)));

			return data;
		}

		static std::shared_ptr<CSharedPaintTask> parse(const std::string &body)
		{
			std::shared_ptr<CSharedPaintTask> task;

			//			try
			//			{
			//				int pos = 0;
			//				std::uint16_t temptype;
			//				pos += CPacketBufferUtil::readInt16( body, pos, temptype, true );

			//				TaskType type = (TaskType)temptype;

			//				task = CSharedPaintTaskFactory::createTask( type );

			//				std::string taskData( (const char *)body.c_str() + pos, body.size() - pos );
			//				if( !task->deserialize( taskData ) )
			//				{
			//					return std::shared_ptr<CSharedPaintTask>();
			//				}
			//			}catch(...)
			//			{
			//				return std::shared_ptr<CSharedPaintTask>();
			//			}

			return task;
		}
	};
};

#endif
