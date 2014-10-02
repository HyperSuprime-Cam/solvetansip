#ifndef  gb9b065e3_3938_48ea_a6ff_ddbf238b103d
#define  gb9b065e3_3938_48ea_a6ff_ddbf238b103d

#include <time.h>

// Mac alternative to clock_gettime
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

namespace my {

    struct clock_t: public timespec
    {
        double operator-(clock_t const& other)
        {
            return (double)(this->tv_sec - other.tv_sec)
                + 1e-9*(double)(this->tv_nsec - other.tv_nsec);
        }
    };

    inline clock_t clock()
    {
        clock_t c;
#if defined(__MACH__) // OS X does not have clock_gettime, use clock_get_time
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        c.tv_sec = mts.tv_sec;
        c.tv_nsec = mts.tv_nsec;
#else
        clock_gettime(CLOCK_REALTIME, &c);
#endif
        return c;
    }

}

#endif //gb9b065e3_3938_48ea_a6ff_ddbf238b103d
