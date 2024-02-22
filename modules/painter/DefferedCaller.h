#pragma once

#include <functional>
#include <mutex>
#include <thread>
#include <memory>

#include <QObject>



#define DefferdCallerPtr()		CSingleton<CDefferedCaller>::Instance()

class CDefferedCaller : public QObject
{
	Q_OBJECT

public:
	typedef std::function< void () > FUNC_TYPE;

	static void singleShot( FUNC_TYPE func ) 
	{
		CDefferedCaller *caller = new CDefferedCaller;
		caller->setAutoDelete();
		caller->performMainThreadAlwaysDeffered( func );
	}

	static void singleShotAfterMiliseconds( FUNC_TYPE func, int msec ) 
	{
		CDefferedCaller *caller = new CDefferedCaller;
		caller->setAutoDelete();
		caller->performMainThreadAfterMilliseconds( func, msec );
	}


	CDefferedCaller(void);
	~CDefferedCaller(void);

	bool isMainThread( void );
	void setAutoDelete( void ) { autoDelete_ = true; }
	void performMainThreadAlwaysDeffered( FUNC_TYPE func );
	void performMainThread( FUNC_TYPE func );	// if on main thread now, just call directly!
	bool performMainThreadAfterMilliseconds( FUNC_TYPE func, int msec );

private slots:
	void timerEvent( void );

private:
	void customEvent( QEvent* e );

private:
	bool autoDelete_;
	typedef std::list<FUNC_TYPE> FUNC_LIST;
	FUNC_LIST deferredMethods_;
	std::recursive_mutex mutex_;
	static std::thread::id mainThreadId_;

	typedef struct 
	{
		bool timer_start;
		int remain_msec;
		FUNC_TYPE func;
		qint64 tick;
	}methodtimer_t;

	typedef std::list< std::shared_ptr<methodtimer_t> > TIMER_LIST;
	TIMER_LIST deferredMethodsForTimer_;
};
