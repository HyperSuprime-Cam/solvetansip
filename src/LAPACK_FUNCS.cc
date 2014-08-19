#include "LAPACK_FUNCS.h"

#include <dlfcn.h>
#include <cstddef>

namespace lapack
{

dgesvx_t  dgesvx_ = NULL;

namespace {
    bool init()
    {
        void* h = dlopen("libopenblas.so", RTLD_LAZY | RTLD_LOCAL | RTLD_DEEPBIND);
        if(!h){
            return false;
        }

        reinterpret_cast<void*&>(dgesvx_)
            = dlsym(h, "dgesvx_");

        return !!dgesvx_;
    }

    bool const dummy = init();
}


} // namespace lapack
