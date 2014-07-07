#ifndef  gb9b065e3_3938_48ea_a6ff_ddbf238b103d
#define  gb9b065e3_3938_48ea_a6ff_ddbf238b103d

#include <time.h>

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
        clock_gettime(CLOCK_REALTIME, &c);
        return c;
    }

}

#endif //gb9b065e3_3938_48ea_a6ff_ddbf238b103d
